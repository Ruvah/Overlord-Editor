#pragma once
#include <qlineedit.h>
class FileLineEdit final :
	public QLineEdit , public Subject
{
	Q_OBJECT
		Q_DISABLE_COPY(FileLineEdit)
public:
	FileLineEdit(QWidget* parent = NULL);
	virtual ~FileLineEdit()=default;

	int GetAssetID() { return m_AssetID; };
	void SetAssetID(int ID);
private slots:
	virtual void Update();

private:
	int m_AssetID;
	QTimer m_UpdateTimer;

	virtual void HandleFileAssignment(QFileInfo fileInfo);
	virtual void dropEvent(QDropEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent *event)override;

};

