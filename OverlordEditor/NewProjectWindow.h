#pragma once
class NewProjectWindow: public QWidget,public Subject
{
	Q_OBJECT
		Q_DISABLE_COPY(NewProjectWindow)
public:
	NewProjectWindow(QWidget* parent = nullptr);
	~NewProjectWindow()=default;

	QDir GetProjectRoot() { return m_ProjectDirectory; }

private:
	QLineEdit* m_pProjectName, *m_pDirectoryPath;
	QLabel* m_pNameLabel,*m_pPathLabel;
	QPushButton* m_pBrowseButton,*m_pCreate;
	QDir m_ProjectDirectory;
	QString m_ProjectRoot;
public slots:
	void BrowseFolders();
	void CreateProject();

};

