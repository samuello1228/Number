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
	Bit* b1;
	
	if(getIsZero())
	{
		cout<<"0"<<endl;
		return;
	}
	
	if(!getSign())
	{
		cout<<"-";
	}
	
	b1 = getLeftEnd();
	if(b1->isRightEnd())
	{
		cout<<"1";
	}
	else
	{
		cout<<"1.";
	}
	while(!b1->isRightEnd())
	{
		b1 = b1->getRight();
		cout<<b1->getDigit();
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
	b1 = m->getLeftEnd();
	cout<<b1->getDigit();
	while(!b1->isRightEnd())
	{
		b1 = b1->getRight();
		cout<<b1->getDigit();
	}
	cout<<endl;
}

//verification
RealNumberBound::RealNumberBound(bool IsZero,bool Sign,unsigned int m,int e)
{
	if(IsZero)
	{
		setIsZero(true);
		setSign(true);
		setLeftEnd(nullptr);
		setRightEnd(nullptr);
		setExponent(nullptr);
		return;
	}
	PositiveInteger* p1;
	Integer* p2;
	Bit* b1;
	Bit* b2;
	Bit* c1;
	
	setIsZero(false);
	if(Sign)
	{
		setSign(true);
	}
	else
	{
		setSign(false);
	}
	if(m==0)
	{
		b1 = new Bit;
		b1->setDigit(1);
		setLeftEnd(b1);
		setRightEnd(b1);
	}
	else
	{
		p1 = new PositiveInteger(m);
		
		c1 = p1->getLeftEnd();
		b1 = new Bit;
		b1->setDigit(c1->getDigit());
		setLeftEnd(b1);
		while(!c1->isRightEnd())
		{
			c1 = c1->getRight();
			b2 = new Bit;
			b2->setDigit(c1->getDigit());
			b1->setRight(b2);
			b2->setLeft(b1);
			b1 = b2;
		}
		b2 = new Bit;
		b2->setDigit(1);
		b1->setRight(b2);
		b2->setLeft(b1);
		setRightEnd(b2);
		delete p1;
	}
	
	p2 = new Integer(e);
	setExponent(p2);
}

bool RealNumberBound::isComplete()
{
	Bit* b1;
	Bit* b2;
	if(getIsZero())
	{
		if(!getSign()) return false;
		if(getLeftEnd()!=nullptr) return false;
		if(getRightEnd()!=nullptr) return false;
		if(getExponent()!=nullptr) return false;
	}
	else
	{
		if(getRightEnd()==nullptr) return false;
		b1 = getRightEnd();
		if(b1->getRight()!=nullptr) return false;
		if(!b1->getDigit()) return false;
		while(true)
		{
			if(b1->getLeft()==nullptr) break;
			b2 = b1->getLeft();
			if(b2->getRight()==nullptr) return false;
			if(b2->getRight()!=b1) return false;
			b1 = b2;
		}
		if(!b1->getDigit()) return false;
		if(getLeftEnd()==nullptr) return false;
		b2 = getLeftEnd();
		if(b1!=b2) return false;

		if(getExponent()==nullptr) return false;
		if(!getExponent()->isComplete()) return false;
	}
	return true;
}

bool RealNumberBound::isSame(bool IsZero,bool Sign,unsigned int m,int e)
{
	PositiveInteger* p1;
	Bit* b1;
	Bit* b2;
	
	if(!isComplete()) return false;
	if(IsZero)
	{
		if(!getIsZero()) return false;
	}
	else
	{
		if(getSign()!=Sign) return false;
		
		if(m==0)
		{
			b1 = getLeftEnd();
			if(b1->getRight()!=nullptr) return false;
		}
		else
		{
			p1 = new PositiveInteger(m);
			b1 = p1->getRightEnd();
			b2 = new Bit;
			b2->setDigit(1);
			b1->setRight(b2);
			b2->setLeft(b1);
			p1->setRightEnd(b2);
			
			b1 = getLeftEnd();
			b2 = p1->getLeftEnd();
			while(true)
			{
				if(b1->getDigit()!=b2->getDigit()) return false;
				if(b1->getRight()==nullptr) break;
				if(b2->getRight()==nullptr) return false;
				b1 = b1->getRight();
				b2 = b2->getRight();
			}
			if(b2->getRight()!=nullptr) return false;
			delete p1;
		}
		
		if(!getExponent()->isSame(e)) return false;
	}
	
	return true;
}


bool RealNumberBound::VerifyCopy(int max)
{
	RealNumberBound* x1;
	
	x1 = new RealNumberBound(true);
	if(!x1->isComplete()) return false;
	x1->printBinary();
	if(!x1->isSame(true)) return false;
	delete x1;
	cout<<endl;
	
	for(unsigned int i=0;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			x1 = new RealNumberBound(false,true,i,j);
			if(!x1->isComplete()) return false;
			x1->printBinary();
			if(!x1->isSame(false,true,i,j)) return false;
			delete x1;
		}
		cout<<endl;
	}
	
	for(unsigned int i=0;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			x1 = new RealNumberBound(false,false,i,j);
			if(!x1->isComplete()) return false;
			x1->printBinary();
			if(!x1->isSame(false,false,i,j)) return false;
			delete x1;
		}
		cout<<endl;
	}
	return true;
}
