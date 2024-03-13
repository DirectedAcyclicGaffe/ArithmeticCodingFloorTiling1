#ifndef WIREBACKEND_H
#define WIREBACKEND_H

#include <memory>

#include <QObject>
#include <QUuid>
#include <QVariant>

#include "Plug.h"
#include "InheritedClasses/DataType.h"
#include "WireState.h"
#include "CasingBackend.h"
#include "InheritedClasses/Idea.h"
#include "Wire.h"

class WireBackend: public QObject
{
    Q_OBJECT

public:
    WireBackend(PlugType plugType, CasingBackend* casingBackend, PlugNumber plugNumber);
    WireBackend(QUuid id, CasingBackend *inCasingBackend, PlugNumber inPlugNumber,
                CasingBackend *outCasingBackend, PlugNumber outPlugNumber);

    ~WireBackend();

public:
    QJsonObject serialize() const;

public:

    QUuid id() const;

    void setRequiredPlugType(PlugType plugType);
    PlugType requiredPlugType() const;

    void setWire(Wire* wire);

    /// Assigns a casing to the required plug.
    /// It is assumed that there is a required plug, no extra checks
    void setCasingToPlug(CasingBackend *casingBackend, PlugType plugType, PlugNumber plugNumber);

    void removeFromCasings() const;

public:
    Wire *getWire() const;

    WireState const & state() const;
    WireState& state();

    CasingBackend* getCasing(PlugType plugType) const;
    CasingBackend*& getCasing(PlugType plugType);

    PlugNumber getPlugIndex(PlugType plugType) const;

    void clearCasingBackend(PlugType plugType);

    int dataType(PlugType plugType) const;

    bool complete() const;

    void sendData(std::shared_ptr<DataType> dataType) const;
    void sendNullData() const;

signals:
    void wireBackendCompleted(WireBackend const&);
    void wireBackendMadeIncomplete(WireBackend const&);
    void updated(WireBackend& conn);

private:
    QUuid m_uid;

    CasingBackend* m_outCasingBackend = nullptr;
    CasingBackend* m_inCasingBackend  = nullptr;

    PlugNumber m_outPlugNumber;
    PlugNumber m_inPlugNumber;

    WireState m_state;
    Wire* m_wire;
};

#endif //WIREBACKEND_H
