#pragma once
#include "Command.h"
class GameObjParentChangeCmd :
	public Command
{
public:
	GameObjParentChangeCmd(UINT obj,UINT parent);
	GameObjParentChangeCmd(UINT obj);

	~GameObjParentChangeCmd() = default;

	virtual void Execute() override;
	virtual void Undo() override;
	virtual void Redo() override;

private:
	UINT m_Obj, m_Parent, m_PrevParent;
	bool m_HadPrevParent,m_NoNewParent;
};

