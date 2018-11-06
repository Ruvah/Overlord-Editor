#pragma once
#include "Command.h"
class TrnsfCompRotChangeCmd :
	public Command
{
public:
	TrnsfCompRotChangeCmd(DirectX::XMFLOAT3 newrot, TransformComponent*pTrnsf);
	~TrnsfCompRotChangeCmd() = default;

	virtual void Execute() override;
	virtual void Undo() override;

private:
	DirectX::XMFLOAT3 m_Old, m_New;
	UINT m_ID;
};


