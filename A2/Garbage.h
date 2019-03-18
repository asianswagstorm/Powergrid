#ifndef PART3_GARBAGE_H
#define PART3_GARBAGE_H
#include "Resource.h"


class Garbage : public Resource {

public:
    Garbage();
    Garbage(int quantity);
    ~Garbage();

    string getType() const;
	
private:

    string type = "Garbage";

};

#endif //PART3_GARBAGE_H
