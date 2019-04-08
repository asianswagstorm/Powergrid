#include "Subject.h"
#include "Observer.h"
#include <iostream>
Subject::Subject() {
	observers = new list<Observer *>;
}

Subject::~Subject() {
	
	for (list<Observer *>::iterator i = observers->begin() ; i != observers->end(); ++i) {
		delete * i;
	}
	delete observers;
}
void Subject::registerObserver(Observer * observer) {
	observers->push_back(observer);
}
void Subject::removeObserver(Observer * observer) {
	observers->remove(observer);
}
void Subject::notify() {

	list<Observer *>::iterator i = observers->begin();

	for (; i != observers->end(); ++i) {
		(*i)->Update();
		system("PAUSE");
	}
}
