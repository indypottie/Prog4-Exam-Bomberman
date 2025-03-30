#pragma once


//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <vector>

namespace dae
{
	class GameObject;
}

//-----------------------------------------------------
// Subject Class									 
//-----------------------------------------------------
struct Event;
class Observer;

class Subject
{
public:
	~Subject() = default; // Destructor

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);


	void NotifyObservers(const Event& event, dae::GameObject* actor);

private:

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	std::vector<Observer*> m_Observers;
};