#include "stdafx.h"
#include "GameObjParentChangeCmd.h"
#include <GameObject.h>
#include <SceneManager.h>
#include <GameScene.h>

GameObjParentChangeCmd::GameObjParentChangeCmd(UINT obj, UINT parent):
	Command(),
	m_Parent{parent},
	m_Obj{obj},
	m_PrevParent{0},
	m_NoNewParent{false},
	m_HadPrevParent{false}
{
	GameObject* pObj = GameObject::GetGameObject(obj);
	GameObject* pCurrParent = pObj->GetParent();
	if (pCurrParent)
	{
		m_PrevParent = pCurrParent->GetID();
		m_HadPrevParent = true;
	}
}

GameObjParentChangeCmd::GameObjParentChangeCmd(UINT obj):
	Command(),
	m_Parent{ 0 },
	m_Obj{ obj },
	m_PrevParent{ 0 },
	m_NoNewParent{ true },
	m_HadPrevParent{ false }
{
	GameObject* pObj = GameObject::GetGameObject(obj);
	GameObject* pCurrParent = pObj->GetParent();
	if (pCurrParent)
	{
		m_PrevParent = pCurrParent->GetID();
		m_HadPrevParent = true;
	}
}

void GameObjParentChangeCmd::Execute()
{
	Command::Execute();
	GameObject* pObj = GameObject::GetGameObject(m_Obj);
	auto pSceneMan = SceneManager::GetInstance();
	GameScene* pScene = pSceneMan->GetActiveScene();

	if (m_HadPrevParent)
	{
		GameObject* pCurrParent = pObj->GetParent();
		if (pCurrParent)
		{
			pCurrParent->RemoveChild(pObj);
		}
	}
	else
	{
		pScene->RemoveChild(pObj,false);
	}

	if (m_NoNewParent)
	{
		pScene->AddChild(pObj);
	}
	else
	{
		GameObject* pParent = GameObject::GetGameObject(m_Parent);

		pParent->AddChild(pObj);
	}
	Notify(OVLEvent::GameObjParentChanged, this);

}

void GameObjParentChangeCmd::Undo()
{
	Command::Undo();
	GameObject* pObj = GameObject::GetGameObject(m_Obj);
	if (!m_NoNewParent)
	{
		GameObject* pCurrParent = pObj->GetParent();
		pCurrParent->RemoveChild(pObj);

	}
	if (m_HadPrevParent)
	{
		GameObject* pParent = GameObject::GetGameObject(m_PrevParent);
		pParent->AddChild(pObj);

	}
	else
	{
		auto pSceneMan = SceneManager::GetInstance();
		GameScene* pScene = pSceneMan->GetActiveScene();
		pScene->AddChild(pObj);
	}

	Notify(OVLEvent::GameObjParentChanged, this);


}

void GameObjParentChangeCmd::Redo()
{
	Execute();
	Notify(OVLEvent::GameObjParentChanged, this);

}



