#pragma once
#include "Command.h"
class CreateGameObjectCmd :
	public Command
{
public:
	CreateGameObjectCmd();
	~CreateGameObjectCmd();

	virtual void Execute()override;

	virtual void Undo()override;


private:

	GameObject* m_pGameObject;
};

