#include "stdafx.h"
#include "Command.h"


Command::Command()
{
}


Command::~Command()
{
}

void Command::Execute()
{
	auto cmdMan = CommandManager::GetInstance();
	cmdMan->AddUndo(this);
}

void Command::Undo()
{
	auto cmdMan = CommandManager::GetInstance();
	cmdMan->AddRedo(this);
}
