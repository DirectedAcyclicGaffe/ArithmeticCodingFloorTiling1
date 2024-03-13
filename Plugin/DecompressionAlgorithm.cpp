#include "DecompressionAlgorithm.h"
#include <QtMath>
#include <QDebug>

DecompressionAlgorithmAttributes::DecompressionAlgorithmAttributes()
{
    m_listName = "Decompression 1 to 3";
    m_displayName = "Decompression 1 to 3";
    m_iconPath = "qrc:/Icons/BruteForceWayICon.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/DecompressionAlgorithm.qml";
}

const IdeaAttributes DecompressionAlgorithmTilerIdea::attributes()
{
    return Magic<DecompressionAlgorithmAttributes>::cast();
}

DecompressionAlgorithmTilerIdea::DecompressionAlgorithmTilerIdea() :
    m_nextIsAddTile(false),
    m_nextIsPause(false),
    m_speed(1000.0)
{
    m_bot = 0.0;
    m_top = 1.0;
    m_tileTop = 1.0;
    m_tileMid = 0.75;
    m_tileBot = 0.0;

    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &DecompressionAlgorithmTilerIdea::step);

    restart();
}

std::shared_ptr<DataType> DecompressionAlgorithmTilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void DecompressionAlgorithmTilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &DecompressionAlgorithmTilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &DecompressionAlgorithmTilerIdea::coinsCleared);
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

void DecompressionAlgorithmTilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void DecompressionAlgorithmTilerIdea::coinsCleared()
{
    emit resetAnimation();
    m_coinsUsed = 0;
    m_coinsCounter = 0;
    m_coinsSum = 0;

    m_bot = 0.0;
    m_top = 1.0;
    m_tileTop = 1.0;
    m_tileMid = 0.75;
    m_tileBot = 0.0;
    m_currentTileRow = 0;

    m_tiles->getModel()->clearTiles();
}

void DecompressionAlgorithmTilerIdea::step()
{
    auto n = m_input.lock();

    if(m_nextIsAddTile)
    {
        addTileStep();
        return;
    }
    if(m_nextIsPause)
    {
        pauseStep();
        return;
    }
    if(m_nextIsZoom)
    {
        zoomResetStep();
        return;
    }

    if(m_bot >= m_tileMid)
    {
        emit newGoldTile(m_currentTileRow, m_tileMid + (m_tileTop - m_tileMid) / 2.0);
        m_tileBot = m_tileMid;
        m_tileMid = m_tileBot + 0.75 * (m_tileTop - m_tileBot);
        emit showNextChoiceTile(m_currentTileRow, m_tileTop, m_tileTop - m_tileBot);
        m_currentTileRow++;
        m_tiles->getModel()->addGold(1);
        emit m_tiles->getModel()->tilesAdded();
        return;
    }
    if(m_top <= m_tileMid)
    {
        emit newBlueTile(m_currentTileRow, m_tileBot + (m_tileMid - m_tileBot) / 2.0);
        m_tileTop = m_tileMid;
        m_tileMid = m_tileBot + 0.75 * (m_tileTop - m_tileBot);
        emit showNextChoiceTile(m_currentTileRow, m_tileTop, m_tileTop - m_tileBot);
        m_currentTileRow++;
        m_tiles->getModel()->addBronze(1);
        emit m_tiles->getModel()->tilesAdded();
        return;
    }

    if(n->getModel()->numCoins() > m_coinsUsed)
    {
        bool isHeads = n->getModel()->isHeads(m_coinsUsed);
        double a = -4.375;
        double b = 560 - 140.0 / qPow(2, m_coinsCounter);
        if(isHeads)
        {
            m_coinsSum += qPow(2, (6 - m_coinsCounter));
            emit newHeads(m_coinsCounter, a * m_coinsSum + b - 17.5);
            m_bot = m_bot + (m_top - m_bot) / 2;
        }
        else
        {
            emit newTails(m_coinsCounter, a * m_coinsSum + b - 17.5);
            m_top = m_top - (m_top - m_bot) / 2;
        }
        emit showNextChoice(m_coinsCounter);

        m_coinsUsed++;
        m_coinsCounter++;
    }
    else
    {
        m_timer->stop();
    }
}

void DecompressionAlgorithmTilerIdea::restart()
{
    emit resetAnimation();

    m_bot = 0.0;
    m_top = 1.0;
    m_tileTop = 1.0;
    m_tileMid = 0.75;
    m_tileBot = 0.0;
    m_currentTileRow = 0;
    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void DecompressionAlgorithmTilerIdea::zoomResetStep()
{

}

void DecompressionAlgorithmTilerIdea::pauseStep()
{

}

void DecompressionAlgorithmTilerIdea::addTileStep()
{

}

double DecompressionAlgorithmTilerIdea::speed() const
{
    return m_speed;
}


void DecompressionAlgorithmTilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
