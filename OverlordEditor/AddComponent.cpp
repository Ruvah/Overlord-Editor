#include "stdafx.h"
#include "AddComponent.h"



AddComponent::AddComponent(std::function<void()> addComp, std::function<void()> remove)
	:m_AddComp{addComp},
	m_Remove{remove}
{
}

void AddComponent::Execute()
{
	Command::Execute();
	m_AddComp();
}

void AddComponent::Undo()
{
	Command::Undo();

	m_Remove();
}
