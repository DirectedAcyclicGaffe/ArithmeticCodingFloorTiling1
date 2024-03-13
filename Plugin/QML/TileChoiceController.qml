import QtQuick 2.12

Item
{
    id: root
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -1

    width: parent.width;
    height: 560

    property double tileRectWidth: 40
    property double fractionGold: 0.25;
    property double resetTop: 0.0;
    property double resetBot: 0.0;

    function reset()
    {
        topShadowLoc = 0.0;
        botShadowLoc = 560.0;
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].destroy();
        }

        let comp; let obj;
        comp = Qt.createComponent("TileChoice.qml");
        obj = comp.createObject(root, {x: 105, y: 0, width: tileRectWidth + 1, choiceHeight: height,
                                fractionGold: fractionGold})
    }
    function zoomReset(top, bot, coinXMove, coinHeightFactor, a, b)
    {
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].zoomDestroy(coinXMove, coinHeightFactor, a, b);
        }
        root.resetTop = top; root.resetBot = bot;

        let comp; let obj;
        comp = Qt.createComponent("TileChoice.qml");
        obj = comp.createObject(root, {x: lastRect.x, choiceY: lastRect.y, width: lastRect.width
                                    , choiceHeight: lastRect.height,
                                fractionGold: fractionGold})
        obj.topShadow(topShadowLoc);
        obj.botShadow(botShadowLoc);
        obj.pauseDestroy();

        topShadowLoc = 0.0;
        botShadowLoc = 560.0;
        zoomResetDelay.start();
    }

    SequentialAnimation
    {
        id: zoomResetDelay
        PauseAnimation
        {
            duration: 4.5 * idea.speed
        }
        ScriptAction{script: createInitial();}
    }

    property double topShadowLoc: 0.0;
    property double botShadowLoc: 0.0;

    function topShadow(y)
    {
        topShadowLoc = y;
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].topShadow(y);
        }
    }
    function botShadow(y)
    {
        botShadowLoc = y;
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].botShadow(y);
        }
    }
    function createInitial()
    {
        let comp; let obj;
        comp = Qt.createComponent("TileChoice.qml");
        obj = comp.createObject(root, {x: 105, choiceY: 560*(1.0 - root.resetTop), width: tileRectWidth + 1,
                                    choiceHeight: 560*(root.resetTop - root.resetBot),
                                fractionGold: fractionGold})
        obj.topShadow(0);
        obj.botShadow(560.0);
    }

    property rect lastRect;

    function addTileChoice(x, y, width, height)
    {
        lastRect = Qt.rect(x, y, width, height);
        let comp; let obj;
        comp = Qt.createComponent("TileChoice.qml");
        obj = comp.createObject(root, {x: x, choiceY: y, width: width, choiceHeight: height,
                                    fractionGold: fractionGold})
        obj.topShadow(topShadowLoc);
        obj.botShadow(botShadowLoc);
    }

    Component.onCompleted:
    {
        reset();
    }
}
