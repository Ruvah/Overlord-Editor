#pragma once
class SelectCommand;
class GameObjectViewer;
class InspectorPanel:public QWidget, public Observer, public Subject
{
	Q_OBJECT
	Q_DISABLE_COPY(InspectorPanel)
public:

	InspectorPanel(QWidget* parent = NULL);
	virtual ~InspectorPanel();
	virtual QPaintEngine* paintEngine() const { return NULL; };

	virtual void OnNotify(const OVLEvent OEvent, Subject* subj = nullptr)override;

	void DeleteCurrent();


	QWidget* GetCurrentViewer()const { return m_pCurrentViewer; };



private:
	void ComponentRemoved(Subject* pSubj);
	void ComponentAdded(Subject* pSubj);
	void GameObjectRemoved(Subject* pSubj);
	void GameObjSelected(SelectCommand* command);
	void FileOpened(Subject* pSubj);

	void OpenPhysxMat(QFileInfo info);

	QGridLayout* m_pLayout;

	QWidget* m_pCurrentViewer;

	list<GameObjectViewer*> m_pGameObjectViewers;
};

