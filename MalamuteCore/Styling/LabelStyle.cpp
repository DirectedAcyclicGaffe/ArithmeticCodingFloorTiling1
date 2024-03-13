#include "LabelStyle.h"

LabelStyle::LabelStyle()
{
    m_colorList = {QColor(0xd4985d),
                   QColor(0xe70c0c),
                   QColor(0xe76f0c),
                   QColor(0xe7b80c),
                   QColor(0xa6e70c),
                   QColor(0x0ce717),
                   QColor(0x0ce7c9),
                   QColor(0x0c52e7),
                   QColor(0x850ce7),
                   QColor(0xe70cc5),
                   QColor(0xe70c47),

                   QColor(0x26d326),
                   QColor(0x0bafd1),
                   QColor(0xea42cb),
                   QColor(0x26d3a7),
                   QColor(0xe76f0c),
                   QColor(0xa942ea),

                   QColor(0xd28888),
                   QColor(0xd29cf4),
                   QColor(0x8cea8c),
                   QColor(0x8ae6f9),
                   QColor(0xd1d693),
                   QColor(0xab9af4),
                   QColor(0xf49ce4),
                   QColor(0xa4efdc),

                   QColor(0xd4b35d),
                   QColor(0xb15e43),
                   QColor(0xd242ea),
                   QColor(0x26d363),
                   QColor(0x0b80d1),
                   QColor(0x7cb143),
                   QColor(0xf5580a),
                   QColor(0x8e1155),
                   QColor(0x1e9fa5)};
}

QColor LabelStyle::defaultColor()
{
    return QColor(0xa6b0cb);
}

QColor LabelStyle::getColor()
{
    colorListIndex++;
    if(colorListIndex == m_colorList.length())
        colorListIndex = 0;

    return m_colorList.at(colorListIndex);
}
