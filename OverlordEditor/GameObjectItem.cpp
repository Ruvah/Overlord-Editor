#include "stdafx.h"
#include "GameObjectItem.h"
#include <GameObject.h>



GameObjectItem::GameObjectItem(UINT gameObjID, QTreeWidget * pParent):
	QTreeWidgetItem(pParent),
	m_pGameObjectID(gameObjID)
{
	auto gameObj = GameObject::GetGameObject(gameObjID);
	setText(0, QString::fromStdWString(gameObj->GetTag()));

}

GameObjectItem::GameObjectItem(UINT gameObjID, GameObjectItem * pParent) :
	QTreeWidgetItem(pParent),
	m_pGameObjectID(gameObjID)
{
	auto gameObj = GameObject::GetGameObject(gameObjID);
	setText(0, QString::fromStdWString(gameObj->GetTag()));

}

GameObjectItem::~GameObjectItem()
{
}
