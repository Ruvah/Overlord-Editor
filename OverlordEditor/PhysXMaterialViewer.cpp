#include "stdafx.h"
#include "PhysXMaterialViewer.h"
#include <PhysxManager.h>
#include <Serialization.h>

PhysXMaterialViewer::PhysXMaterialViewer(QFileInfo materialFile, QWidget* parent) :
	QWidget(parent),
	m_pStatFr(new QLabel("Static Friction", this)),
	m_pDynFr(new QLabel("Dynamic Friction", this)),
	m_pResti(new QLabel("Restitution", this)),
	m_pTitle(new QLabel(this)),
	m_pLayout (new QVBoxLayout(this)),
	m_pLayStaticFr(new QHBoxLayout()),
	m_pLayDynFric(new QHBoxLayout()),
	m_pLayResti(new QHBoxLayout()),
	m_pLayHeader(new QHBoxLayout()),
	m_pSave(new QPushButton(this)),
	m_pSpinStaticFr(new QDoubleSpinBox(this)),
	m_pSpinDynFric(new QDoubleSpinBox(this)),
	m_pSpinResti(new QDoubleSpinBox(this))
{
	m_pSpinStaticFr->setSingleStep(0.05);
	m_pSpinDynFric->setSingleStep(0.05);
	m_pSpinResti->setSingleStep(0.05);

	m_pSpinStaticFr->setMaximum(1);
	m_pSpinStaticFr->setMinimum(0);
	m_pSpinDynFric->setMaximum(1);
	m_pSpinDynFric->setMinimum(0);
	m_pSpinResti->setMaximum(1);
	m_pSpinResti->setMinimum(0);

	m_pSave->setText("Save");

	m_pLayStaticFr->addWidget(m_pStatFr);
	m_pLayStaticFr->addWidget(m_pSpinStaticFr);

	m_pLayDynFric->addWidget(m_pDynFr);
	m_pLayDynFric->addWidget(m_pSpinDynFric);

	m_pLayResti->addWidget(m_pResti);
	m_pLayResti->addWidget(m_pSpinResti);

	m_pLayHeader->addWidget(m_pTitle);
	m_pLayHeader->addWidget(m_pSave);


	m_pLayout->addLayout(m_pLayHeader);
	m_pLayout->addLayout(m_pLayStaticFr);
	m_pLayout->addLayout(m_pLayDynFric);
	m_pLayout->addLayout(m_pLayResti);
	m_pLayout->setMargin(0);
	m_pLayout->setSpacing(5);
	m_pLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
	m_pLayout->setAlignment(Qt::AlignTop);

	setLayout(m_pLayout);

	SetFile(materialFile);

	connect(m_pSave, SIGNAL(clicked()),
		this, SLOT(Save()));
	connect(m_pSpinDynFric, SIGNAL(valueChanged(double)),
		this, SLOT(UpdateMat()));
	connect(m_pSpinResti, SIGNAL(valueChanged(double)),
		this, SLOT(UpdateMat()));
	connect(m_pSpinStaticFr, SIGNAL(valueChanged(double)),
		this, SLOT(UpdateMat()));
}
void PhysXMaterialViewer::SetFile(QFileInfo materialFile)
{
	m_FileInfo = QFileInfo{materialFile};
	string absolutePath = m_FileInfo.absoluteFilePath().toStdString();
	YAML::Node mat = YAML::LoadFile(absolutePath);

	auto physX = PhysxManager::GetInstance()->GetPhysics();
	physx::PxMaterial *material = physX->createMaterial(0, 0, 0);
	PARSE_VAR(*material, mat);

	m_pMaterial = material;

	m_pSpinStaticFr->setValue(m_pMaterial->getStaticFriction());
	m_pSpinDynFric->setValue(m_pMaterial->getDynamicFriction());
	m_pSpinResti->setValue(m_pMaterial->getRestitution());

	m_pTitle->setText(m_FileInfo.baseName());
	m_pTitle->setStyleSheet("font-weight: bold;");
}

void PhysXMaterialViewer::UpdateMat()
{
	m_pMaterial->setStaticFriction(m_pSpinStaticFr->value());
	m_pMaterial->setDynamicFriction(m_pSpinDynFric->value());
	m_pMaterial->setRestitution(m_pSpinResti->value());

}

void PhysXMaterialViewer::Save()
{
	QFile newMat{ m_FileInfo.absoluteFilePath() };
	physx::PxMaterial *material = m_pMaterial;
	if (newMat.open(QIODevice::WriteOnly))
	{
		QTextStream stream{ &newMat };
		YAML::Emitter out{};
		out << YAML::BeginDoc << YAML::BeginMap;
		SERIALIZE_VAR(*material, out);
		out << YAML::EndMap << YAML::EndDoc;
		stream << QString::fromStdString(out.c_str());
	}
	newMat.close();
}
