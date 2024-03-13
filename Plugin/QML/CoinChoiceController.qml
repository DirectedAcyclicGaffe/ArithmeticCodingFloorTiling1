import QtQuick 2.12

Item
{
    id: root

    property double coinRectWidth: 70
    property bool stairs : true;

    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -1

    width: parent.width;
    height: 560

    function reset()
    {
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].destroy();
        }

        createInitial();
    }

    function createInitial()
    {
        let comp; let obj;
        comp = Qt.createComponent("CoinChoice.qml");
        let wid = stairs ? coinRectWidth + 9 : coinRectWidth + 1
        obj = comp.createObject(root, {x: 105, y: 0, width: wid, height: 560, stairs: stairs})
    }

    function zoomReset(coinXMove, coinHeightFactor, a, b)
    {
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].zoomDestroy(coinXMove, coinHeightFactor, a, b);
        }

        let comp; let obj;
        comp = Qt.createComponent("CoinChoice.qml");
        obj = comp.createObject(root, {x: lastRect.x, y: lastRect.y, width: lastRect.width
                                    , height: lastRect.height, stairs: stairs})
        obj.pauseDestroy();

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

    property rect lastRect;

    function addCoinChoice(x, y, width, height)
    {
        lastRect = Qt.rect(x, y, width, height);
        let comp; let obj;
        comp = Qt.createComponent("CoinChoice.qml");
        obj = comp.createObject(root, {x: x, y: y, width: width, height: height, stairs: stairs})
    }

    Component.onCompleted:
    {
        reset();
    }
}
