import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import QtQuick.Controls.Material 2.12

Rectangle
{
    id: root
    visible: true
    width: 216
    height: 571
    radius: 4
    color: "#050512"

    property int coinsToAdd: 1
    property int currentCoins: 0;


    Rectangle
    {
        id: controlsRect
        width: 78
        height: 216
        radius: 2
        color: "#333333"
        Button
        {
            id: flipCoinButton
            anchors.top: parent.top
            anchors.topMargin: -2
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: 70
            text: "Flip"
            font.bold: true
            font.pointSize: 14

            onClicked:
            {
                CoinModel.addRandom(coinsToAdd);
                currentCoins += coinsToAdd;
            }
            font.capitalization: Font.MixedCase
            Material.background: Material.Grey
            Material.foreground:  "#1a1a1a"
        }
        Button
        {
            id: addHeadButton
            anchors.top: flipCoinButton.bottom
            anchors.topMargin: -5
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: 70
            Image
            {
                anchors.centerIn: parent
                source: "qrc:/Images/CoinHeads60.png"
                sourceSize: Qt.size(60,60)
                width: 30
                height: 30
            }

            onClicked:
            {
                CoinModel.addHeads(coinsToAdd);
                currentCoins += coinsToAdd;
            }
            font.capitalization: Font.MixedCase
            Material.background: Material.Grey
            Material.foreground:  "#1a1a1a"
        }
        Button
        {
            id: addTailsButton
            anchors.top: addHeadButton.bottom
            anchors.topMargin: -5
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: 70
            Image
            {
                anchors.centerIn: parent
                source: "qrc:/Images/CoinTails60.png"
                sourceSize: Qt.size(60,60)
                width: 30
                height: 30
            }

            onClicked:
            {
                CoinModel.addTails(coinsToAdd);
                currentCoins += coinsToAdd;
            }
            font.capitalization: Font.MixedCase
            Material.background: Material.Grey
            Material.foreground:  "#1a1a1a"
        }

        Rectangle
        {
            id: numCoinsFlipBox
            anchors.top: addTailsButton.bottom
            anchors.left: parent.left
            anchors.leftMargin: 4

            width: 70
            height: 36
            radius: 2
            color: "#9e9e9e"

            TextInput
            {
                anchors.centerIn: parent
                validator: IntValidator{bottom: 0; top: 9999}
                selectByMouse: true;
                font.bold: true
                font.pointSize: 14
                color: "#1a1a1a"
                text: "1"
                onEditingFinished:
                {
                    coinsToAdd = text;
                }
            }
        }

        Button
        {
            id: clearCoinsButton
            anchors.top: numCoinsFlipBox.bottom
            anchors.left: parent.left
            anchors.leftMargin: 4
            width: 70
            text: "Clear"
            font.bold: true
            font.pointSize: 14

            onClicked:
            {
                CoinModel.clearCoins();
                currentCoins = 0;
            }
            font.capitalization: Font.MixedCase
            Material.background: Material.Grey
            Material.foreground:  "#1a1a1a"
        }


    }

    Image
    {
        anchors.top: controlsRect.bottom
        anchors.bottom: coinLabelRect.top
        source: "qrc:/Images/CoinFlipperSide.png"
    }

    Flickable
    {
        id: flickable

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 2

        width: 134
        clip: true

        contentHeight: grid.height
        contentWidth: grid.width

        Grid
        {
            id: grid;
            columns: 10
            spacing: 1
            flow: GridLayout.LeftToRight

            Repeater
            {
                model: CoinModel
                Image
                {
                    id: image
                    width: 12
                    height: 12
                    sourceSize: Qt.size(60,60)
                    source: model.Side === true ? "qrc:/Images/CoinHeads60.png" : "qrc:/Images/CoinTails60.png"
                    opacity: 0.1

                    NumberAnimation
                    {
                        id: opacityAnimation
                        target: image
                        property: "opacity"
                        to: 1.0
                        duration: 800
                    }
                    Component.onCompleted:
                    {
                        opacityAnimation.start();
                    }
                }
            }

        }

        onContentHeightChanged:
        {
            if(contentHeight > (root.height - 20))
                contentY = - (root.height - 20) + contentHeight;
        }
        Behavior on contentY
        {
            NumberAnimation
            {
                target: flickable
                property: "contentY"
                duration: 700
                easing.type: Easing.InOutQuad
            }
        }

    }
    Rectangle
    {
        id: coinLabelRect
        color: "#1a1a1a"
        anchors.bottom: parent.bottom;
        anchors.left: parent.left
        width: parent.width
        height: 20
        radius: 3
        z: 100;

        Label
        {
            anchors.centerIn: parent
            font.bold: true
            font.pointSize: 12
            text: "Coins: " + currentCoins;
            color: "#cccccc"
        }
    }
}
