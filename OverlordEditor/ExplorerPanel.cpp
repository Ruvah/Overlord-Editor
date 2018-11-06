#include "stdafx.h"
#include "ExplorerPanel.h"
#include <PhysxManager.h>
#include <Serialization.h>
#include <AssetManager.h>

ExplorerPanel::ExplorerPanel(QWidget* parent):
	QWidget(parent),
	m_pDirectoryView(new QTreeView(this)),
	m_pFileView ( new QListView(this)),
	m_pDir ( new QFileSystemModel(this)),
	m_pFiles (new QFileSystemModel(this)),
	m_pLayout (new QHBoxLayout(this)),
	m_SelectedFile(),
	m_pCreateNewPhysxMat (new QAction(QStringLiteral("New PhysxMaterial"), this)),
	m_pCreateNewScene (new QAction(QStringLiteral("New Scene"), this))

{

	m_pDir->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	m_pDirectoryView->setModel(m_pDir);
	
	m_pFiles->setFilter(QDir::Filter::NoSymLinks | QDir::NoDotAndDotDot 
		| QDir::AllDirs | QDir::Filter::Files);
	m_pFiles->setReadOnly(false);
	m_pFileView->setEditTriggers(QAbstractItemView::EditTrigger::EditKeyPressed);
	m_pFileView->setModel(m_pFiles);


	m_pDirectoryView->setColumnHidden(1, true);
	m_pDirectoryView->setColumnHidden(2, true);
	m_pDirectoryView->setColumnHidden(3, true);

	
	//layout
	QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spLeft.setHorizontalStretch(0.75);
	m_pDirectoryView->setSizePolicy(spLeft);

	QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spRight.setHorizontalStretch(2.25);
	m_pFileView->setSizePolicy(spRight);
	m_pFileView->setFlow(QListView::Flow::LeftToRight);
	m_pFileView->setViewMode(QListView::ViewMode::IconMode);
	m_pFileView->setGridSize(QSize(100, 100));

	m_pLayout->addWidget(m_pDirectoryView);
	m_pLayout->addWidget(m_pFileView);

		

	//connect signals
	connect(m_pDirectoryView, SIGNAL(clicked(QModelIndex )),
		this, SLOT(OnDirSelect()));
	connect(m_pFileView, SIGNAL(doubleClicked(QModelIndex)),
		this, SLOT(OnFileDblClick()));
	connect(m_pFileView, SIGNAL(clicked(QModelIndex)),
		this, SLOT(OnFileClick()));

	connect(m_pFiles, SIGNAL(fileRenamed(QString, QString, QString)), this, SLOT(FileRenamed(QString, QString, QString)));
	//invisible without opened project
	Hide(true);

	//Actions
	m_pFileView->addAction(m_pCreateNewScene);
	m_pFileView->addAction(m_pCreateNewPhysxMat);
	QObject::connect(m_pCreateNewPhysxMat, SIGNAL(triggered()), this, SLOT(NewPhysxMat()));
	QObject::connect(m_pCreateNewScene, SIGNAL(triggered()), this, SLOT(NewScene()));


	m_pFileView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);

	m_pFileView->setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);
}



void ExplorerPanel::SetDirectory(QString path)
{

	m_pDir->setRootPath(path);

	m_pDirectoryView->setRootIndex(m_pDir->index(path));
	m_pFiles->setRootPath(path);
	m_pFileView->setRootIndex(m_pFiles->index(path));
	Hide(false);
}

void ExplorerPanel::Hide(bool enabled)
{

	m_pFileView->setVisible(!enabled);
	m_pDirectoryView->setVisible(!enabled);
	
}

void ExplorerPanel::OnFileDblClick()
{
	QFileInfo fileInfo = m_pFiles->fileInfo(m_pFileView->currentIndex());
	if (fileInfo.isDir())
	{
		QString path{ fileInfo.absoluteFilePath() };
		m_pFiles->setRootPath(path);
		m_pFileView->setRootIndex(m_pFiles->index(path));
	}
	else if (fileInfo.completeSuffix() == "ovlscene")
	{
		m_SelectedFile = fileInfo;
		Notify(OVLEvent::OpenScene, this);
		
	}
	else
	{
		QDesktopServices::openUrl(QString("file:///").append(fileInfo.absoluteFilePath()));
		
	}

}

void ExplorerPanel::OnFileClick()
{
	QFileInfo fileInfo = m_pFiles->fileInfo(m_pFileView->currentIndex());
	m_SelectedFile = fileInfo;
	Notify(OVLEvent::OpenFile, this);
}

void ExplorerPanel::FileRenamed(const QString & path, const QString & oldName, const QString & newName)
{
	AssetManager* pAssetMan{ AssetManager::GetInstance() };
	pAssetMan->FileRenamed(path, oldName, newName);
}

void ExplorerPanel::NewPhysxMat()
{
	auto physX = PhysxManager::GetInstance()->GetPhysics();
	auto material = physX->createMaterial(0, 0, 0);

	QDir dir = m_pFiles->rootDirectory();
	QFile newMat{ dir.absolutePath().append("\\NewPhysxMaterial.ovlphysxmat") };
	if (newMat.open(QIODevice::WriteOnly))
	{
		QTextStream stream{ &newMat };
		YAML::Emitter out{};
		out << YAML::BeginDoc << YAML::BeginMap;
		SERIALIZE_VAR(*material, out);
		out << YAML::EndMap << YAML::EndDoc;
		stream << QString::fromStdString(out.c_str());
	}
	newMat.close();

	QFileInfo info{ newMat };
	AssetManager::GetInstance()->AddToFiles(info);

	QModelIndex index = m_pFiles->index(info.absoluteFilePath());
	m_pFileView->setCurrentIndex(index);
	m_pFileView->edit(index);
}

void ExplorerPanel::NewScene()
{

	QDir dir = m_pFiles->rootDirectory();
	QFile newScene{ dir.absolutePath().append("\\Scene.ovlscene") };
	if (newScene.open(QIODevice::WriteOnly))
	{
		QTextStream stream{ &newScene };
		YAML::Emitter out{};
		out << YAML::BeginDoc;

		out << YAML::EndDoc;
		stream << QString::fromStdString(out.c_str());
	}
	newScene.close();

	QFileInfo info{ newScene };


	QModelIndex index = m_pFiles->index(info.absoluteFilePath());
	m_pFileView->setCurrentIndex(index);
	m_pFileView->edit(index);
}

void ExplorerPanel::OnDirSelect()
{
	
	QString path = m_pDir->fileInfo(m_pDirectoryView->currentIndex()).absoluteFilePath();
	m_pFiles->setRootPath(path);
	m_pFileView->setRootIndex(m_pFiles->index(path));

}
