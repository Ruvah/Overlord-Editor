#pragma once
#include <stdafx.h>

static bool rmDir(const QString &dirPath)
{
	QDir dir(dirPath);
	if (!dir.exists())
		return true;
	foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
		if (info.isDir()) {
			if (!rmDir(info.filePath()))
				return false;
		}
		else {
			if (!dir.remove(info.fileName()))
				return false;
		}
	}
	QDir parentDir(QFileInfo(dirPath).path());
	return parentDir.rmdir(QFileInfo(dirPath).fileName());
}

inline bool CpDir(const QString &srcPath, const QString &dstPath)
{
	rmDir(dstPath);
	QDir parentDstDir(QFileInfo(dstPath).path());
	if (!parentDstDir.mkdir(QFileInfo(dstPath).fileName()))
		return false;

	QDir srcDir(srcPath);
	foreach(const QFileInfo &info, srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
		QString srcItemPath = srcPath + "/" + info.fileName();
		QString dstItemPath = dstPath + "/" + info.fileName();
		if (info.isDir()) {
			if (!CpDir(srcItemPath, dstItemPath)) {
				return false;
			}
		}
		else if (info.isFile()) {
			if (!QFile::copy(srcItemPath, dstItemPath)) {
				return false;
			}
		}
		else {
			qDebug() << "Unhandled item" << info.filePath() << "in cpDir";
		}
	}
	return true;
}