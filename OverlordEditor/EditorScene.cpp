
#include "stdafx.h"

#include "EditorScene.h"
#include "..\OverlordEngine\GameObject.h"
#include "..\OverlordEngine\Prefabs.h"
#include "..\OverlordEngine\Components.h"
#include "..\OverlordEngine\PhysxProxy.h"
#include "..\OverlordEngine\PhysxManager.h"
#include "..\OverlordEngine\ContentManager.h"
#include "..\OverlordEngine\MeshFilter.h"
#include "..\Materials\ColorMaterial.h"
#include "..\Materials\UberMaterial.h"
#include "..\OverlordEngine\ModelComponent.h"
#include <SphereColliderComponent.h>
#include <PhysxProxy.h>

#define FPS_COUNTER 1

EditorScene::EditorScene(void) :
	GameScene(L"EditorScene"),
	m_FpsInterval{},
	m_Path{}

{
}

EditorScene::EditorScene(QString sceneName, QString path):
	EditorScene()
{
	SetPath(path);
	m_SceneName = sceneName.toStdWString();
}


EditorScene::~EditorScene(void)
{
}

void EditorScene::SaveSceneText()
{
	string content = Serialize();
	QString fullPath = m_Path.append(QString::fromStdWString(m_SceneName)).append(QStringLiteral(".ovlscene"));
	QFile file{ fullPath };
	if (file.open(QIODevice::ReadWrite))
	{
		QTextStream stream{ &file };
		stream << QString::fromStdString(content);
	}
	file.close();
}

void EditorScene::SetPath(QString path)
{
	m_Path = path;
	m_Path.append(QStringLiteral("\\"));
}

void EditorScene::ParseFromYAML(string absolutePath)
{

	GameScene::ParseFromYAML(absolutePath);
	if (!m_pActiveCamera)
	{
		CreateDefaultCam();
	}
}

void EditorScene::Initialize(const GameContext& gameContext)
{

	//IMPORTANT
	
	gameContext.pGameTime->ForceElapsedUpperbound(true, 0.016);
	m_UpdatePhysX = false;

	
	
}

void EditorScene::Update(const GameContext& gameContext)
{

	m_FpsInterval += gameContext.pGameTime->GetElapsed();
	if (m_FpsInterval >= FPS_COUNTER)
	{
		m_FpsInterval -= FPS_COUNTER;
		//Logger::LogFormat(LogLevel::Info, L"FPS: %i", gameContext.pGameTime->GetFPS());
	}


}



void EditorScene::Draw(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void EditorScene::SceneActivated()
{
	Notify(OVLEvent::NewSceneActivated);
}

void EditorScene::ParseComponent(YAML::Node component, GameObject * pParent)
{
	string type = component["Type"].as<string>();
	if (type == "TransformComponent")
	{
		auto pTransf = pParent->GetComponent<TransformComponent>();
		pTransf->ParseFromNode(component);
	}
	else if (type == "CameraComponent")
	{
		
		CameraComponent* pExistCam = pParent->GetComponent<CameraComponent>();
		if (pExistCam)
		{
			pExistCam->ParseFromNode(component);
			if (pExistCam->IsActive())
			{
				SetActiveCamera(pExistCam);
			}
		}
		else
		{
			CameraComponent* pCamComp = new CameraComponent();
			pCamComp->ParseFromNode(component);
			pParent->AddComponent(pCamComp);
			if (pCamComp->IsActive())
			{
				SetActiveCamera(pCamComp);
			}
		}

	
	}
	else if (type == "SphereColliderComponent")
	{
		SphereColliderComponent* pSphereColl = new SphereColliderComponent();
		pSphereColl->ParseFromNode(component);
		pParent->AddComponent(pSphereColl);
	}
}

void EditorScene::RootInitialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	if (m_IsInitialized)
		return;

	RootInitGame(pDevice, pDeviceContext);

	
	m_IsInitialized = true;

}
