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
}

RealNumberBound::RealNumberBound(std::string m,std::string e)
{
	Integer* p1 = new Integer(m);
	setSignificand(p1);
	
	if(p1->getIsZero())
	{
		setExponent(nullptr);
	}
	else
	{
		p1 = new Integer(e);
		setExponent(p1);
	}
}
RealNumberBound::~RealNumberBound()
{
	if(!getSignificand()->getIsZero())
	{
		delete getExponent();
	}
	delete getSignificand();
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

	Integer* p1 = new Integer();
	p1->setIsZero(false);
	if(Sign)
	{
		p1->setSign(true);
	}
	else
	{
		p1->setSign(false);
	}
	
	PositiveInteger* p2;
	if(m==0)
	{
		p2 = new PositiveInteger(1);
	}
	else
	{
		p2 = new PositiveInteger(m);
		
		Byte* b1 = p2->getRightEnd();
		b1->setIsRightEnd(false);
		
		Byte* b2 = new Byte;
		b2->setByteOne();
		b1->setRight(b2);
		b2->setLeft(b1);
		b2->setIsRightEnd(true);
		b2->setRight(nullptr);
		p2->setRightEnd(b2);
	}
	p1->setMagnitude(p2);
	setSignificand(p1);
	
	p1 = new Integer(e);
	setExponent(p1);
}

bool RealNumberBound::isComplete() const
{
	if(getSignificand()==nullptr) {cout<<"Error Code: 26"<<endl; return false;}
	Integer* p1 = getSignificand();
	
	if(p1->getIsZero())
	{
		if(!p1->isSame(0)) {cout<<"Error Code: 27"<<endl; return false;}
		if(getExponent()!=nullptr) {cout<<"Error Code: 28"<<endl; return false;}
	}
	else
	{
		if(!p1->isComplete()) {cout<<"Error Code: 29"<<endl; return false;}
		if(p1->getMagnitude()->getRightEnd()->isZero()) {cout<<"Error Code: 30"<<endl; return false;}

		if(getExponent()==nullptr) {cout<<"Error Code: 31"<<endl; return false;}
		if(!getExponent()->isComplete()) {cout<<"Error Code: 32"<<endl; return false;}
	}
	return true;
}

bool RealNumberBound::isSame(bool IsZero,bool Sign,unsigned int m,int e) const
{
	if(!isComplete()) return false;
	Integer* p1 = getSignificand();
	if(IsZero)
	{
		if(!p1->getIsZero()) return false;
	}
	else
	{
		if(p1->getSign()!=Sign) return false;
		
		PositiveInteger* p2 = p1->getMagnitude();
		if(m==0)
		{
			if(!p2->isSame(1)) return false;
		}
		else
		{
			PositiveInteger* p3 = new PositiveInteger(m);
			{
				Byte* b1 = p3->getRightEnd();
				b1->setIsRightEnd(false);
				
				Byte* b2 = new Byte;
				b2->setByteOne();
				b1->setRight(b2);
				b2->setLeft(b1);
				b2->setIsRightEnd(true);
				b2->setRight(nullptr);
				p3->setRightEnd(b2);
			}
			{
				Byte* b1 = p2->getLeftEnd();
				Byte* b2 = p3->getLeftEnd();
				while(true)
				{
					if(!Byte::compare(*b1,*b2).isEqual()) return false;
					if(b1->getIsLeftEnd()) break;
					if(b2->getIsLeftEnd()) return false;
					b1 = b1->getRight();
					b2 = b2->getRight();
				}
				if(!b2->getIsLeftEnd()) return false;
			}
			delete p3;
		}
		
		if(!getExponent()->isSame(e)) return false;
	}
	
	return true;
}


bool RealNumberBound::VerifyCopy(int max)
{
	RealNumberBound* x1 = new RealNumberBound(true,true,0,0);
	if(!x1->isComplete()) return false;
	x1->printByte();
	if(!x1->isSame(true)) return false;
	delete x1;
	cout<<endl;
	
	for(unsigned int i=0;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			x1 = new RealNumberBound(false,true,i,j);
			if(!x1->isComplete()) return false;
			x1->printByte();
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
			x1->printByte();
			if(!x1->isSame(false,false,i,j)) return false;
			delete x1;
		}
		cout<<endl;
	}
	
	return true;
}

