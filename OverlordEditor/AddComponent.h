#pragma once
#include <GameObjectViewer.h>
#include <Command.h>
class AddComponent:public Command 
{
public:
	AddComponent(std::function<void()> addComp, std::function<void()> remove);
	virtual ~AddComponent() = default;

	virtual void Execute() override;
	virtual void Undo() override;
private:
	
	std::function<void()> m_AddComp, m_Remove;
};

