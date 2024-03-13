#ifndef MOSTEFFICIENT1TO3_H
#define MOSTEFFICIENT1TO3_H

#include <QTimer>

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct MostEfficient1to3Attributes : public IdeaAttributes
{
    MostEfficient1to3Attributes();
};

class MostEfficient1to3TilerIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit MostEfficient1to3TilerIdea();

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
    void showNextChoice(double x, double y, double width, double height);
    void newCoin(bool isHeads, double xLoc, double yLoc);
    void leftBotMove(double x, double y);
    void rightBotMove(double x, double y);
    void addShadow(bool isHeads, double x, double y, double height);
    void extendBridge(double x, double y, double height);
    void addTile(bool isBronze, double xLoc, double yLoc);    
    void addTileChoice(double x, double y, double width, double height);
    void zoom(double coinXMove, double tileXMove, double coinHeightFactor,
              double top, double bot, double a, double b);
    void reset();

    void extendLeftSide();
    void extendRightSide();

    void speedChanged();

private:
    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    void restart();
    int m_coinsUsed;

    QTimer* m_timer;

    int m_coinsCounter;
    int m_tileCounter;
    double m_coinsSum;

    void addCoinChoice();
    void addTile();
    void leftBotMove();
    void rightBotMove();
    void zoomStep();
    bool m_addTileChoiceStep = false;
    bool m_leftBotMoveStep = false;
    bool m_rightBotMoveStep = false;
    bool m_addTileStep = false;
    bool m_addBronze = false;
    bool m_zoomStep = false;
    bool m_tileAddedSinceZoom = false;
    int m_zoomPauseStep = 0;
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

#endif // MOSTEFFICIENT1TO3_H
