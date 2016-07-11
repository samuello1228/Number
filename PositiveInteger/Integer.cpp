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
	setIsZero(false);
	setSign(true);
	setMagnitude(nullptr);
}

Integer::Integer(std::string x)
{
    std::string::iterator i=x.begin();
    
    if(*i == '0')
    {
        setIsZero(true);
		setSign(true);
		setMagnitude(nullptr);
        return;
    }
    else if(*i == '-')
    {
        setIsZero(false);
        setSign(false);
        x.erase(i);
    }
    else
    {
        setIsZero(false);
        setSign(true);
    }
    
    PositiveInteger* m = new PositiveInteger(x);
    setMagnitude(m);
}
Integer::~Integer()
{
	if(!getIsZero())
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
		y->setSign(true);
		y->setMagnitude(nullptr);
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

//verification
Integer::Integer(int x)
{
	if(x==0)
	{
		setIsZero(true);
		setSign(true);
		setMagnitude(nullptr);
	}
	else
	{
		PositiveInteger* m;
		setIsZero(false);
		if(x>0)
		{
			setSign(true);
			m = new PositiveInteger(x);
			setMagnitude(m);
		}
		else
		{
			setSign(false);
			m = new PositiveInteger(-x);
			setMagnitude(m);
		}
	}
}
bool Integer::isComplete()
{
	if(getIsZero())
	{
		if(!getSign()) return false;
		if(getMagnitude()!=nullptr) return false;
	}
	else
	{
		if(getMagnitude()==nullptr) return false;
		if(!getMagnitude()->isComplete()) return false;
	}
	return true;
}
bool Integer::isSame(int x)
{
	if(!isComplete()) return false;
	
	if(x==0)
	{
		if(!getIsZero()) return false;
	}
	else
	{
		if(getIsZero()) return false;
		if(x>0)
		{
			if(!getSign()) return false;
			if(!getMagnitude()->isSame(x)) return false;

		}
		else
		{
			if(getSign()) return false;
			if(!getMagnitude()->isSame(-x)) return false;
		}
	}
	return true;
}
bool Integer::VerifyCopy(int max)
{
	Integer* p1;
	Integer* p2;
	for(int i=-max;i<=max;i++)
	{
		p1 = new Integer(i);
		//if(!p1->isComplete()) return false;
		//p1->printBinary();
		p2 = p1->copy();
		if(!p2->isSame(i)) return false;
		p2->printBinary();
		
		delete p1;
		delete p2;
	}
	return true;
}
