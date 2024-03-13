import QtQuick 2.12

Item
{
    height: 560;
    width: 35
    Rectangle
    {
        id: gold
        width: parent.width
        height: parent.height * 0.25;
        color: "#d4af37"
        opacity: 0.0;
        Behavior on opacity
        {
            SequentialAnimation
            {
                PauseAnimation{duration: 1.0 * idea.speed;}
                NumberAnimation{duration: 0.2 * idea.speed;}
            }
        }
        Component.onCompleted:
        {
            opacity = 1;
        }
    }

    Rectangle
    {
        id: blue
        width: parent.width
        height: parent.height * 0.75;
        anchors.bottom: parent.bottom;
        color: "#1a438d";
        opacity: 0.0;
        Behavior on opacity
        {
            SequentialAnimation
            {
                PauseAnimation{duration: 1.0 * idea.speed;}
                NumberAnimation{duration: 0.2 * idea.speed;}
            }
        }
        Component.onCompleted:
        {
            opacity = 1;
        }
    }
}
