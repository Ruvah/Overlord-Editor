#pragma once
enum class OVLEvent : int
{
	NewSceneActivated,
	GameObjectSelected,
	GameObjectNameChange,
	ProjectOpen,
	OpenScene,
	OpenFile,
	GameObjCreated,
	GameObjRemoved,
	GameObjParentChanged,
	TransformCompChanged,
	ColliderCompChanged,
	ComponentDeleted,
	ComponentAdded,
	DropEvent
};
class Subject;

class Observer
{
public:
	Observer() = default ;
	virtual ~Observer()= default;
	virtual void OnNotify(const OVLEvent event, Subject* subj = nullptr)=0;




protected:
	
};

