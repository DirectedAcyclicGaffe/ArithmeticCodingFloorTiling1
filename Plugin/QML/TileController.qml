import QtQuick 2.12

Item
{
    property double xFinal : 0;
    property double yFinal : 0;

    id: tileController;
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width;
    height: 560

    function addTile(isBronze, xLoc, yLoc)
    {
        let comp; let obj;
        comp = Qt.createComponent("MovingTile.qml");
        obj = comp.createObject(tileController,
                                {isBronze: isBronze})
        obj.animate(xLoc, yLoc, xFinal, yFinal);
    }
}
