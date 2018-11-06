#include "stdafx.h"
#include "OVLTreeWidget.h"
#include "GameObjectItem.h"
#include "GameObject.h"
#include "SelectCommand.h"
#include <GameObjParentChangeCmd.h>

OVLTreeWidget::OVLTreeWidget(QWidget* parent ):
	QTreeWidget(parent)
{
	setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
	connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
		this, SLOT(CurrentSelectChanged(void)));
	
}


OVLTreeWidget::~OVLTreeWidget()
{
	m_pTreeItems.clear();
}

void OVLTreeWidget::ChangeTitle(string title)
{
	QString ColumnName{ QString::fromStdString(title) };
	setHeaderLabel(ColumnName);
}

GameObjectItem * OVLTreeWidget::AddRootItem(UINT gameObjTag)
{
	auto treeItem = new GameObjectItem(gameObjTag, this);
	addTopLevelItem(treeItem);
	m_pTreeItems.push_back(treeItem);
	return treeItem;
}



void OVLTreeWidget::AddChild(UINT  childTag, GameObjectItem * parent)
{
	auto treeChild = new GameObjectItem(childTag, parent);
	parent->addChild(treeChild);

	GameObject* pThisObj = GameObject::GetGameObject(childTag);
	vector<GameObject*> pChildren = pThisObj->GetAllChildren();

	for (GameObject* pChild : pChildren)
	{
		AddChild(pChild->GetID(), treeChild);
	}
}

void OVLTreeWidget::AddChild(UINT childObj, UINT parentTag)
{
	auto it = find_if(m_pTreeItems.begin(), m_pTreeItems.end(),
		[childObj](GameObjectItem* a) {return a->GetGameObjectID() == childObj; });
	if (it == m_pTreeItems.end())
		Logger::LogError(L"OVLTreeWidget::AddChild > parent gameobject is not part of the current hierarchy.");
	else
	{
		AddChild(childObj, *it);
	}
}

void OVLTreeWidget::SetCurrent(UINT  pItem)
{
	if ( m_pCurrent == pItem)
		return;

	m_pCurrent = pItem;
		auto inList = find_if(m_pTreeItems.begin(),m_pTreeItems.end(),
			[pItem](GameObjectItem* a)
		{
			return a->GetGameObjectID() == pItem;
		});
		if (inList != m_pTreeItems.end())
		{
			setCurrentItem(*inList);
		}
	
}

void OVLTreeWidget::dropEvent(QDropEvent * event)
{
	//QTreeView::dropEvent(event);
	QModelIndex newParent = indexAt(event->pos());

	

	auto pDragged = dynamic_cast<GameObjectItem*>(currentItem());
	
	auto pParent = dynamic_cast<GameObjectItem*>(itemFromIndex(newParent));
	if (pParent)
	{
		UINT draggedID = pDragged->GetGameObjectID(),
			parentID = pParent->GetGameObjectID();

		GameObjParentChangeCmd* pCommand = new GameObjParentChangeCmd(draggedID, parentID);
		CopyObserversTo(pCommand);
		pCommand->Execute();
	}
	else
	{
		UINT draggedID = pDragged->GetGameObjectID();

		GameObjParentChangeCmd* pCommand = new GameObjParentChangeCmd(draggedID);
		CopyObserversTo(pCommand);
		pCommand->Execute();
	}
}






void OVLTreeWidget::CurrentSelectChanged()
{

	QTreeWidgetItem* item = currentItem();
	auto current = dynamic_cast<GameObjectItem*>(currentItem());

	UINT newId = current->GetGameObjectID();
	SelectCommand* command = new SelectCommand(m_pCurrent,newId);
	CopyObserversTo(command);
	command->Execute();
}





