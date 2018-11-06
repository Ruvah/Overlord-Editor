#pragma once
#include "../OverlordEngine/GameScene.h"

class EditorScene: public GameScene, public Subject
{

public:
	EditorScene(void);
	EditorScene(QString SceneName, QString Path);

	virtual ~EditorScene(void);

	void SaveSceneText();
	void SetPath(QString path);

	virtual void ParseFromYAML(string absolutePath)override;
protected:

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);
	virtual void SceneActivated();
	QString m_Path;

private:
	virtual void ParseComponent(YAML::Node component, GameObject* pParent) override;
	virtual void RootInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext) override ;


	GameObject* m_pTestObj1, *m_pTestObj2;
	float m_FpsInterval;
	bool m_Editorwindow;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EditorScene(const EditorScene &obj);
	EditorScene& operator=(const EditorScene& obj);
};

