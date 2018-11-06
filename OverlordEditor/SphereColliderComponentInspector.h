#pragma once
#include "ComponentInspector.h"
class FileLineEdit;
class SphereColliderComponent;
class SphereColliderComponentInspector :
	public ComponentInspector, public Observer
{
	Q_OBJECT
	Q_DISABLE_COPY(SphereColliderComponentInspector)
public:
	SphereColliderComponentInspector(SphereColliderComponent* pCollider,QWidget* parent);
	virtual ~SphereColliderComponentInspector()=default;

	virtual void Refresh() override;
	
	virtual void OnNotify(const OVLEvent OEvent, Subject* pSubj) override;
private:
	SphereColliderComponent* m_pCollider;
	QLabel* m_pLabTitle, *m_pLabRadius, *m_pLabRotation, *m_pLabIsTrigger, *m_pLabMaterial;
	QDoubleSpinBox *m_pSpinRotX, *m_pSpinRotY, *m_pSpinRotZ,*m_pSpinRadius;
	QHBoxLayout *m_pLayRadius, *m_pLayRot, *m_pLayTrigger, *m_pLayMaterial;
	QCheckBox *m_pCheckIsTrigger;
	FileLineEdit *m_pPathMaterial;
public slots:
	void RadiusChanged();
	void RotationChanged();
	void IsTriggerChanged();
	void MaterialChanged();
};

