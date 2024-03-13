#ifndef ADDCASINGCOMMAND_H
#define ADDCASINGCOMMAND_H

#include "UndoCommand.h"
#include <QJsonObject>

class Corkboard;

class AddCasingCommand: public UndoCommand
{
public:
    AddCasingCommand(const QJsonObject& obj, Corkboard* corkboard);

    void undo() override;
    void redo() override;

private:
    Corkboard* m_corkboard;
    QJsonObject m_obj;
};

#endif // ADDCASINGCOMMAND_H
