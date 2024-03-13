#ifndef DECOMPRESSIONALGORITHM_H
#define DECOMPRESSIONALGORITHM_H

#include <QTimer>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct DecompressionAlgorithmAttributes : public IdeaAttributes
{
    DecompressionAlgorithmAttributes();
};

class DecompressionAlgorithmTilerIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit DecompressionAlgorithmTilerIdea();

    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    double speed() const;

public slots:
    void coinsAdded();
    void coinsCleared();

    void step();

    void setSpeed(double newSpeed);


signals:
    void modelCleared();
    void newHeads(int row, double col);
    void newTails(int row, double col);

    void newBlueTile(int row, double col);
    void newGoldTile(int row, double col);

    void resetAnimation();

    void showNextChoice(int row);
    void showNextChoiceTile(int row, double top, double height);

    void showArrow(int col);

    void speedChanged();

private:
    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    void restart();

    int m_coinsUsed;

    bool m_nextIsAddTile;
    bool m_nextIsPause;
    bool m_nextIsZoom;

    int m_coinRows = 4;
    int m_currentTileRow = 0;

    double m_top;
    double m_bot;

    double m_tileTop;
    double m_tileMid;
    double m_tileBot;

    void zoomResetStep();
    void pauseStep();
    void addTileStep();

    QTimer* m_timer;

    int m_coinsCounter;
    int m_coinsSum;

    double m_speed;
};

#endif // DECOMPRESSIONALGORITHM_H
