#ifndef PART3_URANIUM_H
#define PART3_URANIUM_H
#include "Resource.h"

class Uranium : public Resource {

public:
    Uranium();
    ~Uranium();
    Uranium(int quantity);
    string getType() const;
	
private:

    string type = "Uranium";

};

#endif //PART3_URANIUM_H
