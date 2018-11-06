#pragma once
#include <typeinfo>
#include <functional>
#include <vector>
class GameObject;
class TransformComponent;
struct GameContext;


class BaseComponent
{
	friend class GameObject;
	void RootInitialize(const GameContext& gameContext);
public:
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
	BaseComponent();
	virtual ~BaseComponent() = default;

	GameObject* GetGameObject() const { return m_pGameObject; }
	TransformComponent* GetTransform() const;
	virtual void Serialize(YAML::Emitter& out) ;
	UINT GetID() { return m_ID; };
	void AssignID();
	virtual void ParseFromNode(YAML::Node& info) { UNREFERENCED_PARAMETER(info); };

	template <class T>
	static T* GetComponent(UINT ID)
	{
		const type_info& ti = typeid(T);
		
		if (ti == typeid(BaseComponent))
		{
			for (auto* comp : m_pAllComps)
			{
				if (comp && comp->GetID() == ID)
					return static_cast<T*>(comp);
			}
		}
		else
		{
			for (auto* comp : m_pAllComps)
			{
				if (comp && typeid(*comp) == ti && comp->GetID() == ID)
					return static_cast<T*>(comp);
			}
		}
		return nullptr;
	}
protected:

	virtual void Initialize(const GameContext& gameContext) = 0;
	virtual void Update(const GameContext& gameContext) = 0;
	virtual void Draw(const GameContext& gameContext) = 0;
	virtual void PostDraw(const GameContext&) {}
	

	GameObject* m_pGameObject;
	bool m_IsInitialized;
	UINT m_ID;



	static UINT m_NextID;
	static std::vector<BaseComponent*> m_pAllComps;
	

};


