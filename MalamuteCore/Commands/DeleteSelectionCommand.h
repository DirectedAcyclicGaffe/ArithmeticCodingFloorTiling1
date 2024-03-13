#ifndef DELETESELECTIONCOMMAND_H
#define DELETESELECTIONCOMMAND_H

#include "UndoCommand.h"
#include <QJsonObject>
#include <QJsonArray>

class Corkboard;

class DeleteSelectionCommand: public UndoCommand
{
public:
    DeleteSelectionCommand(const QJsonObject& obj, Corkboard* corkboard);

    void undo() override;
    void redo() override;

private:
    Corkboard* m_corkboard;
    QJsonObject m_obj;
    QJsonArray m_extraWireArray;
};

#endif // REMOVESELECTIONCOMMAND_H
