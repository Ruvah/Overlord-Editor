#pragma once
#include "Command.h"
class DeleteGameObjCmd :
	public Command
{
public:
	DeleteGameObjCmd(UINT objID);
	~DeleteGameObjCmd();

	virtual void Execute()override;

	virtual void Undo()override;

	UINT GetID() { return m_ID; }
private:
	UINT m_ID;
};

