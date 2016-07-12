//
//  RealNumberBound.cpp
//  Number
//
//  Created by Samuel Lo on 12/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "RealNumberBound.hpp"

RealNumberBound::RealNumberBound()
{
	setIsZero(false);
	setSign(true);
	setMagnitude(nullptr);
	setExponent(nullptr);
}

RealNumberBound::RealNumberBound(std::string m,std::string e)
{
	std::string::iterator i=m.begin();
	
	if(*i == '0')
	{
		setIsZero(true);
		setSign(true);
		setMagnitude(nullptr);
		setExponent(nullptr);
		return;
	}
	else if(*i == '-')
	{
		setIsZero(false);
		setSign(false);
		m.erase(i);
	}
	else
	{
		setIsZero(false);
		setSign(true);
	}
	
	PositiveInteger* p1 = new PositiveInteger(m);
	setMagnitude(p1);
	
	Integer* p2 = new Integer(e);
	setExponent(p2);
}
RealNumberBound::~RealNumberBound()
{
	if(!getIsZero())
	{
		delete magnitude;
		delete exponent;
	}
}


bool RealNumberBound::getIsZero()
{
	return isZero;
}
void RealNumberBound::setIsZero(bool newIsZero)
{
	isZero = newIsZero;
}

bool RealNumberBound::getSign()
{
	return sign;
}
void RealNumberBound::setSign(bool newSign)
{
	sign = newSign;
}

PositiveInteger* RealNumberBound::getMagnitude()
{
	return magnitude;
}
void RealNumberBound::setMagnitude(PositiveInteger* newMagnitude)
{
	magnitude = newMagnitude;
}

Integer* RealNumberBound::getExponent()
{
	return exponent;
}
void RealNumberBound::setExponent(Integer* newExponent)
{
	exponent = newExponent;
}

