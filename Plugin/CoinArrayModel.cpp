#include "CoinArrayModel.h"

CoinArrayModel::CoinArrayModel(QObject *parent) : QAbstractListModel(parent)
{

}


int CoinArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_coins.size();
}

QVariant CoinArrayModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_coins.count())
        return QVariant();

    //Valid index.
    switch (role)
    {
    case SideRole:
        return m_coins[index.row()];
    default:
        return QVariant();
    }
}

bool CoinArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == SideRole)
    {
        m_coins[index.row()] = value.toBool();
        emit dataChanged(index,index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CoinArrayModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> CoinArrayModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SideRole] = "Side";
    return roles;
}

void CoinArrayModel::addHeads(int count)
{
    const int index = m_coins.size();

    beginInsertRows(QModelIndex(), index, index+count-1);
    for(int i = 0; i < count; i++)
        m_coins.append(true);
    endInsertRows();

    emit coinsAdded();
}

void CoinArrayModel::addTails(int count)
{
    const int index = m_coins.size();

    beginInsertRows(QModelIndex(), index, index+count-1);
    for(int i = 0; i < count; i++)
        m_coins.append(false);
    endInsertRows();

    emit coinsAdded();
}

void CoinArrayModel::addRandom(int count)
{
    const int index = m_coins.size();

    beginInsertRows(QModelIndex(), index, index+count-1);
    for(int i = 0; i < count; i++)
    {
        int randInt = QRandomGenerator::global()->bounded(2);
        if(randInt == 1)
            m_coins.append(false);
        else
            m_coins.append(true);
    }
    endInsertRows();

    emit coinsAdded();
}

void CoinArrayModel::clearCoins()
{
    beginRemoveRows(QModelIndex(), 0, m_coins.size());
    m_coins.clear();
    endRemoveRows();

    emit coinsCleared();
    emit coinsAdded();
}

QString CoinArrayModel::lastNCoins(int modulus)
{
    int size = m_coins.size();
    int numCoins = size % modulus;
    if(numCoins == 0)
        numCoins = modulus;
    int startIndex = size - numCoins;

    QString returnValue;
    if(startIndex < 0)
    {
        for(int i = 0; i < modulus; i++)
            returnValue.append("n");
        return returnValue;
    }

    for(int i = startIndex; i < startIndex+ numCoins; i++)
    {
        if(m_coins[i] == true)
            returnValue.append("h");
        else
            returnValue.append("t");
    }
    for(int i = 0; i < modulus - numCoins; i++)
        returnValue.append("n");
    return returnValue;
}

int CoinArrayModel::numCoins()
{
    return m_coins.count();
}

bool CoinArrayModel::isHeads(int index)
{
    return m_coins[index];
}
