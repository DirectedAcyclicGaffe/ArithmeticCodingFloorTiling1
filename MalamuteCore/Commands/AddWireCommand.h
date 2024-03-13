#ifndef ADDWIRECOMMAND_H
#define ADDWIRECOMMAND_H

#include "UndoCommand.h"
#include <QJsonObject>

class Corkboard;

class AddWireCommand: public UndoCommand
{
public:
    AddWireCommand(const QJsonObject& obj,Corkboard* corkboard, bool actionNeeded);

    void undo() override;
    void redo() override;

private:
    Corkboard* m_corkboard;
    QJsonObject m_obj;
    bool m_actionNeeded;
};

#endif // ADDWIRECOMMAND_H
