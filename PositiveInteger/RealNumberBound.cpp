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

RealNumberBound::RealNumberBound(std::string& m,std::string& e)
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
		Byte const* d1 = getSignificand()->getMagnitude()->getLeftEnd();
		cout<<d1->getByteChar();
		if(!d1->getIsRightEnd())
		{
			cout<<".";
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
RealNumberBound::RealNumberBound(RealNumberBound::ID const& element)
{
	if(element.IsZero)
	{
		Integer* const p1 = new Integer(0);
		setSignificand(p1);
		setExponent(nullptr);
		return;
	}
	
	{
		Integer* const p1 = new Integer();
		p1->setIsZero(false);
		if(element.Sign)
		{
			p1->setSign(true);
		}
		else
		{
			p1->setSign(false);
		}
		
		PositiveInteger* p2;
		if(element.m==0)
		{
			p2 = new PositiveInteger(element.RightEnd);
		}
		else
		{
			p2 = new PositiveInteger(element.m);
			
			Byte* const b1 = p2->getRightEnd();
			b1->setIsRightEnd(false);
			
			Byte* const b2 = new Byte;
			b2->setByteInt(element.RightEnd);
			b1->setRight(b2);
			b2->setLeft(b1);
			b2->setIsRightEnd(true);
			b2->setRight(nullptr);
			p2->setRightEnd(b2);
		}
		p1->setMagnitude(p2);
		setSignificand(p1);
	}
	
	{
		Integer* const p1 = new Integer(element.e);
		setExponent(p1);
	}
}

bool RealNumberBound::isComplete() const
{
	if(getSignificand()==nullptr) {cout<<"Error Code: 26"<<endl; return false;}
	Integer const * const p1 = getSignificand();
	
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

bool RealNumberBound::isSame(RealNumberBound::ID const& element) const
{
	if(!isComplete()) {cout<<"Error Code: 32"<<endl; return false;}
	Integer const * const p1 = getSignificand();
	if(element.IsZero)
	{
		if(!p1->getIsZero()) {cout<<"Error Code: 33"<<endl; return false;}
	}
	else
	{
		if(p1->getSign()!=element.Sign) {cout<<"Error Code: 34"<<endl; return false;}
		
		PositiveInteger const * const p2 = p1->getMagnitude();
		if(element.m==0)
		{
			if(!p2->isSame(element.RightEnd)) {cout<<"Error Code: 35"<<endl; return false;}
		}
		else
		{
			PositiveInteger * const p3 = new PositiveInteger(element.m);
			{
				Byte* const b1 = p3->getRightEnd();
				b1->setIsRightEnd(false);
				
				Byte* const b2 = new Byte;
				b2->setByteInt(element.RightEnd);
				b1->setRight(b2);
				b2->setLeft(b1);
				b2->setIsRightEnd(true);
				b2->setRight(nullptr);
				p3->setRightEnd(b2);
			}
			{
				Byte const * b1 = p2->getLeftEnd();
				Byte const * b2 = p3->getLeftEnd();
				while(true)
				{
					if(!Byte::compare(*b1,*b2).isEqual()) {cout<<"Error Code: 36"<<endl; return false;}
					if(b1->getIsLeftEnd()) break;
					if(b2->getIsLeftEnd()) {cout<<"Error Code: 37"<<endl; return false;}
					b1 = b1->getRight();
					b2 = b2->getRight();
				}
				if(!b2->getIsLeftEnd()) {cout<<"Error Code: 38"<<endl; return false;}
			}
			delete p3;
		}
		
		if(!getExponent()->isSame(element.e)) {cout<<"Error Code: 39"<<endl; return false;}
	}
	return true;
}


bool RealNumberBound::VerifyCopy(std::vector<RealNumberBound::ID>& list)
{
	for(unsigned int i=0;i<list.size();i++)
	{
		RealNumberBound const * const x1 = new RealNumberBound(list[i]);
		if(!x1->isComplete()) return false;
		x1->printByte();
		if(!x1->isSame(list[i])) return false;
		delete x1;
	}
	
	return true;
}

