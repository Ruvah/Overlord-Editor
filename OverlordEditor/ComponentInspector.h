#pragma once
#include <qwidget.h>
class ComponentInspector :
	public QWidget,public Subject
{
	Q_OBJECT
	Q_DISABLE_COPY(ComponentInspector)
public:
	ComponentInspector(UINT ID,QWidget*parent = NULL);
	virtual ~ComponentInspector()=default;
	virtual QPaintEngine* paintEngine() const { return NULL; };

	UINT GetID() { return m_ID; };
	virtual void Refresh() = 0;
protected:
	QVBoxLayout *m_pLayout;
	UINT m_ID;
	QAction *m_pDeleteComp;

private slots:
	void RemoveThis();
};

