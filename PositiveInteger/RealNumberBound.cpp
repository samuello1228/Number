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

RealNumberBound::RealNumberBound(std::string& Significand,std::string& Exponent)
{
	if(Significand=="inf")
	{
		setIsInfinity(true);
		Integer* p1 = new Integer;
		p1->setIsZero(false);
		p1->setSign(true);
		//p1->setMagnitude(nullptr);
		setSignificand(p1);
		setExponent(nullptr);
	}
	else if(Significand=="-inf")
	{
		setIsInfinity(true);
		Integer* p1 = new Integer;
		p1->setIsZero(false);
		p1->setSign(false);
		//p1->setMagnitude(nullptr);
		setSignificand(p1);
		setExponent(nullptr);
	}
	else
	{
		setIsInfinity(false);
		Integer* p1 = new Integer(Significand);
		setSignificand(p1);
		if(p1->getIsZero())
		{
			setExponent(nullptr);
		}
		else
		{
			p1 = new Integer(Exponent);
			setExponent(p1);
		}
	}
}
RealNumberBound::~RealNumberBound()
{
	if(!getIsInfinity() && !getSignificand()->getIsZero())
	{
		delete getExponent();
	}
	delete getSignificand();
}

bool RealNumberBound::getIsInfinity() const
{
	return isInfinity;
}
void RealNumberBound::setIsInfinity(bool const newIsInfinity)
{
	isInfinity = newIsInfinity;
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
	if(getIsInfinity())
	{
		if(getSignificand()->getSign())
		{
			cout<<"inf"<<endl;
			return;
		}
		else
		{
			cout<<"-inf"<<endl;
			return;
		}
	}
	
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

RealNumberBound* RealNumberBound::copy() const
{
	Integer const * const p1 = getSignificand();
	if(isInfinity)
	{
		if(p1->getSign())
		{
			std::string s = "inf";
			RealNumberBound* const y = new RealNumberBound(s,s);
			return y;
		}
		else
		{
			std::string s = "-inf";
			RealNumberBound* const y = new RealNumberBound(s,s);
			return y;
		}
	}
	else if(p1->getIsZero())
	{
		std::string s = "0";
		RealNumberBound* const y = new RealNumberBound(s,s);
		return y;
	}
	else
	{
		RealNumberBound* const y = new RealNumberBound;
		y->setIsInfinity(false);
		
		Integer * const p2 = p1->copy();
		y->setSignificand(p2);
		
		Integer * const p3 = getExponent()->copy();
		y->setExponent(p3);
		
		return y;
	}
}

//verification
RealNumberBound::RealNumberBound(RealNumberBound::ID const& element)
{
	if(element.IsInfinity)
	{
		setIsInfinity(true);
		Integer* const p1 = new Integer;
		p1->setIsZero(false);
		p1->setSign(element.Sign);
		//p1->setMagnitude(nullptr);
		setSignificand(p1);
		setExponent(nullptr);
		return;
	}
	if(element.IsZero)
	{
		setIsInfinity(false);
		Integer* const p1 = new Integer(0);
		setSignificand(p1);
		setExponent(nullptr);
		return;
	}
	
	{
		setIsInfinity(false);
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
		if(element.Magnitude==0)
		{
			p2 = new PositiveInteger(element.RightEnd);
		}
		else
		{
			p2 = new PositiveInteger(element.Magnitude);
			
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
		Integer* const p1 = new Integer(element.Exponent);
		setExponent(p1);
	}
}

bool RealNumberBound::isComplete() const
{
	if(getSignificand()==nullptr) {cout<<"Error Code: 27"<<endl; return false;}
	Integer const * const p1 = getSignificand();
	
	if(getIsInfinity())
	{
		if(p1->getIsZero()) {cout<<"Error Code: 28"<<endl; return false;}
		if(p1->getMagnitude()!=nullptr) {cout<<"Error Code: 29"<<endl; return false;}
		if(getExponent()!=nullptr) {cout<<"Error Code: 30"<<endl; return false;}
	}
	else if(p1->getIsZero())
	{
		if(!p1->isSame(0)) {cout<<"Error Code: 31"<<endl; return false;}
		if(getExponent()!=nullptr) {cout<<"Error Code: 32"<<endl; return false;}
	}
	else
	{
		if(!p1->isComplete()) {cout<<"Error Code: 33"<<endl; return false;}
		if(p1->getMagnitude()->getRightEnd()->isZero()) {cout<<"Error Code: 34"<<endl; return false;}

		if(getExponent()==nullptr) {cout<<"Error Code: 35"<<endl; return false;}
		if(!getExponent()->isComplete()) {cout<<"Error Code: 36"<<endl; return false;}
	}
	return true;
}

bool RealNumberBound::isSame(RealNumberBound::ID const& element) const
{
	if(!isComplete()) {cout<<"Error Code: 37"<<endl; return false;}
	Integer const * const p1 = getSignificand();
	if(element.IsInfinity)
	{
		if(!getIsInfinity()) {cout<<"Error Code: 38"<<endl; return false;}
		if(p1->getSign()!=element.Sign) {cout<<"Error Code: 39"<<endl; return false;}
	}
	else if(element.IsZero)
	{
		if(!p1->getIsZero()) {cout<<"Error Code: 40"<<endl; return false;}
	}
	else
	{
		if(p1->getSign()!=element.Sign) {cout<<"Error Code: 41"<<endl; return false;}
		
		PositiveInteger const * const p2 = p1->getMagnitude();
		if(element.Magnitude==0)
		{
			if(!p2->isSame(element.RightEnd)) {cout<<"Error Code: 42"<<endl; return false;}
		}
		else
		{
			PositiveInteger * const p3 = new PositiveInteger(element.Magnitude);
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
					if(!Byte::compare(*b1,*b2).isEqual()) {cout<<"Error Code: 43"<<endl; return false;}
					if(b1->getIsLeftEnd()) break;
					if(b2->getIsLeftEnd()) {cout<<"Error Code: 44"<<endl; return false;}
					b1 = b1->getRight();
					b2 = b2->getRight();
				}
				if(!b2->getIsLeftEnd()) {cout<<"Error Code: 45"<<endl; return false;}
			}
			delete p3;
		}
		
		if(!getExponent()->isSame(element.Exponent)) {cout<<"Error Code: 46"<<endl; return false;}
	}
	return true;
}

bool RealNumberBound::VerifyCopy(std::vector<RealNumberBound::ID>& list)
{
	for(unsigned int i=0;i<list.size();i++)
	{
		RealNumberBound const * const x1 = new RealNumberBound(list[i]);
		//if(!x1->isComplete()) return false;
		//x1->printByte();
		
		RealNumberBound const * const x2 = x1->copy();
		if(!x1->isSame(list[i])) return false;
		if(!x2->isSame(list[i])) return false;
		//x2->printByte();
		delete x1;
		delete x2;
	}
	
	return true;
}

bool RealNumberBound::VerifyRealNumberBound(std::vector<RealNumberBound::ID>& list)
{
	for(unsigned int i=0;i<list.size();i++)
	{
		
		std::string Significand;
		std::string Exponent;
		if(list[i].IsInfinity)
		{
			if(list[i].Sign)
			{
				Significand = "inf";
			}
			else
			{
				Significand = "-inf";
			}
		}
		else if(list[i].IsZero)
		{
			Significand = "0";
		}
		else
		{
			Significand.clear();
			if(!list[i].Sign) Significand.push_back('-');
			
			if(list[i].Magnitude>0)
			{
				PositiveInteger const p = PositiveInteger(list[i].Magnitude);
				Byte const * d1 = p.getLeftEnd();
				while(true)
				{
					Significand.push_back(d1->getByteChar());
					if(d1->getIsRightEnd()) break;
					d1 = d1->getRight();
				}
			}
			{
				PositiveInteger const p = PositiveInteger(list[i].RightEnd);
				Significand.push_back(p.getLeftEnd()->getByteChar());
			}
			
			if(list[i].Exponent==0) Exponent = "0";
			else
			{
				Exponent.clear();
				if(list[i].Exponent<0) Exponent.push_back('-');
				
				{
					Integer const p = Integer(list[i].Exponent);
					Byte const * d1 = p.getMagnitude()->getLeftEnd();
					while(true)
					{
						Exponent.push_back(d1->getByteChar());
						if(d1->getIsRightEnd()) break;
						d1 = d1->getRight();
					}
				}
			}
		}
		
		RealNumberBound const * const x2 = new RealNumberBound(Significand,Exponent);
		if(!x2->isSame(list[i])) return false;
		delete x2;
	}
	return true;
}


