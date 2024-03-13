#include "TakeAllot1to3.h"
#include <QtMath>
#include <QDebug>

TakeAllot1to3Attributes::TakeAllot1to3Attributes()
{
    m_listName = "Take a lot 1 to 3";
    m_displayName = "1 Gold to 3 Bronze\nTake a lot of Tiles";
    m_iconPath = "qrc:/Icons/TakeALot.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/TakeAllot1to3.qml";
}

const IdeaAttributes TakeAllot1to3TilerIdea::attributes()
{
    return Magic<TakeAllot1to3Attributes>::cast();
}

TakeAllot1to3TilerIdea::TakeAllot1to3TilerIdea() :
    m_speed(1000.0)
{
    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &TakeAllot1to3TilerIdea::step);

    restart();
}

std::shared_ptr<DataType> TakeAllot1to3TilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void TakeAllot1to3TilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &TakeAllot1to3TilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &TakeAllot1to3TilerIdea::coinsCleared);
        emit n->getModel()->coinsAdded();
        emit newData(0);
    }
    else
    {
        setContextProperty("CoinModel", nullptr);
        restart();
        emit modelCleared();
        setDefaultStatus();
    }
}

void TakeAllot1to3TilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void TakeAllot1to3TilerIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void TakeAllot1to3TilerIdea::step()
{
    auto n = m_input.lock();

    if(m_leftBotMoveStep)
    {
        m_leftBotMoveStep = false;
        leftBotMove();
        return;
    }
    if(m_rightBotMoveStep)
    {
        m_rightBotMoveStep = false;
        rightBotMove();
        return;
    }
    if(m_addTileStep)
    {
        m_addTileStep = false;
        //m_addTileChoiceStep = true;
        addTile();
        return;
    }
//    if(m_addTileChoiceStep)
//    {
//        m_addTileChoiceStep = false;
//        emit addTileChoice(113.371 - 9.0 + 49.0 * m_tileCounter,
//                           560 - 560*m_rightTop,
//                           49.0, 560.0 * (m_rightTop - m_rightBot));
//        return;
//    }

    if(m_resetStep)
    {
        m_resetStep = false;
        emit reset();
        return;
    }
    if(m_leftTop <= m_rightMid) // Can we add a bronze tile?
    {
        m_rightBotMoveStep = true;
        m_addTileStep = true;
        m_addBronze = true;

        m_rightBotXGoal = 113.371 + 20 + 49.0 * m_tileCounter;
        double top = qMin(m_leftTop, m_rightMid);
        double bot = qMax(m_leftBot, m_rightBot);
        m_rightBotYGoal = 560.0 - 280.0 *(top+bot);

        m_rightTop = m_rightMid;
        m_rightMid = m_rightBot + 0.75 *(m_rightTop-m_rightBot);
        return;
    }
    if(m_leftBot >= m_rightMid)
    {
        m_rightBotMoveStep = true;
        m_addTileStep = true;
        m_addBronze = false;
        m_rightBotXGoal = 113.371 + 20 + 49.0 * m_tileCounter;

        double top = qMin(m_leftTop, m_rightTop);
        double bot = qMax(m_leftBot, m_rightMid);
        m_rightBotYGoal = 560.0 - 280.0 *(top+bot);

        m_rightBot = m_rightMid;
        m_rightMid = m_rightBot + 0.75 *(m_rightTop-m_rightBot);

        return;
    }


    if(n->getModel()->numCoins() > m_coinsUsed) // Use the next coin.
    {

        bool isHeads = n->getModel()->isHeads(m_coinsUsed);
        m_leftBotXGoal = 113.371 + 20 + 49 * m_coinsCounter;

        double newTop = m_leftTop;
        double newBot = m_leftBot;

        if(isHeads)
        {
            m_coinsSum += qPow(2, (3 - m_coinsCounter));
            newBot = m_leftBot + (m_leftTop - m_leftBot) / 2;
            emit addShadow(m_leftBotXGoal - 20.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_leftBot));
        }
        else
        {
            newTop = m_leftTop - (m_leftTop - m_leftBot) / 2;
            emit addShadow(m_leftBotXGoal - 20.0, 560.0*(1.0-newTop) - 560.0 *(m_leftTop - newTop) , 560.0 * (m_leftTop - newTop));
        }
        m_leftBot = newBot; m_leftTop = newTop;

        double a = -35;
        double b = 560 - 140.0 / qPow(2, m_coinsCounter);
        m_leftBotYGoal = a * m_coinsSum + b;
        m_leftBotMoveStep = true;
        emit newCoin(isHeads, m_leftBotXGoal, m_leftBotYGoal);

        m_coinsCounter++;
        m_coinsUsed++;

        if(m_coinsCounter == 4)
        {
            m_zoomStep = true;
        }
    }
    else
    {
        m_timer->stop();
    }

}

void TakeAllot1to3TilerIdea::restart()
{
    emit reset();
    m_leftBotMoveStep = false;
    m_rightBotMoveStep = false;
    m_addTileChoiceStep = false;
    m_addTileStep = false;
    m_resetStep = false;

    m_coinsCounter = 0;
    m_tileCounter = 0;
    m_coinsSum = 0;
    m_leftTop = 1.0;
    m_leftBot = 0.0;
    m_rightTop = 1.0;
    m_rightMid = 0.75;
    m_rightBot = 0.0;
    m_leftBotYGoal = 280;
    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void TakeAllot1to3TilerIdea::addTile()
{
    m_tileCounter++;
    if (!m_addBronze)
    {
        emit addTile(false, m_rightBotXGoal, m_rightBotYGoal);
        m_tiles->getModel()->addGold(1);
        emit m_tiles->getModel()->tilesAdded();
    }
    else
    {
        emit addTile(true, m_rightBotXGoal, m_rightBotYGoal);
        m_tiles->getModel()->addBronze(1);
        emit m_tiles->getModel()->tilesAdded();
    }
}

void TakeAllot1to3TilerIdea::leftBotMove()
{
    emit leftBotMove(m_leftBotXGoal, m_leftBotYGoal);
}

void TakeAllot1to3TilerIdea::rightBotMove()
{
    emit rightBotMove(m_rightBotXGoal, m_rightBotYGoal);
}

double TakeAllot1to3TilerIdea::speed() const
{
    return m_speed;
}

void TakeAllot1to3TilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
