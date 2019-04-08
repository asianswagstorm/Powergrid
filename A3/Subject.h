#pragma once
#include "Observable.h"
#include <list>
#include <string>

using namespace std;

class Subject : public Observable {
public:
	Subject();
	~Subject();
	void registerObserver(Observer * observer);
	void removeObserver(Observer * observer);
	void notify();

private:
	list<Observer *> * observers;
	
};