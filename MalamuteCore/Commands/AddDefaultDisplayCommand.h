#ifndef ADDDEFAULTDISPLAYCOMMAND_H
#define ADDDEFAULTDISPLAYCOMMAND_H

#include "UndoCommand.h"
#include <QJsonObject>

class Corkboard;

class AddDefaultDisplayCommand: public UndoCommand
{
public:
    AddDefaultDisplayCommand(const QJsonObject& casingObj, const QJsonObject& wireObj, Corkboard* corkboard);

    void undo() override;
    void redo() override;

private:
    Corkboard* m_corkboard;
    QJsonObject m_casingObj;
    QJsonObject m_wireObj;
};

#endif // ADDDEFAULTDISPLAYCOMMAND_H
