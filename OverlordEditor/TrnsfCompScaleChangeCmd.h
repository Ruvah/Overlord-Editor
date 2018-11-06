#pragma once
#include "Command.h"
class TrnsfCompScaleChangeCmd :
	public Command
{
public:
	TrnsfCompScaleChangeCmd(DirectX::XMFLOAT3 newscale,TransformComponent*pTrnsf);
	~TrnsfCompScaleChangeCmd() = default;

	virtual void Execute() override;
	virtual void Undo() override;

private:
	DirectX::XMFLOAT3 m_Old, m_New;
	UINT m_ID;
};

