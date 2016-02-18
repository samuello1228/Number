//
//  PositiveInteger.cpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "PositiveInteger.hpp"
#include <iostream>
using namespace std;
PositiveInteger::PositiveInteger()
{
	leftEnd = nullptr;
	rightEnd = nullptr;
	numberOfDigit = nullptr;
	numberOfDigitParent = nullptr;
	isOne=false;
	isTwo=false;
}

PositiveInteger::~PositiveInteger()
{
	if(getLeftEnd() != nullptr && getRightEnd() != nullptr)
	{
		Bit* digit1 = getLeftEnd();
		Bit* digit2;
		while(!digit1->isRightEnd())
		{
			digit2 = digit1->getRight();
			delete digit1;
			digit1 = digit2;
		}
		delete digit1;
	}

	if(!getIsOne() && !getIsTwo())
	{
		delete numberOfDigit;
	}
}

Bit* PositiveInteger::getLeftEnd()
{
	return leftEnd;
}
void PositiveInteger::setLeftEnd(Bit* newLeftEnd)
{
	leftEnd = newLeftEnd;
}

Bit* PositiveInteger::getRightEnd()
{
	return rightEnd;
}
void PositiveInteger::setRightEnd(Bit* newRightEnd)
{
	rightEnd = newRightEnd;
}

PositiveInteger* PositiveInteger::getNumberOfDigit()
{
	return numberOfDigit;
}
void PositiveInteger::setNumberOfDigit(PositiveInteger* newNumberOfDigit)
{
	numberOfDigit = newNumberOfDigit;
}
PositiveInteger* PositiveInteger::getNumberOfDigitParent()
{
	return numberOfDigitParent;
}
void PositiveInteger::setNumberOfDigitParent(PositiveInteger* newNumberOfDigitParent)
{
	numberOfDigitParent = newNumberOfDigitParent;
}

bool PositiveInteger::getIsOne()
{
	return isOne;
}
void PositiveInteger::setIsOne(bool newIsOne)
{
	isOne = newIsOne;
}

bool PositiveInteger::getIsTwo()
{
	return isTwo;
}
void PositiveInteger::setIsTwo(bool newIsTwo)
{
	isTwo = newIsTwo;
}


PositiveInteger::PositiveInteger(unsigned int x)
{
	if(x==1)
	{
		setIsOne(true);
		setIsTwo(false);
		rightEnd = new Bit;
		rightEnd->setDigit(1);
		setLeftEnd(rightEnd);
		setNumberOfDigit(nullptr);
		setNumberOfDigitParent(nullptr);
	}
	else if(x==2)
	{
		setIsOne(false);
		setIsTwo(true);
		rightEnd = new Bit;
		leftEnd = new Bit;
		rightEnd->setDigit(0);
		leftEnd->setDigit(1);
		rightEnd->setLeft(leftEnd);
		leftEnd->setRight(rightEnd);
		setNumberOfDigit(nullptr);
		setNumberOfDigitParent(nullptr);
	}
	else if(x>=3)
	{
		setIsOne(false);
		setIsTwo(false);
		
		int count=1;
		rightEnd = new Bit;
		rightEnd->setDigit(x%2);
		x = (x - rightEnd->getDigit())/2;
		
		Bit* digit1 = getRightEnd();
		Bit* digit2;
		while(x>=1)
		{
			count++;
			digit2 = new Bit;
			digit2->setDigit(x%2);
			digit1->setLeft(digit2);
			digit2->setRight(digit1);
			x = (x - digit2->getDigit())/2;
			digit1 = digit2;
		}
		setLeftEnd(digit1);
		
		numberOfDigit = new PositiveInteger(count);
		numberOfDigit->setNumberOfDigitParent(this);
	}
}

void PositiveInteger::printBinary()
{
	PositiveInteger* x = this;
	Bit* digit;
	while(!x->getIsOne() && !x->getIsTwo())
	{
		digit = x->getLeftEnd();
		cout<<digit->getDigit();
		while(!digit->isRightEnd())
		{
			digit = digit->getRight();
			cout<<digit->getDigit();
		}
		cout<<" - ";
		
		x = x->getNumberOfDigit();
	}
	
	if(x->getIsOne())
	{
		cout<<"1"<<endl;
	}
	else if(x->getIsTwo())
	{
		cout<<"10"<<endl;
	}
	
}

int PositiveInteger::compare(PositiveInteger* x1, PositiveInteger* x2)
{
	/*
	1: x1>x2
	0: x1=x2
	-1: x1<x2
	*/
	
	PositiveInteger* n1 = x1;
	PositiveInteger* n2 = x2;
	while( !n1->getIsOne() && !n1->getIsTwo() && !n2->getIsOne() && !n2->getIsTwo())
	{
		n1 = n1->getNumberOfDigit();
		n2 = n2->getNumberOfDigit();
	}
	
	if( (n1->getIsOne() || n1->getIsTwo()) && (!n2->getIsOne() && !n2->getIsTwo()) )
	{
		return -1;
	}
	
	if( (!n1->getIsOne() && !n1->getIsTwo()) && (n2->getIsOne() || n2->getIsTwo()) )
	{
		return 1;
	}

	//(n1->getIsOne() || n1->getIsTwo()) && (n2->getIsOne() || n2->getIsTwo())
	if(n1->getIsOne() && n2->getIsOne())
	{
		return 0;
	}
	if(n1->getIsOne() && n2->getIsTwo())
	{
		return -1;
	}
	if(n1->getIsTwo() && n2->getIsOne())
	{
		return 1;
	}
	
	// n1->getIsTwo() && n2->getIsTwo()
	Bit* digit1;
	Bit* digit2;
	
	n1 = n1->getNumberOfDigitParent();
	n2 = n2->getNumberOfDigitParent();
	while(n1!=nullptr && n2!=nullptr)
	{
		digit1 = n1->getLeftEnd();
		digit2 = n2->getLeftEnd();
		//the digit at the left end must be 1, no need to check
		while(!digit1->isRightEnd() && !digit2->isRightEnd())
		{
			digit1 = digit1->getRight();
			digit2 = digit2->getRight();
			if(digit1->getDigit()==0 && digit2->getDigit()==1)
			{
				return -1;
			}
			if(digit1->getDigit()==1 && digit2->getDigit()==0)
			{
				return 1;
			}
		}
		n1 = n1->getNumberOfDigitParent();
		n2 = n2->getNumberOfDigitParent();
	}
	
	
	return 0;
}