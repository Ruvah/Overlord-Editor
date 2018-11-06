#include "stdafx.h"
#include "AssetManager.h"

void AssetManager::FileRenamed(const QString & path, const QString & oldName, const QString & newName)
{

	auto changeIfIsAsset = [&path ,&oldName,&newName](QFileInfo& registeredFile)
	{
		if (registeredFile.absolutePath() == path && registeredFile.fileName() == oldName)//usebasename if newName doesnt include filetype
		{
			registeredFile = QFileInfo(path + "\\" +newName);
		}
	};
	for_each(m_pAssets.begin(), m_pAssets.end(), changeIfIsAsset);
}

void AssetManager::Load()
{
	QFile asFil(m_FilePath);
	if (asFil.exists())
	{
		YAML::Node file{ YAML::LoadFile(m_FilePath.toStdString()) };
		vector<string> paths;

		switch (file.Type()) {

		case YAML::NodeType::Sequence:
			for (std::size_t i = 0; i < file.size(); i++)
			{
				paths.push_back(file[i].as<string>());
			}
			break;
		}

		m_pAssets.clear();
		for (string path : paths)
		{
			QFile file(QString::fromStdString(path));
			QFileInfo asset{ file };
			m_pAssets.push_back(asset);
		}
	}
}

void AssetManager::Write()
{
	vector<string> paths;
	for (QFileInfo file : m_pAssets)
	{
		paths.push_back(file.absoluteFilePath().toStdString());
	}

	YAML::Emitter out;
	out << YAML::BeginDoc;
	out << paths;
	out << YAML::EndDoc;


	string contents = out.c_str();
	QFile file{ m_FilePath };
	if (file.exists())
	{
		file.resize(sizeof(contents));
	}
	if (file.open(QIODevice::OpenModeFlag::ReadWrite))
	{
		QTextStream stream{ &file };
		stream << QString::fromStdString(out.c_str());
	}
	file.close();
}

void AssetManager::SetFilePath(QString path)
{
	m_FilePath = path;
}

void AssetManager::AddToFiles(QFileInfo info)
{
	auto isFile = [&info](QFileInfo registeredFile)
	{
		return registeredFile.absoluteFilePath() == info.absoluteFilePath();
	};
	auto it = find_if(m_pAssets.begin(), m_pAssets.end(),
		isFile);
	if (it == m_pAssets.end())
	{
		m_pAssets.push_back(info);
		cout << info.absoluteFilePath().toStdString();
	}

}

int AssetManager::GetID(QFileInfo info)
{
	auto isFile = [&info](QFileInfo registeredFile)
	{
		return registeredFile.absoluteFilePath() == info.absoluteFilePath();
	};
	auto it = find_if(m_pAssets.begin(), m_pAssets.end(),
		isFile);
	if (it != m_pAssets.end())
	{
		int count = std::distance(begin(m_pAssets), it);
		return count;
	}
	QString warning{ "File not recognized by AssetManager: " + info.absoluteFilePath() };
	Logger::LogWarning(warning.toStdWString());
	return -1;
}

QFileInfo AssetManager::GetFile(int id)
{
	if (id >= 0 && id < m_pAssets.size())
	{
		return m_pAssets.at(size_t(id));
	}
	else
	{
		QFileInfo wrongFile("InvalidFile.invalid");
		return wrongFile;
	}
}

