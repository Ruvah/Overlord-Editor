#include "stdafx.h"
#include "DeleteGameObjCmd.h"
#include <GameObject.h>
#include <SceneManager.h>
#include <GameScene.h>

DeleteGameObjCmd::DeleteGameObjCmd(UINT objID) :
	m_ID{objID},
	Command()
{
}

DeleteGameObjCmd::~DeleteGameObjCmd()
{
	GameObject* pObj = GameObject::GetGameObject(m_ID);
	delete pObj;
}

void DeleteGameObjCmd::Execute()
{
	Command::Execute();
	GameObject* pObj = GameObject::GetGameObject(m_ID);
	auto pSceneMan = SceneManager::GetInstance();
	GameScene* pScene = pObj->GetScene();
	if (pScene)
	{
		pScene->RemoveChild(pObj, false);
	}
	else
	{
		GameObject* pParent = pObj->GetParent();
		pParent->RemoveChild(pObj);
	}
	Notify(OVLEvent::GameObjRemoved, this);

}

void DeleteGameObjCmd::Undo()
{
	Command::Undo();
	GameObject* pObj = GameObject::GetGameObject(m_ID);
	auto pSceneMan = SceneManager::GetInstance();
	GameScene* pScene = pSceneMan->GetActiveScene();
	pScene->AddChild(pObj);
	Notify(OVLEvent::GameObjCreated, this);

}
