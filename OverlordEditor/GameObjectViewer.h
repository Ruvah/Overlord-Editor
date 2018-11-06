#pragma once
class ComponentInspector;
class GameObjectViewer: public QWidget, public Subject,
	public Observer
{
	Q_OBJECT
	Q_DISABLE_COPY(GameObjectViewer)
public:
	GameObjectViewer(QWidget* parent = NULL);
	virtual ~GameObjectViewer();
	virtual QPaintEngine* paintEngine() const { return NULL; };

	QString GetGameObjTag()const {  return (m_pObjectName->text()); }
	void SetGameObject(GameObject* pObject);
	UINT GetGameObjID()const;


	void Refresh();
	void DeleteLast();
	virtual void OnNotify(const OVLEvent OEvent, Subject* pSubject)override;


	template <class T>
	T* GetInspector()
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		return nullptr;
	}

	template <class T>
	std::vector<T*> GetInspectors()
	{
		const type_info& ti = typeid(T);
		std::vector<T*> components;

		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				components.push_back(static_cast<T*>(component));
		}

		return components;
	}

private:
	friend class InspectorPanel;
	QLineEdit* m_pObjectName;
	QVBoxLayout* m_pLayout;
	QHBoxLayout* m_pNameLayout;
	GameObject* m_pObject;
	vector <ComponentInspector*> m_pComponents;
	QMenu* m_pAddMenu;
	QAction *m_pAddSphereCollider;
	QPushButton *m_pAddButton;

	void OpenComponents();
	void OpenSphereColliders();
	void PlaceButtonsBottom();
	void AddSphereColliderComp();
	void AddComp(UINT id);
	void DeleteComp(UINT id);

public slots:
	void EditObjectTag();
	void AddSphereCollider();
};

