#include "ResourceMarket.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

//Resource Market intializes game resources according to rules first round
ResourceMarket::ResourceMarket() {
    market[0] = new ResourceManager();
    market[0]->edit("Coal", 3, 1); //edit(type,quantity,cost)
    market[0]->edit("Oil", 0, 1);
    market[0]->edit("Garbage", 0, 1);
    market[0]->edit("Uranium", 0, 1);


    market[1] = new ResourceManager();
    market[1]->edit("Coal", 3, 2);
    market[1]->edit("Oil", 0, 2);
    market[1]->edit("Garbage", 0, 2);
    market[1]->edit("Uranium", 0, 2);

    market[2] = new ResourceManager();
    market[2]->edit("Coal", 3, 3);
    market[2]->edit("Oil", 3, 3);
    market[2]->edit("Garbage", 0, 3);
    market[2]->edit("Uranium", 0, 3);

    market[3] = new ResourceManager();
    market[3]->edit("Coal", 3, 4);
    market[3]->edit("Oil", 3, 4);
    market[3]->edit("Garbage", 0, 4);
    market[3]->edit("Uranium", 0, 4);


    market[4] = new ResourceManager();
    market[4]->edit("Coal", 3, 5);
    market[4]->edit("Oil", 3, 5);
    market[4]->edit("Garbage", 0, 5);
    market[4]->edit("Uranium", 0, 5);

    market[5] = new ResourceManager();
    market[5]->edit("Coal", 3, 6);
    market[5]->edit("Oil", 3, 6);
    market[5]->edit("Garbage", 0, 6);
    market[5]->edit("Uranium", 0, 6);


    market[6] = new ResourceManager();
    market[6]->edit("Coal", 3, 7);
    market[6]->edit("Oil", 3, 7);
    market[6]->edit("Garbage", 3, 7);
    market[6]->edit("Uranium", 0, 7);


    market[7] = new ResourceManager();
    market[7]->edit("Coal", 3, 8);
    market[7]->edit("Oil", 3, 8);
    market[7]->edit("Garbage", 3, 8);
    market[7]->edit("Uranium", 0, 8);

    //Just Uranium from here on
    market[8] = new ResourceManager();
    market[8]->edit("Uranium", 0, 10);

    market[9] = new ResourceManager();
    market[9]->edit("Uranium", 0, 12);

    market[10] = new ResourceManager();
    market[10]->edit("Uranium", 1, 14);

    market[11] = new ResourceManager();
    market[11]->edit("Uranium", 1, 16);

}

// Haven't finished it, still working on it