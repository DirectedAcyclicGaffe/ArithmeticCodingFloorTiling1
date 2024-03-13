import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle
{
    property int numTileTall: 50;
    property int numTileWide: 20;
    property int tileSize: 11
    color: "#050512"
    radius: 3

    visible: true
    width: numTileWide*(tileSize) + 4;
    height: numTileTall*(tileSize) + 21;

    Grid
    {
        y: 2;
        x: 2
        height: numTileTall*(tileSize+1)
        clip: true;
        columns: numTileWide
        spacing: 0

        Repeater
        {
            model: TileModel

            Rectangle
            {
                id: image
                visible: idea.tilesVisible;
                width: tileSize
                height: tileSize
                color: model.Side === true ? "#CD7F32" : "#d4af37"
                border.width: 1
                border.color: Qt.lighter(color);
                opacity: 0.1

                NumberAnimation
                {
                    id: opacityAnimation
                    target: image
                    property: "opacity"
                    to: 1.0
                    duration: 1600
                }
                Component.onCompleted:
                {
                opacityAnimation.start();
                }
            }
        }
    }

    Rectangle
    {
        width: parent.width
        anchors.bottom: parent.bottom
        height: 20;
        radius: 3
        color: "#1a1a1a"

        Text
        {
            anchors.centerIn: parent
            id: countText
            font.pointSize: 12
            font.bold: true
            font.family: "consolas"
            text: "Tiles: 0"
            z: 1
            color: "#cccccc"
        }
        Connections
        {
            target: idea
            function onTilesAdded(tiles)
            {
                countText.text = "Tiles: " + tiles;
            }
        }
    }
}
