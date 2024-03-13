#ifndef TILEFLOORIDEA_H
#define TILEFLOORIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "TileArrayDataType.h"

struct TileFloorAttributes : public IdeaAttributes
{
    TileFloorAttributes();
};

class TileFloorIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(bool tilesVisible READ tilesVisible WRITE setTilesVisible NOTIFY tilesVisibleChanged)

public:
    explicit TileFloorIdea();
    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

    bool tilesVisible() const;

public slots:
    void setTilesVisible(bool tilesVisible);
    void tilesAddedHandler();

signals:
    void tilesVisibleChanged(bool tilesVisible);
    void tilesAdded(int tiles);

private:
    std::weak_ptr<TileArrayDataType> m_input;
    bool m_tilesVisible;
};

#endif // TILEFLOORIDEA_H
