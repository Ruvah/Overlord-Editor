#pragma once
#include <qwidget.h>

class ExplorerPanel :
	public QWidget, public Subject
{
	Q_OBJECT
	Q_DISABLE_COPY(ExplorerPanel)
public:
	ExplorerPanel(QWidget* parent = NULL);
	virtual ~ExplorerPanel() = default;

	virtual QPaintEngine* paintEngine() const { return NULL; };
	void SetDirectory(QString path);
	void Hide(bool enabled);
	QFileInfo GetSelectedFile()const { return m_SelectedFile; };
private:
	QFileSystemModel* m_pDir;
	QFileSystemModel* m_pFiles;

	QListView* m_pFileView;
	QTreeView* m_pDirectoryView;
	QHBoxLayout* m_pLayout;

	QFileInfo m_SelectedFile;

	QAction* m_pCreateNewPhysxMat;
	QAction* m_pCreateNewScene;


public slots:
	void OnDirSelect();
	void OnFileDblClick();
	void OnFileClick();
	void FileRenamed(const QString &path, const QString &oldName, const QString &newName);

	void NewPhysxMat();
	void NewScene();

};

