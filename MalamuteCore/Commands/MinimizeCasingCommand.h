#ifndef MINIMIZECASINGCOMMAND_H
#define MINIMIZECASINGCOMMAND_H

#include "UndoCommand.h"
#include <QUuid>

class Corkboard;

class MinimizeCasingCommand : public UndoCommand
{
public:
    MinimizeCasingCommand(const QUuid& id, Corkboard* corkboard, bool oldState, bool actionNeeded = false);

    void undo() override;
    void redo() override;

private:
    Corkboard* m_corkboard;
    QUuid m_id;
    bool m_oldState;
    bool m_actionNeeded;
};

#endif // MINIMIZECASINGCOMMAND_H
