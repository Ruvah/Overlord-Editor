#pragma once
#include "Command.h"
class ComponentInspector;
class DeleteComponent :
	public Command
{
public:
	DeleteComponent(ComponentInspector* pInsp);
	virtual ~DeleteComponent();

	virtual void Execute() override;
	virtual void Undo() override;

	UINT GetID() const { return m_ID; }
	
private:
	UINT m_ID;
};

