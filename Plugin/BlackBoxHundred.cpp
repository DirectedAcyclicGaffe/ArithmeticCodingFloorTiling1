#include "BlackBoxHundred.h"
#include <QtMath>
#include <QDebug>

BlackBoxAttributes::BlackBoxAttributes()
{
    m_listName = "Black Box Hundred";
    m_displayName = "1 Gold to 100 Bronze\nBlack Box";
    m_iconPath = "qrc:/Icons/BlackBox.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/BlackBox.qml";
}

const IdeaAttributes BlackBoxHundredIdea::attributes()
{
    return Magic<BlackBoxAttributes>::cast();
}

BlackBoxHundredIdea::BlackBoxHundredIdea() :
    m_speed(10.0)
{
    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &BlackBoxHundredIdea::step);

    restart();
}

std::shared_ptr<DataType> BlackBoxHundredIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void BlackBoxHundredIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &BlackBoxHundredIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &BlackBoxHundredIdea::coinsCleared);
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

void BlackBoxHundredIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void BlackBoxHundredIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void BlackBoxHundredIdea::step()
{
    auto n = m_input.lock();

    if(m_botMoveStep)
    {
        m_botMoveStep = false;
        botMove();
        return;
    }
    if(m_bridgeExtendStep)
    {
        m_bridgeExtendStep = false;
        m_botMoveStep = true;
        m_addTileStep = true;
        m_botXGoal = 789.498 + 70;
        emit extendBridge(555.625 - 4.375 * m_coinsSum);
        return;
    }
    if(m_addTileStep)
    {
        m_resetStep = true;
        m_addTileStep = false;
        addTile();
        return;
    }
    if(m_resetStep)
    {
        m_resetStep = false;
        emit reset();
        return;
    }

    if(n->getModel()->numCoins() > m_coinsUsed)
    {
        if(m_coinsCounter == 7)
        {
            m_bridgeExtendStep = true;
            return;
        }
        else
        {
            bool isHeads = n->getModel()->isHeads(m_coinsUsed);
            m_botXGoal = 113.371 + 35 + 79 * m_coinsCounter;

            double newTop = m_top;
            double newBot = m_bot;

            if(isHeads)
            {
                m_coinsSum += qPow(2, (6 - m_coinsCounter));
                newBot = m_bot + (m_top - m_bot) / 2;
                emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_bot));
            }
            else
            {
                newTop = m_top - (m_top - m_bot) / 2;
                emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newTop) - 560.0 *(m_top - newTop) , 560.0 * (m_top - newTop));
            }
            m_bot = newBot; m_top = newTop;

            double a = -4.375;
            double b = 560 - 140.0 / qPow(2, m_coinsCounter);
            m_botYGoal = a * m_coinsSum + b;

            m_botMoveStep = true;
            emit newCoin(isHeads, m_botXGoal, m_botYGoal);

            m_coinsCounter++;
            m_coinsUsed++;
        }
    }
    else
    {
        if(m_coinsCounter == 7)
            m_bridgeExtendStep = true;
        else
            m_timer->stop();
    }
}

void BlackBoxHundredIdea::restart()
{
    emit reset();
    m_botMoveStep = false;
    m_bridgeExtendStep = false;
    m_addTileStep = false;
    m_resetStep = false;

    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_bot = 0.0;
    m_top = 1.0;
    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void BlackBoxHundredIdea::addTile()
{
    if(m_coinsSum > 100)
    {
        //REJECTION!
    }
    else if (m_coinsSum == 100)
    {
        emit addTile(false, m_botXGoal, m_botYGoal);
        m_tiles->getModel()->addGold(1);
        emit m_tiles->getModel()->tilesAdded();
    }
    else
    {
        emit addTile(true, m_botXGoal, m_botYGoal);
        m_tiles->getModel()->addBronze(1);
        emit m_tiles->getModel()->tilesAdded();
    }

    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_bot = 0.0;
    m_top = 1.0;
}

void BlackBoxHundredIdea::botMove()
{
    emit forwardMoveBot(m_botXGoal, m_botYGoal);
}

double BlackBoxHundredIdea::speed() const
{
    return m_speed;
}

void BlackBoxHundredIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
