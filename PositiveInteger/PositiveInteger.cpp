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
	setLeftEnd(nullptr);
	setRightEnd(nullptr);
	setNumberOfDigit(nullptr);
	setNumberOfDigitParent(nullptr);
	setIsOne(false);
	setIsTwo(false);
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

	if(!isOneOrTwo())
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
bool PositiveInteger::isOneOrTwo()
{
	return getIsOne() || getIsTwo();
}
void PositiveInteger::One(PositiveInteger* x)
{
	x->setIsOne(true);
	x->setIsTwo(false);
	Bit* temp = new Bit;
	x->setRightEnd(temp);
	
	x->getRightEnd()->setDigit(1);
	x->setLeftEnd(x->getRightEnd());
	x->setNumberOfDigit(nullptr);
	x->setNumberOfDigitParent(nullptr);
}
void PositiveInteger::Two(PositiveInteger* x)
{
	x->setIsOne(false);
	x->setIsTwo(true);
	Bit* temp = new Bit;
	x->setRightEnd(temp);
	temp = new Bit;
	x->setLeftEnd(temp);
	
	x->getRightEnd()->setDigit(0);
	x->getLeftEnd()->setDigit(1);
	x->getRightEnd()->setLeft(x->getLeftEnd());
	x->getLeftEnd()->setRight(x->getRightEnd());
	x->setNumberOfDigit(nullptr);
	x->setNumberOfDigitParent(nullptr);
}

PositiveInteger::PositiveInteger(unsigned int x)
{
	if(x==1)
	{
		PositiveInteger::One(this);
	}
	else if(x==2)
	{
		PositiveInteger::Two(this);

	}
	else if(x>=3)
	{
		setIsOne(false);
		setIsTwo(false);
		
		int count=1;
		Bit* digit1 = new Bit;;
		Bit* digit2;
		digit1->setDigit(x%2);
		setRightEnd(digit1);
		x = (x - digit1->getDigit())/2;

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
		
		PositiveInteger* temp2 = new PositiveInteger(count);
		setNumberOfDigit(temp2);
		getNumberOfDigit()->setNumberOfDigitParent(this);
	}
}

void PositiveInteger::printBinary()
{
	PositiveInteger* x = this;
	Bit* digit;
	/*
	digit = x->getLeftEnd();
	cout<<digit->getDigit();
	while(!digit->isRightEnd())
	{
		digit = digit->getRight();
		cout<<digit->getDigit();
	}
	cout<<endl;
	*/
	///*
	while(!x->isOneOrTwo())
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
	//*/
}

PositiveInteger* PositiveInteger::copy()
{
	PositiveInteger* a1 = this;
	PositiveInteger* a2;
	
	PositiveInteger* x1 = new PositiveInteger;
	PositiveInteger* x2;
	PositiveInteger* y = x1;
	Bit* temp;
	Bit* digit1;
	Bit* digit2;
	
	x1->setIsOne(a1->getIsOne());
	x1->setIsTwo(a1->getIsTwo());
	temp = a1->getRightEnd();
	digit1 = new Bit;
	digit1->setDigit(temp->getDigit());
	x1->setRightEnd(digit1);
	while(!temp->isLeftEnd())
	{
		temp = temp->getLeft();
		digit2 = new Bit;
		digit2->setDigit(temp->getDigit());
		digit1->setLeft(digit2);
		digit2->setRight(digit1);
		digit1 = digit2;
	}
	x1->setLeftEnd(digit1);
	
	while(!a1->isOneOrTwo())
	{
		a2 = a1->getNumberOfDigit();
		
		x2 = new PositiveInteger;
		x2->setIsOne(a2->getIsOne());
		x2->setIsTwo(a2->getIsTwo());
		temp = a2->getRightEnd();
		digit1 = new Bit;
		digit1->setDigit(temp->getDigit());
		x2->setRightEnd(digit1);
		while(!temp->isLeftEnd())
		{
			temp = temp->getLeft();
			digit2 = new Bit;
			digit2->setDigit(temp->getDigit());
			digit1->setLeft(digit2);
			digit2->setRight(digit1);
			digit1 = digit2;
		}
		x2->setLeftEnd(digit1);
		x1->setNumberOfDigit(x2);
		x2->setNumberOfDigitParent(x1);
		
		a1=a2;
		x1=x2;
	}

	return y;
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
	while(!n1->isOneOrTwo() && !n2->isOneOrTwo())
	{
		n1 = n1->getNumberOfDigit();
		n2 = n2->getNumberOfDigit();
	}
	
	if(n1->isOneOrTwo() && !n2->isOneOrTwo())
	{
		return -1;
	}
	
	if(!n1->isOneOrTwo() && n2->isOneOrTwo())
	{
		return 1;
	}

	// n1->isOneOrTwo() && n2->isOneOrTwo()
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
			if(!digit1->getDigit() && digit2->getDigit())
			{
				return -1;
			}
			if(digit1->getDigit() && !digit2->getDigit())
			{
				return 1;
			}
		}
		n1 = n1->getNumberOfDigitParent();
		n2 = n2->getNumberOfDigitParent();
	}
	return 0;
}

void PositiveInteger::AddThreeBit(bool x1, bool x2, bool x3, bool &y1, bool &y2)
{
	if(!x1)
	{
		if(!x2)
		{
			if(!x3)
			{
				//000
				y1=0;
				y2=0;
			}
			else
			{
				//001
				y1=0;
				y2=1;
			}
		}
		else
		{
			if(!x3)
			{
				//010
				y1=0;
				y2=1;
			}
			else
			{
				//011
				y1=1;
				y2=0;
			}
		}
	}
	else
	{
		if(!x2)
		{
			if(!x3)
			{
				//100
				y1=0;
				y2=1;
			}
			else
			{
				//101
				y1=1;
				y2=0;
			}
		}
		else
		{
			if(!x3)
			{
				//110
				y1=1;
				y2=0;
			}
			else
			{
				//111
				y1=1;
				y2=1;
			}
		}
	}
}

PositiveInteger* PositiveInteger::Add(PositiveInteger* x1,PositiveInteger* x2)
{
	PositiveInteger* temp;
	Bit* temp2=nullptr;
	Bit* temp3=nullptr;
	if(PositiveInteger::compare(x1,x2)==-1)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	
	PositiveInteger* y;
	if(x1->getIsOne() && x2->getIsOne())
	{
		y = new PositiveInteger;
		PositiveInteger::Two(y);
		return y;
	}
	if(x1->getIsTwo() && x2->getIsOne())
	{
		y = new PositiveInteger;
		y->setIsOne(false);
		y->setIsTwo(false);
		temp2 = new Bit;
		y->setLeftEnd(temp2);
		temp2 = new Bit;
		y->setRightEnd(temp2);
		
		y->getLeftEnd()->setDigit(1);
		y->getRightEnd()->setDigit(1);
		y->getLeftEnd()->setRight(y->getRightEnd());
		y->getRightEnd()->setLeft(y->getLeftEnd());
		
		temp = new PositiveInteger;
		PositiveInteger::Two(temp);
		y->setNumberOfDigit(temp);
		temp->setNumberOfDigitParent(y);
	}
	
	//
	y = new PositiveInteger;
	y->setIsOne(false);
	y->setIsTwo(false);
	
	bool carry=0;
	bool result1;
	bool result2;
	
	Bit* digit1=x1->getRightEnd();
	Bit* digit2=x2->getRightEnd();
	PositiveInteger::AddThreeBit(digit1->getDigit(),digit2->getDigit(),carry,result1,result2);
	temp2 = new Bit;
	temp2->setDigit(result2);
	y->setRightEnd(temp2);
	carry=result1;
	
	while(!digit2->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		digit2 = digit2->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),digit2->getDigit(),carry,result1,result2);
		temp3 = new Bit;
		temp3->setDigit(result2);
		temp2->setLeft(temp3);
		temp3->setRight(temp2);
		carry=result1;
		temp2=temp3;
	}
	
	while(!digit1->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),0,carry,result1,result2);
		temp3 = new Bit;
		temp3->setDigit(result2);
		temp2->setLeft(temp3);
		temp3->setRight(temp2);
		carry=result1;
		temp2=temp3;
	}
	if(carry)
	{
		temp3 = new Bit;
		temp3->setDigit(1);
		temp2->setLeft(temp3);
		temp3->setRight(temp2);
		temp2=temp3;
		
		
	}
	else
	{
		
	}
	y->setLeftEnd(temp2);
	
	return y;
}
