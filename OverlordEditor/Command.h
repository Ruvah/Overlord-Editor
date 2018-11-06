#pragma once
class Command: public Subject
{
public:
	Command();
	virtual ~Command();

	virtual void Execute() =0;
	virtual void Undo() ;
	virtual void Redo() { Execute(); };

};

