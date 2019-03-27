#include "ResourceMarket.h"
#include "ResourceHelper.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

//the constructor initializes game resources
ResourceMarket::ResourceMarket() {
	market[0] = new ResourceHelper();
	market[0]->edit("Coal", 3, 1); //edit(type,quantity,cost)
	market[0]->edit("Oil", 0, 1);
	market[0]->edit("Garbage", 0, 1);
	market[0]->edit("Uranium", 0, 1);


	market[1] = new ResourceHelper();
	market[1]->edit("Coal", 3, 2);
	market[1]->edit("Oil", 0, 2);
	market[1]->edit("Garbage", 0, 2);
	market[1]->edit("Uranium", 0, 2);

	market[2] = new ResourceHelper();
	market[2]->edit("Coal", 3, 3);
	market[2]->edit("Oil", 3, 3);
	market[2]->edit("Garbage", 0, 3);
	market[2]->edit("Uranium", 0, 3);

	market[3] = new ResourceHelper();
	market[3]->edit("Coal", 3, 4);
	market[3]->edit("Oil", 3, 4);
	market[3]->edit("Garbage", 0, 4);
	market[3]->edit("Uranium", 0, 4);


	market[4] = new ResourceHelper();
	market[4]->edit("Coal", 3, 5);
	market[4]->edit("Oil", 3, 5);
	market[4]->edit("Garbage", 0, 5);
	market[4]->edit("Uranium", 0, 5);

	market[5] = new ResourceHelper();
	market[5]->edit("Coal", 3, 6);
	market[5]->edit("Oil", 3, 6);
	market[5]->edit("Garbage", 0, 6);
	market[5]->edit("Uranium", 0, 6);


	market[6] = new ResourceHelper();
	market[6]->edit("Coal", 3, 7);
	market[6]->edit("Oil", 3, 7);
	market[6]->edit("Garbage", 3, 7);
	market[6]->edit("Uranium", 0, 7);


	market[7] = new ResourceHelper();
	market[7]->edit("Coal", 3, 8);
	market[7]->edit("Oil", 3, 8);
	market[7]->edit("Garbage", 3, 8);
	market[7]->edit("Uranium", 0, 8);


	market[8] = new ResourceHelper();
	market[8]->edit("Uranium", 0, 10);

	market[9] = new ResourceHelper();
	market[9]->edit("Uranium", 0, 12);

	market[10] = new ResourceHelper();
	market[10]->edit("Uranium", 1, 14);

	market[11] = new ResourceHelper();
	market[11]->edit("Uranium", 1, 16);

}

//Destructor
ResourceMarket::~ResourceMarket() {

}



//Removes resources purchased by players during phase 3
void ResourceMarket::updateMarket(string resource, int quantity) {

	for (int i = 11; i >= 0; i++) {

		while (market[i]->getResourceQuantity(resource) != 0) {
			market[i]->removeSingleResource(resource);//removeOneUnit
			quantity--;
			if (quantity == 0)
				break;
		}
		if (quantity == 0)
			break;
	}

}



//Return total quantity of resource in market
int ResourceMarket::getMarketQuantity(string resource) {

	int amount_in_market = 0;

	for (int i = 0; i <= 11; i++) {
		amount_in_market += market[i]->getResourceQuantity(resource); // no change
	}
	return amount_in_market;
}

//The purpose of this function is to fill the market according to the rule from the table (last page)
//Calls the replenish method which is a helper method for this function
void ResourceMarket::refill(int step, int players) {
                                         //numOfPlayers

	switch (players) {

	case 2:
		if (step == 1) {
			 refillHelper("Coal",3);
			 refillHelper("Oil",2);
			 refillHelper("Garbage",1);
			 refillHelper("Uranium",1);
		}

		if (step == 2) {
			refillHelper("Coal", 4);
			refillHelper("Oil", 2);
			refillHelper("Garbage", 2);
			refillHelper("Uranium", 1);
			
		}

		if (step == 3) {
			refillHelper("Coal", 3);
			refillHelper("Oil", 4);
			refillHelper("Garbage", 3);
			refillHelper("Uranium", 1);

		}

		else if (step != 1 && step != 2 && step != 3) {
			cout << "Error not step 1,2,3" << endl;
			system("pause");
		}

		break;

	case 3:
		if (step == 1) {
			refillHelper("Coal", 4);
			refillHelper("Oil", 2);
			refillHelper("Garbage", 1);
			refillHelper("Uranium", 1);
		}

		if (step == 2) {
			refillHelper("Coal", 5);
			refillHelper("Oil", 3);
			refillHelper("Garbage", 2);
			refillHelper("Uranium", 1);

		}

		if (step == 3) {
			refillHelper("Coal", 3);
			refillHelper("Oil", 4);
			refillHelper("Garbage", 3);
			refillHelper("Uranium", 1);

		}

		else if (step != 1 && step != 2 && step != 3) {
			cout << "Error not step 1,2,3" << endl;
			system("pause");
		}
		break;

	case 4:
		if (step == 1) {
			refillHelper("Coal", 5);
			refillHelper("Oil", 3);
			refillHelper("Garbage", 2);
			refillHelper("Uranium", 1);
		}

		if (step == 2) {
			refillHelper("Coal", 6);
			refillHelper("Oil", 4);
			refillHelper("Garbage", 3);
			refillHelper("Uranium", 2);

		}

		if (step == 3) {
			refillHelper("Coal", 4);
			refillHelper("Oil", 5);
			refillHelper("Garbage", 4);
			refillHelper("Uranium", 2);

		}

		else if (step != 1 && step != 2 && step != 3) {
			cout << "Error not step 1,2,3" << endl;
			system("pause");
		}
		break;

	case 5:// too large for a demo
		break;
	case 6:// too large for a demo
		break;

	default:
		cout << "Error number of players" << endl;
		system("pause");

	}


}

//Replenish resources at any quantity
void ResourceMarket::refillHelper(string resource, int quantity) {

	if (resource == "Coal" || resource == "Oil" || resource == "Garbage") {

		for (int i = 7; i >= 0; i--) { // why 7? -> only market obj from [0] to [7] has Coal,Oil, Garbage

			//why < 3? -> no market obj has less than 3 quantities from [0] to [7]
			while (market[i]->getResourceQuantity(resource) < 3) {
				market[i]->addSingleResource(resource);
				quantity--;
				if (quantity == 0)
					break;
			}
			if (quantity == 0)
				break;
		}
	}
	
	//Replenishing Uranium occurs at the last index
	if (resource == "Uranium") {

		for (int i = 11; i >= 0; i--) { // why 11? -> all 11 markets objs has Uranium

			//why < 1? -> no market obj has less than 1 quantity of Uranium
			while (market[i]->getResourceQuantity(resource) < 1) {
				market[i]->addSingleResource(resource);//addOneUnit
				quantity--;
			
				if (quantity == 0)
					break;
			}
			if (quantity == 0)
				break;
		}
	}

}

//It find empty cells, if no empty cells Return -1
//It's a "helper function" for getMarketCost
int ResourceMarket::findEmpty(string resource) {

	int i = 0; // i is a global variable

	if (resource == "Oil" || resource == "Coal" || resource == "Garbage")
		i = 7;
	else {
		i = 11;
	}

	for (i; i >= 0; i--) {

		//If index has empty "Resource" 
		if (market[i]->getResourceQuantity(resource) == 0) {
			return i;
		}
	}

	return -1;
}


//It returns index with partial amount of resources
//It's a "helper function" for getMarketCost
int ResourceMarket::findRemaining(string resource) {

	if (resource == "Uranium") //Should not use this function for Uranium since Uranium can only have 1
		return findEmpty("Uranium");

	for (int i = 7; i >= 0; i--) {

		//If index is not full
		if (market[i]->getResourceQuantity(resource) == 1 || market[i]->getResourceQuantity(resource) == 2) {
			return i;
		}
	}

	return -1;
}

//It returns current cost of an valid quantity of a resource
int ResourceMarket::getMarketCost(string resource, int quantity) {

	if (quantity > this->getMarketQuantity(resource)) {
		cout << "The market does not have enough quantity for " << resource <<" "<< endl;
		return -1;
	}

	//The following are helper counters for the functionality of the method
	int i = 0;
	int i1 = findRemaining(resource); //-1 is everything is full or not empty
	int i2 = findEmpty(resource); //-1 if nothing is empty
	int counter = 0;
	bool insideIndex = true;

	//The cost of the resource
	int cost = 0;
	//The following two if statements allow us to start at the proper resource slot
	if (i1 != -1)
		i = i1;

	else if (i2 != -1)
		i = i2;

	//Looping through market to find cost the desired quantity
	while (quantity != 0) {
		insideIndex = true;
		int amountAtIndex = market[i + counter]->getResourceQuantity(resource);

		while (insideIndex) {

			if (amountAtIndex != 0) {
				cost += market[i + counter]->getResourceCost(resource); //Computing cost of 1 unit at that index
				quantity -= 1; //Getting the cost of 1 resource at a time
				amountAtIndex--;

				if (quantity == 0)
					return cost;
			}
			else {
				counter++; //Move to next slot
				insideIndex = false; //No longer inside current slot
			}
		} //End of inner while

	}//End of while
	return cost;

}



void ResourceMarket::saveMarket() {

	ofstream output;

	//  Open existing file resourcemarket.txt or create a new file
	output.open("resourcemarket.txt");
	cout << "Saving ResourceMarket" << endl;

	// Loops through the ResourceMarket array and saves only the quantities to the .txt
	for (int i = 0; i <= 11; i++) {
		output << 
			market[i]->getResourceQuantity("Coal") << "  " <<
			market[i]->getResourceQuantity("Oil") << "  " <<
			market[i]->getResourceQuantity("Garbage") << "  " <<
			market[i]->getResourceQuantity("Uranium") << "  " << endl;
	}

	output.close();

	cout << "\nResourceMarket Saved!" << endl << endl;

}
void ResourceMarket::loadMarket() {

	int coal_amt,oil_amt,garbage_amt,uranium_amt,i=0,k = 10;
	

	// Opening "resourcemarket.txt"
	ifstream input("resourcemarket.txt");

	cout << "Loading ResourceMarket" << endl << "-------------------------" << endl;

	// Reads each int one by one in line (left to right) coal->oil->garbage->uranium...nextline
	while (input >> coal_amt >> oil_amt >> garbage_amt >> uranium_amt) {


		if (i < 8) { //the price of the resource market
			//obj[0]->[7]

			market[i]->edit("Coal", coal_amt, i + 1); // cost i+1
			market[i]->edit("Oil", oil_amt, i + 1);
			market[i]->edit("Garbage", garbage_amt, i + 1);
			market[i]->edit("Uranium", uranium_amt, i + 1);
		}
			
	
		// Handles prices 10,12,14,16 from the price of the resource market
		if (i >= 8) {
			
			market[i]->edit("Coal", coal_amt, k);
			market[i]->edit("Oil", oil_amt, k);
			market[i]->edit("Garbage", garbage_amt, k);
			market[i]->edit("Uranium", uranium_amt, k);
			k = k + 2;
		}
			i++;

		/*
		// IGNORE:: checking if right amounts are implemented
			cout << "Coal" << coal_amt << endl;
			cout << "Oil" << oil_amt << endl;
			cout << "Garbage" << garbage_amt << endl;
			cout << "Uranium" << uranium_amt << endl;
			cout << i << endl;
			i++;
		*/
	}
}


void ResourceMarket::showInfo() {

	for (int i = 0; i <= 11; i++) {

		cout << "Slot[" << i << "]: " << "Coal, Oil, Garbage, Uranium" << endl << "Quantity: " <<
			market[i]->getResourceQuantity("Coal") << ",  " <<
			market[i]->getResourceQuantity("Oil") << ",  " <<
			market[i]->getResourceQuantity("Garbage") << ",  " <<
			market[i]->getResourceQuantity("Uranium") << "  " << endl << "Price: " << market[i]->getResourceCost("Uranium") << endl << endl;
	}

}

int ResourceMarket::getTotal(string resource) {

	int quantity = 0;

	if (resource == "Uranium") {
		for (int i = 0; i <= 11; i++)
			quantity += market[i]->getResourceQuantity(resource);
		return quantity;
	}

	for (int i = 0; i <= 7; i++)
		quantity += market[i]->getResourceQuantity(resource);

	return quantity;
}

void ResourceMarket::showRemaining() {

	cout << "Remaining Coal in Market: " << getTotal("Coal") << endl
		<< "Remaining Oil in Market: " << getTotal("Oil") << endl
		<< "Remaining Garbage in Market: " << getTotal("Garbage") << endl
		<< "Remaining Uranium in Market: " << getTotal("Uranium") << endl;

}
