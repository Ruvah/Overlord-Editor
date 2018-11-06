#pragma once
#include "stdafx.h"

class RenderTarget;


class OverlordGame
{
public:
	OverlordGame(const OverlordGame& other) = delete;
	OverlordGame(OverlordGame&& other) noexcept = delete;
	OverlordGame& operator=(const OverlordGame& other) = delete;
	OverlordGame& operator=(OverlordGame&& other) noexcept = delete;
	OverlordGame();
	virtual ~OverlordGame();

	static LRESULT CALLBACK WindowsProcedureStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static const GameSettings& GetGameSettings() { return m_GameSettings; }

	virtual HRESULT Run(HINSTANCE hInstance);

	void SetRenderTarget(RenderTarget* renderTarget);
	RenderTarget* GetRenderTarget() const;
	bool IsActive()const { return m_IsActive; };
protected:

	virtual void OnGamePreparing(GameSettings& gameSettings){ UNREFERENCED_PARAMETER(gameSettings); }
	virtual LRESULT WindowProcedureHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Initialize() = 0;
	bool m_IsActive;

protected:

	//FUNCTIONS
	//Initializations
	HRESULT InitializeAdapterAndOutput();
	HRESULT InitializeWindow();
	HRESULT InitializeDirectX();
	HRESULT InitializePhysX() const;
	HRESULT InitializeGame();
	HRESULT InitializeImGui();
	virtual void GameLoop() const;
	virtual void Gizmo() const {};

	//imgui
	void CleanUpImgui();

	//Windows Proc
	void StateChanged(int state, bool active);
	LRESULT WindowsProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//MEMBERS
	static GameSettings m_GameSettings;

	HINSTANCE m_hInstance;
	HWND m_WindowHandle;	
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapchain;
	IDXGIFactory* m_pDxgiFactory;
	RenderTarget* m_pDefaultRenderTarget, * m_pCurrentRenderTarget = nullptr; 
	D3D11_VIEWPORT m_Viewport{};
	
};

