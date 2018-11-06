#pragma once
#include <qtreewidget.h>
class GameObjectItem :
	public QTreeWidgetItem
{
public:
	GameObjectItem(UINT gameObjID, QTreeWidget* pParent = nullptr);

	GameObjectItem(UINT gameObjID, GameObjectItem * pParent);

	virtual ~GameObjectItem();

	
	UINT GetGameObjectID()const { return m_pGameObjectID; }
private:

	UINT m_pGameObjectID;
};

