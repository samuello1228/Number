//
//  RealNumberBound.cpp
//  Number
//
//  Created by Samuel Lo on 12/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "RealNumberBound.hpp"
#include <iostream>
using namespace std;

RealNumberBound::RealNumberBound()
{
	setIsZero(false);
	setSign(true);
	setLeftEnd(nullptr);
	setRightEnd(nullptr);
	setExponent(nullptr);
}

RealNumberBound::RealNumberBound(std::string m,std::string e)
{
	std::string::iterator i=m.begin();
	
	if(*i == '0')
	{
		setIsZero(true);
		setSign(true);
		setLeftEnd(nullptr);
		setRightEnd(nullptr);
		setExponent(nullptr);
		return;
	}
	else if(*i == '-')
	{
		setIsZero(false);
		setSign(false);
		m.erase(i);
		i=m.begin();
	}
	else
	{
		setIsZero(false);
		setSign(true);
	}
	
	Bit* b1 = new Bit;
	Bit* b2;
	setLeftEnd(b1);
	if(*i == '1')
	{
		b1->setDigit(1);
	}
	i++;
	
	while(i!=m.end())
	{
		b2 = new Bit;
		b1->setRight(b2);
		b2->setLeft(b1);
		if(*i == '1')
		{
			b2->setDigit(1);
		}
		b1 = b2;
		i++;
	}
	setRightEnd(b1);

	Integer* p2 = new Integer(e);
	setExponent(p2);
}
RealNumberBound::~RealNumberBound()
{
	if(!getIsZero())
	{
		//if(getLeftEnd() != nullptr && getRightEnd() != nullptr)
		//{
		Bit* digit1 = getLeftEnd();
		Bit* digit2;
		while(!digit1->isRightEnd())
		{
			digit2 = digit1->getRight();
			delete digit1;
			digit1 = digit2;
		}
		delete digit1;
		//}
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

Bit* RealNumberBound::getLeftEnd()
{
	return leftEnd;
}
void RealNumberBound::setLeftEnd(Bit* newLeftEnd)
{
	leftEnd = newLeftEnd;
}
Bit* RealNumberBound::getRightEnd()
{
	return rightEnd;
}
void RealNumberBound::setRightEnd(Bit* newRightEnd)
{
	rightEnd = newRightEnd;
}

Integer* RealNumberBound::getExponent()
{
	return exponent;
}
void RealNumberBound::setExponent(Integer* newExponent)
{
	exponent = newExponent;
}

void RealNumberBound::printBinary()
{
	PositiveInteger* m;
	Bit* digit;
	
	if(getIsZero())
	{
		cout<<"0"<<endl;
		return;
	}
	
	if(!getSign())
	{
		cout<<"-";
	}
	
	digit = getLeftEnd();
	if(digit->isRightEnd())
	{
		cout<<"1";
	}
	else
	{
		cout<<"1.";
	}
	while(!digit->isRightEnd())
	{
		digit = digit->getRight();
		cout<<digit->getDigit();
	}
	
	cout<<"e";
	if(getExponent()->getIsZero())
	{
		cout<<"0"<<endl;
		return;
	}
	if(!getExponent()->getSign())
	{
		cout<<"-";
	}
	
	m = getExponent()->getMagnitude();
	digit = m->getLeftEnd();
	cout<<digit->getDigit();
	while(!digit->isRightEnd())
	{
		digit = digit->getRight();
		cout<<digit->getDigit();
	}
	cout<<endl;
}