#pragma once
#include <list>
using namespace std;

class Observer;

class Observable
{
public:
	virtual ~Observable() {};
	virtual void registerObserver(Observer *) = 0;
	virtual void removeObserver(Observer *) = 0;
	virtual void notify() = 0;
protected:
	Observable() {};
private:
	list<Observer*> observer;
};

