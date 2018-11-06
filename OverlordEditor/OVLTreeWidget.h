#pragma once
#include <qtreewidget.h>

class GameObjectItem;
class OVLTreeWidget :
	public QTreeWidget, public Subject
{
	Q_OBJECT
public:
	OVLTreeWidget(QWidget* parent = NULL);
	~OVLTreeWidget();

	void ChangeTitle(string title);

	GameObjectItem* AddRootItem(UINT gameObjTag);

	void AddChild(UINT childTag, GameObjectItem* parent);
	void AddChild(UINT obj, UINT parentTag);

	vector<GameObjectItem*> GetTreeItems() { return m_pTreeItems; };

	void SetCurrent(UINT pItem);

public slots:
	void CurrentSelectChanged();

private: 
	void dropEvent(QDropEvent* event) override;
	
	UINT m_pCurrent;
	vector<GameObjectItem*> m_pTreeItems;
};

