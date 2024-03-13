#include "RejectionSamplingFive.h"
#include <QtMath>
#include <QDebug>

RejectionSampingFiveTilerAttributes::RejectionSampingFiveTilerAttributes()
{
    m_listName = "Rejection Sampling Five";
    m_displayName = "1 Gold to 5 Bronze\n Rejection Sampling";
    m_iconPath = "qrc:/Icons/Rejection1to5.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/RejectionSamplingFive.qml";
}

const IdeaAttributes RejectionSampingFiveTilerIdea::attributes()
{
    return Magic<RejectionSampingFiveTilerAttributes>::cast();
}

RejectionSampingFiveTilerIdea::RejectionSampingFiveTilerIdea() :
    m_speed(1000.0)
{
    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &RejectionSampingFiveTilerIdea::step);

    restart();
}

std::shared_ptr<DataType> RejectionSampingFiveTilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void RejectionSampingFiveTilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &RejectionSampingFiveTilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &RejectionSampingFiveTilerIdea::coinsCleared);
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

void RejectionSampingFiveTilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void RejectionSampingFiveTilerIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void RejectionSampingFiveTilerIdea::step()
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
        m_botXGoal = 669.390 + 70;
        emit extendBridge(490 - 70 * m_coinsSum);
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
        if(m_coinsCounter == 3)
        {
            m_bridgeExtendStep = true;
            return;
        }
        else
        {
            bool isHeads = n->getModel()->isHeads(m_coinsUsed);
            m_botXGoal = 113.371 + 70 + 149 * m_coinsCounter;

            double newTop = m_top;
            double newBot = m_bot;

            if(isHeads)
            {
                m_coinsSum += qPow(2, (2 - m_coinsCounter));
                newBot = m_bot + (m_top - m_bot) / 2;
                emit addShadow(m_botXGoal - 70.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_bot));
            }
            else
            {
                newTop = m_top - (m_top - m_bot) / 2;
                emit addShadow(m_botXGoal - 70.0, 560.0*(1.0-newTop) - 560.0 *(m_top - newTop) , 560.0 * (m_top - newTop));
            }
            m_bot = newBot; m_top = newTop;

            double a = -70;
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
        if(m_coinsCounter == 3)
            m_bridgeExtendStep = true;
        else
            m_timer->stop();
    }
}

void RejectionSampingFiveTilerIdea::restart()
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

void RejectionSampingFiveTilerIdea::addTile()
{
    if(m_coinsSum > 5)
    {
        //REJECTION!
    }
    else if (m_coinsSum == 5)
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

void RejectionSampingFiveTilerIdea::botMove()
{
    emit forwardMoveBot(m_botXGoal, m_botYGoal);
}

double RejectionSampingFiveTilerIdea::speed() const
{
    return m_speed;
}

void RejectionSampingFiveTilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
