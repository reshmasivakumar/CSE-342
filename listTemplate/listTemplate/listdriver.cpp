//
//  main.cpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright � 2016 Reshma Sivakumar. All rights reserved.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "list.h"
#include "nodedata.hpp"
using namespace std;


int main() {
	
	list<nodedata> list1, list2;
	nodedata* dataPtr = new nodedata(110, 'g');
	nodedata* dataPtr2 = new nodedata(115, 'a');
	nodedata* dataPtr3 = new nodedata(15, 'a');
	nodedata deletedPtr;
	//ifstream infile("nodedata1.txt");
	//list1.buildList(infile);
	//cout << list1 << endl;
	list1.insert(*dataPtr);
	list1.insert(*dataPtr2);
//	cout << list1 << endl;
	list1.insert(*dataPtr3);
	//list2.insertFirst(*dataPtr3);
	std::cout << list1 << endl;
	list<nodedata> list4(list1);
	std::cout << "list2 " << list2 << endl;
	std::cout << "list4 " << list4 << endl;
	/*
	list<nodedata> list5;
	//list1 = list1;
	//list5.intersect(list1, list2);
	//list1 = list1 + list2;
	std::cout << " list5 " << list5;
	//std::cout << " list4 " << list4;
	//cout << "after meger " << list1;
	//list1.remove(*dataPtr, deletedPtr);
	//cout << "deleted " << deletedPtr;
	//deletedPtr = NULL;
	//cout << list1.retrieve(*dataPtr, deletedPtr) << endl;
	//cout << "deleted " << deletedPtr;
	


	//list2.remove(*dataPtr2, deletedPtr);
	//cout << "deleted " << deletedPtr;

	/*
	if (deletedPtr)
	{
		cout << "remove node " << *deletedPtr << endl;
		delete deletedPtr;
            
	}
	cout << list1 << endl;
	nodedata* deletedPtr1;
	if (list2.retrieve(*dataPtr3, deletedPtr1))
		cout << "Found " << endl;
	else
		cout << "No foun" << endl;

	if (deletedPtr1)
		cout << "retrieve node " << *deletedPtr1 << endl;
	*/

	/*\list<double> list1, list2;
	double d1 = 10.0;
	double d2 = 11.0;
	double d3 = 15.0;
	double d4 = 11.0;
	
	list1.insert(d1);
	list1.insert(d2);
	list2.insert(d3);
	list2.insert(d4);
	cout << "list1 " <<list1 << endl;
	cout << "list2 " << list2 << endl;

	list<double> list3 = list1 + list2;
	//.intersect(list1, list2);

	//cout << "after merge " <<  list1.remove(d1 ) << endl;

	//////intersect not working 
	////retrieve not woring for double, not sure how to pass second param
	/// retrieve , amd others crashes

	cout << "list3 " << list3 <<endl;
	//list3.makeEmpty();
	//cout << "list3" << list3 << endl;
	*/
	return 0;
}
