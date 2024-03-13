#ifndef TAKEALLOT1TO3_H
#define TAKEALLOT1TO3_H

#include <QTimer>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct TakeAllot1to3Attributes : public IdeaAttributes
{
    TakeAllot1to3Attributes();
};

class TakeAllot1to3TilerIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit TakeAllot1to3TilerIdea();

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
    void leftBotMove(double x, double y);
    void rightBotMove(double x, double y);
    void addShadow(double x, double y, double height);
    void extendBridge(double x, double y, double height);
    void addTile(bool isBronze, double xLoc, double yLoc);    
    void addTileChoice(double x, double y, double width, double height);
    void reset();

    void speedChanged();

private:
    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    void restart();
    int m_coinsUsed;

    QTimer* m_timer;

    int m_coinsCounter;
    int m_tileCounter;
    int m_coinsSum;

    void addTile();
    void leftBotMove();
    void rightBotMove();
    bool m_addTileChoiceStep = false;
    bool m_leftBotMoveStep = false;
    bool m_rightBotMoveStep = false;
    bool m_addTileStep = false;
    bool m_addBronze = false;
    bool m_zoomStep = false;
    bool m_resetStep = false;

    double m_leftBotXGoal;
    double m_leftBotYGoal;
    double m_rightBotXGoal;
    double m_rightBotYGoal;

    double m_leftTop;
    double m_leftBot;
    double m_rightTop;
    double m_rightMid;
    double m_rightBot;

    double m_speed;
};

#endif // TAKEALLOT1TO3_H
