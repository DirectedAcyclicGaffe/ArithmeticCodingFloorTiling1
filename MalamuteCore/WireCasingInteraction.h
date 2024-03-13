#ifndef WIRECASINGINTERACTION_H
#define WIRECASINGINTERACTION_H

#include "CasingBackend.h"
#include "WireBackend.h"

/// Handles the interaction between a wire and a casing.
/// Created and destroyed frequently.

class WireCasingInteraction
{
public:
    WireCasingInteraction(CasingBackend& casingBackend, WireBackend& wireBackend);

    bool canConnect(PlugNumber & plugNumber) const;
    bool tryConnect() const;
    bool disconnect(PlugType disconnectingPlug) const;

    bool tryHover();

private:
    PlugType wireRequiredPlug() const;
    QPointF wireEndScenePosition(PlugType plugType) const;
    PlugNumber casingPlugNumberUnderScenePoint(PlugType plugType, QPointF const &p) const;
    bool casingPlugIsEmpty(PlugType plugType, PlugNumber plugNumber) const;

    CasingBackend* m_casingBackend;
    WireBackend* m_wireBackend;
};

#endif
