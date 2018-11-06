#pragma once
#include <Singleton.h>
class Command;
class CommandManager :
	public Singleton<CommandManager>
{
public:

	~CommandManager();
	void AddUndo(Command* pCommand);
	void AddRedo(Command* pCommand);

	void Undo();
	void Redo();

	void ClearBuffers();
private:
	friend class Singleton<CommandManager>;
	CommandManager();

	vector<Command*> m_pUndoStack;
	vector<Command*> m_pRedoStack;

};

