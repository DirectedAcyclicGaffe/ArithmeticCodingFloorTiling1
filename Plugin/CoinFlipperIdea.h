#ifndef COINFLIPPERIDEA_H
#define COINFLIPPERIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"

struct CoinFlipperAttributes : public IdeaAttributes
{
    CoinFlipperAttributes();
};

class CoinFlipperIdea : public Idea
{
    Q_OBJECT

public:
    explicit CoinFlipperIdea();

    const IdeaAttributes attributes() override;

    void finishSetupQmlContext() override;

    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

public slots:

signals:

private:
    std::shared_ptr<CoinArrayDataType> m_coins;
};

#endif // COINFLIPPERIDEA_H
