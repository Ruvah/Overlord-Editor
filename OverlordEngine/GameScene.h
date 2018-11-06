#pragma once

class GameObject;
class SceneManager;
class CameraComponent;
class PhysxProxy;
class PostProcessingMaterial;

class GameScene
{
public:
	GameScene(std::wstring sceneName);
	GameScene(const GameScene& other) = delete;
	GameScene(GameScene&& other) noexcept = delete;
	GameScene& operator=(const GameScene& other) = delete;
	GameScene& operator=(GameScene&& other) noexcept = delete;
	virtual ~GameScene();

	wstring GetName() { return m_SceneName; }
	
	void AddChild(GameObject* obj);
	void RemoveChild(GameObject* obj, bool deleteObject = true);
	const GameContext& GetGameContext() const { return m_GameContext; }

	PhysxProxy* GetPhysxProxy() const { return m_pPhysxProxy; }
	void SetActiveCamera(CameraComponent* pCameraComponent);

	// Update PP
	void AddPostProcessingEffect(PostProcessingMaterial* effect);
	void RemovePostProcessingEffect(PostProcessingMaterial* effect);



	std::vector<GameObject*> GetGameObjs() const { return m_pChildren; }


	CameraComponent* GetActiveCamera() { return m_pActiveCamera; };

	//Serialization 
	string Serialize();
	virtual void ParseFromYAML(string absolutePath);



protected:
	std::wstring m_SceneName;

	virtual void Initialize(const GameContext& gameContext) = 0;
	virtual void Update(const GameContext& gameContext) = 0;
	virtual void Draw(const GameContext& gameContext) = 0;

	virtual void SceneActivated() {}
	virtual void SceneDeactivated() {}

	bool m_UpdatePhysX;
	// Update PP
	std::vector<PostProcessingMaterial*> m_PostProcessingEffects;
	CameraComponent *m_pDefaultCamera, *m_pActiveCamera;


	virtual GameObject* ParseGameObject(YAML::Node gameObject, GameScene* scene);
	virtual GameObject* ParseFreeCam(YAML::Node gameObject, GameScene* scene);

	virtual void ParseComponent(YAML::Node component, GameObject* pParent);
protected:

	friend class SceneManager;

	virtual void RootInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	void RootUpdate();
	void RootDraw();
	void RootSceneActivated();
	void RootSceneDeactivated();
	void RootWindowStateChanged(int state, bool active) const;

	void RootInitGame(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	void CreateDefaultCam();

	std::vector<GameObject*> m_pChildren;
	GameContext m_GameContext;
	bool m_IsInitialized;


	// TODO: what if you have a game without physics? dependency should not exist here.
	PhysxProxy* m_pPhysxProxy;
};
