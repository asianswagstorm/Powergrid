#ifndef PART3_HOUSE_H
#define PART3_HOUSE_H
#include <iostream>
using namespace std;

class House{
public:
    House();
	House(int, string);
    House(int, string,string);
	~House();
    int getIndex();
    void setIndex(int);
    string getLocation();
    void setLocation(string location);
	string getHouseColor();
	void setHouseColor(string house_color);
	bool getisPowered();
	void setisPowered(bool isPowered);

private:
    int index;
    string location;
	string house_color;
	bool isPowered;
};


#endif //PART3_HOUSE_H
