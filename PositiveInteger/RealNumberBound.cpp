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
	setSignificand(nullptr);
	setExponent(nullptr);
}

RealNumberBound::RealNumberBound(std::string m,std::string e)
{
	Integer* p1 = new Integer(m);
	setSignificand(p1);
	
	p1 = new Integer(e);
	setExponent(p1);
}
RealNumberBound::~RealNumberBound()
{
	if(!getSignificand()->getIsZero())
	{
		delete getSignificand();
		delete getExponent();
	}
}


Integer* RealNumberBound::getSignificand() const
{
	return significand;
}
void RealNumberBound::setSignificand(Integer* const& newSignificand)
{
	significand = newSignificand;
}

Integer* RealNumberBound::getExponent() const
{
	return exponent;
}
void RealNumberBound::setExponent(Integer* const& newExponent)
{
	exponent = newExponent;
}

void RealNumberBound::printByte() const
{
	if(getSignificand()->getIsZero())
	{
		cout<<"0"<<endl;
		return;
	}
	
	if(!getSignificand()->getSign())
	{
		cout<<"-";
	}
	
	{
		Byte* d1 = getSignificand()->getMagnitude()->getLeftEnd();
		if(d1->getIsRightEnd())
		{
			cout<<"1";
		}
		else
		{
			cout<<"1.";
		}
		
		while(true)
		{
			if(d1->getIsRightEnd()) break;
			d1 = d1->getRight();
			cout<<d1->getByteChar();
		}
	}

	cout<<"e";
	getExponent()->printByte();
}

//verification
RealNumberBound::RealNumberBound(bool IsZero,bool Sign,unsigned int m,int e)
{
	if(IsZero)
	{
		Integer* p1 = new Integer(0);
		setSignificand(p1);
		setExponent(nullptr);
		return;
	}

	Integer* p2 = getSignificand();
	p2->setIsZero(false);
	if(Sign)
	{
		p2->setSign(true);
	}
	else
	{
		p2->setSign(false);
	}
	
	PositiveInteger* p1;
	if(m==0)
	{
		p1 = new PositiveInteger(1);
	}
	else
	{
		p1 = new PositiveInteger(m);
		
		Byte* b1 = p1->getRightEnd();
		b1->setIsRightEnd(false);
		
		Byte* b2 = new Byte;
		b2->setByteOne();
		b1->setRight(b2);
		b2->setLeft(b1);
		b2->setIsRightEnd(true);
		b2->setRight(nullptr);
		p1->setRightEnd(b2);
	}
	p2->setMagnitude(p1);
	setSignificand(p2);
	
	p2 = new Integer(e);
	setExponent(p2);
}
/*
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
 */
