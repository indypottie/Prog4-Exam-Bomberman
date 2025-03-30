#pragma once
//-----------------------------------------------------
// abstract Command Class									 
//-----------------------------------------------------
class Command
{
public:
	virtual ~Command() = default; // Destructor

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	virtual void Execute() = 0;
};