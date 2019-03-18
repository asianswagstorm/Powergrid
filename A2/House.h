#ifndef PART3_HOUSE_H
#define PART3_HOUSE_H
#include <iostream>
using namespace std;

class House{
public:
    House();
    ~House();
    House(int, string,string);
    int getIndex();
    void setIndex(int);
    string getLocation();
    void setLocation(string location);
	string getHouseColor();
	void setHouseColor(string house_color);

private:
    int index;
    string location;
	string house_color;
};


#endif //PART3_HOUSE_H
