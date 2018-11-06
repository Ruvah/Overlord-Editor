#include "stdafx.h"
#include "FileLineEdit.h"
#include <AssetManager.h>


FileLineEdit::FileLineEdit(QWidget* parent ):
	QLineEdit(parent),
	m_AssetID{-1},
	m_UpdateTimer()
{
	m_UpdateTimer.setInterval(100);
	m_UpdateTimer.start();
	connect(&m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));

	setAcceptDrops(true);
	
}
void FileLineEdit::Update()
{
	auto pAssMan = AssetManager::GetInstance();
	QFileInfo info = pAssMan->GetFile(m_AssetID);
	if (m_AssetID == -1)
	{
		setText("Invalid_File");

	}
	else
	{
		setText(info.baseName());
	}
}

void FileLineEdit::SetAssetID(int ID)
{
	m_AssetID = ID;
}

void FileLineEdit::HandleFileAssignment(QFileInfo fileInfo)
{
	auto pAssMan = AssetManager::GetInstance();
	int id =pAssMan->GetID(fileInfo);

	m_AssetID = id;
}

void FileLineEdit::dropEvent(QDropEvent * event)
{
	
	auto mimeData = event->mimeData();
	vector<QString> filePaths;
	if (mimeData->hasUrls())
	{
		for(QUrl url : mimeData->urls())
		{
			filePaths.push_back(url.toLocalFile());
		}
	}
	QFileInfo fileInfo(filePaths.at(0));
	HandleFileAssignment(fileInfo);

	Notify(OVLEvent::DropEvent, this);
}

void FileLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}