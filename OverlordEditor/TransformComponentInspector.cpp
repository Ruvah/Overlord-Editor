#include "stdafx.h"
#include "TransformComponentInspector.h"
#include <TransformComponent.h>
#include <TrnsfCompPosChangeCmd.h>
#include <TrnsfCompRotChangeCmd.h>
#include <TrnsfCompScaleChangeCmd.h>


TransformComponentInspector::TransformComponentInspector(TransformComponent * pTransform, QWidget * parent):
	ComponentInspector(pTransform->GetID(),parent),
	m_pTransform(pTransform),
	m_pLabPos(new QLabel("Position", this)),
	m_pLabRotation(new QLabel("Rotation", this)),
	m_pLabScale(new QLabel("Scale", this)),
	m_pLabTitle(new QLabel("TransformComponent")),
	m_pLayPos(new QHBoxLayout()),
	m_pLayRot(new QHBoxLayout()),
	m_pLayScale(new QHBoxLayout()),
	m_pSpinPosX(new QDoubleSpinBox(this)),
	m_pSpinPosY(new QDoubleSpinBox(this)),
	m_pSpinPosZ(new QDoubleSpinBox(this)),
	m_pSpinScaleX(new QDoubleSpinBox(this)),
	m_pSpinScaleY(new QDoubleSpinBox(this)),
	m_pSpinScaleZ(new QDoubleSpinBox(this)),
	m_pSpinRotX(new QDoubleSpinBox(this)),
	m_pSpinRotY(new QDoubleSpinBox(this)),
	m_pSpinRotZ(new QDoubleSpinBox(this))
{
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition();
	DirectX::XMFLOAT3 rot = m_pTransform->GetRotationEuler();
	DirectX::XMFLOAT3 scale = m_pTransform->GetScale();
	
	m_pSpinPosX->setValue(pos.x);
	m_pSpinPosY->setValue(pos.y);
	m_pSpinPosZ->setValue(pos.z);

	m_pSpinRotX->setValue(rot.x);
	m_pSpinRotY->setValue(rot.y);
	m_pSpinRotZ->setValue(rot.z);

	m_pSpinScaleX->setValue(scale.x);
	m_pSpinScaleY->setValue(scale.y);
	m_pSpinScaleZ->setValue(scale.z);

	
	m_pSpinScaleX->setMaximum(DBL_MAX);
	m_pSpinScaleY->setMaximum(DBL_MAX);
	m_pSpinScaleZ->setMaximum(DBL_MAX);
	m_pSpinRotX->setMaximum(DBL_MAX);
	m_pSpinRotY->setMaximum(DBL_MAX);
	m_pSpinRotZ->setMaximum(DBL_MAX);
	m_pSpinPosX->setMaximum(DBL_MAX);
	m_pSpinPosY->setMaximum(DBL_MAX);
	m_pSpinPosZ->setMaximum(DBL_MAX);

	m_pSpinScaleX->setMinimum(-DBL_MAX);
	m_pSpinScaleY->setMinimum(-DBL_MAX);
	m_pSpinScaleZ->setMinimum(-DBL_MAX);
	m_pSpinRotX->setMinimum(-DBL_MAX);
	m_pSpinRotY->setMinimum(-DBL_MAX);
	m_pSpinRotZ->setMinimum(-DBL_MAX);
	m_pSpinPosX->setMinimum(-DBL_MAX);
	m_pSpinPosY->setMinimum(-DBL_MAX);
	m_pSpinPosZ->setMinimum(-DBL_MAX);

	m_pSpinScaleX->setSingleStep(0.1);
	m_pSpinScaleY->setSingleStep(0.1);
	m_pSpinScaleZ->setSingleStep(0.1);
	m_pSpinRotX->setSingleStep(0.5);
	m_pSpinRotY->setSingleStep(0.5);
	m_pSpinRotZ->setSingleStep(0.5);

	m_pLabTitle->setStyleSheet("font-weight: bold;");

	m_pLayPos->addWidget(m_pLabPos);
	m_pLayPos->addWidget(m_pSpinPosX);
	m_pLayPos->addWidget(m_pSpinPosY);
	m_pLayPos->addWidget(m_pSpinPosZ);

	m_pLayRot->addWidget(m_pLabRotation);
	m_pLayRot->addWidget(m_pSpinRotX);
	m_pLayRot->addWidget(m_pSpinRotY);
	m_pLayRot->addWidget(m_pSpinRotZ);

	m_pLayScale->addWidget(m_pLabScale);
	m_pLayScale->addWidget(m_pSpinScaleX);
	m_pLayScale->addWidget(m_pSpinScaleY);
	m_pLayScale->addWidget(m_pSpinScaleZ);

	m_pLayout->addWidget(m_pLabTitle);
	m_pLayout->addLayout(m_pLayPos);
	m_pLayout->addLayout(m_pLayRot);
	m_pLayout->addLayout(m_pLayScale);

	connect(m_pSpinPosX, SIGNAL(valueChanged(double)), this, SLOT(PositionChanged()));
	connect(m_pSpinPosY, SIGNAL(valueChanged(double)), this, SLOT(PositionChanged()));
	connect(m_pSpinPosZ, SIGNAL(valueChanged(double)), this, SLOT(PositionChanged()));
	connect(m_pSpinRotX, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinRotY, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinRotZ, SIGNAL(valueChanged(double)), this, SLOT(RotationChanged()));
	connect(m_pSpinScaleX, SIGNAL(valueChanged(double)), this, SLOT(ScaleChanged()));
	connect(m_pSpinScaleY, SIGNAL(valueChanged(double)), this, SLOT(ScaleChanged()));
	connect(m_pSpinScaleZ, SIGNAL(valueChanged(double)), this, SLOT(ScaleChanged()));
}

void TransformComponentInspector::PositionChanged()
{
	float x = float(m_pSpinPosX->value());
	float y = float(m_pSpinPosY->value());
	float z = float(m_pSpinPosZ->value());

	DirectX::XMFLOAT3 newPos{ x,y,z };
	TrnsfCompPosChangeCmd* command = new TrnsfCompPosChangeCmd(newPos, m_pTransform);
	CopyObserversTo(command);
	command->Execute();
}

void TransformComponentInspector::Refresh()
{
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition();
	DirectX::XMFLOAT3 rot = m_pTransform->GetRotationEuler();
	DirectX::XMFLOAT3 scale = m_pTransform->GetScale();

	m_pSpinPosX->setValue(pos.x);
	m_pSpinPosY->setValue(pos.y);
	m_pSpinPosZ->setValue(pos.z);

	m_pSpinRotX->setValue(rot.x);
	m_pSpinRotY->setValue(rot.y);
	m_pSpinRotZ->setValue(rot.z);

	m_pSpinScaleX->setValue(scale.x);
	m_pSpinScaleY->setValue(scale.y);
	m_pSpinScaleZ->setValue(scale.z);
}

void TransformComponentInspector::RotationChanged()
{
	float x = float(m_pSpinRotX->value());
	float y = float(m_pSpinRotY->value());
	float z = float(m_pSpinRotZ->value());

	DirectX::XMFLOAT3 newRot{ x,y,z };
	TrnsfCompRotChangeCmd* command = new TrnsfCompRotChangeCmd(newRot, m_pTransform);
	CopyObserversTo(command);
	command->Execute();
}

void TransformComponentInspector::ScaleChanged()
{
	float x = float(m_pSpinScaleX->value());
	float y = float(m_pSpinScaleY->value());
	float z = float(m_pSpinScaleZ->value());

	DirectX::XMFLOAT3 newScale{ x,y,z };
	TrnsfCompScaleChangeCmd* command = new TrnsfCompScaleChangeCmd(newScale, m_pTransform);
	CopyObserversTo(command);
	command->Execute();
}
