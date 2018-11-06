#pragma once
#include "Command.h"
class TrnsfCompPosChangeCmd :
	public Command
{
public:
	TrnsfCompPosChangeCmd(DirectX::XMFLOAT3 newPos,TransformComponent*pTrnsf);
	~TrnsfCompPosChangeCmd() = default;

	virtual void Execute() override;
	virtual void Undo() override;

private:
	DirectX::XMFLOAT3 m_Old, m_New;
	UINT m_ID;
};

