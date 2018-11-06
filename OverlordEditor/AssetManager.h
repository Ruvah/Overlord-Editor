#pragma once
#include <Singleton.h>
class AssetManager : public Singleton<AssetManager>
{

public:
	friend class Singleton<AssetManager>;
	
	virtual ~AssetManager() = default;

	void FileRenamed(const QString &path, const QString &oldName, const QString &newName);
	void Load();
	void Write();
	void SetFilePath(QString path);
	void AddToFiles(QFileInfo info);
	int GetID(QFileInfo info);
	QFileInfo GetFile(int id);

private:
	
	vector<QFileInfo> m_pAssets;
	QString m_FilePath;
	
};

