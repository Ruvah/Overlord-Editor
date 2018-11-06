#pragma once
#include <qwidget.h>
class PhysXMaterialViewer :
	public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY(PhysXMaterialViewer)
public:
	PhysXMaterialViewer(QFileInfo materialFile, QWidget* parent = NULL);
	virtual ~PhysXMaterialViewer()=default;
	virtual QPaintEngine* paintEngine() const { return NULL; };

private:
	void SetFile(QFileInfo material);

	QFileInfo m_FileInfo;
	QLabel* m_pStatFr, *m_pDynFr, *m_pResti, *m_pTitle;
	QVBoxLayout* m_pLayout;
	QHBoxLayout* m_pLayStaticFr,*m_pLayDynFric,*m_pLayResti,
		*m_pLayHeader;
	QPushButton* m_pSave;
	physx::PxMaterial *m_pMaterial;

	QDoubleSpinBox* m_pSpinStaticFr, *m_pSpinDynFric, *m_pSpinResti;
public slots:
	void Save();
	void UpdateMat();
};

