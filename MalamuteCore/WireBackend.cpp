#include "WireBackend.h"

WireBackend::WireBackend(PlugType plugType, CasingBackend* casingBackend, PlugNumber plugNumber)
    : m_uid(QUuid::createUuid())
    , m_outPlugNumber(NONE)
    , m_inPlugNumber(NONE)
    , m_state()
{
    setCasingToPlug(casingBackend, plugType, plugNumber);
    setRequiredPlugType(oppositePlug(plugType));
}


WireBackend::WireBackend(QUuid id, CasingBackend* inCasingBackend, PlugNumber inPlugNumber,
                         CasingBackend* outCasingBackend, PlugNumber outPlugNumber)
    : m_uid(id)
    , m_outCasingBackend(outCasingBackend)
    , m_inCasingBackend(inCasingBackend)
    , m_outPlugNumber(outPlugNumber)
    , m_inPlugNumber(inPlugNumber)
    , m_state()
{
    setCasingToPlug(inCasingBackend, PlugType::IN, inPlugNumber);
    setCasingToPlug(outCasingBackend, PlugType::OUT, outPlugNumber);
}


WireBackend::~WireBackend()
{
    if (complete())
    {
        wireBackendMadeIncomplete(*this);
        sendNullData();
    }
    delete m_wire;
}


QJsonObject WireBackend::serialize() const
{
    QJsonObject wireJson;

    if (m_inCasingBackend && m_outCasingBackend)
    {
        wireJson["id"] = id().toString();
        wireJson["i_id"] = m_inCasingBackend->id().toString();
        wireJson["i_n"] = m_inPlugNumber;

        wireJson["o_id"] = m_outCasingBackend->id().toString();
        wireJson["o_n"] = m_outPlugNumber;
    }
    return wireJson;
}


QUuid WireBackend::id() const
{
    return m_uid;
}


bool WireBackend::complete() const
{
    return m_inCasingBackend != nullptr && m_outCasingBackend != nullptr;
}


void WireBackend::setRequiredPlugType(PlugType plugType)
{
    m_state.setPlugTypeNeeded(plugType);

    switch (plugType)
    {
    case PlugType::OUT:
        m_outCasingBackend = nullptr;
        m_outPlugNumber = NONE;
        break;
        
    case PlugType::IN:
        m_inCasingBackend = nullptr;
        m_inPlugNumber = NONE;
        break;

    default:
        break;
    }
}


PlugType WireBackend::requiredPlugType() const
{
    return m_state.plugTypeNeeded();
}


void WireBackend::setWire(Wire *wire)
{
    m_wire = wire;
}

PlugNumber WireBackend::getPlugIndex(PlugType plugType) const
{
    PlugNumber result = NONE;

    switch (plugType)
    {
    case PlugType::IN:
        result = m_inPlugNumber;
        break;
        
    case PlugType::OUT:
        result = m_outPlugNumber;

        break;

    default:
        break;
    }

    return result;
}


void WireBackend::setCasingToPlug(CasingBackend* casingBackend, PlugType plugType, PlugNumber plugNumber)
{
    bool wasIncomplete = !complete();
    auto& weakCasingBackend = getCasing(plugType);
    weakCasingBackend = casingBackend;
    
    if (plugType == PlugType::OUT)
        m_outPlugNumber = plugNumber;
    else
        m_inPlugNumber = plugNumber;

    m_state.pluginIn();

    updated(*this);
    if (complete() && wasIncomplete)
    {
        wireBackendCompleted(*this);
    }
}


void WireBackend::removeFromCasings() const
{
    if (m_inCasingBackend)
        m_inCasingBackend->casingState().eraseWire(PlugType::IN, m_inPlugNumber, id());

    if (m_outCasingBackend)
        m_outCasingBackend->casingState().eraseWire(PlugType::OUT, m_outPlugNumber, id());
}

Wire *WireBackend::getWire() const
{
    return m_wire;
}

WireState& WireBackend::state()
{
    return m_state;
}

WireState const& WireBackend::state() const
{
    return m_state;
}

CasingBackend* WireBackend::getCasing(PlugType plugType) const
{
    if(plugType == PlugType::IN)
        return m_inCasingBackend;
    else
        return m_outCasingBackend;
}

CasingBackend*& WireBackend::getCasing(PlugType plugType)
{
    if(plugType == PlugType::IN)
        return m_inCasingBackend;
    else
        return m_outCasingBackend;

}

void WireBackend::clearCasingBackend(PlugType plugType)
{
    if (complete())
    {
        wireBackendMadeIncomplete(*this);
    }

    getCasing(plugType) = nullptr;
    
    if (plugType == PlugType::IN)
        m_inPlugNumber = NONE;
    else
        m_outPlugNumber = NONE;
}

int WireBackend::dataType(PlugType plugType) const
{
    if (m_inCasingBackend && m_outCasingBackend)
    {
        auto const & idea = (plugType == PlugType::IN) ?
                    m_inCasingBackend->idea() :
                    m_outCasingBackend->idea();
        PlugNumber index = (plugType == PlugType::IN) ?
                    m_inPlugNumber :
                    m_outPlugNumber;

        int candidateCasingDataType;
        if(plugType == PlugType::IN)
            candidateCasingDataType = idea->attributes().dataTypesIn()[index];
        else
            candidateCasingDataType = idea->attributes().dataTypesOut()[index];

        return candidateCasingDataType;
    }
    else
    {
        CasingBackend* validCasingBackend;
        PlugNumber index = NONE;

        if ((validCasingBackend = m_inCasingBackend))
        {
            index    = m_inPlugNumber;
            plugType = PlugType::IN;
        }
        else if ((validCasingBackend = m_outCasingBackend))
        {
            index    = m_outPlugNumber;
            plugType = PlugType::OUT;
        }

        if (validCasingBackend)
        {
            auto const &idea = validCasingBackend->idea();

            int candidateCasingDataType;
            if(plugType == PlugType::IN)
                candidateCasingDataType = idea->attributes().dataTypesIn()[index];
            else
                candidateCasingDataType = idea->attributes().dataTypesOut()[index];

            return candidateCasingDataType;
        }
    }

    qFatal("Invalid datatype in WireBackend");
}

void WireBackend::sendData(std::shared_ptr<DataType> dataType) const
{
    if(m_inCasingBackend)
        m_inCasingBackend->sendDataToIdea(dataType, m_inPlugNumber);
}

void WireBackend::sendNullData() const
{
    std::shared_ptr<DataType> emptyData;

    sendData(emptyData);
}
