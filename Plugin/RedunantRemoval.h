#ifndef REDUNANTREMOVAL_H
#define REDUNANTREMOVAL_H

#include <QTimer>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct RedundantRemovalAttributes : public IdeaAttributes
{
    RedundantRemovalAttributes();
};

class RedunantRemovalTilerIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit RedunantRemovalTilerIdea();

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
    void newCoin(bool isHeads, double xLoc, double yLoc);
    void forwardMoveBot(double x, double y);
    void addShadow(double x, double y, double height);
    void extendBridge(double y);
    void addTile(bool isBronze, double xLoc, double yLoc);
    void reset();

    void speedChanged();

private:
    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    void restart();

    int m_coinsUsed;

    QTimer* m_timer;

    int m_coinsCounter;
    int m_coinsSum;

    void addTile();
    void botMove();
    bool m_botMoveStep = false;
    bool m_bridgeExtendStep = false;
    bool m_addTileStep = false;
    bool m_resetStep = false;
    double m_botXGoal;
    double m_botYGoal;
    double m_top;
    double m_bot;

    double m_speed;
};

#endif // REDUNANTREMOVAL_H
