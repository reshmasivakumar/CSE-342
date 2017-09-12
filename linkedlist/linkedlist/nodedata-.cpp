//
//  nodedata.cpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright © 2016 Reshma Sivakumar. All rights reserved.
//

#include "stdafx.h"
#include "nodedata.hpp"


nodedata::nodedata(int n, char c) : num(n), ch(c) {};

bool nodedata::setData(ifstream& inFile) {

	if (inFile >> num >> ch)
		return true;
	else
		return false;
}

bool nodedata :: operator ==(const nodedata& rhs) const {
	return (num == rhs.num && ch == rhs.ch);
}

bool nodedata :: operator !=(const nodedata& rhs) const {
	return !(*this == rhs);
}

bool nodedata :: operator >(const nodedata& rhs) const {
	if (num > rhs.num)
		return true;
	else if (num == rhs.num && ch > rhs.ch)
		return true;
	else
		return false;
}

bool nodedata :: operator <(const nodedata& rhs) const {
	if (num < rhs.num)
		return true;
	else if (num == rhs.num && ch < rhs.ch)
		return true;
	else
		return false;
}

ostream& operator <<(ostream& out, const nodedata& data) {
	out << data.num << " " << data.ch << endl;
	return out;
}
