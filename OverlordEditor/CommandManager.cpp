#include "stdafx.h"
#include "CommandManager.h"


CommandManager::CommandManager()
{
}


CommandManager::~CommandManager()
{
}

void CommandManager::AddUndo(Command * pCommand)
{
	m_pUndoStack.push_back(pCommand);
}

void CommandManager::AddRedo(Command * pCommand)
{
	m_pRedoStack.push_back(pCommand);
}

void CommandManager::Undo()
{
	if (m_pUndoStack.size() == 0)
		return;

	auto undoAction = m_pUndoStack.back();
	m_pUndoStack.pop_back();
	AddRedo(undoAction);
	undoAction->Undo();

}

void CommandManager::Redo()
{
	if (m_pRedoStack.size() == 0)
		return;

	auto redoAction = m_pRedoStack.back();
	m_pRedoStack.pop_back();
	AddUndo(redoAction);
	redoAction->Redo();
}

void CommandManager::ClearBuffers()
{
	for (auto pUndo : m_pUndoStack)
	{
		SafeDelete(pUndo);
	}
	for (auto pRedo : m_pRedoStack)
	{
		SafeDelete(pRedo);
	}
	m_pUndoStack.clear();
	m_pRedoStack.clear();
}


