#include "stdafx.h"
#include "SphereColliderComponentInspector.h"
#include <SphereColliderComponent.h>
#include <SphereColliderRadiusChanged.h>
#include <SphereColliderRotChangeCmd.h>
#include <SphereColliderTriggerChange.h>
#include <FileLineEdit.h>


SphereColliderComponentInspector::SphereColliderComponentInspector(SphereColliderComponent * pCollider, QWidget * parent):
	ComponentInspector(pCollider->GetID(),parent),
	m_pCollider(pCollider),
	m_pLabRadius(new QLabel("Radius",this)),
	m_pLabRotation(new QLabel("Rotation",this)),
	m_pLabTitle(new QLabel("SphereColliderComponent",this)),
	m_pLabIsTrigger(new QLabel("IsTrigger", this)),
	m_pLabMaterial(new QLabel("Material", this)),
	m_pLayRadius(new QHBoxLayout()),
	m_pLayRot(new QHBoxLayout()),
	m_pLayTrigger(new QHBoxLayout()),
	m_pLayMaterial(new QHBoxLayout()),
	m_pSpinRadius(new QDoubleSpinBox(this)),
	m_pSpinRotX(new QDoubleSpinBox(this)),
	m_pSpinRotY(new QDoubleSpinBox(this)),
	m_pSpinRotZ(new QDoubleSpinBox(this)),
	m_pCheckIsTrigger(new QCheckBox(this)),
	m_pPathMaterial(new FileLineEdit(this))
{
	physx::PxVec3 rot = m_pCollider->GetRotation();
	int assetID = m_pCollider->GetMaterialAssetId();

	m_pPathMaterial->SetAssetID(assetID);
	m_pCheckIsTrigger->setChecked(m_pCollider->IsTrigger());
	m_pSpinRadius->setValue(m_pCollider->GetRadius());
	m_pSpinRotX->setValue(rot.x);
	m_pSpinRotY->setValue(rot.y);
	m_pSpinRotZ->setValue(rot.z);

	m_pSpinRadius->setMinimum(0);
	m_pSpinRotX->setMinimum(-DBL_MAX);
	m_pSpinRotY->setMinimum(-DBL_MAX);
	m_pSpinRotZ->setMinimum(-DBL_MAX);

	m_pSpinRadius->setSingleStep(0.1);
	m_pLabTitle->setStyleSheet("font-weight: bold;");

	m_pLayRadius->addWidget(m_pLabRadius);
	m_pLayRadius->addWidget(m_pSpinRadius);
	
	m_pLayRot->addWidget(m_pLabRotation);
	m_pLayRot->addWidget(m_pSpinRotX);
	m_pLayRot->addWidget(m_pSpinRotY);
	m_pLayRot->addWidget(m_pSpinRotZ);

	m_pLayTrigger->addWidget(m_pLabIsTrigger);
	m_pLayTrigger->addWidget(m_pCheckIsTrigger);

	m_pLayMaterial->addWidget(m_pLabMaterial);
	m_pLayMaterial->addWidget(m_pPathMaterial);

	m_pLayout->addWidget(m_pLabTitle);
	m_pLayout->addLayout(m_pLayRadius);
	m_pLayout->addLayout(m_pLayRot);
	m_pLayout->addLayout(m_pLayTrigger);
	m_pLayout->addLayout(m_pLayMaterial);

	connect(m_pSpinRotX, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinRotY, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinRotZ, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinRadius, SIGNAL(valueChanged(double)), this, SLOT(RadiusChanged()));
	connect(m_pCheckIsTrigger, SIGNAL(stateChanged(int)), this, SLOT(IsTriggerChanged()));


}

void SphereColliderComponentInspector::Refresh()
{
	physx::PxVec3 rot = m_pCollider->GetRotation();

	m_pCheckIsTrigger->setChecked(m_pCollider->IsTrigger());
	m_pSpinRadius->setValue(m_pCollider->GetRadius());
	m_pSpinRotX->setValue(rot.x);
	m_pSpinRotY->setValue(rot.y);
	m_pSpinRotZ->setValue(rot.z);
}

void SphereColliderComponentInspector::OnNotify(const OVLEvent OEvent, Subject * pSubj)
{
	switch (OEvent)
	{
	case OVLEvent::DropEvent:
		MaterialChanged();
		break;
	default:
		break;
	}
}

void SphereColliderComponentInspector::RadiusChanged()
{
	
	SphereColliderRadiusChanged* command = new SphereColliderRadiusChanged(
		m_pSpinRadius->value(), m_pCollider);
	CopyObserversTo(command);
	command->Execute();
}
void SphereColliderComponentInspector::RotationChanged()
{
	physx::PxVec3 angles{ float(m_pSpinRotX->value()),
	float(m_pSpinRotY->value()),float(m_pSpinRotZ->value()) };
	SphereColliderRotChangeCmd* command = new SphereColliderRotChangeCmd(angles, m_pCollider);
	CopyObserversTo(command);
	command->Execute();
}

void SphereColliderComponentInspector::IsTriggerChanged()
{
	
	SphereColliderTriggerChange* command = new SphereColliderTriggerChange(
		m_pCheckIsTrigger->isChecked() , m_pCollider);
	CopyObserversTo(command);
	command->Execute();
}

void SphereColliderComponentInspector::MaterialChanged()
{
	int id = m_pPathMaterial->GetAssetID();
	m_pCollider->SetMaterialAssID(id);
}
