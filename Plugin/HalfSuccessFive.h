#ifndef HALFSUCCESSFIVE_H
#define HALFSUCCESSFIVE_H

#include <QTimer>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct HalfSuccessFiveAttributes : public IdeaAttributes
{
    HalfSuccessFiveAttributes();
};

class HalfSuccessFiveTilerIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit HalfSuccessFiveTilerIdea();

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
    void setBackgroundWidth(double width);
    void showNextChoice(double x, double y, double width, double height);
    void newCoin(bool isHeads, double xLoc, double yLoc);
    void forwardMoveBot(double x, double y);
    void addShadow(double x, double y, double height);
    void extendBridge(double x, double y, double height);
    void addTile(bool isBronze, double xLoc, double yLoc);
    void addTileStep(bool isBlue);
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
    double m_top;
    double m_bot;
    bool m_addGold;

    void addCoinChoice();
    void addTile();
    void botMove();
    bool m_addCoinChoiceStep = false;
    bool m_botMoveStep = false;
    bool m_bridgeExtendStep = false;
    bool m_backgroundResizeStep = false;
    bool m_addTileStep = false;
    bool m_resetStep = false;
    double m_botXGoal;
    double m_botYGoal;

    double m_speed;
};

#endif // HALFSUCCESSFIVE_H
