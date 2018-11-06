#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OverlordEditor.h"
#include "DirectX11Widget.h"
#include "HierarchyPanel.h"

#include "InspectorPanel.h"
#include <ExplorerPanel.h>
class OverlordEditor : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	OverlordEditor(QWidget *parent = Q_NULLPTR);
	virtual void OnNotify(const OVLEvent event, Subject* subj = nullptr)override; 
private:
	Ui::OverlordEditorClass ui;
	QDockWidget* m_pCentralDock;
	DirectX11Widget* m_pMainSceneEditor;
	HierarchyPanel* m_pHierarchyPanel;
	InspectorPanel* m_pInspectorPanel;
	ExplorerPanel* m_pExplorerPanel;
	QString m_ProjectPath;

	void closeEvent(QCloseEvent * qEvent) override;

	void Restore();
	void OpenProject(QDir directory);
	void SaveScene();
protected:
	virtual void keyPressEvent(QKeyEvent* event) override;
	bool IsDirectoryProject(QDir project);
public slots:
	void NewProject();
	void OpenProject();
	void SaveProject();
};
