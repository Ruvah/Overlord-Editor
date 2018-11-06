#pragma once
class OVLTreeWidget;
class SelectCommand: public Command
{
public:
	SelectCommand( UINT currentObj, UINT newObj);
	virtual ~SelectCommand()= default;

	virtual void Execute() override;
	virtual void Undo() override;


	UINT GetCurrent() { return m_Curr; };
private:
	
	UINT m_NewObj, m_PrevObj,m_Curr;
};

