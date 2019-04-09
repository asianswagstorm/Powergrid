#pragma once
#include "Observable.h"
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
	std::list<Observer *> * observers;
	
};