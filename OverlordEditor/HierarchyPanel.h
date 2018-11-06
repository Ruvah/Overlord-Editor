class GameObjectItem;
class OVLTreeWidget;
class HierarchyPanel :
	public QWidget, public Subject, public Observer
{
	Q_OBJECT
	Q_DISABLE_COPY(HierarchyPanel)
public:
	HierarchyPanel(QWidget* parent = NULL);
	virtual ~HierarchyPanel();
	virtual QPaintEngine* paintEngine() const { return NULL; };

	void SetupTree();
	void OnNotify(const OVLEvent OEvent, Subject* subj = nullptr)override;
	
private:

	QPushButton* m_pCreateBtn;
	QGridLayout* m_pLayout;

	//gameobject creation
	QMenu* m_pCreateMenu;
	QAction* m_pCreateGameObj;

	//tree
	OVLTreeWidget* m_pHierarchyTree;

public slots:
	void AddGameObj();
	
};

