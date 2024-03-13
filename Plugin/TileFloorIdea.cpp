#include "TileFloorIdea.h"
#include <QtMath>
#include <QDebug>

TileFloorAttributes::TileFloorAttributes()
{
    m_listName = "Tile Floor";
    m_displayName = "Tile Floor";
    m_iconPath = "qrc:/Icons/TileFloor.png";

    m_dataTypesIn.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());
    m_customLabels = true;
    m_labelsIn.push_back("");

    m_embeddedQMLPath = ":/QML/TileFloor.qml";
}

const IdeaAttributes TileFloorIdea::attributes()
{
    return Magic<TileFloorAttributes>::cast();
}

TileFloorIdea::TileFloorIdea()
{
    m_tilesVisible = false;
}


void TileFloorIdea::onNewDataIn(std::shared_ptr<DataType> data, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<TileArrayDataType>(data);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("TileModel", n->getModel());
        QObject::connect(n->getModel(), &TileArrayModel::tilesAdded, this, &TileFloorIdea::tilesAddedHandler);
        setTilesVisible(true);
        emit n->getModel()->tilesAdded();
    }
    else
    {
        setTilesVisible(false);
        setContextProperty("TileModel", nullptr);
        setDefaultStatus();
    }
}

bool TileFloorIdea::tilesVisible() const
{
    return m_tilesVisible;
}

void TileFloorIdea::setTilesVisible(bool tilesVisible)
{
    if (m_tilesVisible == tilesVisible)
        return;

    m_tilesVisible = tilesVisible;
    emit tilesVisibleChanged(m_tilesVisible);
}

void TileFloorIdea::tilesAddedHandler()
{
    emit tilesAdded(m_input.lock()->getModel()->tileCount());
}



