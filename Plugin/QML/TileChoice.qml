import QtQuick 2.12

Item
{
    id: root;
    height: 560;
    width: 44;

    property double fractionGold : 0.25;
    property double choiceY: 0.0;
    property double choiceHeight: 560;
    Rectangle
    {
        id: bar
        width: 1
        color: "black"
        height: 560
    }

    Rectangle
    {
        id: gold;
        x: 1;
        y: choiceY;
        width: parent.width - 1
        height: choiceHeight * fractionGold;
        color: "#d4af37"
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
        id: bronze
        x: 1
        y: choiceY + fractionGold*choiceHeight;
        width: parent.width - 1
        height: choiceHeight * (1.0 - fractionGold);
        color: "#cd7f32";
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
        id: shadowBottomUp;
        x: bronze.x
        width: bronze.width
        anchors.bottom: bronze.bottom;
        color: "black"
        opacity: 0.5;
    }
    Rectangle
    {
        id: shadowTopDown;
        x: gold.x
        width: gold.width
        anchors.top: gold.top;

        color: "black"
        opacity: 0.5;
    }

    function topShadow(y)
    {
        if(y < choiceY)
            return;
        shadowTopDown.height = (y - choiceY);
    }

    function botShadow(y)
    {
        if(y > choiceY + choiceHeight)
            return;
        shadowBottomUp.height = (choiceY + choiceHeight - y);
    }

    property double zoomHeight;
    property double finalX;
    property double finalY : 0;
    property double topShadowHeight: 0
    property double botShadowHeight: 0

    function zoomDestroy(xMove, zoomHeightFactor, a, b)
    {
        root.zoomHeight = choiceHeight * zoomHeightFactor;
        topShadowHeight = shadowTopDown.height * zoomHeightFactor;
        botShadowHeight = shadowBottomUp.height * zoomHeightFactor;
        root.finalX = root.x - xMove;
        root.finalY = -560.0 * (a * (1.0 - root.choiceY / 560.0) + b) + 560
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
                property: "choiceY"
                to: finalY
                easing.type: Easing.InExpo;
                duration: 2.9 * idea.speed
            }
            NumberAnimation
            {
                target: root;
                property: "choiceHeight"
                to: zoomHeight
                easing.type: Easing.InExpo;
                duration: 2.9 * idea.speed
            }
            NumberAnimation
            {
                target: shadowBottomUp
                property: "height"
                to: botShadowHeight;
                easing.type: Easing.InExpo;
                duration: 2.9 * idea.speed
            }
            NumberAnimation
            {
                target: shadowTopDown
                property: "height"
                to: topShadowHeight;
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
