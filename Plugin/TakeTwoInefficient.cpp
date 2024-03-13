#include "TakeTwoInefficient.h"
#include <QtMath>
#include <QDebug>

TakeTwoInefficientAttributes::TakeTwoInefficientAttributes()
{
    m_listName = "Take Two 1 to 3 Inefficient";
    m_displayName = "1 Gold to 3 Bronze Inefficient\nTake Two Tiles";
    m_iconPath = "qrc:/Icons/Take2.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/TakeTwoInefficient.qml";
}

const IdeaAttributes TakeTwoInefficientTilerIdea::attributes()
{
    return Magic<TakeTwoInefficientAttributes>::cast();
}

TakeTwoInefficientTilerIdea::TakeTwoInefficientTilerIdea() :
    m_speed(1000.0)
{
    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &TakeTwoInefficientTilerIdea::step);

    restart();
}

std::shared_ptr<DataType> TakeTwoInefficientTilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void TakeTwoInefficientTilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &TakeTwoInefficientTilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &TakeTwoInefficientTilerIdea::coinsCleared);
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

void TakeTwoInefficientTilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void TakeTwoInefficientTilerIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void TakeTwoInefficientTilerIdea::step()
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
        m_botXGoal = 538.370 + 35;

        double bridgeTop = 525.0 - 35.0 * m_coinsSum;
        emit extendBridge(429.370, bridgeTop, 560 / qPow(2, 4));
        return;
    }
    if(m_addTileStep)
    {
        m_addTileStep = false;
        m_botMoveStep = true;
        m_addSecondTileStep = true;
        addFirstTile();
        return;
    }
    if(m_addSecondTileStep)
    {
        m_addSecondTileStep = false;
        m_resetStep = true;
        addSecondTile();
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
        bool isHeads = n->getModel()->isHeads(m_coinsUsed);
        m_botXGoal = 113.371 + 35 + 79 * m_coinsCounter;

        double newTop = m_top;
        double newBot = m_bot;

        if(isHeads)
        {
            m_coinsSum += qPow(2, (3 - m_coinsCounter));
            newBot = m_bot + (m_top - m_bot) / 2;
            emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_bot));
        }
        else
        {
            newTop = m_top - (m_top - m_bot) / 2;
            emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newTop) - 560.0 *(m_top - newTop) , 560.0 * (m_top - newTop));
        }
        m_bot = newBot; m_top = newTop;

        double a = -35;
        double b = 560 - 140.0 / qPow(2, m_coinsCounter);
        m_botYGoal = a * m_coinsSum + b;
        m_botMoveStep = true;
        emit newCoin(isHeads, m_botXGoal, m_botYGoal);

        m_coinsCounter++;
        m_coinsUsed++;

        // if(m_coinsSum == 0 || (m_coinsSum == 12 && m_coinsCounter == 3)
        //     || (m_coinsSum == 10 && m_coinsCounter == 3))
        // {
        //     m_bridgeExtendStep = true;
        // }
        if(m_coinsCounter == 4)
        {
            m_bridgeExtendStep = true;
        }
    }
    else
    {
        if(m_bridgeExtendStep)
            return;

        m_timer->stop();
    }

}

void TakeTwoInefficientTilerIdea::restart()
{
    emit reset();
    m_botMoveStep = false;
    m_bridgeExtendStep = false;
    m_addTileStep = false;
    m_resetStep = false;

    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_top = 1.0;
    m_bot = 0.0;
    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void TakeTwoInefficientTilerIdea::addFirstTile()
{
    if (m_coinsSum > 10)
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
    m_botXGoal += 79;
}
void TakeTwoInefficientTilerIdea::addSecondTile()
{
    if (m_coinsSum == 15 || m_coinsSum == 10 || m_coinsSum == 9)
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
    m_top = 1.0;
    m_bot = 0.0;
}

void TakeTwoInefficientTilerIdea::botMove()
{
    emit forwardMoveBot(m_botXGoal, m_botYGoal);
}

double TakeTwoInefficientTilerIdea::speed() const
{
    return m_speed;
}

void TakeTwoInefficientTilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
