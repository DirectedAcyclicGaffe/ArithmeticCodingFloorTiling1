import QtQuick 2.12

Item
{
    id: root
    height: 560;
    width: 44;
    property bool stairs: true;

    Image
    {
        source: "qrc:/Images/Backgrounds/StairsDown.png"
        y: - parent.y;
        sourceSize: Qt.size(18, 1120);
        width: 9;
        height: 560;
        visible: stairs;
    }
    Rectangle
    {
        y: - parent.y;
        width: 1
        color: "black"
        height: 560
        visible: !stairs;
    }

    Rectangle
    {
        x: stairs ? 9 : 1;
        width: parent.width - x
        height: parent.height / 2;
        color: "#661212"
        opacity: 0.0;
        Behavior on opacity
        {
            NumberAnimation{duration: 0.2 * idea.speed;}
        }
        Component.onCompleted:
        {
            opacity = 1;
        }
    }

    Rectangle
    {
        x: stairs ? 9 : 1;
        width: parent.width - x
        height: parent.height / 2;
        anchors.bottom: parent.bottom;
        color: "#9a9a9a";
        opacity: 0.0;
        Behavior on opacity
        {
            NumberAnimation{duration: 0.2 * idea.speed;}
        }
        Component.onCompleted:
        {
            opacity = 1;
        }
    }

    property double zoomHeight;
    property double finalX;
    property double finalY : 0;

    function zoomDestroy(xMove, zoomHeightFactor, a, b)
    {
        root.zoomHeight = height * zoomHeightFactor;
        root.finalX = root.x - xMove;
        root.finalY = -560.0 * (a * (1.0 - root.y / 560.0) + b) + 560
        zoomDestroyAnimation.start();
    }

    SequentialAnimation
    {
        id: zoomDestroyAnimation;
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0.9;
            duration: 1.1 * idea.speed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: root;
                property: "x"
                to: finalX
                duration: 2.9 * idea.speed
            }
            NumberAnimation
            {
                target: root;
                property: "y"
                to: finalY
                easing.type: Easing.InExpo;
                duration: 2.9 * idea.speed
            }
            NumberAnimation
            {
                target: root;
                property: "height"
                to: zoomHeight
                easing.type: Easing.InExpo;
                duration: 2.9 * idea.speed
            }
        }
        PauseAnimation {duration: 0.5*idea.speed}
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0
            duration: 1.0 * idea.speed
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }

    function pauseDestroy()
    {
        pauseDestroyAnimation.start();
    }
    SequentialAnimation
    {
        id: pauseDestroyAnimation
        PauseAnimation {duration: 4.5*idea.speed}
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0
            duration: 1.0 * idea.speed
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }
}
