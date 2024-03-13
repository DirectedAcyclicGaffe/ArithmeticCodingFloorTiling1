import QtQuick 2.12

Item
{
    id: root
    anchors.verticalCenter: parent.verticalCenter
    width: 280
    height: 560
    property double coinSize: 100

    function addCoin(isHeads, xLoc, yLoc)
    {
        let comp; let obj;
        comp = Qt.createComponent("MovingCoin.qml");
        obj = comp.createObject(root,
                                {isHeads: isHeads,
                                width: coinSize})
        obj.animate(xLoc, yLoc);
    }

    function reset()
    {
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].destroy();
        }
    }
}
