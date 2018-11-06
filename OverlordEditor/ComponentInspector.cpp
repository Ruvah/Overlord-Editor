#include "stdafx.h"
#include "ComponentInspector.h"
#include <DeleteComponent.h>
ComponentInspector::ComponentInspector(UINT id,QWidget*parent):
	QWidget(parent),
	m_pLayout(new QVBoxLayout(this)),
	m_ID(id),
	m_pDeleteComp(new QAction("Delete Component",this))
{
	m_pLayout->setMargin(0);
	m_pLayout->setSpacing(5);
	m_pLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);

	setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
	QObject::connect(m_pDeleteComp, SIGNAL(triggered()), this, SLOT(RemoveThis()));
	addAction(m_pDeleteComp);

}

void ComponentInspector::RemoveThis()
{
	DeleteComponent* pCmd{ new DeleteComponent(this) };
	CopyObserversTo(pCmd);
	pCmd->Execute();
}

