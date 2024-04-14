#include "MostEfficient1to100.h"
#include <QtMath>
#include <QDebug>

MostEfficient1to100Attributes::MostEfficient1to100Attributes()
{
    m_listName = "Most Efficient 1 to 100";
    m_displayName = "1 Gold to 100 Bronze\nArithmetic Decoder";
    m_iconPath = "qrc:/Icons/MostEfficient1to100.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/MostEfficient1to100.qml";
}

const IdeaAttributes MostEfficient1to100TilerIdea::attributes()
{
    return Magic<MostEfficient1to100Attributes>::cast();
}

MostEfficient1to100TilerIdea::MostEfficient1to100TilerIdea() :
    m_speed(1000.0)
{
    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &MostEfficient1to100TilerIdea::step);

    restart();
}

std::shared_ptr<DataType> MostEfficient1to100TilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void MostEfficient1to100TilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &MostEfficient1to100TilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &MostEfficient1to100TilerIdea::coinsCleared);
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

void MostEfficient1to100TilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void MostEfficient1to100TilerIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void MostEfficient1to100TilerIdea::step()
{
    auto n = m_input.lock();

    if(m_zoomPauseStep > 0)
    {
        m_zoomPauseStep--;
        return;
    }

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
        emit addTileChoice(m_rightBotXGoal + 2, 560 * (1.0 - m_rightTop),
                           4.0, 560.0*(m_rightTop - m_rightBot));
        addTile();
        return;
    }

    if(m_zoomStep)
    {
        m_zoomStep = false;
        m_tileAddedSinceZoom = false;
        zoomStep();
        return;
    }
    if(m_leftTop <= m_rightMid) // Can we add a bronze tile?
    {
        m_tileAddedSinceZoom = true;
        m_rightBotMoveStep = true;
        m_addTileStep = true;
        m_addBronze = true;

        m_rightBotXGoal = 105.0 + 2.0 + 4.0 * m_tileCounter;
        double top = qMin(m_leftTop, m_rightMid);
        double bot = qMax(m_leftBot, m_rightBot);
        m_rightBotYGoal = 560.0 - 280.0 *(top+bot);

        m_rightTop = m_rightMid;
        m_rightMid = m_rightBot + 100.0/101.0 *(m_rightTop-m_rightBot);
        return;
    }
    if(m_leftBot >= m_rightMid)
    {
        m_tileAddedSinceZoom = true;
        m_rightBotMoveStep = true;
        m_addTileStep = true;
        m_addBronze = false;
        m_rightBotXGoal = 105.0 + 2.0 + 4.0 * m_tileCounter;

        double top = qMin(m_leftTop, m_rightTop);
        double bot = qMax(m_leftBot, m_rightMid);
        m_rightBotYGoal = 560.0 - 280.0 *(top+bot);

        m_rightBot = m_rightMid;
        m_rightMid = m_rightBot + 100.0/101.0 *(m_rightTop-m_rightBot);

        return;
    }
    else if(m_tileAddedSinceZoom) //Is it time to zoom? Must have added tile to prevent infinite loop.
    {
        if(m_leftTop - m_leftBot < 0.05 || m_tileCounter > 60)
        {
            m_zoomStep = true;
            return;
        }
    }

    if(n->getModel()->numCoins() > m_coinsUsed) // Use the next coin.
    {

        bool isHeads = n->getModel()->isHeads(m_coinsUsed);
        m_leftBotXGoal = 106.000 + 10 + 21 * m_coinsCounter;

        double newTop = m_leftTop;
        double newBot = m_leftBot;

        if(isHeads)
        {
            m_coinsSum += qPow(2.0, (3.0 - 1.0*m_coinsCounter));
            newBot = m_leftBot + (m_leftTop - m_leftBot) / 2;
            emit addShadow(true, m_leftBotXGoal - 10.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_leftBot));
        }
        else
        {
            newTop = m_leftTop - (m_leftTop - m_leftBot) / 2;
            emit addShadow(false, m_leftBotXGoal - 10.0, 560.0*(1.0-newTop) - 560.0 *(m_leftTop - newTop) , 560.0 * (m_leftTop - newTop));
        }
        m_leftBot = newBot; m_leftTop = newTop;

        double a = -35;
        double b = 560 - 140.0 / qPow(2.0, 1.0*m_coinsCounter);
        m_leftBotYGoal = a * m_coinsSum + b;
        m_leftBotMoveStep = true;
        emit newCoin(isHeads, m_leftBotXGoal, m_leftBotYGoal);

        m_coinsCounter++;
        m_coinsUsed++;
        addCoinChoice();
    }
    else
    {
        m_timer->stop();
    }

}

void MostEfficient1to100TilerIdea::restart()
{
    emit reset();
    m_leftBotMoveStep = false;
    m_rightBotMoveStep = false;
    m_addTileChoiceStep = false;
    m_addTileStep = false;
    m_resetStep = false;
    m_tileAddedSinceZoom = false;

    m_coinsCounter = 0;
    m_tileCounter = 0;
    m_coinsSum = 0;
    m_leftTop = 1.0;
    m_leftBot = 0.0;
    m_rightTop = 1.0;
    m_rightMid = 100.0/101.0;
    m_rightBot = 0.0;
    m_leftBotYGoal = 280;
    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void MostEfficient1to100TilerIdea::addCoinChoice()
{
    emit showNextChoice(105.000 + 21.0*m_coinsCounter, 560.0 - 560.0 * m_leftTop,
                        21.0, 560.0 * (m_leftTop - m_leftBot));
}

void MostEfficient1to100TilerIdea::addTile()
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

void MostEfficient1to100TilerIdea::leftBotMove()
{
    emit leftBotMove(m_leftBotXGoal, m_leftBotYGoal);
}

void MostEfficient1to100TilerIdea::rightBotMove()
{
    emit rightBotMove(m_rightBotXGoal, m_rightBotYGoal);
}

void MostEfficient1to100TilerIdea::zoomStep()
{
    //Calculate the linear transform;
    double a = 1.0 / (m_leftTop - m_leftBot);
    double b = 1.0 - m_leftTop * a;

    m_leftTop = 1.0;
    m_leftBot = 0.0;
    m_rightTop = a * m_rightTop + b;
    m_rightBot = a * m_rightBot + b;
    m_rightMid = a * m_rightMid + b;

    emit zoom(21.0 * m_coinsCounter, 4.0 * m_tileCounter, qPow(2.0, m_coinsCounter),
              m_rightTop, m_rightBot, a, b);

    m_tileCounter = 0;
    m_coinsSum = 0;
    m_coinsCounter = 0;

    m_zoomPauseStep = 8;
}

double MostEfficient1to100TilerIdea::speed() const
{
    return m_speed;
}

void MostEfficient1to100TilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(m_speed);
    emit speedChanged();
}
