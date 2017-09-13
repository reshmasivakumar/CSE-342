//
//  Node.hpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright � 2016 Reshma Sivakumar. All rights reserved.
//

#ifndef nodedata_HPP
#define nodedata_HPP


#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class nodedata {
	friend ostream& operator<<(ostream&, const nodedata&);

public:

	nodedata(int n = 0, char c = 'z');
	nodedata(const nodedata& other);
	bool setData(ifstream&);
	bool operator ==(const nodedata&) const;
	bool operator !=(const nodedata&) const;
	bool operator <(const nodedata&) const;
	bool operator >(const nodedata&) const;

private:
	int num;
	char ch;
};

#endif /* Node_hpp */

#pragma once
