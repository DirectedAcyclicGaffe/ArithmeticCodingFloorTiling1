#ifndef COINARRAYPROPERTY_H
#define COINARRAYPROPERTY_H

#include <QObject>
#include <QAbstractListModel>
#include <QDebug>
#include <QRandomGenerator>

class CoinArrayModel : public QAbstractListModel
{
    Q_OBJECT
    enum CoinRoles
    {
        SideRole = Qt::UserRole + 1
    };

public:
    explicit CoinArrayModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addHeads(int count);
    Q_INVOKABLE void addTails(int count);
    Q_INVOKABLE void addRandom(int count);
    Q_INVOKABLE void clearCoins();
    Q_INVOKABLE QString lastNCoins(int modulus);
    Q_INVOKABLE int numCoins();
    Q_INVOKABLE bool isHeads(int index);

signals:
    void coinsAdded();
    void coinsCleared();

private:
    QList<bool> m_coins; //Head=true, Tails=false
};

#endif // COINARRAYPROPERTY_H
