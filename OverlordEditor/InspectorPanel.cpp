#include "stdafx.h"
#include "InspectorPanel.h"
#include "GameObjectViewer.h"
#include "OVLTreeWidget.h"
#include "GameObjectItem.h"
#include <GameObject.h>
#include "SelectCommand.h"
#include <ExplorerPanel.h>
#include <PhysXMaterialViewer.h>
#include <DeleteComponent.h>
#include <DeleteGameObjCmd.h>
InspectorPanel::InspectorPanel(QWidget* parent):
	m_pCurrentViewer(nullptr)
{
	m_pLayout = new QGridLayout(this);

	m_pLayout->setMargin(10);

}


InspectorPanel::~InspectorPanel()
{
}

void InspectorPanel::OnNotify(const OVLEvent OEvent, Subject* subj )
{

	auto command = dynamic_cast<SelectCommand*>(subj);

	switch (OEvent)
	{
	case OVLEvent::GameObjectSelected:

		if (command)
		{
			GameObjSelected(command);
		}
		
		break;
	case OVLEvent::GameObjectNameChange:
		dynamic_cast<GameObjectViewer*>(m_pCurrentViewer)->Refresh();
		break;

	case OVLEvent::OpenFile:
		FileOpened(subj);
		break;
	case OVLEvent::ComponentDeleted:
		ComponentRemoved(subj);
		break;
	case OVLEvent::ComponentAdded:
		ComponentAdded(subj);
		break;
	case OVLEvent::GameObjRemoved:
		GameObjectRemoved(subj);
		break;
	default:
		break;
	}
}

void InspectorPanel::DeleteCurrent()
{
	GameObjectViewer* pView = dynamic_cast<GameObjectViewer*>(m_pCurrentViewer);
	if (pView)
	{
		DeleteGameObjCmd* pCmd = new DeleteGameObjCmd(pView->GetGameObjID());
		CopyObserversTo(pCmd);
		pCmd->AddObserver(this);
		pCmd->Execute();
	}
}

void InspectorPanel::ComponentRemoved(Subject * pSubj)
{
	GameObjectViewer* pView = dynamic_cast<GameObjectViewer*>(m_pCurrentViewer);
	if (pView)
	{
		auto pCmd = static_cast<DeleteComponent*>(pSubj);
		pView->DeleteComp(pCmd->GetID());
	}
}

void InspectorPanel::ComponentAdded(Subject * pSubj)
{
	GameObjectViewer* pView = dynamic_cast<GameObjectViewer*>(m_pCurrentViewer);
	if (pView)
	{
		auto pCmd = static_cast<DeleteComponent*>(pSubj);
		pView->AddComp(pCmd->GetID());
	}
}

void InspectorPanel::GameObjectRemoved(Subject * pSubj)
{
	auto pCmd = static_cast<DeleteGameObjCmd*>(pSubj);
	GameObjectViewer* pView = dynamic_cast<GameObjectViewer*>(m_pCurrentViewer);
	if (pView)
	{
		if (pView->GetGameObjID() == pCmd->GetID())
		{
			pView = nullptr;
		}
	}
	auto findInGViewers = [&pCmd](GameObjectViewer*pView)
	{
		return pView->GetGameObjID() == pCmd->GetID();
	};
	auto it = find_if(m_pGameObjectViewers.begin(), m_pGameObjectViewers.end(),
		findInGViewers);
	if (it != m_pGameObjectViewers.end())
	{
		(*it)->deleteLater();
		m_pGameObjectViewers.erase(it);
	}

}

void InspectorPanel::GameObjSelected(SelectCommand * command)
{

	auto current = command->GetCurrent();
	auto findInGViewrs = [current](GameObjectViewer* pView) 
	{
		return current == pView->GetGameObjID();
	};
	auto it = find_if(m_pGameObjectViewers.begin(), m_pGameObjectViewers.end(),
		findInGViewrs);
	if (it != m_pGameObjectViewers.end())
	{
		if (m_pCurrentViewer)
		{
			m_pCurrentViewer->setVisible(false);
			(*it)->setVisible(true);
			m_pCurrentViewer = (*it);
		}
	}
	else
	{
		if (m_pCurrentViewer)
		{
			m_pCurrentViewer->setVisible(false);
			m_pCurrentViewer = nullptr;
		}
		auto currGameObj = GameObject::GetGameObject(current);
		if (currGameObj)
		{
			GameObjectViewer* pView = new GameObjectViewer(this);
			pView->AddObserver(this);
			pView->SetGameObject(currGameObj);
			m_pCurrentViewer = pView;
			CopyObserversTo(pView);
			m_pLayout->addWidget(m_pCurrentViewer);

		}
	}
}

void InspectorPanel::FileOpened(Subject * pSubj)
{
	auto pExplorerPanel = dynamic_cast<ExplorerPanel*>(pSubj);

	QFileInfo info = pExplorerPanel->GetSelectedFile();
	if (info.completeSuffix() == "ovlphysxmat")
	{
		OpenPhysxMat(info);
	}
}

void InspectorPanel::OpenPhysxMat(QFileInfo info)
{
	QFile file{ info.absolutePath() };
	if (file.exists())
	{
		if (m_pCurrentViewer)
		{
			delete m_pCurrentViewer;
			m_pCurrentViewer = nullptr;
		}
		PhysXMaterialViewer* pView = new PhysXMaterialViewer(info, this);
		m_pCurrentViewer = pView;
		m_pLayout->addWidget(m_pCurrentViewer);

	}
}


