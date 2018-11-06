#pragma once


class Subject
{
public:
	Subject()= default;
	virtual ~Subject()= default;

	void AddObserver(Observer* pObs);
	void RemoveObserver(Observer*pObs);
	void CopyObserversTo(Subject* pObs);
protected:
	void Notify(const OVLEvent OEvent, Subject* subj = nullptr);

private:
	vector<Observer*> m_pObservers;

};

