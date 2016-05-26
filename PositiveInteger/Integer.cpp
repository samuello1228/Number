//
//  Integer.cpp
//  Number
//
//  Created by Samuel Lo on 26/5/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "Integer.hpp"
#include <iostream>
using namespace std;

Integer::Integer()
{
	isZero = false;
	sign = true;
	magnitude = nullptr;
}
Integer::Integer(int x)
{
	if(x==0)
	{
		isZero = true;
		sign = true;
		magnitude = nullptr;
	}
	else
	{
		isZero = false;
		if(x>0)
		{
			sign = true;
			magnitude = new PositiveInteger(x);
		}
		else
		{
			sign = false;
			magnitude = new PositiveInteger(-x);
		}
	}
}

Integer::~Integer()
{
	if(!isZero)
	{
		delete magnitude;
	}
}


bool Integer::getIsZero()
{
	return isZero;
}
void Integer::setIsZero(bool newIsZero)
{
	isZero = newIsZero;
}

bool Integer::getSign()
{
	return sign;
}
void Integer::setSign(bool newSign)
{
	sign = newSign;
}

PositiveInteger* Integer::getMagnitude()
{
	return magnitude;
}
void Integer::setMagnitude(PositiveInteger* newMagnitude)
{
	magnitude = newMagnitude;
}

void Integer::One(Integer* x)
{
	x->setIsZero(false);
	x->setSign(true);
	PositiveInteger* a = new PositiveInteger;
	PositiveInteger::One(a);
	x->setMagnitude(a);
}

void Integer::printBinary()
{
	if(getIsZero())
	{
		cout<<"0"<<endl;
	}
	else if(getSign())
	{
		getMagnitude()->printBinary();
	}
	else
	{
		cout<<"-";
		getMagnitude()->printBinary();
	}
}
void Integer::printDecimal(bool overwrite)
{
	if(getIsZero())
	{
		cout<<"0"<<endl;
	}
	else if(getSign())
	{
		getMagnitude()->printDecimal(overwrite);
	}
	else
	{
		cout<<"-";
		getMagnitude()->printDecimal(overwrite);
	}
}

Integer* Integer::copy()
{
	Integer* y = new Integer;
	PositiveInteger* p1;
	if(getIsZero())
	{
		y->setIsZero(true);
		return y;
	}
	else
	{
		y->setIsZero(false);
		if(getSign())
		{
			y->setSign(true);
			p1 = getMagnitude()->copy();
			y->setMagnitude(p1);
			return y;
		}
		else
		{
			y->setSign(false);
			p1 = getMagnitude()->copy();
			y->setMagnitude(p1);
			return y;
		}
	}
	
}