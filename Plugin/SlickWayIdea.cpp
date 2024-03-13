#include "SlickWayIdea.h"
#include <QtMath>
#include <QDebug>

SlickWayAttributes::SlickWayAttributes()
{
    m_listName = "Arithmetic Decompression";
    m_displayName = "Decompression Algorithm";
    m_iconPath = "qrc:/Icons/SlickWayIcon.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/SlickWay.qml";

    m_externalQMLPaths << ":/QML/SlickWayControls.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
    m_minimizedName = "Decompression\nAlgorithm";

}

const IdeaAttributes SlickWayIdea::attributes()
{
    return Magic<SlickWayAttributes>::cast();
}

SlickWayIdea::SlickWayIdea():
    m_probability(100.0/101.0),
    m_zoom(true),
    m_running(true),
    m_speed(0.3),
    m_coinRows(2),
    m_tileRows(4)
{
    m_outPortLabelColors.append("#a6b0cb");
    m_nullModel = new CoinArrayModel(this);

    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    top = 1.0;
    mid = m_probability;
    bot = 0.0;
    m_coinsUsed = 0;
}

QJsonObject SlickWayIdea::save() const
{
    QJsonObject saveJson = Idea::save();
    saveJson["p"] = m_probability;
    saveJson["s"] = m_speed;
    saveJson["ru"] = m_running;
    saveJson["z"] = m_zoom;
    saveJson["cr"] = m_coinRows;
    saveJson["tr"] = m_tileRows;

    return saveJson;
}

void SlickWayIdea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["p"];
    if(!v.isUndefined())
    {
        m_probability = v.toDouble();
        emit probabilityChanged(m_probability);
    }

    v = obj["s"];
    if(!v.isUndefined())
    {
        m_speed = v.toDouble();
        emit speedChanged(m_speed);
    }

    v = obj["ru"];
    if(!v.isUndefined())
    {
        m_running = v.toBool();
        emit runningChanged(m_running);
    }

    v = obj["z"];
    if(!v.isUndefined())
    {
        m_zoom = v.toBool();
        emit zoomChanged(m_zoom);
    }

    v = obj["cr"];
    if(!v.isUndefined())
    {
        m_coinRows = v.toInt();
        emit coinRowsChanged(m_coinRows);
    }

    v = obj["tr"];
    if(!v.isUndefined())
    {
        m_tileRows = v.toInt();
        emit tileRowsChanged(m_tileRows);
    }
}

double SlickWayIdea::probability() const
{
    return m_probability;
}

bool SlickWayIdea::zoom() const
{
    return m_zoom;
}

bool SlickWayIdea::running() const
{
    return m_running;
}

double SlickWayIdea::speed() const
{
    return m_speed;
}

int SlickWayIdea::coinRows() const
{
    return m_coinRows;
}

int SlickWayIdea::tileRows() const
{
    return m_tileRows;
}

void SlickWayIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        //A valid input array.
        setStatus(IdeaStatus::Working);
        m_tiles->getModel()->clearTiles();
        coinsCleared();
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this,&SlickWayIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared,this,&SlickWayIdea::coinsCleared);
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

std::shared_ptr<DataType> SlickWayIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void SlickWayIdea::coinsAdded()
{
    auto n = m_input.lock();

    while(n->getModel()->numCoins() > m_coinsUsed)
    {
        if(n->getModel()->isHeads(m_coinsUsed))
        {
            //Zoom in on top section.
            top = 2.0*top - 1.0;
            mid = 2.0*mid - 1.0;
            bot = 2.0*bot - 1.0;
        }
        else
        {
            //Zoom in on bottom section.
            top *= 2.0;
            bot *= 2.0;
            mid *= 2.0;

        }
        bool addGold = top >= 1.0 && mid <= 0.0;
        bool addBlue = mid >= 1.0 && bot <= 0.0;
        while(addGold || addBlue)
        {
            if(addGold)
            {
                m_tiles->getModel()->addGold(1);
                emit m_tiles->getModel()->tilesAdded();
                bot = mid;
                mid = bot + (top-bot) * probability();
                addGold = top >= 1.0 && mid <= 0.0;
                addBlue = mid >= 1.0 && bot <= 0.0;
            }
            if(addBlue)
            {
                m_tiles->getModel()->addBronze(1);
                emit m_tiles->getModel()->tilesAdded();
                top = mid;
                mid = bot + (top-bot) * probability();
                addGold = top >= 1.0 && mid <= 0.0;
                addBlue = mid >= 1.0 && bot <= 0.0;
            }
        }
        m_coinsUsed++;
    }
}

void SlickWayIdea::coinsCleared()
{
    top = 1.0;
    mid = m_probability;
    bot = 0.0;

    m_coinsUsed = 0;
    m_tiles->getModel()->clearTiles();
}

void SlickWayIdea::setProbability(double probability)
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

void SlickWayIdea::setZoom(bool zoom)
{
    if (m_zoom == zoom)
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["z"] = m_zoom;
    m_zoom = zoom;
    newParamsJson["z"] = m_zoom;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit zoomChanged(m_zoom);
}

void SlickWayIdea::setRunning(bool running)
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

void SlickWayIdea::setSpeed(double speed)
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

void SlickWayIdea::setCoinRows(int coinRows)
{
    if (m_coinRows == coinRows)
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["cr"] = m_coinRows;
    m_coinRows = coinRows;
    newParamsJson["cr"] = m_coinRows;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit coinRowsChanged(m_coinRows);
}

void SlickWayIdea::setTileRows(int tileRows)
{
    if (m_tileRows == tileRows)
        return;

    QJsonObject oldParamsJson = Idea::save();
    QJsonObject newParamsJson = Idea::save();
    oldParamsJson["tr"] = m_tileRows;
    m_tileRows = tileRows;
    newParamsJson["tr"] = m_tileRows;
    emit reportParamsChanged(oldParamsJson,newParamsJson);
    emit tileRowsChanged(m_tileRows);
}

void SlickWayIdea::step()
{
    emit startTimer();
}
