#pragma once
#include "Command.h"
class RenameGameObjectCmd: public Command
{
public:
	RenameGameObjectCmd(UINT tagID, QString newName);
	~RenameGameObjectCmd();

	virtual void Execute()override;
	
	virtual void Undo()override;

	GameObject* GetGameObject();
	UINT GetTag() { return m_TagID; }
private:
	QString m_OldName, m_NewName;
	UINT m_TagID;
	GameObject* m_pGameObject;
};

