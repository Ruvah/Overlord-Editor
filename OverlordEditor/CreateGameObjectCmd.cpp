#include "stdafx.h"
#include "CreateGameObjectCmd.h"
#include <GameObject.h>
#include <SceneManager.h>
#include <GameScene.h>

CreateGameObjectCmd::CreateGameObjectCmd():

	m_pGameObject ( new GameObject()),
	Command()
{
	m_pGameObject->SetTag(L"GameObject");
}


CreateGameObjectCmd::~CreateGameObjectCmd()
{
	if (m_pGameObject)
	{
		delete m_pGameObject;
	}
}

void CreateGameObjectCmd::Execute()
{
	Command::Execute();
	auto pSceneMan = SceneManager::GetInstance();
	GameScene* pScene = pSceneMan->GetActiveScene();
	pScene->AddChild(m_pGameObject);
	Notify(OVLEvent::GameObjCreated, this);
}

void CreateGameObjectCmd::Undo()
{
	Command::Undo();
	auto pSceneMan = SceneManager::GetInstance();
	GameScene* pScene = pSceneMan->GetActiveScene();
	pScene->RemoveChild(m_pGameObject);
	Notify(OVLEvent::GameObjRemoved, this);

}
