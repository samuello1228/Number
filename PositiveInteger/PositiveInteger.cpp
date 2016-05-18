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
	//while(!x->isOneOrTwo())
	while(x!=nullptr && !x->isOneOrTwo())
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
	
	if(x==nullptr) {cout<<endl; return;}
	
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
	
	while(n1!=x1 && n2!=x2)
	{
		n1 = n1->getNumberOfDigitParent();
		n2 = n2->getNumberOfDigitParent();
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

PositiveInteger* PositiveInteger::Add(PositiveInteger*& x1,PositiveInteger*& x2,bool overwrite)
{
	PositiveInteger* y;
	PositiveInteger* p1 = nullptr;
	PositiveInteger* p2;
	Bit* b1= nullptr;
	Bit* b2;
	
	if(x1->getIsOne() && x2->getIsOne())
	{
		if(overwrite)
		{
			x1->setIsOne(false);
			x1->setIsTwo(true);
			b1 = x1->getRightEnd();
			b1->setDigit(0);
			
			b2 = new Bit;
			b2->setDigit(1);
			b1->setLeft(b2);
			b2->setRight(b1);
			x1->setLeftEnd(b2);
			return x1;
		}
		else
		{
			y = new PositiveInteger;
			PositiveInteger::Two(y);
			return y;
		}
	}
	
	//swap x1 and x2, if overwrite and the number of digit of x2 is larger.
	int test = PositiveInteger::compare(x1->getNumberOfDigit(),x2->getNumberOfDigit());
	PositiveInteger* n1;
	PositiveInteger* n2;
	if(overwrite)
	{
		if(test==-1)
		{
			p1=x1;
			x1=x2;
			x2=p1;
		}
		n1=x1;
		n2=x2;
		y=x1;
	}
	else
	{
		if(test==-1)
		{
			n1=x2;
			n2=x1;
		}
		else
		{
			n1=x1;
			n2=x2;
		}
		y = new PositiveInteger;
	}
	
	//
	if(overwrite && y->isOneOrTwo())
	{
		p1 = y->copy();
	}
	
	bool carry=0;
	bool result1;
	bool result2;
	
	Bit* digit1=n1->getRightEnd();
	Bit* digit2=n2->getRightEnd();
	PositiveInteger::AddThreeBit(digit1->getDigit(),digit2->getDigit(),carry,result1,result2);
	
	if(overwrite)
	{
		digit1->setDigit(result2);
	}
	else
	{
		b1 = new Bit;
		b1->setDigit(result2);
		y->setRightEnd(b1);
	}
	carry=result1;
	
	while(!digit2->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		digit2 = digit2->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),digit2->getDigit(),carry,result1,result2);
		if(overwrite)
		{
			digit1->setDigit(result2);
		}
		else
		{
			b2 = new Bit;
			b2->setDigit(result2);
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		carry = result1;
	}
	
	while(!digit1->isLeftEnd())
	{
		digit1 = digit1->getLeft();
		PositiveInteger::AddThreeBit(digit1->getDigit(),0,carry,result1,result2);
		if(overwrite)
		{
			digit1->setDigit(result2);
		}
		else
		{
			b2 = new Bit;
			b2->setDigit(result2);
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		carry = result1;
	}
	
	if(carry)
	{
		b2 = new Bit;
		b2->setDigit(1);
		if(overwrite)
		{
			digit1->setLeft(b2);
			b2->setRight(digit1);
			digit1 = b2;
			y->setLeftEnd(digit1);
		}
		else
		{
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		
		
		p2 = new PositiveInteger;
		PositiveInteger::One(p2);
		if(overwrite)
		{
			//Because p1 >= p2, Add function will not swap two numbers
			if(y->isOneOrTwo())
			{
				//y>=3
				p1 = PositiveInteger::Add(p1,p2,true);
				y->setNumberOfDigit(p1);
				p1->setNumberOfDigitParent(y);
			}
			else
			{
				p1 = y->getNumberOfDigit();
				p1 = PositiveInteger::Add(p1,p2,true);
			}
		}
		else
		{
			p1 = n1->getNumberOfDigit();
			p1 = PositiveInteger::Add(p1,p2,false);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
		delete p2;
	}
	else
	{
		if(overwrite)
		{
			if(y->isOneOrTwo())
			{
				//y>=3
				y->setNumberOfDigit(p1);
				p1->setNumberOfDigitParent(y);
			}
		}
		else
		{
			p1 = n1->getNumberOfDigit()->copy();
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
	}
	
	if(!overwrite)
	{
		y->setLeftEnd(b1);
	}
	y->setIsOne(false);
	y->setIsTwo(false);
	return y;
}
PositiveInteger* PositiveInteger::SubtractAux(Bit*& LeftEnd1,Bit*& RightEnd1,PositiveInteger*& n1,bool& isOne1,bool& isTwo1,
											  Bit* LeftEnd2,Bit* RightEnd2,PositiveInteger* n2,bool isOne2,bool isTwo2,
											  bool overwrite)
{
	PositiveInteger* y;
	PositiveInteger* p1;
	PositiveInteger* p2;
	
	Bit* b1;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	Bit* digitLeft1;
	Bit* digitLeft2;
	Bit* digitRight2;
	int test1;
	int test2 = -1;
	
	p2 = new PositiveInteger;
	PositiveInteger::One(p2);
	PositiveInteger* count = new PositiveInteger;
	PositiveInteger::One(count);
	test1 = PositiveInteger::compare(n1,n2);
	if(test1!=0)
	{
		p1 = PositiveInteger::Add(n2,p2,false);
		test2 = PositiveInteger::compare(n1,p1);
		delete p1;
	}
	
	if(overwrite)
	{
		y = nullptr;
	}
	else
	{
		y = new PositiveInteger;
	}
	
	if(test1==0 || (test1!=0 && test2==0))
	{
		if(test1==0)
		{
			//p1 = p2
			digitLeft1 = LeftEnd1;
			digitLeft2 = LeftEnd2;
			while(digitLeft1->getDigit()==digitLeft2->getDigit())
			{
				count = PositiveInteger::Add(count,p2,true);
				digitLeft1 = digitLeft1->getRight();
				digitLeft2 = digitLeft2->getRight();
				if(overwrite)
				{
					delete digitLeft1->getLeft();
					digitLeft1->setLeft(nullptr);
					LeftEnd1 = digitLeft1;
				}
			}
			//digitLeft1 = 1,  digitLeft2 = 0
			if(digitLeft1->isRightEnd())
			{
				//y = 1
				if(overwrite)
				{
					//x1 originally cannot be one or two
					isOne1 = true;
					isTwo1 = false;
				}
				else
				{
					PositiveInteger::One(y);
				}
				delete p2;
				delete count;
				return y;
			}
			digitLeft1 = digitLeft1->getRight();
			digitLeft2 = digitLeft2->getRight();
		}
		else
		{
			//p1 - p2 = 1
			digitLeft1 = LeftEnd1->getRight();
			digitLeft2 = LeftEnd2;
		}
		
		while(!digitLeft1->getDigit() && digitLeft2->getDigit())
		{
			//digitLeft1 = 0, digitLeft2 =1
			count = PositiveInteger::Add(count,p2,true);
			if(overwrite)
			{
				delete digitLeft1->getLeft();
				digitLeft1->setLeft(nullptr);
				LeftEnd1 = digitLeft1;
				digitLeft1->setDigit(1);
			}
			if(digitLeft1->isRightEnd())
			{
				//y = 1
				if(overwrite)
				{
					isOne1 = true;
					isTwo1 = false;
				}
				else
				{
					PositiveInteger::One(y);
				}
				delete p2;
				delete count;
				return y;
			}
			digitLeft1 = digitLeft1->getRight();
			digitLeft2 = digitLeft2->getRight();
		}
		
		//(digitLeft1,digitLeft2) = (0,0) or (1,1) or (1,0)
		if(overwrite)
		{
			t1 = digitLeft1;
		}
		else
		{
			t1 = new Bit;
			t1->setDigit(1);
			y->setLeftEnd(t1);
			
			t2 = new Bit;
			t1->setRight(t2);
			t2->setLeft(t1);
			t1 = t2;
		}
		if(digitLeft1->getDigit() && !digitLeft2->getDigit())
		{
			//case: (1,0)
			t1->setDigit(1);
			if(digitLeft1->isRightEnd())
			{
				//y = 3
				p1 = new PositiveInteger;
				PositiveInteger::Two(p1);
				if(overwrite)
				{
					isOne1 = false;
					isTwo1 = false;
					//x1 originally cannot be one or two
					delete n1;
					n1 = p1;
				}
				else
				{
					y->setRightEnd(t1);
					y->setIsOne(false);
					y->setIsTwo(false);
					y->setNumberOfDigit(p1);
					p1->setNumberOfDigitParent(y);
				}
				delete p2;
				delete count;
				return y;
			}
		}
		else
		{
			//case: (0,0) or (1,1)
			t1->setDigit(0);
			if(digitLeft1->isRightEnd())
			{
				//y = 2
				if(overwrite)
				{
					//x1 originally cannot be one or two
					isOne1 = false;
					isTwo1 = true;
				}
				else
				{
					y->setRightEnd(t1);
					y->setIsOne(false);
					y->setIsTwo(true);
					y->setNumberOfDigit(y);
				}
				delete p2;
				delete count;
				return y;
			}
		}
		
		if(!overwrite)
		{
			while(!digitLeft1->isRightEnd())
			{
				digitLeft1 = digitLeft1->getRight();
				t2 = new Bit;
				t2->setDigit(digitLeft1->getDigit());
				t1->setRight(t2);
				t2->setLeft(t1);
				t1 = t2;
			}
			y->setRightEnd(t1);
		}
		
		digitLeft2 = digitLeft2->getRight();
		while(true)
		{
			if(digitLeft2->getDigit())
			{
				break;
			}
			if(digitLeft2->isRightEnd())
			{
				//y >= 4
				if(overwrite)
				{
					isOne1 = false;
					isTwo1 = false;
					//x1 originally cannot be one or two
					p1 = PositiveInteger::Subtract(n1,count,true,false);
					p1 = PositiveInteger::Add(p1,p2,true);
				}
				else
				{
					y->setIsOne(false);
					y->setIsTwo(false);
					p1 = PositiveInteger::Subtract(n1,count,false,false);
					p1 = PositiveInteger::Add(p1,p2,true);
					y->setNumberOfDigit(p1);
					p1->setNumberOfDigitParent(y);
				}
				delete p2;
				delete count;
				return y;
			}
			digitLeft2 = digitLeft2->getRight();
		}
		
	}
	else
	{
		//p1 - p2 >= 2
		//(x1 - x2) >= 3, if (p1 - p2) >= 2
		if(!overwrite)
		{
			c1 = RightEnd1;
			t1 = new Bit;
			t1->setDigit(c1->getDigit());
			y->setRightEnd(t1);
			while(!c1->isLeftEnd())
			{
				c1 = c1->getLeft();
				t2 = new Bit;
				t2->setDigit(c1->getDigit());
				t1->setLeft(t2);
				t2->setRight(t1);
				t1 = t2;
			}
			y->setLeftEnd(t1);
		}
		digitLeft2 = LeftEnd2;
	}
	
	if(overwrite)
	{
		isOne1 = false;
		isTwo1 = false;
		b1 = RightEnd1;
	}
	else
	{
		y->setIsOne(false);
		y->setIsTwo(false);
		b1 = y->getRightEnd();
	}
	
	
	digitRight2 = RightEnd2;
	while(true)
	{
		if(!b1->getDigit() && digitRight2->getDigit())
		{
			b1->setDigit(1);
			
			c1 = b1;
			c1 = c1->getLeft();
			while(!c1->getDigit())
			{
				c1->setDigit(1);
				c1 = c1->getLeft();
			}
			c1->setDigit(0);
		}
		else
		{
			if(b1->getDigit() && !digitRight2->getDigit())
			{
				b1->setDigit(1);
			}
			else
			{
				b1->setDigit(0);
			}
		}
		
		if(digitRight2==digitLeft2)
		{
			break;
		}
		else
		{
			b1 = b1->getLeft();
			digitRight2 = digitRight2->getLeft();
		}
	}
	
	if(overwrite)
	{
		b1 = LeftEnd1;
	}
	else
	{
		b1 = y->getLeftEnd();
	}
	
	if(b1->getDigit())
	{
		if(overwrite)
		{
			p1 = PositiveInteger::Subtract(n1,count,true,false);
			p1 = PositiveInteger::Add(p1,p2,true);
		}
		else
		{
			p1 = PositiveInteger::Subtract(n1,count,false,false);
			p1 = PositiveInteger::Add(p1,p2,true);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
	}
	else
	{
		c1 = b1->getRight();
		delete c1->getLeft();
		c1->setLeft(nullptr);
		
		if(overwrite)
		{
			LeftEnd1 = c1;
			p1 = PositiveInteger::Subtract(n1,count,true,false);
		}
		else
		{
			y->setLeftEnd(c1);
			p1 = PositiveInteger::Subtract(n1,count,false,false);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
	}
	
	delete p2;
	delete count;
	return y;
}

PositiveInteger* PositiveInteger::Subtract(PositiveInteger* x1,PositiveInteger* x2,bool overwrite,bool checking)
{
	PositiveInteger* y;
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* p4;
	
	int test1;
	int test2 = -1;
	if(checking)
	{
		test1 = PositiveInteger::compare(x1,x2);
		if(test1==0)
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			y = new PositiveInteger;
			return y;
		}
		
		if(test1==-1)
		{
			p1=x1;
			x1=x2;
			x2=p1;
		}
	}
	
	Bit* d1 = x1->getLeftEnd();
	Bit* d2 = x1->getRightEnd();
	PositiveInteger* q1 = x1->getNumberOfDigit();
	bool w1;
	bool w2;
	y = PositiveInteger::SubtractAux(d1,d2,q1,w1,w2,x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),overwrite);
	if(overwrite)
	{
		if(w1)
		{
			if(!x1->isOneOrTwo())
			{
				delete x1->getNumberOfDigit();
			}
			x1->setIsOne(true);
			x1->setIsTwo(false);
			x1->setLeftEnd(d1);
			x1->setRightEnd(d2);
			x1->setNumberOfDigit(x1);
			
		}
		else if(w2)
		{
			if(!x1->isOneOrTwo())
			{
				delete x1->getNumberOfDigit();
			}
			x1->setIsOne(false);
			x1->setIsTwo(true);
			x1->setLeftEnd(d1);
			x1->setRightEnd(d2);
			x1->setNumberOfDigit(x1);
		}
		else
		{
			x1->setIsOne(false);
			x1->setIsTwo(false);
			x1->setLeftEnd(d1);
			x1->setRightEnd(d2);
			//For x1 = 1,2,3
			x1->setNumberOfDigit(q1);
			q1->setNumberOfDigitParent(x1);
		}
		return x1;
	}
	else
	{
		return y;
	}
	
	
	
	Bit* b1;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	Bit* digitLeft1;
	Bit* digitLeft2;
	Bit* digitRight2;
	
	p1 = x1->getNumberOfDigit();
	p2 = x2->getNumberOfDigit();
	p3 = new PositiveInteger;
	PositiveInteger::One(p3);
	PositiveInteger* count = new PositiveInteger;
	PositiveInteger::One(count);
	test1 = PositiveInteger::compare(p1,p2);
	if(test1!=0)
	{
		p4 = PositiveInteger::Add(p2,p3,false);
		test2 = PositiveInteger::compare(p1,p4);
		delete p4;
	}
	
	if(overwrite)
	{
		y = x1;
	}
	else
	{
		y = new PositiveInteger;
	}
	
	if(test1==0 || (test1!=0 && test2==0))
	{
		if(test1==0)
		{
			//p1 = p2
			digitLeft1 = x1->getLeftEnd();
			digitLeft2 = x2->getLeftEnd();
			while(digitLeft1->getDigit()==digitLeft2->getDigit())
			{
				count = PositiveInteger::Add(count,p3,true);
				digitLeft1 = digitLeft1->getRight();
				digitLeft2 = digitLeft2->getRight();
				if(overwrite)
				{
					delete digitLeft1->getLeft();
					digitLeft1->setLeft(nullptr);
					x1->setLeftEnd(digitLeft1);
				}
			}
			//digitLeft1 = 1,  digitLeft2 = 0
			if(digitLeft1->isRightEnd())
			{
				//y = 1
				if(overwrite)
				{
					x1->setIsOne(true);
					x1->setIsTwo(false);
					//x1 originally cannot be one or two
					delete x1->getNumberOfDigit();
					x1->setNumberOfDigit(x1);
				}
				else
				{
					PositiveInteger::One(y);
				}
				delete p3;
				delete count;
				return y;
			}
			digitLeft1 = digitLeft1->getRight();
			digitLeft2 = digitLeft2->getRight();
		}
		else
		{
			//p1 - p2 = 1
			digitLeft1 = x1->getLeftEnd()->getRight();
			digitLeft2 = x2->getLeftEnd();
		}
		
		while(!digitLeft1->getDigit() && digitLeft2->getDigit())
		{
			//digitLeft1 = 0, digitLeft2 =1
			count = PositiveInteger::Add(count,p3,true);
			if(overwrite)
			{
				delete digitLeft1->getLeft();
				digitLeft1->setLeft(nullptr);
				x1->setLeftEnd(digitLeft1);
				digitLeft1->setDigit(1);
			}
			if(digitLeft1->isRightEnd())
			{
				//y = 1
				if(overwrite)
				{
					if(!x1->isOneOrTwo())
					{
						delete x1->getNumberOfDigit();
						x1->setNumberOfDigit(x1);
					}
					x1->setIsOne(true);
					x1->setIsTwo(false);
				}
				else
				{
					PositiveInteger::One(y);
				}
				delete p3;
				delete count;
				return y;
			}
			digitLeft1 = digitLeft1->getRight();
			digitLeft2 = digitLeft2->getRight();
		}
		
		//(digitLeft1,digitLeft2) = (0,0) or (1,1) or (1,0)
		if(overwrite)
		{
			t1 = digitLeft1;
		}
		else
		{
			t1 = new Bit;
			t1->setDigit(1);
			y->setLeftEnd(t1);
			
			t2 = new Bit;
			t1->setRight(t2);
			t2->setLeft(t1);
			t1 = t2;
		}
		if(digitLeft1->getDigit() && !digitLeft2->getDigit())
		{
			//case: (1,0)
			t1->setDigit(1);
			if(digitLeft1->isRightEnd())
			{
				//y = 3
				if(overwrite)
				{
					//x1 originally cannot be one or two
					delete x1->getNumberOfDigit();
				}
				else
				{
					y->setRightEnd(t1);
					y->setIsOne(false);
					y->setIsTwo(false);
				}
				p1 = new PositiveInteger;
				PositiveInteger::Two(p1);
				y->setNumberOfDigit(p1);
				p1->setNumberOfDigitParent(y);
				delete p3;
				delete count;
				return y;
			}
		}
		else
		{
			//case: (0,0) or (1,1)
			t1->setDigit(0);
			if(digitLeft1->isRightEnd())
			{
				//y = 2
				if(overwrite)
				{
					//x1 originally cannot be one or two
					delete x1->getNumberOfDigit();
				}
				else
				{
					y->setRightEnd(t1);
				}
				y->setIsOne(false);
				y->setIsTwo(true);
				y->setNumberOfDigit(y);
				delete p3;
				delete count;
				return y;
			}
		}
		
		if(!overwrite)
		{
			while(!digitLeft1->isRightEnd())
			{
				digitLeft1 = digitLeft1->getRight();
				t2 = new Bit;
				t2->setDigit(digitLeft1->getDigit());
				t1->setRight(t2);
				t2->setLeft(t1);
				t1 = t2;
			}
			y->setRightEnd(t1);
		}
		
		digitLeft2 = digitLeft2->getRight();
		while(true)
		{
			if(digitLeft2->getDigit())
			{
				break;
			}
			if(digitLeft2->isRightEnd())
			{
				//y >= 4
				if(overwrite)
				{
					//x1 originally cannot be one or two
					p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,true,false);
					p1 = PositiveInteger::Add(p1,p3,true);
				}
				else
				{
					y->setIsOne(false);
					y->setIsTwo(false);
					p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,false,false);
					p1 = PositiveInteger::Add(p1,p3,true);
					y->setNumberOfDigit(p1);
					p1->setNumberOfDigitParent(y);
				}
				delete p3;
				delete count;
				return y;
			}
			digitLeft2 = digitLeft2->getRight();
		}
		
	}
	else
	{
		//p1 - p2 >= 2
		//(x1 - x2) >= 3, if (p1 - p2) >= 2
		if(!overwrite)
		{
			c1 = x1->getRightEnd();
			t1 = new Bit;
			t1->setDigit(c1->getDigit());
			y->setRightEnd(t1);
			while(!c1->isLeftEnd())
			{
				c1 = c1->getLeft();
				t2 = new Bit;
				t2->setDigit(c1->getDigit());
				t1->setLeft(t2);
				t2->setRight(t1);
				t1 = t2;
			}
			y->setLeftEnd(t1);
		}
		digitLeft2 = x2->getLeftEnd();
	}
	
	if(!overwrite)
	{
		y->setIsOne(false);
		y->setIsTwo(false);
	}
	
	b1 = y->getRightEnd();
	digitRight2 = x2->getRightEnd();
	while(true)
	{
		if(!b1->getDigit() && digitRight2->getDigit())
		{
			b1->setDigit(1);
			
			c1 = b1;
			c1 = c1->getLeft();
			while(!c1->getDigit())
			{
				c1->setDigit(1);
				c1 = c1->getLeft();
			}
			c1->setDigit(0);
		}
		else
		{
			if(b1->getDigit() && !digitRight2->getDigit())
			{
				b1->setDigit(1);
			}
			else
			{
				b1->setDigit(0);
			}
		}
		
		if(digitRight2==digitLeft2)
		{
			break;
		}
		else
		{
			b1 = b1->getLeft();
			digitRight2 = digitRight2->getLeft();
		}
	}
	
	if(y->getLeftEnd()->getDigit())
	{
		if(overwrite)
		{
			p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,true,false);
			p1 = PositiveInteger::Add(p1,p3,true);
		}
		else
		{
			p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,false,false);
			p1 = PositiveInteger::Add(p1,p3,true);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
	}
	else
	{
		c1 = y->getLeftEnd()->getRight();
		delete c1->getLeft();
		c1->setLeft(nullptr);
		y->setLeftEnd(c1);
		
		if(overwrite)
		{
			p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,true,false);
		}
		else
		{
			p1 = PositiveInteger::Subtract(x1->getNumberOfDigit(),count,false,false);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
	}
	
	delete p3;
	delete count;
	return y;
}

PositiveInteger* PositiveInteger::Multiply(PositiveInteger* x1,PositiveInteger* x2)
{
	PositiveInteger* y;
	PositiveInteger* p1;
	PositiveInteger* p2;
	Bit* b1;
	Bit* b2;
	Bit* tLeft;
	Bit* tRight;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	
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
		//Now, b1 is an additional 0 at the left end, and it must be 1
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
	
	//add one more 0 at the left end
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
		//add one more 0 at the left end
		t2 = new Bit;
		t2->setDigit(0);
		tLeft->setLeft(t2);
		t2->setRight(tLeft);
		tLeft=t2;
		
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
		//delete one right end
		tRight = tRight->getLeft();
		delete tRight->getRight();
		tRight->setRight(nullptr);
	}
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
		
		p1 = x1->getNumberOfDigit();
		p2 = x2->getNumberOfDigit();
		p1 = PositiveInteger::Add(p1,p2,false);
		y->setNumberOfDigit(p1);
		p1->setNumberOfDigitParent(y);
	}
	else
	{
		y->setLeftEnd(b1);
		
		p1 = x1->getNumberOfDigit();
		p2 = x2->getNumberOfDigit();
		p1 = PositiveInteger::Add(p1,p2,false);
		
		p2 = new PositiveInteger;
		PositiveInteger::One(p2);
		p1 = PositiveInteger::Subtract(p1,p2,true,false);
		y->setNumberOfDigit(p1);
		p1->setNumberOfDigitParent(y);
		delete p2;
	}
	delete t1;
	return y;
}

void PositiveInteger::Divide(PositiveInteger* x1,PositiveInteger* x2,PositiveInteger*& y1,PositiveInteger*& y2,bool& divisible, bool overwrite, bool checking)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* p4;
	
	Bit* b1;
	Bit* b2;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	//Bit* c2;
	Bit* digitLeft1;
	Bit* digitLeft2;
	Bit* digit1;
	Bit* digit2;
	

	if(checking)
	{
		int test = PositiveInteger::compare(x1,x2);
		if(test==-1)
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
	}
	
	/*
	else if(test==0)
	{
		PositiveInteger::One(y1);
		y2 = x2->copy();
		divisible = true;
		return;
	}
	*/
	
	if(overwrite)
	{
		y2=x1;
	}
	else
	{
		c1 = x1->getRightEnd();
		t1 = new Bit;
		t1->setDigit(c1->getDigit());
		y2->setRightEnd(t1);
		while(!c1->isLeftEnd())
		{
			c1 = c1->getLeft();
			t2 = new Bit;
			t2->setDigit(c1->getDigit());
			t1->setLeft(t2);
			t2->setRight(t1);
			t1 = t2;
		}
		y2->setLeftEnd(t1);
	}
	
	
	digit1 = y2->getLeftEnd();
	digit2 = x2->getLeftEnd();
	//digit1 = 1, digit2 = 1
	int compare =0;
	while(true)
	{
		if(digit2->isRightEnd())
		{
			compare = 0;
			break;
		}
		if(digit1->isRightEnd())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
		
		digit1 = digit1->getRight();
		digit2 = digit2->getRight();
		if(digit1 && !digit2)
		{
			//digit1 = 1, digit2 = 0
			compare = 1;
			break;
		}
		if(!digit1 && digit2)
		{
			//digit1 = 0, digit2 = 1
			compare = -1;
			break;
		}
	}
	while(true)
	{
		if(digit2->isRightEnd())
		{
			break;
		}
		if(digit1->isRightEnd())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
		digit1 = digit1->getRight();
		digit2 = digit2->getRight();
	}
	t1 = y2->getLeftEnd();
	t2 = digit1;
	
	b1 = new Bit;
	b1->setDigit(1);
	y1->setLeftEnd(b1);
	while(true)
	{
		if(digit1->isRightEnd())
		{
			break;
		}
		b2 = new Bit;
		b1->setRight(b2);
		b2->setLeft(b1);
		b1 = b2;
		
		digit1 = digit1->getRight();
	}
	p1 = x1->getNumberOfDigit();
	p2 = new PositiveInteger;
	PositiveInteger::One(p2);
	p1 = PositiveInteger::Add(p1,p2,false);
	
	p3 = x2->getNumberOfDigit();
	p1 = PositiveInteger::Subtract(p1,p3,true,false);

	if(compare == -1)
	{
		b1 = b1->getLeft();
		delete b1->getRight();
		b1->setRight(nullptr);
		
		p1 = PositiveInteger::Subtract(p1,p2,true,false);
		t2 = t2->getRight();
	}
	else
	{
		
	}
	y1->setRightEnd(b1);
	b1 = y1->getLeftEnd()->getRight();
	
	y1->setNumberOfDigit(p1);
	p1->setNumberOfDigitParent(y1);
	
	
	Bit* d1;
	Bit* d2;
	PositiveInteger* q1;
	bool w1;
	bool w2;
	bool isEnd = false;
	while(true)
	{
		if(compare == 0)
		{
			digit2 = x2->getLeftEnd();
			while(!digit2->isRightEnd())
			{
				digit2 = digit2->getRight();
				
				t1 = t1->getRight();
				delete t1->getLeft();
				t1->setLeft(nullptr);
				
				b1->setDigit(0);
				if(b1->isRightEnd())
				{
					isEnd = true;
				}
				b1 = b1->getRight();
			}
		}
		
		if(compare == 1)
		{
			d1 = t1;
			d2 = t2;
			q1 = x2->getNumberOfDigit();
			p1 = PositiveInteger::SubtractAux(d1,d2,q1,w1,w2,x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),true);
		}
	
		if(compare == -1)
		{
			d1 = t1;
			d2 = t2;
			p1 = x2->getNumberOfDigit();
			q1 = PositiveInteger::Add(p1,p2,false);
			p1 = PositiveInteger::SubtractAux(d1,d2,q1,w1,w2,x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),true);
		}
		
		
		
		//digit1 = 1, digit2 = 1
		digit1 = digitLeft1;
		digit2 = x2->getLeftEnd();
		
		while(true)
		{
			if(digit2->isRightEnd())
			{
				compare = 0;
				break;
			}
			if(digit1->isRightEnd())
			{
				isEnd = true;
				break;
			}
			
			digit1 = digit1->getRight();
			digit2 = digit2->getRight();
			if(digit1 && !digit2)
			{
				//digit1 = 1, digit2 = 0
				compare = 1;
				break;
			}
			if(!digit1 && digit2)
			{
				//digit1 = 0, digit2 = 1
				compare = -1;
				break;
			}
		}
		
		if(isEnd)
		{
			
		}
		
		
	}
	delete p2;
}