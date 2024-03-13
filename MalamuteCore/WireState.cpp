#include "WireState.h"

WireState::WireState(PlugType plugType) :
    m_plugTypeNeeded(plugType)
{

}

void WireState::setPlugTypeNeeded(PlugType end)
{
    m_plugTypeNeeded = end;
}

PlugType WireState::plugTypeNeeded() const
{
    return m_plugTypeNeeded;
}

bool WireState::unplugged() const
{
    return m_plugTypeNeeded != PlugType::NA;
}

void WireState::pluginIn()
{
    m_plugTypeNeeded = PlugType::NA;
}

void WireState::resetStopLights()
{
    foreach (CasingBackend* casingBackend, m_casingWithStopLights)
    {
        casingBackend->clearStopLights();
    }
    m_casingWithStopLights.clear();
}

void WireState::casingHasStopLights(CasingBackend *casingBackend)
{
    m_casingWithStopLights.insert(casingBackend);
}
