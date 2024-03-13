import com.malamute.core 1.0
import QtGraphicalEffects 1.12
import QtQuick 2.12
import QtQuick.Controls 2.12

MalamuteCasing
{
    id: root
    width: casingSize.width + 1.4 * 15 + 10;
    height: casingSize.height + 0.4 * 15;

    RectangularGlow
    {
        id: effect
        width: selected ? frameRect.width + 14 : frameRect.width + 2
        height: selected ? frameRect.height + 14 : frameRect.height + 2
        anchors.centerIn: frameRect
        opacity: selected ? 1.0 : 0.2

        glowRadius: CasingStyle.glowRadius()
        spread: CasingStyle.glowSpread()
        color: "teal"
        cornerRadius: frameRect.radius + CasingStyle.glowRadius()
        z: frameRect.z - 2
    }

    Rectangle
    {
        id: frameRect
        x: 0.7 * 15; y: 0.2 * 15;
        z: 0
        width: casingSize.width;
        height: casingSize.height
        radius: 20;
        gradient: Gradient
        {
            GradientStop{position: 0.05; color: "#181818"}
            GradientStop{position: 0.95; color: "#5b5b5b"}
        }
        Rectangle
        {
            id: mainSurface
            width: parent.width - 8
            height: parent.height - 8
            x: 4
            y: 4
            radius: parent.radius
            gradient: Gradient
            {
                GradientStop{position: 0.05; color: "#5b5b5b"}
                GradientStop{position: 0.95; color: "#333333"}
            }
        }
        Rectangle
        {
            id: nameBackground
            anchors.top: frameRect.top;
            anchors.horizontalCenter: frameRect.horizontalCenter;
            width: frameRect.width
            height: nameSize.height + 10
            visible: ideaName !== "";

            radius: CasingStyle.frameRadius();

            gradient: Gradient
            {
                GradientStop{position: 0.05; color: "#4d4d4d"}
                GradientStop{position: 0.95; color: "#000000"}
            }
            Rectangle
            {
                anchors.top: parent.top;
                anchors.topMargin: 4
                anchors.horizontalCenter: parent.horizontalCenter;
                width: parent.width - 8
                height: parent.height - 8
                visible: ideaName !== "";

                radius: CasingStyle.frameRadius();

                gradient: Gradient
                {
                    GradientStop{position: 0.05; color: "#272727"}
                    GradientStop{position: 0.95; color: "#4d4d4d"}
                }
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenterOffset: 1
                    anchors.horizontalCenterOffset: 2
                    color: "black"
                    font: CasingStyle.nameFont()
                    horizontalAlignment: Text.AlignHCenter
                    text: ideaName
                }
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenterOffset: -3
                    anchors.horizontalCenterOffset: -2
                    color: "black"
                    font: CasingStyle.nameFont()
                    horizontalAlignment: Text.AlignHCenter
                    text: ideaName
                }
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenterOffset: -3
                    anchors.horizontalCenterOffset: 2
                    color: "black"
                    font: CasingStyle.nameFont()
                    horizontalAlignment: Text.AlignHCenter
                    text: ideaName
                }
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenterOffset: 1
                    anchors.horizontalCenterOffset: -2
                    color: "black"
                    font: CasingStyle.nameFont()
                    horizontalAlignment: Text.AlignHCenter
                    text: ideaName
                }
                Text
                {
                    id: name
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: -1
                    color: selected ? "#4df64d" : Qt.lighter("#4df64d", 1.3)
                    font: CasingStyle.nameFont()
                    horizontalAlignment: Text.AlignHCenter
                    text: ideaName
                }

            }

        }
        Column
        {
            id: inPortsColumn
            y: plugBoxTop
            x: -0.5*15 + frameRect.border.width / 2;
            z: 99
            width: 15;

            spacing:  CasingStyle.portSpacing();

            Repeater
            {
                model: inPlugLabels.length
                Rectangle
                {
                    radius: CasingStyle.portSize();
                    width: CasingStyle.portSize();
                    height: CasingStyle.portSize();
                    border.color: "black"
                    border.width: CasingStyle.portBorderWidth();
                    color: inPlugLabelColors[index]
                }
            }
        }
        Column
        {
            id: inPortLabelsColumn
            x: inPortsColumn.x + inPortsColumn.width/2 - 2;
            y: plugBoxTop - 2;
            width: inLabelWidth

            spacing: CasingStyle.portSpacing() - 4;

            Repeater
            {
                model: inPlugLabels

                Rectangle
                {
                    visible: modelData !== "";
                    width: text.width + text.x + 3
                    height: CasingStyle.portSize() + 4;
                    color: "#1a1a1a"
                    border.width: 2
                    border.color: "black"
                    radius: 6
                    z: -1
                    Text
                    {
                        id: text
                        x: inPortsColumn.width/2 + 2
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.verticalCenterOffset: -1
                        font: CasingStyle.portLabelsFont();
                        color: inPlugLabelColors[index]
                        text: modelData
                    }
                }
            }
        }
        Column
        {
            id: outPortsColumn
            y: plugBoxTop
            x: frameRect.width - 0.5*15 - frameRect.border.width / 2;
            z: 99
            width: 15;

            spacing: CasingStyle.portSpacing();

            Repeater
            {
                model: outPlugLabels.length
                Rectangle
                {
                    id: outPortRect
                    radius: CasingStyle.portSize();
                    width: CasingStyle.portSize();
                    height: CasingStyle.portSize();
                    border.color: "black"
                    border.width: CasingStyle.portBorderWidth();
                    color: outPlugLabelColors[index]
                }
            }
        }
        Column
        {
            id: outPortLabelsColumn
            y: outPortsColumn.y - 2
            x: outPortsColumn.x - outLabelWidth - 3;
            width: outLabelWidth

            spacing: CasingStyle.portSpacing() - 4;


            Repeater
            {
                model: outPlugLabels
                Rectangle
                {
                    visible: modelData !== "";
                    width: textout.width + 5 + CasingStyle.portSize()/2
                    height: CasingStyle.portSize() + 4;
                    color: "#1a1a1a"
                    border.width: 2
                    border.color: "black"
                    radius: 6
                    z: -1
                    Text
                    {
                        id: textout
                        x: 3
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.verticalCenterOffset: -1
                        font: CasingStyle.portLabelsFont();
                        color: outPlugLabelColors[index]
                        text: modelData
                    }
                }
            }
        }
        Rectangle
        {
            gradient: Gradient
            {
                GradientStop{position: 0.05; color: "#181818"}
                GradientStop{position: 0.95; color: "#5b5b5b"}
            }
            radius: frameRect.radius;

            y: validationBoxTop - 2
            anchors.left: frameRect.left;
            width: frameRect.width
            height: validationBoxSize.height === 0 ? 0 : validationBoxSize.height + 2*5 + 2*border.width + 4

            Rectangle
            {
                width: parent.width - 8
                height: parent.height - 8
                x: 4
                y: 4
                radius: parent.radius
                gradient: Gradient
                {
                    GradientStop{position: 0.05; color: "#5b5b5b"}
                    GradientStop{position: 0.95; color: "#333333"}
                }

                Rectangle
                {
                    width: parent.width - 8
                    height: parent.height - 8
                    anchors.centerIn: parent

                    radius: parent.radius
                    gradient: Gradient
                    {
                        GradientStop{position: 0.05; color: Qt.darker(validationColor, 1.15)}
                        GradientStop{position: 0.5; color: validationColor}
                        GradientStop{position: 0.95; color: Qt.darker(validationColor, 1.15)}
                    }
                    color: validationColor
                    Text
                    {
                        id: validatationMessageDisplay
                        color: CasingStyle.validationTextColor();
                        font: CasingStyle.validationTextFont();
                        horizontalAlignment: Text.AlignHCenter
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: -1
                        text: validationMessage
                    }
                }
            }



        }
    }

    Rectangle
    {
        id: minimizerButton
        visible: minimizable
        width: CasingStyle.buttonSize()
        height: CasingStyle.buttonSize()
        color: "transparent"
        radius: CasingStyle.buttonSize()
        anchors.top: frameRect.top
        anchors.topMargin: -width / 2 + 2.5
        anchors.right: frameRect.right
        anchors.rightMargin: width /2

        Rectangle
        {
            visible: minimizable
            width: 8
            height: 1
            color: "white";
            anchors.centerIn: parent
        }

        MouseArea
        {
            anchors.fill: parent
            anchors.margins: -1
            hoverEnabled: true
            onClicked:
            {
                minimizeButtonClicked();
            }
            onEntered:
            {
                minimizerButton.color = Qt.lighter("#845a35",1.5)
            }
            onExited:
            {
                minimizerButton.color = "transparent"
            }
        }
    }



    Rectangle
    {
        id: extraButton
        visible: hasExtraQML
        width: CasingStyle.buttonSize()
        height: CasingStyle.buttonSize()
        color: "transparent"
        radius: CasingStyle.buttonSize()
        anchors.top: frameRect.top
        anchors.topMargin:  width/2
        anchors.right: frameRect.right
        anchors.rightMargin: -width / 2 + 2

        MouseArea
        {
            anchors.fill: parent
            anchors.margins: -1
            hoverEnabled: true
            onClicked:
            {
                extraButtonClicked();
            }
            onEntered:
            {
                extraButton.color = Qt.lighter(CasingStyle.buttonColor(),1.5)
            }
            onExited:
            {
                extraButton.color = "transparent"
            }
        }
        Rectangle
        {
            id: centerDot
            visible: hasExtraQML
            width: 3
            height: 3
            radius: 2
            color: "white";
            x: parent.width / 2 - width / 2
            y: parent.height / 2 - height / 2
        }
        Rectangle
        {
            visible: hasExtraQML
            width: 3
            height: 3
            radius: 2
            color: "white";
            x: centerDot.x
            y: centerDot.y - 6
        }
        Rectangle
        {
            visible: hasExtraQML
            width: 3
            height: 3
            radius: 2
            color: "white";
            x: centerDot.x
            y: centerDot.y + 6
        }
    }

    Rectangle
    {
        id: resizer;
        visible: resizeable
        x: frameRect.x + frameRect.width - width;
        y: frameRect.y + frameRect.height - height;
        z: frameRect.z + 1;
        width: CasingStyle.resizerSize()
        height: CasingStyle.resizerSize()
        radius: CasingStyle.resizerSize()
        border.width: 2;
        color: CasingStyle.resizerColor()
        border.color: CasingStyle.resizerBorderColor()
    }
}
