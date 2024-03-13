#ifndef PLUG_H
#define PLUG_H

enum PlugType
{
    NA,
    IN,
    OUT
};

static const int NONE = -1;
using PlugNumber = int;

inline PlugType oppositePlug(PlugType plugType)
{
    if(plugType == PlugType::IN)
        return PlugType::OUT;
    else if (plugType == PlugType::OUT)
        return PlugType::IN;
    else
        return PlugType::NA;
}

class UnplugWiresInfo
{
public:
    UnplugWiresInfo(PlugNumber plugNumber, PlugType plugType) :
        m_plugNumber(plugNumber),
        m_plugType(plugType)
    {

    }
    int plugNumber() const {return m_plugNumber;};
    PlugType isInput() const {return m_plugType;};

private:
    int m_plugNumber;
    PlugType m_plugType;
};


#endif

