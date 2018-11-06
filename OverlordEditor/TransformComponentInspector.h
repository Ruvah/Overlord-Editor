#pragma once
#include <qwidget.h>
#include <ComponentInspector.h>
class TransformComponentInspector :
	public ComponentInspector
{
	Q_OBJECT
	Q_DISABLE_COPY(TransformComponentInspector)
public:
	TransformComponentInspector(TransformComponent* pTransform, QWidget* parent = NULL);
	virtual ~TransformComponentInspector()=default;

	virtual void Refresh() override;
private:
	TransformComponent* m_pTransform;

	QLabel* m_pLabTitle, *m_pLabRotation, *m_pLabScale, *m_pLabPos;
	QDoubleSpinBox *m_pSpinRotX, *m_pSpinRotY, *m_pSpinRotZ,
		*m_pSpinScaleX, *m_pSpinScaleY, *m_pSpinScaleZ,
		*m_pSpinPosX, *m_pSpinPosY, *m_pSpinPosZ;
	QHBoxLayout *m_pLayPos, *m_pLayRot, *m_pLayScale;
public slots:
	void PositionChanged();
	void RotationChanged();
	void ScaleChanged();
};

