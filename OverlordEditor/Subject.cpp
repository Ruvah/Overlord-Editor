#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"



void Subject::AddObserver(Observer * pObs)
{
	m_pObservers.push_back(pObs);
}

void Subject::RemoveObserver(Observer * pObs)
{
	auto it = find_if(m_pObservers.begin(), m_pObservers.end(),
		[&pObs](Observer* a) {return pObs == a; });
	if (it == m_pObservers.end())
		return;

	m_pObservers.erase(it);

}

void Subject::CopyObserversTo(Subject * pSubj)
{
	for (auto pObserver : m_pObservers)
	{
		pSubj->AddObserver(pObserver);

	}
}

void Subject::Notify(const OVLEvent OEvent, Subject* subj )
{
	for (auto& obs : m_pObservers)
	{
		if(obs)
			obs->OnNotify(OEvent, this);
	}
}
