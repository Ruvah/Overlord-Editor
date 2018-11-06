#pragma once
#include "../OverlordEngine/OverlordGame.h"

namespace tinygizmo
{
	class gizmo_application_state;
	class gizmo_context;
}
class HierarchyPanel;
class DirectX11Widget: public QWidget, public OverlordGame, public Observer, public Subject
{
	Q_OBJECT
	Q_DISABLE_COPY(DirectX11Widget)
public:
	DirectX11Widget(QWidget* parent = NULL);
	DirectX11Widget(Observer* pEvents,QWidget* parent = NULL);

	virtual ~DirectX11Widget();
	virtual QPaintEngine* paintEngine() const { return NULL; };
	virtual void OnNotify(const OVLEvent OEvent,Subject* pSubj) override;

protected:

	//widget
	virtual void resizeEvent(QResizeEvent * evt) override;
	virtual void paintEvent(QPaintEvent* evt) override;
	virtual void focusInEvent(QFocusEvent* event)override;
	virtual void focusOutEvent(QFocusEvent* event)override;


	//overlordgame
	virtual void OnGamePreparing(GameSettings& gameSettings);

	virtual void Initialize() override;
	
	//Dx11Widget
	virtual void InitializeEngine();

	
private:
	HRESULT Run(HINSTANCE hInstance) { return S_OK; }

	HRESULT InitializeDirectX();
	virtual LRESULT WindowProcedureHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return -1; };

	void CreateBuffers();
	void ClearBuffers();
	void OpenScene(QFileInfo info);
	virtual void Gizmo()const override;
	void GameObjectSelected(Subject* pSubj);


	bool m_IsInitialized;

	QTimer m_UpdateTimer;

	Observer* m_pObserver;
	GameObject* m_pCurrentObj;
private slots:
	void Update();
private:
	tinygizmo::gizmo_application_state* gizmo_state;
	tinygizmo::gizmo_context* gizmo_ctx;
};





