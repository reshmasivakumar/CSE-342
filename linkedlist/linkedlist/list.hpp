//
//  list.hpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright � 2016 Reshma Sivakumar. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "nodedata.hpp"
using namespace std;

class list {
	friend ostream& operator<<(ostream&, const list&);

private:
	struct Node {
		nodedata* data;
		Node* next;
	};

	Node* head;
	int size;
	void copy(const list&);


public:
	list();
	list(const list&);
	~list();
	void buildList(ifstream&);
	bool insert(nodedata&);
	bool remove(const nodedata&);
	bool remove(const nodedata&, nodedata*&);
	bool isEmpty() const;
	bool retrieve(const nodedata&, nodedata*&) const;
	bool retrieve(const nodedata&) const;
	void merge(list&, list&);
	void intersect(const list&, const list&);
	void makeEmpty();
	void makeEmpty(list&) const;
	int getSize() const;
	list operator +(const list&) const;
	list& operator =(const list&);
	bool operator ==(const list&) const;
	bool operator !=(const list&) const;


};


#endif /* list_hpp */
#pragma once
