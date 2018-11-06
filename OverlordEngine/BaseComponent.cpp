#include "stdafx.h"
#include "BaseComponent.h"
#include "GameObject.h"

UINT BaseComponent::m_NextID{};
vector<BaseComponent*> BaseComponent::m_pAllComps{};

BaseComponent::BaseComponent() : m_pGameObject(nullptr), m_IsInitialized(false) {}

void BaseComponent::RootInitialize(const GameContext& gameContext)
{
	if(m_IsInitialized)
		return;

	Initialize(gameContext);
	AssignID();
	m_IsInitialized = true;
}

TransformComponent* BaseComponent::GetTransform() const
{
#if _DEBUG
	if(m_pGameObject == nullptr)
	{
		Logger::LogWarning(L"BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL.");
		return nullptr;
	}
#endif

	return m_pGameObject->GetTransform();
}

void BaseComponent::Serialize(YAML::Emitter & out)
{
	UNREFERENCED_PARAMETER(out);
}

void BaseComponent::AssignID()
{
	m_ID = m_NextID++;
	m_pAllComps.push_back(this);
}




