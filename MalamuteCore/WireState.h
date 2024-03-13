#ifndef WIRESTATE_H
#define WIRESTATE_H

#include <set>

#include "Plug.h"
#include "CasingBackend.h"

class WireState
{
public:
    WireState(PlugType plugType = PlugType::NA);

    void setPlugTypeNeeded(PlugType end);
    PlugType plugTypeNeeded() const;
    bool unplugged() const;
    void pluginIn();

    void resetStopLights();
    void casingHasStopLights(CasingBackend* casingBackend);

private:
    PlugType m_plugTypeNeeded;
    std::set<CasingBackend*> m_casingWithStopLights;
};

#endif // WIRESTATE_H
