#include "stdafx.h"
#include "DirectX11Widget.h"
#include "../OverlordEngine/RenderTarget.h"
#include "../OverlordEngine/SceneManager.h"
#include "../OverlordEngine/ContentManager.h"
#include "../OverlordEngine/PhysxManager.h"
#include "../OverlordEngine/DebugRenderer.h"
#include "../OverlordEngine/SpriteRenderer.h"
#include "../OverlordEngine/TextRenderer.h"
#include "../OverlordEngine/SoundManager.h"
#include "../OverlordEngine/imgui.h"

#include "../OverlordEngine/imgui_impl_dx11.h"
#include "../OverlordEngine/imgui_impl_win32.h"

#include "EditorScene.h"
#include <ExplorerPanel.h>
#include <GameScene.h>
#include <SceneManager.h>
#include <InputManager.h>

#include <SelectCommand.h>
#include <GameObject.h>
#include <TransformComponent.h>
#include <tiny-gizmo.hpp> 
#include <DebugRenderer.h>


DirectX11Widget::DirectX11Widget(QWidget* parent):
	QWidget(parent),
	m_IsInitialized{false},
	m_pCurrentObj{nullptr},
	gizmo_ctx(new tinygizmo::gizmo_context()),
	gizmo_state(new tinygizmo::gizmo_application_state())
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	InitializeEngine();

	m_UpdateTimer.setInterval(16);
	m_UpdateTimer.start();
	connect(&m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
}



DirectX11Widget::DirectX11Widget(Observer * pEvents, QWidget * parent):
	QWidget(parent),
	m_IsInitialized{ false },
	m_pObserver(pEvents),
	m_pCurrentObj{nullptr},
	gizmo_ctx(new tinygizmo::gizmo_context()),
	gizmo_state(new tinygizmo::gizmo_application_state())
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	InitializeEngine();

	m_UpdateTimer.setInterval(16);
	m_UpdateTimer.start();
	connect(&m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
}

DirectX11Widget::~DirectX11Widget()
{
}

void DirectX11Widget::OnNotify(const OVLEvent OEvent, Subject * pSubj)
{

	switch (OEvent)
	{
	case OVLEvent::OpenScene:
		if (pSubj)
		{
			auto pExplorer = dynamic_cast<ExplorerPanel*>(pSubj);
			QFileInfo info = pExplorer->GetSelectedFile();
			OpenScene(info);

		}
			break;
	case OVLEvent::GameObjectSelected:
		GameObjectSelected(pSubj);
		break;
	}
}

void DirectX11Widget::OnGamePreparing(GameSettings & gameSettings)
{
	gameSettings.Window.WindowHandle = HWND(winId());
	gameSettings.Window.Height = height();
	gameSettings.Window.Width = width();
	gameSettings.Window.AspectRatio = gameSettings.Window.Width / static_cast<float>(gameSettings.Window.Height);

	m_WindowHandle = HWND(winId());
}

void DirectX11Widget::InitializeEngine()
{

	//PREPARATION
	//***********
	OnGamePreparing(m_GameSettings);

	//INITIALIZE
	//**********
	auto hr = InitializeAdapterAndOutput();
	if (Logger::LogHResult(hr, L"OverlordGame::InitializeAdapterAndOutput")) return;

	hr = InitializeDirectX();
	if (Logger::LogHResult(hr, L"OverlordGame::InitializeDirectX")) return;

	hr = InitializePhysX();
	if (Logger::LogHResult(hr, L"OverlordGame::InitializePhysX")) return;

	hr = InitializeGame();
	if (Logger::LogHResult(hr, L"OverlordGame::InitializeGame")) return;

	//Imgui
	hr = InitializeImGui();
	if (Logger::LogHResult(hr, L"OverlordGame::InitializeGame")) return;


	

}

void DirectX11Widget::CreateBuffers()
{
	//Create the default rendertarget.
	m_pDefaultRenderTarget = new RenderTarget(m_pDevice);

	ID3D11Texture2D *pBackbuffer = nullptr;
	m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer));
	

	RENDERTARGET_DESC rtDesc;
	rtDesc.pColor = pBackbuffer;
	m_pDefaultRenderTarget->Create(rtDesc);
	

	//Set Default Rendertarget 
	SetRenderTarget(nullptr);

	m_Viewport.Width = static_cast<FLOAT>(m_GameSettings.Window.Width);
	m_Viewport.Height = static_cast<FLOAT>(m_GameSettings.Window.Height);
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &m_Viewport);
}

void DirectX11Widget::ClearBuffers()
{
	SafeDelete(m_pDefaultRenderTarget);
	
}

void DirectX11Widget::OpenScene(QFileInfo info) 
{
	QString sceneName{ info.baseName() };
	wstring wSceneName{ sceneName.toStdWString() };
	auto pSceneManager = SceneManager::GetInstance();
	if (pSceneManager->DoesSceneExist(wSceneName))
	{
		pSceneManager->SetActiveGameScene(wSceneName);
	}
	else
	{
		auto pSceneMan = SceneManager::GetInstance();
		for (auto pScene : pSceneMan->GetScenes())
		{
			pSceneMan->RemoveGameScene(pScene);
		}
		m_UpdateTimer.stop();
		EditorScene* newScene = new EditorScene(info.baseName(),info.absoluteFilePath());
		CopyObserversTo(newScene);
		pSceneManager->AddGameScene(newScene);
		pSceneManager->SetActiveGameScene(wSceneName);
		newScene->ParseFromYAML(info.absoluteFilePath().toStdString());
		m_UpdateTimer.start();


	}
}

void DirectX11Widget::Gizmo()const
{


}

void DirectX11Widget::GameObjectSelected(Subject * pSubj)
{
	auto cmd = static_cast<SelectCommand*>(pSubj);
	UINT id{ cmd->GetCurrent() };
	m_pCurrentObj = GameObject::GetGameObject(id);
	

}





void DirectX11Widget::Update()
{

	GameLoop();


}

void DirectX11Widget::Initialize()
{


	m_IsInitialized = true;

}



HRESULT DirectX11Widget::InitializeDirectX()
{
	//Create DX11 Device & Context
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	auto hr = D3D11CreateDevice(m_GameSettings.DirectX.pAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		createDeviceFlags,
		nullptr, 0,
		D3D11_SDK_VERSION,
		&m_pDevice,
		&featureLevel,
		&m_pDeviceContext);

	if (FAILED(hr))return hr;
	if (featureLevel < D3D_FEATURE_LEVEL_10_0)
	{
		Logger::LogHResult(-1, L"Feature level 10.0+ not supported on this device!");
		exit(-1);
	}
	if (featureLevel < D3D_FEATURE_LEVEL_11_0)
	{
		Logger::LogWarning(L"Feature level 10.1, some DirectX11 specific features won't be available on this device!");
	}

	//Create Swapchain descriptor
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc.Width = m_GameSettings.Window.Width;
	swapChainDesc.BufferDesc.Height = m_GameSettings.Window.Height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 60;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	// Update PP
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = m_WindowHandle;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	hr = m_pDxgiFactory->CreateSwapChain(m_pDevice, &swapChainDesc, &m_pSwapchain);
	if (FAILED(hr))	return hr;

	//Create the default rendertarget.
	m_pDefaultRenderTarget = new RenderTarget(m_pDevice);

	ID3D11Texture2D *pBackbuffer = nullptr;
	hr = m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer));
	if (FAILED(hr)) return hr;

	RENDERTARGET_DESC rtDesc;
	rtDesc.pColor = pBackbuffer;
	hr = m_pDefaultRenderTarget->Create(rtDesc);
	if (FAILED(hr)) return hr;

	//Set Default Rendertarget 
	SetRenderTarget(nullptr);

	Logger::LogFixMe(L"Viewport ownership, overlordgame");
	m_Viewport.Width = static_cast<FLOAT>(m_GameSettings.Window.Width);
	m_Viewport.Height = static_cast<FLOAT>(m_GameSettings.Window.Height);
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &m_Viewport);


	return S_OK;
}

void DirectX11Widget::resizeEvent(QResizeEvent * evt)
{

	if (!m_pDeviceContext)//it can happen that Qt calls resize b4 the ovl was set up
		return;
	HRESULT hr;
	m_pDeviceContext->OMSetRenderTargets(0, 0, 0);

	//release all outstanding references to the swap chain buffers
	m_pCurrentRenderTarget->CleanUp();
	
	hr = m_pSwapchain->ResizeBuffers(1, width(), height(), DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	if(FAILED(hr))
	{
		Logger::LogError(L"Error while resizing the swapchain buffer during the resize event");

	}
	ImGui_ImplDX11_CreateDeviceObjects();

	
	ID3D11Texture2D *pBackbuffer = nullptr;
	hr = m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer));
	if (FAILED(hr))
	{
		Logger::LogError(L"Error while getting the swapchains backbuffer during the resize event");


	}

	RENDERTARGET_DESC rtDesc;
	rtDesc.pColor = pBackbuffer;
	hr = m_pCurrentRenderTarget->Create(rtDesc);
	if (FAILED(hr))
	{
		Logger::LogError(L"Error while creating a new rendertarget during the resize event");


	}
	SetRenderTarget(m_pCurrentRenderTarget);

	m_Viewport.Width = width();
	m_Viewport.Height = height();
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	m_pDeviceContext->RSSetViewports(1, &m_Viewport);
}

void DirectX11Widget::paintEvent(QPaintEvent * evt)
{
	
}

void DirectX11Widget::focusInEvent(QFocusEvent * event)
{
	QWidget::focusInEvent(event);
	m_IsActive = true;


}

void DirectX11Widget::focusOutEvent(QFocusEvent * event)
{
	QWidget::focusOutEvent(event);
	//m_IsActive = false;

}




