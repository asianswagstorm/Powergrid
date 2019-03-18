#ifndef PART3_OIL_H
#define PART3_OIL_H
#include "Resource.h"

class Oil : public Resource { //extends
public:

    Oil();
    Oil(int quantity);
    ~Oil();
    string getType() const;

private:

    string type = "Oil";
};

#endif //PART3_OIL_H
