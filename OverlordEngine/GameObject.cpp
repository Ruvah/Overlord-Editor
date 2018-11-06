#include "stdafx.h"
#include "GameObject.h"
#include "GameScene.h"
#include <algorithm>
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"

UINT GameObject::m_NextSceneID{};
vector<GameObject*> GameObject::m_pAllGameObjects{};

GameObject::GameObject():
	m_pChildren(std::vector<GameObject*>()),
	m_pComponents(std::vector<BaseComponent*>()),
	m_IsInitialized(false),
	m_IsActive(true),
	m_pParentScene(nullptr),
	m_pParentObject(nullptr),
	m_pTransform(nullptr),
	m_OnTriggerCallback(nullptr),
	m_Tag(L"GameObject"),
	m_UniqueID{},
	m_IDGiven{false}
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
	m_pAllGameObjects.push_back(this);
}

GameObject::~GameObject()
{
	for(BaseComponent* pComp: m_pComponents)
	{
		SafeDelete(pComp);
	}

	for(GameObject* pChild: m_pChildren)
	{
		SafeDelete(pChild);
	}

	auto it = find_if(m_pAllGameObjects.begin(), m_pAllGameObjects.end(), [this](GameObject* a) {return a == this; });
	if (it != m_pAllGameObjects.end())
	{
		m_pAllGameObjects.erase(it);
	}
	//DeleteLater
	for (BaseComponent* pComp : m_pDeleteLater)
	{
		SafeDelete(pComp);
	}
}

void GameObject::RootInitialize(const GameContext& gameContext)
{
	if(m_IsInitialized)
		return;

	if (!m_IDGiven)
	{
		m_UniqueID = m_NextSceneID++;
		m_IDGiven = true;
	}

	//User-Object Initialization
	Initialize(gameContext);

	
	//Root-Component Initialization
	for(BaseComponent* pComp: m_pComponents)
	{
		pComp->RootInitialize(gameContext);
	}

	//Root-Object Initialization
	for(GameObject* pChild: m_pChildren)
	{
		pChild->RootInitialize(gameContext);
	}

	//After Childrend and Component Initialize
	PostInitialize(gameContext);

	m_IsInitialized = true;
	
}

void GameObject::RootUpdate(const GameContext& gameContext)
{
	//User-Object Update
	Update(gameContext);
	
	//Component Update
	for(BaseComponent* pComp: m_pComponents)
	{
		pComp->Update(gameContext);
	}

	//Root-Object Update
	for(GameObject* pChild: m_pChildren)
	{
		pChild->RootUpdate(gameContext);
	}

	//DeleteLater
	for (BaseComponent* pComp : m_pDeleteLater)
	{
		SafeDelete(pComp);
	}
	m_pDeleteLater.clear();
}

void GameObject::RootDraw(const GameContext& gameContext)
{
	//User-Object Draw
	Draw(gameContext);

	//Component Draw
	for(BaseComponent* pComp: m_pComponents)
	{
		pComp->Draw(gameContext);
	}

	//Root-Object Draw
	for(GameObject* pChild: m_pChildren)
	{
		pChild->RootDraw(gameContext);
	}
}

void GameObject::RootPostDraw(const GameContext& gameContext)
{
	//Post-Draw
	PostDraw(gameContext);

	//Component Post-Draw
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->PostDraw(gameContext);
	}

	//Root-Object Post-Draw
	for (GameObject* pChild : m_pChildren)
	{
		pChild->RootPostDraw(gameContext);
	}
}

void GameObject::SetID(UINT id)
{
	if (!m_IDGiven)
	{
		m_UniqueID = id;
		m_IDGiven = true;
	}
}

void GameObject::Serialize(YAML::Emitter & out)
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Serialize(out);
	}

	out << YAML::Anchor("gameobject:" + to_string(m_UniqueID));

	out << YAML::BeginMap;
	out << YAML::Key << "Type";
	out << YAML::Value << "gameobject";
	out << YAML::Key << "Tag";
	out << YAML::Value << string{ m_Tag.begin(),m_Tag.end() };
	out << YAML::Key << "m_pParent";
	if (m_pParentObject)
	{
		out << YAML::Alias ("gameobject:" + to_string(m_pParentObject->GetID()));

	}
	else
	{
		out << YAML::Value << YAML::Null;

	}
	out << YAML::Key << "ID";
	out << YAML::Value << m_UniqueID;
	out << YAML::Key << "m_pComponents";
	out << YAML::BeginSeq;
	for (BaseComponent* pComp : m_pComponents)
	{
		out << YAML::Alias("component:"+to_string(pComp->GetID()));
	}
	out << YAML::EndSeq;

	out << YAML::EndMap;
	
	std::cout << "Emitter error: " << out.GetLastError() << "\n";

	for (GameObject* pChild : m_pChildren)
	{
		pChild->Serialize(out);
	}




}

void GameObject::AddChild(GameObject* obj)
{
#if _DEBUG
	if(obj->m_pParentObject)
	{
		if(obj->m_pParentObject == this)
			Logger::LogWarning(L"GameObject::AddChild > GameObject to add is already attached to this parent");
		else
			Logger::LogWarning(L"GameObject::AddChild > GameObject to add is already attached to another GameObject. Detach it from it's current parent before attaching it to another one.");

		return;
	}

	if(obj->m_pParentScene)
	{
		Logger::LogWarning(L"GameObject::AddChild > GameObject is currently attached to a GameScene. Detach it from it's current parent before attaching it to another one.");
		return;
	}
#endif

	obj->m_pParentObject = this;
	m_pChildren.push_back(obj);

	if(m_IsInitialized)
	{
		auto scene = GetScene();

		if(!scene)
		{
			Logger::LogWarning(L"GameObject::AddChild > Failed to initialize the added GameObject! (Parent GameObject is not part of a Scene)");
		}
		else
		{
			
			obj->RootInitialize(scene->GetGameContext());
		}
	}
}

void GameObject::RemoveChild(GameObject* obj)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), obj);

#if _DEBUG
	if(it == m_pChildren.end())
	{
		Logger::LogWarning(L"GameObject::RemoveChild > GameObject to remove is not attached to this GameObject!");
		return;
	}
#endif

	m_pChildren.erase(it);
	obj->m_pParentObject = nullptr;
}

void GameObject::AddComponent(BaseComponent* pComp)
{
#if _DEBUG
	if(typeid(*pComp) == typeid(TransformComponent) && HasComponent<TransformComponent>())
	{
		Logger::LogWarning(L"GameObject::AddComponent > GameObject can contain only one TransformComponent!");
		return;
	}

	for(auto *component : m_pComponents)
	{
		if(component == pComp)
		{
			Logger::LogWarning(L"GameObject::AddComponent > GameObject already contains this component!");
			return;
		}
	}
#endif
	
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
	if (!pComp->m_IsInitialized && m_IsInitialized)
	{
		auto context = SceneManager::GetInstance()->GetActiveScene()->GetGameContext();
		pComp->RootInitialize(context);
	}
}

void GameObject::RemoveComponent(BaseComponent* pComp, bool deleteLater )
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if (deleteLater)
	{
		m_pDeleteLater.push_back(*it);
	}

#if _DEBUG
	if(it == m_pComponents.end())
	{
		Logger::LogWarning(L"GameObject::RemoveComponent > Component is not attached to this GameObject!");
		return;
	}

	if(typeid(*pComp) == typeid(TransformComponent))
	{
		Logger::LogWarning(L"GameObject::RemoveComponent > TransformComponent can't be removed!");
		return;
	}
#endif

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}

void GameObject::OnTrigger(GameObject* triggerobject, GameObject* otherobject, TriggerAction action)
{
	if(m_OnTriggerCallback)
		m_OnTriggerCallback(triggerobject, otherobject, action);
}

GameScene* GameObject::GetScene()
{
	if(!m_pParentScene && m_pParentObject)
	{
		return m_pParentObject->GetScene();
	}

	return m_pParentScene;
}

void GameObject::SetOnTriggerCallBack(PhysicsCallback callback)
{
	m_OnTriggerCallback = callback;
}

GameObject * GameObject::GetGameObject(UINT id)
{
	auto it = find_if(m_pAllGameObjects.begin(), m_pAllGameObjects.end(), [id](GameObject* a)
	{
		return a->GetID() == id;
	});
	if (it != m_pAllGameObjects.end())
	{
		return *it;
	}

	return nullptr;
}
