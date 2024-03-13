#include "CasingStyle.h"

CasingStyle::CasingStyle(QObject *parent) : QObject(parent)
{
    m_gradientTopColors = {QColor(0x338347), QColor(0x6b8333), QColor(0x33836c),
                           QColor(0x337b83), QColor(0x5b3383), QColor(0x836a33),
                           QColor(0xa11212), QColor(0xeae9cc), QColor(0x1c132b)};

    m_gradientBottomColors = {QColor(0x71A67B), QColor(0x96a671), QColor(0x71a696),
                              QColor(0x71a0a6), QColor(0x8b71a6), QColor(0xa69571),
                              QColor(0xe63c10), QColor(0xd7d7cf), QColor(0x0a080d)};

    m_nameFont = QFont("verdana", 20, QFont::Bold);
    m_portLabelsFont = QFont("verdana", 11, QFont::Bold);
    m_validationTextFont = QFont("verdana", 14,QFont::Bold);
}

double CasingStyle::bordersWidth() const
{
    return m_bordersWidth;
}

QColor CasingStyle::borderColor() const
{
    return m_borderColor;
}

QColor CasingStyle::borderSelectedColor() const
{
    return m_borderSelectedColor;
}

QColor CasingStyle::gradientTopColor(int i)
{
    return m_gradientTopColors.at(i);
}

QColor CasingStyle::gradientBottomColor(int i)
{
    return m_gradientBottomColors.at(i);
}

int CasingStyle::glowRadius() const
{
    return m_glowRadius;
}

double CasingStyle::glowSpread() const
{
    return m_glowSpread;
}

QColor CasingStyle::glowColor() const
{
    return m_glowColor;
}

double CasingStyle::portSize() const
{
    return m_portSize;
}

double CasingStyle::portSpacing() const
{
    return m_portSpacing;
}

double CasingStyle::portBorderWidth() const
{
    return m_portBorderWidth;
}

QColor CasingStyle::nameColor() const
{
    return m_nameColor;
}

QFont CasingStyle::nameFont() const
{
    return m_nameFont;
}

QFont CasingStyle::portLabelsFont() const
{
    return m_portLabelsFont;
}

QFont CasingStyle::validationTextFont() const
{
    return m_validationTextFont;
}

QColor CasingStyle::validationTextColor() const
{
    return m_validationTextColor;
}

double CasingStyle::buttonSize() const
{
    return m_buttonSize;
}

QColor CasingStyle::buttonColor() const
{
    return m_buttonColor;
}

double CasingStyle::buttonHoverDarkenFactor() const
{
    return m_buttonHoverDarkenFactor;
}

QColor CasingStyle::resizerColor() const
{
    return m_resizerColor;
}

QColor CasingStyle::resizerBorderColor() const
{
    return m_resizerBorderColor;
}

double CasingStyle::frameRadius() const
{
    return m_frameRadius;
}

double CasingStyle::resizerSize() const
{
    return m_resizerSize;
}
