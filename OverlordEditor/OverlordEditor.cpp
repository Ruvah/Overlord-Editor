#include "stdafx.h"
#include "OverlordEditor.h"
#include "GameObjectViewer.h"
#include <qfiledialog.h>
#include <NewProjectWindow.h>
#include <SceneManager.h>
#include <EditorScene.h>
#include <AssetManager.h>
#include <CommandManager.h>
OverlordEditor::OverlordEditor(QWidget *parent)
	: QMainWindow(parent)
	
{
	
	ui.setupUi(this);

	setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

	//HIERARCHYPANEL
	m_pHierarchyPanel = new HierarchyPanel(this);
	m_pHierarchyPanel->setObjectName(QStringLiteral("Hierarchy"));

	
	ui.DockLeft->setWidget(m_pHierarchyPanel);

	//INSPECTORPANEL
	m_pInspectorPanel = new InspectorPanel(this);
	m_pInspectorPanel->setObjectName(QStringLiteral("Inspector"));

	ui.DockRight->setWidget(m_pInspectorPanel);

	//EXPLORERPANEL
	m_pExplorerPanel = new ExplorerPanel(this);
	m_pExplorerPanel->setObjectName(QStringLiteral("Explorer"));

	ui.dockBottom->setWidget(m_pExplorerPanel);

	//MAIN VIEWPORT
	m_pCentralDock = new QDockWidget(this);
	m_pCentralDock->setWindowTitle("Scene");
	m_pCentralDock->setObjectName(QStringLiteral("CentralDock"));
	m_pMainSceneEditor = new DirectX11Widget((m_pHierarchyPanel),nullptr);
	m_pCentralDock->setWidget(m_pMainSceneEditor);
	m_pCentralDock->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);
	

	m_pMainSceneEditor->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

	setCentralWidget(m_pCentralDock);


	//subjects and observers
	m_pHierarchyPanel->AddObserver(m_pInspectorPanel);
	m_pHierarchyPanel->AddObserver(m_pMainSceneEditor);
	m_pInspectorPanel->AddObserver(m_pHierarchyPanel);
	m_pExplorerPanel->AddObserver(m_pMainSceneEditor);
	m_pExplorerPanel->AddObserver(m_pInspectorPanel);
	m_pMainSceneEditor->AddObserver(m_pHierarchyPanel);
	m_pExplorerPanel->AddObserver(this);

	//restoring window settings
	Restore();


	//Linking
	QObject::connect(ui.actionNew_Project, SIGNAL(triggered()),
		this, SLOT(NewProject()));
	QObject::connect(ui.actionOpen_Project, SIGNAL(triggered()),
		this, SLOT(OpenProject()));
	QObject::connect(ui.actionSaveProject, SIGNAL(triggered()),
		this, SLOT(SaveProject()));
}


void OverlordEditor::OnNotify(const OVLEvent event, Subject * subj)
{
	NewProjectWindow* pDialog = dynamic_cast<NewProjectWindow*>(subj);
	switch (event)
	{
	case OVLEvent::ProjectOpen:
		if (pDialog)
		{
			OpenProject(pDialog->GetProjectRoot());
		}
			break;
	case OVLEvent::OpenScene:
		auto pComMan = CommandManager::GetInstance();
		pComMan->ClearBuffers();
		break;

	}
}

void OverlordEditor::closeEvent(QCloseEvent * qEvent)
{
	QSettings settings("DAE", "OverlordEditor");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	QMainWindow::closeEvent(qEvent);
}

void OverlordEditor::Restore()
{
	QSettings settings("DAE", "OverlordEditor");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

}

void OverlordEditor::OpenProject(QDir directory)
{
	m_ProjectPath = directory.absolutePath();
	m_pExplorerPanel->SetDirectory(m_ProjectPath);
}

void OverlordEditor::SaveScene()
{
}

void OverlordEditor::keyPressEvent(QKeyEvent * qEvent)
{
	

	if (qEvent->modifiers() == Qt::CTRL)
	{

		auto key = qEvent->nativeVirtualKey();
		switch (key)
		{
		case Qt::Key_Z:
			CommandManager::GetInstance()->Undo();
			break;
		case Qt::Key_R:
			CommandManager::GetInstance()->Redo();
			break;
		case Qt::Key_S:
			GameScene *pScene = SceneManager::GetInstance()->GetActiveScene();
			EditorScene* pEditScene = dynamic_cast<EditorScene*>(pScene);
			pEditScene->SetPath(m_ProjectPath);
			pEditScene->SaveSceneText();
			break;
		}
	}
	else
	{
		auto key = qEvent->key();
		switch (key)
		{
		case Qt::Key::Key_Delete:
			m_pInspectorPanel->DeleteCurrent();
			break;

		}

	}
	


}

bool OverlordEditor::IsDirectoryProject(QDir project)
{
	return true;
}

void OverlordEditor::OpenProject()
{
	QDir directory = QFileDialog::getExistingDirectory();
	if (IsDirectoryProject(directory))
	{
		QString assetFile = directory.absolutePath().append("\\"+directory.dirName()+".ovl");
		AssetManager* pAssMan = AssetManager::GetInstance();
		pAssMan->SetFilePath(assetFile);
		pAssMan->Load();

		m_ProjectPath = directory.absolutePath();
		m_pExplorerPanel->SetDirectory(m_ProjectPath);
	}
}


void OverlordEditor::NewProject()
{
	auto pDialog = new QDockWidget(this);
	NewProjectWindow* pNewProject = new NewProjectWindow();
	pDialog->setWidget(pNewProject);
	pDialog->setFeatures(QDockWidget::DockWidgetFeature::DockWidgetFloatable| QDockWidget::DockWidgetFeature::DockWidgetClosable);
	addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, pDialog);
	pDialog->setFloating(true);
	pDialog->resize(300, 300);

	pNewProject->AddObserver(this);
	
}

void OverlordEditor::SaveProject()
{
	AssetManager* pAssMan = AssetManager::GetInstance();
	pAssMan->Write();

	auto pScenes = SceneManager::GetInstance()->GetScenes();
	for (auto pScene : pScenes)
	{
		EditorScene* pEditScene = dynamic_cast<EditorScene*>(pScene);

		//pEditScene->SaveSceneText();
	}
}

