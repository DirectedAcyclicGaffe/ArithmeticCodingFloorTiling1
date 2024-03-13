#include "UndoStack.h"

UndoStack::UndoStack() :
    m_index(0)
{

}

void UndoStack::push(UndoCommand *command)
{
    while(m_commands.length() > m_index)
        m_commands.pop_back();
    m_commands.push_back(command);
    command->redo();
    m_index++;

}

void UndoStack::undo()
{
    if(m_index > 0)
    {
        m_commands[m_index - 1]->undo();
        m_index--;
    }
}

void UndoStack::redo()
{
    if(m_index < m_commands.length() )
    {
        m_index++;
        m_commands[m_index - 1]->redo();
    }
}

void UndoStack::clear()
{
    m_index = 0;
    m_commands.clear();;
}

bool UndoStack::canUndo() const
{
    return m_index > 0;
}

bool UndoStack::canRedo() const
{
    return m_index < m_commands.length();
}
