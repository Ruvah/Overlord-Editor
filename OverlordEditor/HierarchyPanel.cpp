#include "stdafx.h"
#include "HierarchyPanel.h"
#include <SceneManager.h>
#include "OVLTreeWidget.h"
#include <GameScene.h>
#include <GameObject.h>
#include "GameObjectItem.h"
#include "GameObjectViewer.h"
#include "RenameGameObjectCmd.h"
#include "SelectCommand.h"
#include <CreateGameObjectCmd.h>
HierarchyPanel::HierarchyPanel(QWidget * parent):
	QWidget(parent),
	m_pHierarchyTree{nullptr}
{	
	m_pCreateMenu = new QMenu(this);

	m_pCreateGameObj = new QAction("New Gameobject", this);
	QObject::connect(m_pCreateGameObj, SIGNAL(triggered()), this, SLOT(AddGameObj()));
	m_pCreateMenu->addAction(m_pCreateGameObj);

	m_pCreateBtn = new QPushButton(this);
	m_pCreateBtn->setObjectName(QStringLiteral("Createbtn"));
	m_pCreateBtn->setMenu(m_pCreateMenu);
	m_pCreateBtn->setText("Create");
	m_pCreateBtn->move(0, 0);
	
	m_pLayout = new QGridLayout(this);
	m_pLayout->setMargin(30);

}


HierarchyPanel::~HierarchyPanel()
{
}

void HierarchyPanel::SetupTree()
{
	auto scene = SceneManager::GetInstance()->GetActiveScene();
	if (!scene)
		return;
	if (m_pHierarchyTree)
		m_pHierarchyTree->deleteLater();
	
	m_pHierarchyTree = new OVLTreeWidget();
	m_pHierarchyTree->setHeaderLabel(QString::fromStdWString(scene->GetName()));
	
	auto pObjs = scene->GetGameObjs();
	for (auto pObj : pObjs)
	{
		if (!pObj->GetParent())
		{
			auto root = m_pHierarchyTree->AddRootItem(pObj->GetID());
			vector<GameObject*> pChildren = pObj->GetAllChildren();

			for (GameObject* pChild : pChildren)
			{
				m_pHierarchyTree->AddChild(pChild->GetID(),root);
			}
		}

	}

	m_pLayout->addWidget(m_pHierarchyTree);
	CopyObserversTo(m_pHierarchyTree);
	m_pHierarchyTree->AddObserver(this);
	
}

void HierarchyPanel::OnNotify(const OVLEvent OEvent, Subject* subj )
{
	auto command = dynamic_cast<SelectCommand*>(subj);

	switch (OEvent)
	{
	case OVLEvent::NewSceneActivated:
		SetupTree();
		break;
	case OVLEvent::GameObjectNameChange:
		if (m_pHierarchyTree)
		{
			auto renameCommand = dynamic_cast<RenameGameObjectCmd*>(subj);
			auto gameObject = renameCommand->GetGameObject();
			auto pTreeItems = m_pHierarchyTree->GetTreeItems();

			m_pHierarchyTree->currentItem()->setText(0,
				QString::fromStdWString(renameCommand->GetGameObject()->GetTag()));
		}
		break;
	case OVLEvent::GameObjectSelected:
		m_pHierarchyTree->SetCurrent(command->GetCurrent());
		break;

	case OVLEvent::GameObjRemoved:
		SetupTree();
		break;
	case OVLEvent::GameObjCreated:
		SetupTree();
		break;
	case OVLEvent::GameObjParentChanged:
		SetupTree();
		break;
	case OVLEvent::OpenScene:
		SetupTree();
		break;
	default:
		break;
	}
}



void HierarchyPanel::AddGameObj()
{
	CreateGameObjectCmd * pCreateCmd = new CreateGameObjectCmd();
	pCreateCmd->AddObserver(this);
	pCreateCmd->Execute();

}
