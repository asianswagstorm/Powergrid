#ifndef PART3_COAL_H
#define PART3_COAL_H
#include "Resource.h"


class Coal : public Resource {

public:
    ~Coal();
    Coal();
    Coal(int quantity);
    string getType() const;

private:
    const string resource_type = "Coal";
	
};

#endif //PART3_COAL_H
