//
//  main.cpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright � 2016 Reshma Sivakumar. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "list.hpp"
#include "nodedata.hpp"
using namespace std;


int main() {
	list list1, list2;
	nodedata* dataPtr = new nodedata(110, 'g');
	nodedata* dataPtr2 = new nodedata(5, 'a');
	nodedata* dataPtr3 = new nodedata(15, 'a');
	nodedata* deletedPtr;

	list1.insert(*dataPtr);
	list1.insert(*dataPtr2);
	list1.insert(*dataPtr3);
	list1.insert(*deletedPtr);
	cout << list1 << endl;

	// list1.remove(*deletedPtr);

	//cout << list1 << endl;
	//list1.remove(*dataPtr,deletedPtr);
	cout << "list1 " << list1 << endl;
	//cout << "Boob List" << boob << endl;

	ifstream infile("/Users/geethaampalloor/Desktop/Assign_3/Assign_3/nodedata1.txt");
	//list2=list1;
	//cout << "list2 " << list2;
	list2.buildList(infile);
	//if (list1 != list2 )
	// cout << "list1 ad list 2 not equal"<< endl;
	//else
	//   cout << "list1 ad list 2  equal"<< endl;

	cout << "before merge list1  " << list1 << endl;
	cout << "before merge list2 " << list2 << endl;

	list boob;
	list1.intersect(list1, list2);
	//boob = list1 + list2;
	// boob.intersect(list1,list2);
	cout << "after merge list1 " << list1 << endl;
	cout << "after merge list2 " << list2 << endl;
	cout << "Boob List" << boob << endl;


	if (list2.remove(*dataPtr, deletedPtr)) {
		cout << "Data removed " << *deletedPtr << endl;
		delete deletedPtr;
		deletedPtr = NULL;
	}

	// deletedPtr = NULL;
	if (list1.retrieve(*dataPtr, deletedPtr)) {   //uncomment and test , crashes when we try to print null nodedata
		if (deletedPtr)
			cout << "FOUND!!!!!!!!!!!!!!" << *deletedPtr << endl;
		cout << "FOUND!!!!!!!!!!!!!!" << endl;

		// delete deletedPtr;
		//deletedPtr = NULL;
	}
	else
		cout << "NOTTTTTT FOUNDDDD OMG!!!!!!!!!!!!!!" << *deletedPtr << endl;

	//cout << list1 << endl;


	//list boob(list1);

	list2.makeEmpty();
	cout << list1 << " list1" << endl;
	cout << list2 << endl;
	if (list2.isEmpty())
		cout << "Is Empty" << endl;
	else
		cout << "your method sucks!" << endl;

	return 0;
}
