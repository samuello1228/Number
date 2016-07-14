//
//  Integer.cpp
//  Number
//
//  Created by Samuel Lo on 26/5/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "Integer.hpp"
#include <iostream>
using namespace std;

Integer::Integer()
{
	setIsZero(false);
	setSign(true);
	setMagnitude(nullptr);
}

Integer::Integer(std::string x)
{
    std::string::iterator i=x.begin();
    
    if(*i == '0')
    {
        setIsZero(true);
		setSign(true);
		setMagnitude(nullptr);
        return;
    }
    else if(*i == '-')
    {
        setIsZero(false);
        setSign(false);
        x.erase(i);
    }
    else
    {
        setIsZero(false);
        setSign(true);
    }
    
    PositiveInteger* m = new PositiveInteger(x);
    setMagnitude(m);
}
Integer::~Integer()
{
	if(!getIsZero())
	{
		delete magnitude;
	}
}


bool Integer::getIsZero()
{
	return isZero;
}
void Integer::setIsZero(bool newIsZero)
{
	isZero = newIsZero;
}

bool Integer::getSign()
{
	return sign;
}
void Integer::setSign(bool newSign)
{
	sign = newSign;
}

PositiveInteger* Integer::getMagnitude()
{
	return magnitude;
}
void Integer::setMagnitude(PositiveInteger* newMagnitude)
{
	magnitude = newMagnitude;
}

void Integer::printBinary()
{
	if(getIsZero())
	{
		cout<<"0"<<endl;
	}
	else if(getSign())
	{
		getMagnitude()->printBinary();
	}
	else
	{
		cout<<"-";
		getMagnitude()->printBinary();
	}
}
void Integer::printDecimal(bool overwrite)
{
	if(getIsZero())
	{
		cout<<"0"<<endl;
	}
	else if(getSign())
	{
		getMagnitude()->printDecimal(overwrite);
	}
	else
	{
		cout<<"-";
		getMagnitude()->printDecimal(overwrite);
	}
}

Integer* Integer::copy()
{
	Integer* y = new Integer;
	PositiveInteger* p1;
	if(getIsZero())
	{
		y->setIsZero(true);
		//y->setSign(true);
		//y->setMagnitude(nullptr);
		return y;
	}
	else
	{
		//y->setIsZero(false);
		if(getSign())
		{
			//y->setSign(true);
			p1 = getMagnitude()->copy();
			y->setMagnitude(p1);
			return y;
		}
		else
		{
			y->setSign(false);
			p1 = getMagnitude()->copy();
			y->setMagnitude(p1);
			return y;
		}
	}
}

CompareCode Integer::compare(Integer* x1, Integer* x2)
{
	if(x1->getIsZero())
	{
		if(x2->getIsZero())
		{
			//x1=0=x2
			return CompareCode(true);
		}
		else if(x2->getSign())
		{
			//x1=0<x2
			return CompareCode(false,false);
		}
		else
		{
			//x1=0>x2
			return CompareCode(false,true);
		}
	}
	else if(x1->getSign())
	{
		if(x2->getIsZero())
		{
			//x1>0=x2
			return CompareCode(false,true);
		}
		else if(x2->getSign())
		{
			//x1>0, x2>0
			return PositiveInteger::compare(x1->getMagnitude(),x2->getMagnitude());
		}
		else
		{
			//x1>0>x2
			return CompareCode(false,true);
		}
	}
	else
	{
		if(x2->getIsZero())
		{
			//x1<0=x2
			return CompareCode(false,false);
		}
		else if(x2->getSign())
		{
			//x1<0<x2
			return CompareCode(false,false);
		}
		else
		{
			//x1<0, x2<0
			return PositiveInteger::compare(x2->getMagnitude(),x1->getMagnitude());
		}
	}
}
Integer* Integer::Add(Integer*& x1,Integer*& x2,bool overwrite)
{
	Integer* y;
	Integer* p1 = nullptr;
	PositiveInteger* m1 = nullptr;
	PositiveInteger* m2 = nullptr;
	PositiveInteger* m3 = nullptr;
	if(x2->getIsZero())
	{
		if(overwrite)
		{
			return x1;
		}
		else
		{
			y = x1->copy();
			return y;
		}
	}
	else if(x1->getIsZero())
	{
		if(overwrite)
		{
			p1=x1;
			x1=x2;
			x2=p1;
			return x1;
		}
		else
		{
			y = x2->copy();
			return y;
		}
	}
	else if((x1->getSign() && x2->getSign()) ||
			(!x1->getSign() && !x2->getSign()) )
	{
		//x1>0, x1>0
		//x1<0, x1<0
		m1 = x1->getMagnitude();
		m2 = x2->getMagnitude();
		m3 = PositiveInteger::Add(m1,m2,overwrite);
		
		if(overwrite)
		{
			x1->setMagnitude(m1);
			x2->setMagnitude(m2);
			return x1;
		}
		else
		{
			y = new Integer();
			//y->setIsZero(false);
			if(!x1->getSign())
			{
				y->setSign(false);
			}
			y->setMagnitude(m3);
			return y;
		}
	}
	else
	{
		//x1>0, x1<0
		//x1<0, x1>0
		CompareCode code = PositiveInteger::compare(x1->getMagnitude(),x2->getMagnitude());
		if(code.isEqual())
		{
			//y = 0
			if(overwrite)
			{
				x1->setIsZero(true);
				x1->setSign(true);
				delete x1->getMagnitude();
				x1->setMagnitude(nullptr);
				return x1;
			}
			else
			{
				y = new Integer("0");
				return y;
			}
		}
		else
		{
			if(code.isLarger())
			{
				m3 = PositiveInteger::Subtract(x1->getMagnitude(),x2->getMagnitude(),overwrite,false);
			}
			else
			{
				m3 = PositiveInteger::Subtract(x2->getMagnitude(),x1->getMagnitude(),overwrite,false);
			}
			
			if(overwrite)
			{
				if(code.isSmaller())
				{
					if(x1->getSign())
					{
						x1->setSign(false);
					}
					else
					{
						x1->setSign(true);
					}
					
					m1 = x1->getMagnitude();
					x1->setMagnitude(x2->getMagnitude());
					x2->setMagnitude(m1);
				}
				return x1;
			}
			else
			{
				y = new Integer();
				//y->setIsZero(false);
				if((x1->getSign() && code.isSmaller()) ||
				   (!x1->getSign() && code.isLarger()) )
				{
					y->setSign(false);
				}
				y->setMagnitude(m3);
				return y;
			}
		}
	}
}
Integer* Integer::Negation(bool overwrite)
{
	Integer* y;
	if(overwrite)
	{
		y = this;
	}
	else
	{
		y = this->copy();
	}
	
	if(y->getIsZero())
	{
		return y;
	}
	
	if(y->getSign())
	{
		y->setSign(false);
	}
	else
	{
		y->setSign(true);
	}
	return y;
}
Integer* Integer::Subtract(Integer*& x1,Integer*& x2,bool overwrite)
{
	Integer* y;
	if(overwrite)
	{
		x2->Negation(true);
		Integer::Add(x1,x2,true);
		return x1;
	}
	else
	{
		x2->Negation(true);
		y = Integer::Add(x1,x2,false);
		x2->Negation(true);
		return y;
	}
}
Integer* Integer::Multiply(Integer* x1,Integer* x2)
{
	Integer* y;
	if(x1->getIsZero() || x2->getIsZero())
	{
		y = new Integer("0");
		return y;
	}
	
	y = new Integer();
	//y->setIsZero(false);
	if((x1->getSign() && !x2->getSign()) ||
	   (!x1->getSign() && x2->getSign()) )
	{
		y->setSign(false);
	}
	PositiveInteger* m1 = PositiveInteger::Multiply(x1->getMagnitude(),x2->getMagnitude());
	y->setMagnitude(m1);
	return y;
}

//verification
Integer::Integer(int x)
{
	if(x==0)
	{
		setIsZero(true);
		setSign(true);
		setMagnitude(nullptr);
	}
	else
	{
		PositiveInteger* m;
		setIsZero(false);
		if(x>0)
		{
			setSign(true);
			m = new PositiveInteger(x);
			setMagnitude(m);
		}
		else
		{
			setSign(false);
			m = new PositiveInteger(-x);
			setMagnitude(m);
		}
	}
}
bool Integer::isComplete()
{
	if(getIsZero())
	{
		if(!getSign()) return false;
		if(getMagnitude()!=nullptr) return false;
	}
	else
	{
		if(getMagnitude()==nullptr) return false;
		if(!getMagnitude()->isComplete()) return false;
	}
	return true;
}
bool Integer::isSame(int x)
{
	if(!isComplete()) return false;
	
	if(x==0)
	{
		if(!getIsZero()) return false;
	}
	else
	{
		if(getIsZero()) return false;
		if(x>0)
		{
			if(!getSign()) return false;
			if(!getMagnitude()->isSame(x)) return false;

		}
		else
		{
			if(getSign()) return false;
			if(!getMagnitude()->isSame(-x)) return false;
		}
	}
	return true;
}
bool Integer::VerifyCopy(int max)
{
	Integer* p1;
	Integer* p2;
	for(int i=-max;i<=max;i++)
	{
		p1 = new Integer(i);
		//if(!p1->isComplete()) return false;
		//p1->printBinary();
		p2 = p1->copy();
		if(!p1->isSame(i)) return false;
		if(!p2->isSame(i)) return false;
		p2->printBinary();
		
		delete p1;
		delete p2;
	}
	return true;
}
bool Integer::VerifyInteger(int max)
{
	Integer* p1;
	Integer* p2;
	std::string s;
	Bit* b1;
	for(int i=-max;i<=max;i++)
	{
		p1 = new Integer(i);
		if(i==0)
		{
			p2 = new Integer("0");
		}
		else
		{
			s.clear();
			if(i<0) s.push_back('-');
			b1 = p1->getMagnitude()->getLeftEnd();
			while(true)
			{
				if(b1->getDigit())
				{
					s.push_back('1');
				}
				else
				{
					s.push_back('0');
				}
				if(b1->isRightEnd()) break;
				b1 = b1->getRight();
			}
			//cout<<s<<endl;
			p2 = new Integer(s);
		}
		
		if(!p2->isSame(i)) return false;
		
		delete p1;
		delete p2;
	}
	return true;
}
bool Integer::VerifyCompare(int max)
{
	Integer* p1;
	Integer* p2;
	CompareCode code;
	for(int i=-max;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			p1 = new Integer(i);
			p2 = new Integer(j);
			code = Integer::compare(p1,p2);
			if(!p1->isSame(i)) return false;
			if(!p2->isSame(j)) return false;
			if(i==j && !code.isEqual())  return false;
			else if(i>j && !code.isLarger())  return false;
			else if(i<j && !code.isSmaller())  return false;
			
			delete p1;
			delete p2;
		}
	}
	return true;
}
bool Integer::VerifyAdd(int max,bool overwrite)
{
	Integer* p1;
	Integer* p2;
	Integer* p3;
	for(int i=-max;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			p1 = new Integer(i);
			p2 = new Integer(j);
			p3 = Integer::Add(p1,p2,overwrite);
			if(overwrite)
			{
				if(!p1->isSame(i+j)) return false;
			}
			else
			{
				if(!p1->isSame(i)) return false;
				if(!p2->isSame(j)) return false;
			}
			if(!p3->isSame(i+j)) return false;
			//p3->printBinary();
			
			delete p1;
			delete p2;
			if(!overwrite) delete p3;
		}
		//cout<<endl;
	}
	return true;
}
bool Integer::VerifyNegation(int max,bool overwrite)
{
	Integer* p1;
	Integer* p2;
	for(int i=-max;i<=max;i++)
	{
		p1 = new Integer(i);
		p2 = p1->Negation(overwrite);
		if(overwrite)
		{
			if(!p1->isSame(-i)) return false;
		}
		else
		{
			if(!p1->isSame(i)) return false;
		}
		
		if(!p2->isSame(-i)) return false;
		//p2->printBinary();
		
		delete p1;
		if(!overwrite) delete p2;
	}
	return true;
}
bool Integer::VerifySubtract(int max,bool overwrite)
{
	Integer* p1;
	Integer* p2;
	Integer* p3;
	for(int i=-max;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			p1 = new Integer(i);
			p2 = new Integer(j);
			p3 = Integer::Subtract(p1,p2,overwrite);
			if(overwrite)
			{
				if(!p1->isSame(i-j)) return false;
			}
			else
			{
				if(!p1->isSame(i)) return false;
				if(!p2->isSame(j)) return false;
			}
			if(!p3->isSame(i-j)) return false;
			//p3->printBinary();
			
			delete p1;
			delete p2;
			if(!overwrite) delete p3;
		}
		//cout<<endl;
	}
	return true;
}
bool Integer::VerifyMultiply(int max)
{
	Integer* p1;
	Integer* p2;
	Integer* p3;
	for(int i=-max;i<=max;i++)
	{
		for(int j=-max;j<=max;j++)
		{
			p1 = new Integer(i);
			p2 = new Integer(j);
			p3 = Integer::Multiply(p1,p2);
			if(!p1->isSame(i)) return false;
			if(!p2->isSame(j)) return false;
			if(!p3->isSame(i*j)) return false;
			//p3->printBinary();
			
			delete p1;
			delete p2;
			delete p3;
		}
		//cout<<endl;
	}
	return true;
}