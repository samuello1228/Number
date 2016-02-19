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
	x->setNumberOfDigit(x);
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
	x->setNumberOfDigit(x);
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
	///*
	digit = x->getLeftEnd();
	cout<<digit->getDigit();
	while(!digit->isRightEnd())
	{
		digit = digit->getRight();
		cout<<digit->getDigit();
	}
	cout<<endl;
	//*/
	/*
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
	*/
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
	x1->setNumberOfDigit(x1);

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
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	Bit* b1;
	Bit* b2;
	if(PositiveInteger::compare(x1,x2)==-1)
	{
		p1=x1;
		x1=x2;
		x2=p1;
	}
	
	PositiveInteger* y;
	if(x1->getIsOne() && x2->getIsOne())
	{
		y = new PositiveInteger;
		PositiveInteger::Two(y);
		return y;
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
	b1 = new Bit;
	b1->setDigit(result2);
	y->setRightEnd(b1);
	carry=result1;
	
	while(!digit2->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		digit2 = digit2->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),digit2->getDigit(),carry,result1,result2);
		b2 = new Bit;
		b2->setDigit(result2);
		b1->setLeft(b2);
		b2->setRight(b1);
		carry = result1;
		b1 = b2;
	}
	
	while(!digit1->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),0,carry,result1,result2);
		b2 = new Bit;
		b2->setDigit(result2);
		b1->setLeft(b2);
		b2->setRight(b1);
		carry = result1;
		b1 = b2;
	}
	if(carry)
	{
		b2 = new Bit;
		b2->setDigit(1);
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		
		p1 = x1->getNumberOfDigit()->copy();
		p2 = new PositiveInteger;
		PositiveInteger::One(p2);
		p3 = PositiveInteger::Add(p1,p2);
		delete p1;
		delete p2;
		y->setNumberOfDigit(p3);
		p3->setNumberOfDigitParent(y);
	}
	else
	{
		p1 = x1->getNumberOfDigit()->copy();
		y->setNumberOfDigit(p1);
		p1->setNumberOfDigitParent(y);
	}
	y->setLeftEnd(b1);
	
	return y;
}

PositiveInteger* PositiveInteger::Multiply(PositiveInteger* x1,PositiveInteger* x2)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	Bit* b1;
	Bit* b2;
	Bit* tLeft;
	Bit* tRight;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	Bit* c2;
	
	
	PositiveInteger* y;
	
	if(x1->getIsOne() && x2->getIsOne())
	{
		y = new PositiveInteger;
		PositiveInteger::One(y);
		return y;
	}
	if( (x1->getIsOne() && x2->getIsTwo()) || (x1->getIsTwo() && x2->getIsOne()) )
	{
		y = new PositiveInteger;
		PositiveInteger::Two(y);
		return y;
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
	if(!digit1->getDigit() || !digit2->getDigit())
	{
		b1 = new Bit;
		b1->setDigit(0);
		y->setRightEnd(b1);
		while(!digit1->getDigit())
		{
			b2 = new Bit;
			b2->setDigit(0);
			b1->setLeft(b2);
			b2->setRight(b1);
			digit1 = digit1->getLeft();
			b1 = b2;
		}
		while(!digit2->getDigit())
		{
			b2 = new Bit;
			b2->setDigit(0);
			b1->setLeft(b2);
			b2->setRight(b1);
			digit2 = digit2->getLeft();
			b1 = b2;
		}
		//Now, b1 is a additional 0 at the left end, and it must be 1
		b1->setDigit(1);
	}
	else
	{
		b1 = new Bit;
		b1->setDigit(1);
		y->setRightEnd(b1);
	}
	
	//Add one more 0 at the right end temporarily, and delete it later
	t1 = new Bit;
	t1->setDigit(0);
	tRight = t1;
	c1 = digit1;
	while(!c1->isLeftEnd())
	{
		c1 = c1->getLeft();
		t2 = new Bit;
		t2->setDigit(c1->getDigit());
		t1->setLeft(t2);
		t2->setRight(t1);
		t1 = t2;
	}
	
	//add two more 0 at the left end
	t2 = new Bit;
	t2->setDigit(0);
	t1->setLeft(t2);
	t2->setRight(t1);
	t1 = t2;
	
	t2 = new Bit;
	t2->setDigit(0);
	t1->setLeft(t2);
	t2->setRight(t1);
	t1 = t2;
	
	tLeft=t1;
	tRight = tRight->getLeft();
	delete tRight->getRight();
	tRight->setRight(nullptr);
	
	while(!digit2->isLeftEnd())
	{
		digit2 = digit2->getLeft();
		
		if(digit2->getDigit())
		{
			c1 = digit1;
			t1 = tRight;
			carry=0;
			PositiveInteger::AddThreeBit(c1->getDigit(),t1->getDigit(),carry,result1,result2);
			
			b2 = new Bit;
			b2->setDigit(result2);
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
			
			carry=result1;
			while(!c1->isLeftEnd())
			{
				c1 = c1->getLeft();
				t1 = t1->getLeft();
				PositiveInteger::AddThreeBit(c1->getDigit(),t1->getDigit(),carry,result1,result2);
				t1->setDigit(result2);
				carry=result1;
			}
			if(carry)
			{
				t1 = t1->getLeft();
				t1->setDigit(carry);
			}
		}
		else
		{
			b2 = new Bit;
			b2->setDigit(tRight->getDigit());
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		//add one more 0 at the left and delete one right end
		t2 = new Bit;
		t2->setDigit(0);
		tLeft->setLeft(t2);
		t2->setRight(tLeft);
		tLeft=t2;
		tRight = tRight->getLeft();
		delete tRight->getRight();
		tRight->setRight(nullptr);
	}
	tLeft = tLeft->getRight();
	delete tLeft->getLeft();
	tLeft->setLeft(nullptr);

	t1 = tRight;
	while(!t1->isLeftEnd())
	{
		b2 = new Bit;
		b2->setDigit(t1->getDigit());
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		t1 = t1->getLeft();
		delete t1->getRight();
	}
	if(t1->getDigit())
	{
		b2 = new Bit;
		b2->setDigit(t1->getDigit());
		b1->setLeft(b2);
		b2->setRight(b1);
		y->setLeftEnd(b2);
	}
	else
	{
		y->setLeftEnd(b1);
	}
	delete t1;
	
	
	
	return y;
}