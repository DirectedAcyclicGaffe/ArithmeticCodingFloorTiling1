#include "IntermediateWayIdea.h"
#include <QtMath>
#include <QDebug>

IntermediateWayAttributes::IntermediateWayAttributes()
{
    m_listName = "Intermediate Way";
    m_displayName = "Coolish Trick";
    m_iconPath = "qrc:/Icons/IntermediateWayIcon.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/IntermediateWay.qml";

    m_externalQMLPaths << ":/QML/IntermediateWayControls.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes IntermediateWayIdea::attributes()
{
    return Magic<IntermediateWayAttributes>::cast();
}

IntermediateWayIdea::IntermediateWayIdea() :
    m_probability(100.0/101.0),
    m_running(true),
    m_speed(0.3),
    m_coinRows(10)
{
    m_nullModel = new CoinArrayModel(this);
    m_outPortLabelColors.append("#a6b0cb");

    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    //Internal variables
    intervalTop = 0;
    intervalHeight = 1;
    m_coinsUsed = 0;
}

QJsonObject IntermediateWayIdea::save() const
{
    QJsonObject saveJson = Idea::save();
    saveJson["p"] = m_probability;
    saveJson["r"] = m_running;
    saveJson["s"] = m_speed;
    saveJson["c"] = m_coinRows;

    return saveJson;
}

void IntermediateWayIdea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["p"];
    if(!v.isUndefined())
    {
        m_probability = v.toDouble();
        emit probabilityChanged(m_probability);
    }

    v = obj["r"];
    if(!v.isUndefined())
    {
        m_running = v.toBool();
        emit runningChanged(m_running);
    }

    v = obj["s"];
    if(!v.isUndefined())
    {
        m_speed = v.toDouble();
        emit speedChanged(m_speed);
    }

    v = obj["c"];
    if(!v.isUndefined())
    {
        m_coinRows = v.toInt();
        emit coinRowsChanged(m_coinRows);
    }
}

double IntermediateWayIdea::probability() const
{
    return m_probability;
}

bool IntermediateWayIdea::running() const
{
    return m_running;
}

double IntermediateWayIdea::speed() const
{
    return m_speed;
}

int IntermediateWayIdea::coinRows() const
{
    return m_coinRows;
}

void IntermediateWayIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        //A valid input.
        setStatus(IdeaStatus::Working);
        m_tiles->getModel()->clearTiles();
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this,&IntermediateWayIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared,this,&IntermediateWayIdea::coinsCleared);
        emit n->getModel()->coinsAdded();
        emit newData(0);
    }
    else
    {
        m_coinsUsed = 0;
        m_tiles->getModel()->clearTiles();
        coinsCleared();
        setContextProperty("CoinModel", m_nullModel);
        setDefaultStatus();
    }
}

std::shared_ptr<DataType> IntermediateWayIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void IntermediateWayIdea::coinsAdded()
{
    auto n = m_input.lock();

    while(n->getModel()->numCoins() > m_coinsUsed)
    {
        if(n->getModel()->isHeads(m_coinsUsed))
        {
            intervalHeight /= 2.0;
        }
        else
        {
            intervalHeight /= 2.0;
            intervalTop += intervalHeight;
        }

        if(intervalTop + intervalHeight <= (1.0 - m_probability))
        {
            intervalTop = 0;
            intervalHeight = 1;
            m_tiles->getModel()->addGold(1);
            emit m_tiles->getModel()->tilesAdded();
        }

        if(intervalTop >= (1.0 - m_probability))
        {
            intervalTop = 0;
            intervalHeight = 1;
            m_tiles->getModel()->addBronze(1);
            emit m_tiles->getModel()->tilesAdded();
        }

        m_coinsUsed++;
    }
}

void IntermediateWayIdea::coinsCleared()
{
    intervalTop = 0;
    intervalHeight = 1;

    m_coinsUsed = 0;
    m_tiles->getModel()->clearTiles();
}

void IntermediateWayIdea::setProbability(double probability)
{
    if (qFuzzyCompare(m_probability, probability))
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["p"] = m_probability;
    m_probability = probability;
    newParamsJson["p"] = m_probability;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit probabilityChanged(m_probability);
}

void IntermediateWayIdea::setRunning(bool running)
{
    if (m_running == running)
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["r"] = m_running;
    m_running = running;
    newParamsJson["r"] = m_running;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit runningChanged(m_running);
    if(m_running == true)
        emit startTimer();
}

void IntermediateWayIdea::setSpeed(double speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["s"] = m_speed;
    m_speed = speed;
    newParamsJson["s"] = m_speed;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit speedChanged(m_speed);
}

void IntermediateWayIdea::setCoinRows(int coinRows)
{
    if (m_coinRows == coinRows)
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["c"] = m_coinRows;
    m_coinRows = coinRows;
    newParamsJson["c"] = m_coinRows;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit coinRowsChanged(m_coinRows);
}

void IntermediateWayIdea::step()
{
    emit startTimer();
}

