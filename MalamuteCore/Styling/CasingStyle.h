#ifndef CASINGSTYLE_H
#define CASINGSTYLE_H

#include <QObject>
#include <QColor>
#include <QFont>

class CasingStyle : public QObject
{
    Q_OBJECT

public:
    explicit CasingStyle(QObject *parent = nullptr);

    Q_INVOKABLE double bordersWidth() const;
    Q_INVOKABLE double frameRadius() const;
    Q_INVOKABLE QColor borderColor() const;
    Q_INVOKABLE QColor borderSelectedColor() const;

    Q_INVOKABLE QColor gradientTopColor(int i);
    Q_INVOKABLE QColor gradientBottomColor(int i);

    Q_INVOKABLE int glowRadius() const;
    Q_INVOKABLE double glowSpread() const;
    Q_INVOKABLE QColor glowColor() const;

    Q_INVOKABLE double portSize() const;
    Q_INVOKABLE double portSpacing() const;
    Q_INVOKABLE double portBorderWidth() const;

    Q_INVOKABLE QColor nameColor() const;
    Q_INVOKABLE QFont nameFont() const;

    Q_INVOKABLE QFont portLabelsFont() const;

    Q_INVOKABLE QFont validationTextFont() const;
    Q_INVOKABLE QColor validationTextColor() const;

    Q_INVOKABLE double buttonSize() const;
    Q_INVOKABLE QColor buttonColor() const;
    Q_INVOKABLE double buttonHoverDarkenFactor() const;

    Q_INVOKABLE double resizerSize() const;
    Q_INVOKABLE QColor resizerColor() const;
    Q_INVOKABLE QColor resizerBorderColor() const;

private:
    double m_bordersWidth = 4;
    double m_frameRadius = 20;
    QColor m_borderColor = QColor(0x70460c);
    QColor m_borderSelectedColor = QColor("0x0b0b0b");

    std::vector<QColor> m_gradientTopColors;
    std::vector<QColor> m_gradientBottomColors;

    int m_glowRadius = 6;
    double m_glowSpread = 0.4;
    QColor m_glowColor = QColor(0x323232);

    double m_portSize = 15;
    double m_portSpacing = 5;
    double m_portBorderWidth = 3;

    QColor m_nameColor = QColor("black");
    QFont m_nameFont;

    QFont m_portLabelsFont;

    QColor m_portLabelsColor = QColor("black");
    QFont m_validationTextFont;
    QColor m_validationTextColor = QColor("black");

    double m_buttonSize = 22;
    QColor m_buttonColor = QColor(0x845a35);
    double m_buttonHoverDarkenFactor = 1.5;

    double m_resizerSize = 14;
    QColor m_resizerColor = QColor("black");
    QColor m_resizerBorderColor = QColor("grey");
};

#endif // CASINGSTYLE_H
