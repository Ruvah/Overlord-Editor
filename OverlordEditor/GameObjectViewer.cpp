#include "stdafx.h"
#include "GameObjectViewer.h"
#include "GameObject.h"
#include "RenameGameObjectCmd.h"
#include <TransformComponentInspector.h>
#include <TransformComponent.h>
#include <SphereColliderComponent.h>
#include <SphereColliderComponentInspector.h>
#include <BaseComponent.h>
#include <AddComponent.h>
#include <DeleteComponent.h>
GameObjectViewer::GameObjectViewer(QWidget* parent):
	m_pObject(nullptr),
	m_pNameLayout ( new QHBoxLayout()),
	m_pLayout(new QVBoxLayout(this)),
	m_pAddMenu(new QMenu(this)),
	m_pAddSphereCollider(new QAction("Add SphereCollider",this)),
	m_pAddButton(new QPushButton("AddComponent",this))
{

	auto pLabelName = new QLabel(this);
	pLabelName->setText(QStringLiteral("Name: "));
	m_pNameLayout->addWidget(pLabelName);
	m_pObjectName = new QLineEdit(this);
	m_pObjectName->setMaximumSize(500, 30);
	m_pObjectName->setMinimumSize(100, 30);
	setSizePolicy(QSizePolicy::Policy::Ignored,QSizePolicy::Policy::MinimumExpanding);
	m_pNameLayout->addWidget(m_pObjectName);
	m_pLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
	m_pLayout->setAlignment(Qt::AlignTop);
	m_pLayout->addLayout(m_pNameLayout);
	connect(m_pObjectName, &QLineEdit::returnPressed,this,&GameObjectViewer::EditObjectTag);

	QObject::connect(m_pAddSphereCollider, SIGNAL(triggered()), this, SLOT(AddSphereCollider()));
	m_pAddMenu->addAction(m_pAddSphereCollider);
	m_pAddButton->setMenu(m_pAddMenu);
}


GameObjectViewer::~GameObjectViewer()
{
}

void GameObjectViewer::SetGameObject(GameObject * pObject)
{
	m_pObject = pObject;
	m_pObjectName->setText(QString::fromStdWString(pObject->GetTag()));
	OpenComponents();
	m_pLayout->addWidget(m_pAddButton);
}

UINT GameObjectViewer::GetGameObjID() const
{
	return (m_pObject->GetID());
}

void GameObjectViewer::Refresh()
{
	if (!m_pObject)
		m_pObjectName->setText(QStringLiteral(""));
	else
	{
		m_pObjectName->setText(QString::fromStdWString(m_pObject->GetTag()));
	}
}

void GameObjectViewer::DeleteLast()
{
	ComponentInspector* last = m_pComponents.back();
	UINT id{ last->GetID() };
	auto comp{ BaseComponent::GetComponent<BaseComponent>(id) };
	m_pObject->RemoveComponent(comp,true);

	m_pLayout->removeWidget(last);
	last->deleteLater();
	m_pComponents.pop_back();
}

void GameObjectViewer::OnNotify(const OVLEvent OEvent, Subject * pSubject)
{
	auto pTransf = GetInspector<TransformComponentInspector>();

	switch (OEvent)
	{
	case OVLEvent::TransformCompChanged:
		pTransf->Refresh();
		break;

	}
}

void GameObjectViewer::OpenComponents()
{
	TransformComponent* pTransf = m_pObject->GetComponent<TransformComponent>();
	TransformComponentInspector* pTransfInspector{ new TransformComponentInspector(pTransf,this) };
	//pTransfInspector->AddObserver(this);
	m_pComponents.push_back(pTransfInspector);
	m_pLayout->addWidget(pTransfInspector);

	OpenSphereColliders();
}

void GameObjectViewer::OpenSphereColliders()
{
	vector<SphereColliderComponent*> pCols = m_pObject->GetComponents<SphereColliderComponent>();
	for (auto pCol : pCols)
	{
		SphereColliderComponentInspector* pInspec = new SphereColliderComponentInspector(pCol, this);
		//pInspec->AddObserver(this);
		CopyObserversTo(pInspec);
		m_pComponents.push_back(pInspec);
		m_pLayout->addWidget(pInspec);
		PlaceButtonsBottom();
	}
}

void GameObjectViewer::PlaceButtonsBottom()
{
	m_pLayout->removeWidget(m_pAddButton);
	m_pLayout->addWidget(m_pAddButton);

}

void GameObjectViewer::AddSphereColliderComp()
{
	SphereColliderComponent* pSphereCol = new SphereColliderComponent();
	m_pObject->AddComponent(pSphereCol);
	SphereColliderComponentInspector* pInspec = new SphereColliderComponentInspector(pSphereCol, this);
	//pInspec->AddObserver(this);
	CopyObserversTo(pInspec);
	m_pComponents.push_back(pInspec);
	m_pLayout->addWidget(pInspec);
	PlaceButtonsBottom();
}

void GameObjectViewer::AddComp(UINT id)
{
	BaseComponent* pComp = BaseComponent::GetComponent<BaseComponent>(id);
	if (pComp)
	{
		m_pObject->AddComponent(pComp);
		for (auto pInsp : m_pComponents)
		{
			pInsp->deleteLater();

		}
		m_pComponents.clear();
		OpenComponents();
	}
}

void GameObjectViewer::DeleteComp(UINT id)
{
	BaseComponent* pComp = BaseComponent::GetComponent<BaseComponent>(id);
	if (pComp)
	{
		auto findInspec = [&id](ComponentInspector* a)
		{
			return a->GetID() == id;
		};
		auto it = find_if(m_pComponents.begin(), m_pComponents.end(),
			findInspec);
		if (it != m_pComponents.end())
		{
			(*it)->deleteLater();
			m_pComponents.erase(it);
			m_pObject->RemoveComponent(pComp);
		}
	}
}



void GameObjectViewer::AddSphereCollider()
{
	AddComponent* pCommand = new AddComponent(std::bind(&GameObjectViewer::AddSphereColliderComp,this),
		std::bind(&GameObjectViewer::DeleteLast, this));
	pCommand->Execute();
}

void GameObjectViewer::EditObjectTag()
{

	RenameGameObjectCmd* pCommand = new RenameGameObjectCmd(m_pObject->GetID(), m_pObjectName->text());
	CopyObserversTo(pCommand);
	pCommand->Execute();
	m_pObjectName->clearFocus();
}


