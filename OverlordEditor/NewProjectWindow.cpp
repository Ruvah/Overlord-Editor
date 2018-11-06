#include "stdafx.h"
#include "NewProjectWindow.h"
#include <DirectoryFuncs.h>
#include <AssetManager.h>



NewProjectWindow::NewProjectWindow(QWidget* parent ):
	QWidget(parent),
	m_ProjectDirectory{}
{
	
	m_pNameLabel = new QLabel(this);
	m_pNameLabel->setText(QStringLiteral("Project Name:"));
	m_pNameLabel->move(50, 20);

	m_pProjectName = new QLineEdit(this);
	m_pProjectName->resize(200, 30);
	m_pProjectName->move(50, 50);

	m_pPathLabel = new QLabel(this);
	m_pPathLabel->setText(QStringLiteral("Path:"));
	m_pPathLabel->move(50, 100);

	m_pDirectoryPath = new QLineEdit(this);
	m_pDirectoryPath->resize(200, 30);
	m_pDirectoryPath->move(50, 130);

	m_pBrowseButton = new QPushButton(this);
	m_pBrowseButton->setText(QStringLiteral("..."));
	m_pBrowseButton->resize(30, m_pBrowseButton->height());
	m_pBrowseButton->move(250, 130);

	m_pCreate = new QPushButton(this);
	m_pCreate->setText(QStringLiteral("Create"));
	//m_pCreate->resize(30, m_pBrowseButton->height());
	m_pCreate->move(100, 230);
	
	QObject::connect(m_pBrowseButton, SIGNAL(clicked()), this, SLOT(BrowseFolders()));
	QObject::connect(m_pCreate, SIGNAL(clicked()), this, SLOT(CreateProject()));


}

void NewProjectWindow::CreateProject()
{
	if (m_pProjectName->text().isEmpty())
	{
		//invalid project name
		return;
	}
	QString path{m_pDirectoryPath->text()},
		projectName{m_pProjectName->text()};
	QDir directory{ path };
	if (!directory.exists())
	{
		//invalid project directory
		return;
	}
	if (directory.mkdir(projectName))
	{
		//QString ResourcesPath = QDir::currentPath().append("/Resources");
		m_ProjectRoot = QString{ path.append("\\").append(projectName) };
		m_ProjectDirectory = QDir(m_ProjectRoot);
		//m_ProjectDirectory.mkdir("Resources");
		//QString resourcePath = m_ProjectRoot.append("\\Resources");
		//if (!CpDir(ResourcesPath, resourcePath))
		//{
		//	Logger::LogError(L"Unable to add Resources to the project folder, please check directory names.");
		//}
		QString assetFilePath = m_ProjectDirectory.absolutePath().append("\\" + projectName.append(".ovl"));
		AssetManager::GetInstance()->SetFilePath(assetFilePath);
		if (m_ProjectDirectory.exists())
			Notify(OVLEvent::ProjectOpen, this);
		close();
	}

}


void NewProjectWindow::BrowseFolders()
{
	QString path = QFileDialog::getExistingDirectory();
	m_pDirectoryPath->setText(path);

}

