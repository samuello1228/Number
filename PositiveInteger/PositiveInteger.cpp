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
	isOne=false;
	isTwo=false;
}

PositiveInteger::~PositiveInteger()
{
	if(leftEnd != nullptr && rightEnd != nullptr)
	{
		Bit* digit1 = leftEnd;
		Bit* digit2;
		while(!digit1->isRightEnd())
		{
			digit2 = digit1->getRight();
			delete digit1;
			digit1 = digit2;
		}
		delete digit1;
	}

	if(numberOfDigit != nullptr)
	{
		//delete numberOfDigit;
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
		leftEnd = rightEnd;
		numberOfDigit = nullptr;
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
		numberOfDigit = nullptr;
	}
	else
	{
		setIsOne(false);
		setIsTwo(false);
	}
}

void PositiveInteger::printBinary()
{
	Bit* digit1 = leftEnd;
	cout<<digit1->getDigit();
	while(!digit1->isRightEnd())
	{
		digit1 = digit1->getRight();
		cout<<digit1->getDigit();
	}
	cout<<endl;
}