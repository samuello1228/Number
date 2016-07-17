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
}

PositiveInteger::~PositiveInteger()
{
	if(getLeftEnd() != nullptr || getRightEnd() != nullptr)
	{
		Bit* b1 = getLeftEnd();
		Bit* b2;
		while(!b1->getIsRightEnd())
		{
			b2 = b1->getRight();
			delete b1;
			b1 = b2;
		}
		delete b1;
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

PositiveInteger::PositiveInteger(std::string x)
{
    std::string::iterator i=x.begin();
    Bit* b1;
    Bit* b2 = new Bit;
	b2->setLeft(nullptr);
	b2->setIsLeftEnd(true);
    setLeftEnd(b2);
	
	while(true)
	{
		if(*i == '0')
		{
			b2->setBit(0);
		}
		else if(*i == '1')
		{
			b2->setBit(1);
		}
		b1 = b2;
		i++;
		
		if(i==x.end()) break;
		b2 = new Bit;
		b1->setRight(b2);
		b2->setLeft(b1);
	}
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	setRightEnd(b1);
}

void PositiveInteger::printDecimal(bool overwrite)
{
	PositiveInteger* ten = new PositiveInteger("1010");
	PositiveInteger* x1;
	PositiveInteger* x2 = nullptr;
	Bit* b1;
	bool divisible = false;
	bool isEnd = false;
	
	if(overwrite)
	{
		x1 = this;
	}
	else
	{
		x1 = this->copy();
	}
	
	Digit* digit1 = new Digit;
	Digit* digit2;
	while(true)
	{
		if(PositiveInteger::compare(x1,ten).isSmaller())
		{
			divisible = false;
			isEnd = true;
		}
		else
		{
			PositiveInteger::Divide(x1,ten,x2,x1,divisible,true);
		}
		
		if(divisible)
		{
			digit1->digit = '0';
		}
		else
		{
			b1 = x1->getRightEnd();
			if(b1->getBit())
			{
				//x3 = *1 (binary)
				if(b1->getIsLeftEnd())
				{
					//x3 = 1 (binary)
					digit1->digit = '1';
				}
				else
				{
					b1 = b1->getLeft();
					if(b1->getBit())
					{
						//x3 = *11 (binary)
						if(b1->getIsLeftEnd())
						{
							//x3 = 11 (binary)
							digit1->digit = '3';
						}
						else
						{
							//x3 = 111 (binary)
							digit1->digit = '7';
						}
					}
					else
					{
						//x3 = *01 (binary)
						b1 = b1->getLeft();
						if(b1->getBit())
						{
							//x3 = 101 (binary)
							digit1->digit = '5';
						}
						else
						{
							//x3 = 1001 (binary)
							digit1->digit = '9';
							
						}
					}
				}
			}
			else
			{
				//x3 = *0 (binary)
				b1 = b1->getLeft();
				if(b1->getBit())
				{
					//x3 = *10 (binary)
					if(b1->getIsLeftEnd())
					{
						//x3 = 10 (binary)
						digit1->digit = '2';
					}
					else
					{
						//x3 = 110 (binary)
						digit1->digit = '6';
					}
				}
				else
				{
					//x3 = *00 (binary)
					b1 = b1->getLeft();
					if(b1->getIsLeftEnd())
					{
						//x3 = 100 (binary)
						digit1->digit = '4';
					}
					else
					{
						//x3 = 1000 (binary)
						digit1->digit = '8';
					}
				}
			}
		}
		
		if(isEnd)
		{
			cout<<digit1->digit;
			while(digit1->Right!=nullptr)
			{
				digit2 = digit1->Right;
				delete digit1;
				cout<<digit2->digit;
				digit1 = digit2;
			}
			delete digit1;
			cout<<endl;
			delete x1;
			delete ten;
			break;
		}
		
		digit2 = new Digit;
		digit2->Right = digit1;
		digit1 = digit2;
		if(!divisible)
		{
			delete x1;
		}
		x1 = x2;
	}
}

void PositiveInteger::printBinary()
{
	Bit* b1 = getLeftEnd();
	while(true)
	{
		cout<<b1->getBit();
		if(b1->getIsRightEnd()) break;
		b1 = b1->getRight();
	}
	cout<<endl;
}

PositiveInteger* PositiveInteger::getNumberOfBit()
{
	PositiveInteger* one = new PositiveInteger("1");
	PositiveInteger* y = new PositiveInteger("1");
	Bit* c1 = getRightEnd();
	while(true)
	{
		if(c1->getIsLeftEnd()) break;
		PositiveInteger::Add(y,one,true);
		c1 = c1->getLeft();
	}
	delete one;
	return y;
}

PositiveInteger* PositiveInteger::copy()
{
	PositiveInteger* y = new PositiveInteger;
	Bit* b1;
	Bit* b2;
	Bit* c1;
	
	c1 = getRightEnd();
	b2 = new Bit;
	b2->setRight(nullptr);
	b2->setIsRightEnd(true);
	y->setRightEnd(b2);
	while(true)
	{
		b2->setBit(c1->getBit());
		b1 = b2;
		
		if(c1->getIsLeftEnd()) break;
		c1 = c1->getLeft();
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
	}
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	y->setLeftEnd(b1);
	return y;
}

CompareCode PositiveInteger::compare(PositiveInteger* x1, PositiveInteger* x2)
{
	Bit* b1;
	Bit* b2;
	
	b1 = x1->getRightEnd();
	b2 = x2->getRightEnd();

	while(true)
	{
		if(b1->getIsLeftEnd())
		{
			if(b2->getIsLeftEnd())
			{
				break;
			}
			else
			{
				return CompareCode(false,false);
			}
		}
		else
		{
			if(b2->getIsLeftEnd())
			{
				return CompareCode(false,true);
			}
			else
			{
				b1 = b1->getLeft();
				b2 = b2->getLeft();
			}
		}
	}
	
	while(true)
	{
		if(b1->getBit())
		{
			if(!b2->getBit())
			{
				return CompareCode(false,true);
			}
		}
		else
		{
			if(b2->getBit())
			{
				return CompareCode(false,false);
			}
		}
		
		if(b1->getIsRightEnd()) break;
		b1 = b1->getRight();
		b2 = b2->getRight();
	}
	
	return CompareCode(true);
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


PositiveInteger* PositiveInteger::AddAux(Bit* c1, Bit* c2,bool overwrite,bool& AddIsCarried,Bit*& LeftEnd)
{
	PositiveInteger* y = nullptr;
	Bit* b1 = nullptr;
	Bit* b2 = nullptr;
	bool carry=0;
	bool result1;
	bool result2;
	AddIsCarried = false;
	
	if(!overwrite)
	{
		y = new PositiveInteger();
		b2 = new Bit;
		b2->setRight(nullptr);
		b2->setIsRightEnd(true);
		y->setRightEnd(b2);
	}
	
	while(true)
	{
		PositiveInteger::AddThreeBit(c1->getBit(),c2->getBit(),carry,result1,result2);
		if(overwrite)
		{
			c1->setBit(result2);
		}
		else
		{
			b2->setBit(result2);
			b1 = b2;
		}
		carry = result1;
		if(c1->getIsLeftEnd())
		{
			if(c2->getIsLeftEnd())
			{
				if(carry)
				{
					b2 = new Bit;
					b2->setLeft(nullptr);
					b2->setIsLeftEnd(true);
					b2->setBit(1);
					if(overwrite)
					{
						c1->setIsLeftEnd(false);
						c1->setLeft(b2);
						b2->setRight(c1);
						LeftEnd = b2;
						AddIsCarried = true;
						return nullptr;
					}
					else
					{
						b1->setLeft(b2);
						b2->setRight(b1);
						y->setLeftEnd(b2);
						return y;
					}
				}
				else
				{
					//cout<<"For multiply: the left end of x1 is 0"<<endl;
					if(overwrite)
					{
						return nullptr;
					}
					else
					{
						b1->setLeft(nullptr);
						b1->setIsLeftEnd(true);
						y->setLeftEnd(b1);
						return y;
					}
				}
			}
			else
			{
				///////////////////////////start
				if(overwrite)
				{
					c1->setIsLeftEnd(false);
				}
				if(carry)
				{
					while(true)
					{
						c2 = c2->getLeft();
						if(c2->getBit())
						{
							b2 = new Bit;
							b2->setBit(0);
							if(overwrite)
							{
								c1->setLeft(b2);
								b2->setRight(c1);
								c1 = b2;
							}
							else
							{
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							
							if(c2->getIsLeftEnd())
							{
								b2 = new Bit;
								b2->setLeft(nullptr);
								b2->setIsLeftEnd(true);
								b2->setBit(1);
								if(overwrite)
								{
									c1->setLeft(b2);
									b2->setRight(c1);
									LeftEnd = b2;
									AddIsCarried = true;
									return nullptr;
								}
								else
								{
									b1->setLeft(b2);
									b2->setRight(b1);
									y->setLeftEnd(b2);
									return y;
								}
							}
						}
						else
						{
							b2 = new Bit;
							b2->setBit(1);
							if(overwrite)
							{
								c1->setLeft(b2);
								b2->setRight(c1);
								c1 = b2;
							}
							else
							{
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							
							if(c2->getIsLeftEnd())
							{
								cout<<"logic error: the left end of x2 is not 1"<<endl;
								if(overwrite)
								{
									LeftEnd = c1;
									AddIsCarried = true;
									return nullptr;
								}
								else
								{
									b1->setLeft(nullptr);
									b1->setIsLeftEnd(true);
									y->setLeftEnd(b1);
									return y;
								}
							}
							break;
						}
					}
				}
				
				while(true)
				{
					c2 = c2->getLeft();
					b2 = new Bit;
					b2->setBit(c2->getBit());
					if(overwrite)
					{
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
					}
					else
					{
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
					}
					
					if(c2->getIsLeftEnd()) break;
				}
				
				if(overwrite)
				{
					c1->setLeft(nullptr);
					c1->setIsLeftEnd(true);
					LeftEnd = c1;
					AddIsCarried = true;
					return nullptr;
				}
				else
				{
					b1->setLeft(nullptr);
					b1->setIsLeftEnd(true);
					y->setLeftEnd(b1);
					return y;
				}
				///////////////////////////end
			}
		}
		else
		{
			if(c2->getIsLeftEnd())
			{
				///////////////////////////start
				if(carry)
				{
					while(true)
					{
						c1 = c1->getLeft();
						if(c1->getBit())
						{
							if(overwrite)
							{
								c1->setBit(0);
							}
							else
							{
								b2 = new Bit;
								b2->setBit(0);
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							
							if(c1->getIsLeftEnd())
							{
								b2 = new Bit;
								b2->setLeft(nullptr);
								b2->setIsLeftEnd(true);
								b2->setBit(1);
								if(overwrite)
								{
									c1->setIsLeftEnd(false);
									c1->setLeft(b2);
									b2->setRight(c1);
									LeftEnd = b2;
									AddIsCarried = true;
									return nullptr;
								}
								else
								{
									b1->setLeft(b2);
									b2->setRight(b1);
									y->setLeftEnd(b2);
									return y;
								}
							}
							
						}
						else
						{
							if(overwrite)
							{
								c1->setBit(1);
								return nullptr;
							}
							else
							{
								b2 = new Bit;
								b2->setBit(1);
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
								
								if(c1->getIsLeftEnd())
								{
									cout<<"the left end of x1 is not 1"<<endl;
									b1->setLeft(nullptr);
									b1->setIsLeftEnd(true);
									y->setLeftEnd(b1);
									return y;
								}
								break;
							}
						}
					}
				}
				
				if(overwrite)
				{
					return nullptr;
				}
				else
				{
					while(true)
					{
						c1 = c1->getLeft();
						b2 = new Bit;
						b2->setBit(c1->getBit());
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						if(c1->getIsLeftEnd()) break;
					}
					b1->setLeft(nullptr);
					b1->setIsLeftEnd(true);
					y->setLeftEnd(b1);
					return y;
				}
				///////////////////////////end
			}
			else
			{
				c1 = c1->getLeft();
				c2 = c2->getLeft();
			}
		}
		
		if(!overwrite)
		{
			b2 = new Bit;
			b1->setLeft(b2);
			b2->setRight(b1);
		}
	}
}
PositiveInteger* PositiveInteger::Add(PositiveInteger* x1,PositiveInteger* x2,bool overwrite)
{
	PositiveInteger* y = nullptr;
	Bit* c1 = x1->getRightEnd();
	Bit* c2 = x2->getRightEnd();
	Bit* LeftEnd = nullptr;
	bool AddIsCarried = false;
	
	y = PositiveInteger::AddAux(c1,c2,overwrite,AddIsCarried,LeftEnd);
	if(overwrite)
	{
		if(AddIsCarried)
		{
			x1->setLeftEnd(LeftEnd);
		}
		return x1;
	}
	else
	{
		return y;
	}
}

void PositiveInteger::SubtractAux(Bit*& LeftEnd1,Bit* c1,Bit* LeftEnd2,Bit* c2,bool& isShorten,
									bool overwrite, bool Divide, Bit*& y1Digit, Bit*& y2Right, bool& isEnd,bool isSmall)
{
	Bit* d1;
	isShorten = false;
	int Time = 0;
	
	while(true)
	{
		if(!c1->getBit() && c2->getBit())
		{
			c1->setBit(1);
			
			d1 = c1;
			while(true)
			{
				d1 = d1->getLeft();
				if(d1->getBit()) break;
				d1->setBit(1);
			}
			d1->setBit(0);
		}
		else
		{
			if(c1->getBit() && !c2->getBit())
			{
				c1->setBit(1);
			}
			else
			{
				c1->setBit(0);
			}
		}
		
		if(c2->getIsLeftEnd())
		{
			break;
		}
		else
		{
			c1 = c1->getLeft();
			c2 = c2->getLeft();
		}
	}
	
	if(!LeftEnd1->getBit())
	{
		isShorten = true;
		while(true)
		{

			if(Divide && !isEnd)
			{
				
				if(y1Digit->getIsRightEnd() ||
				   (isSmall && y1Digit->getRight()->getIsRightEnd() && Time==0))
				{
					isEnd = true;
				}
				else
				{
					if((!isSmall && Time>=1) ||
					   (isSmall && Time>=2)  )
					{
						y1Digit->setBit(0);
					}
					y1Digit = y1Digit->getRight();
					y2Right = y2Right->getRight();
				}
				Time++;
				
			}
			
			LeftEnd1 = LeftEnd1->getRight();
			delete LeftEnd1->getLeft();
			if(LeftEnd1->getBit()) break;
	
		}
	}
	LeftEnd1->setIsLeftEnd(true);
}


PositiveInteger* PositiveInteger::Subtract(PositiveInteger* x1,PositiveInteger* x2,bool overwrite)
{
	PositiveInteger* y;
	Bit* b1;
	Bit* b2;
	Bit* d1;
	Bit* temp1;
	bool temp2;
	bool isShorten;
	
	if(overwrite)
	{
		y = x1;
		d1 = x1->getLeftEnd();
	}
	else
	{
		y = new PositiveInteger;
		b1 = new Bit;
		b1->setRight(nullptr);
		b1->setIsRightEnd(true);
		y->setRightEnd(b1);
		d1 = x1->getRightEnd();
		while(true)
		{
			b1->setBit(d1->getBit());
			if(d1->getIsLeftEnd()) break;
			b2 = new Bit;
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
			d1 = d1->getLeft();
		}
		b1->setIsLeftEnd(true);
		y->setLeftEnd(b1);
		
		d1 = b1;
	}
	
	PositiveInteger::SubtractAux(d1,y->getRightEnd(),x2->getLeftEnd(),x2->getRightEnd(),isShorten,
									 overwrite,false,temp1,temp1,temp2,temp2);
	d1->setLeft(nullptr);
	if(isShorten) y->setLeftEnd(d1);
	return y;
}

void PositiveInteger::MultiplyAux(Bit* c1,Bit* c2,Bit* tRight,Bit*& b1,bool& MultiplyIsCarried)
{

	Bit* b2;
	Bit* LeftEnd;
	bool AddIsCarried;
	MultiplyIsCarried = false;
	
	if(!c2->getIsLeftEnd())
	{
		while(true)
		{
			c2 = c2->getLeft();
			if(tRight->getIsLeftEnd())
			{
				b1->setIsLeftEnd(false);
				b2 = new Bit;
				if(c2->getBit())
				{
					//x1 must be 2^n
					//c1 must be 1
					//x1->printBinary();
					b2->setBit(1);
				}
				else
				{
					b2->setBit(0);
				}
				b1->setLeft(b2);
				b2->setRight(b1);
				b1 = b2;
				b1->setIsLeftEnd(true);
				tRight = tRight->getLeft();
			}
			else
			{
				tRight = tRight->getLeft();
				if(c2->getBit())
				{
					PositiveInteger::AddAux(tRight,c1,true,AddIsCarried,LeftEnd);
					if(AddIsCarried)
					{
						if(!b1->getLeft()->getIsLeftEnd())
						{
							MultiplyIsCarried = true;
						}
						b1 = LeftEnd;
					}
					else
					{
						MultiplyIsCarried = false;
					}
				}
				else
				{
					b1->setIsLeftEnd(false);
					b2 = new Bit;
					b2->setBit(0);
					b1->setLeft(b2);
					b2->setRight(b1);
					b1 = b2;
					b1->setIsLeftEnd(true);
				}
			}
			if(c2->getIsLeftEnd()) break;
		}
	}
}
PositiveInteger* PositiveInteger::Multiply(PositiveInteger* x1,PositiveInteger* x2,bool& MultiplyIsCarried)
{
	PositiveInteger* y;
	Bit* b1;
	Bit* b2;
	Bit* c1;
	Bit* c2;
	Bit* tRight;
	Bit* d1;
	
	y = new PositiveInteger;
	b1 = new Bit;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	//////////////// copy zero of x1
	c1 = x1->getRightEnd();
	while(true)
	{
		if(c1->getBit()) break;
		b1->setBit(0);
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c1 = c1->getLeft();
	}
	
	////////////////copy zero of x2
	c2 = x2->getRightEnd();
	while(true)
	{
		if(c2->getBit()) break;
		b1->setBit(0);
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c2 = c2->getLeft();
	}
	tRight = b1;
	
	////////////////copy x1 without zero
	d1 = c1;
	while(true)
	{
		b1->setBit(d1->getBit());
		if(d1->getIsLeftEnd()) break;
		d1 = d1->getLeft();
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
	}
	b1->setIsLeftEnd(true);
	
	PositiveInteger::MultiplyAux(c1,c2,tRight,b1,MultiplyIsCarried);
	b1->setLeft(nullptr);
	y->setLeftEnd(b1);
	return y;
}

void PositiveInteger::Divide(PositiveInteger* x1,PositiveInteger* x2,PositiveInteger*& y1,PositiveInteger*& y2,bool& divisible, bool overwrite)
{
	Bit* b1;
	Bit* b2;
	Bit* tLeft;
	Bit* tRight;
	Bit* d1;
	Bit* d2;
	CompareCode compare;
	bool firstTime;
	bool isEnd;
	bool isSubtract;
	bool isShorten;
	
	if(overwrite)
	{
		y2 = x1;
	}
	else
	{
		//copy x1
		y2 = new PositiveInteger;
		b1 = new Bit;
		b1->setRight(nullptr);
		b1->setIsRightEnd(true);
		y2->setRightEnd(b1);
		
		d1 = x1->getRightEnd();
		while(true)
		{
			b1->setBit(d1->getBit());
			if(d1->getIsLeftEnd()) break;
			d1 = d1->getLeft();
			b2 = new Bit;
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		b1->setIsLeftEnd(true);
		y2->setLeftEnd(b1);
	}
	
	//////////////////
	//find tRight
	tLeft = y2->getLeftEnd();
	d1 = y2->getLeftEnd();
	d2 = x2->getLeftEnd();
	while(true)
	{
		if(d2->getIsRightEnd())
		{
			break;
		}
		if(d1->getIsRightEnd())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
		d1 = d1->getRight();
		d2 = d2->getRight();
	}
	tRight = d1;
	
	//create y1
	y1 = new PositiveInteger;
	b1 = new Bit;
	b1->setBit(0);
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	y1->setLeftEnd(b1);
	while(true)
	{
		if(d1->getIsRightEnd()) break;
		b2 = new Bit;
		b2->setBit(0);
		b2->setLeft(b1);
		b1->setRight(b2);
		b1 = b2;
		d1 = d1->getRight();
	}
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y1->setRightEnd(b1);
	
	//////////////////
	b1 = y1->getLeftEnd();
	isEnd = false;
	isSubtract = true;
	divisible = false;
	while(true)
	{
		if(!isEnd)
		{
			d1 = tLeft;
			d2 = x2->getLeftEnd();
			while(true)
			{
				if(d2->getIsRightEnd())
				{
					//c1 = 1, c2 = 1
					compare = CompareCode(true);
					break;
				}
				if(d1->getIsRightEnd())
				{
					//x1 < x2
					//y1 = 0, y2 = x1
					cout<<"Error! PositiveInteger does not support number zero."<<endl;
					return;
				}
				
				d1 = d1->getRight();
				d2 = d2->getRight();
				if(d1->getBit() && !d2->getBit())
				{
					//c1 = 1, c2 = 0
					compare = CompareCode(false,true);
					break;
				}
				if(!d1->getBit() && d2->getBit())
				{
					//c1 = 0, c2 = 1
					compare = CompareCode(false,false);
					break;
				}
			}
			if(b1->getIsRightEnd() && compare.isSmaller())
			{
				b1->setBit(0);
				isEnd = true;
			}
			else if(!compare.isSmaller())
			{
				b1->setBit(1);
			}
			else
			{
				b1->getRight()->setBit(1);
			}
		}
		
		if(isEnd)
		{
			if(divisible)
			{
				delete y2;
			}
			
			if(!y1->getLeftEnd()->getBit())
			{
				//delete the additional 0 at the left end
				b1 = y1->getLeftEnd()->getRight();
				delete b1->getLeft();
				b1->setLeft(nullptr);
				b1->setIsLeftEnd(true);
				y1->setLeftEnd(b1);
			}
			
			if(!divisible)
			{
				tLeft->setLeft(nullptr);
				y2->setLeftEnd(tLeft);
			}
			return;
		}
		
		firstTime = true;
		if(compare.isEqual())
		{
			isSubtract = true;
			d1 = x2->getLeftEnd();
			while(true)
			{
				if(isSubtract)
				{
					tLeft->setBit(0);
					if(d1->getIsRightEnd())
					{
						isSubtract = false;
					}
					else
					{
						d1 = d1->getRight();
					}
				}
				
				if(tLeft->getBit())
				{
					divisible = false;
					tLeft->setIsLeftEnd(true);
					break;
				}
				else
				{
					if(!isEnd)
					{
						if(firstTime)
						{
							firstTime = false;
						}
						else
						{
							b1->setBit(0);
						}
						if(b1->getIsRightEnd())
						{
							isEnd = true;
						}
						else
						{
							b1 = b1->getRight();
							tRight = tRight->getRight();
						}
					}
					
					if(tLeft->getIsRightEnd())
					{
						//isEnd must be true, because tLeft is left, relative to b1
						divisible = true;
						delete y2->getRightEnd();
						y2->setRightEnd(nullptr);
						y2->setLeftEnd(nullptr);
						break;
					}
					else
					{
						tLeft = tLeft->getRight();
						delete tLeft->getLeft();
						tLeft->setLeft(nullptr);
					}
				}
			}
		}
		else if(compare.isLarger())
		{
			PositiveInteger::SubtractAux(tLeft,tRight,x2->getLeftEnd(),x2->getRightEnd(),isShorten,
											  true,true,b1,tRight,isEnd,false);
		}
		else if(compare.isSmaller())
		{
			PositiveInteger::SubtractAux(tLeft,tRight->getRight(),x2->getLeftEnd(),x2->getRightEnd(),isShorten,
											  true,true,b1,tRight,isEnd,true);
			
		}
	}
}
/*
void PositiveInteger::printList(PositiveInteger::ListOfPositiveInteger* list,bool isDecimal)
{
	ListOfPositiveInteger* element1;
	ListOfPositiveInteger* element2;
	
	element1 = list;
	if(isDecimal)
	{
		element1->Element->printDecimal(false);
	}
	else
	{
		element1->Element->printBinary();
	}
	while(element1->Next!=nullptr)
	{
		element2 = element1->Next;
		if(isDecimal)
		{
			element1->Element->printDecimal(false);
		}
		else
		{
			element1->Element->printBinary();
		}
		element1 = element2;
	}
}

void PositiveInteger::deleteList(PositiveInteger::ListOfPositiveInteger* list)
{
	ListOfPositiveInteger* element1;
	ListOfPositiveInteger* element2;
	
	element1 = list;
	delete element1->Element;
	while(element1->Next!=nullptr)
	{
		element2 = element1->Next;
		delete element1;
		delete element2->Element;
		element1 = element2;
	}
	delete element1;
}

PositiveInteger::ListOfPositiveInteger* PositiveInteger::findPrime(PositiveInteger* max)
{
	PositiveInteger* one = new PositiveInteger;
	PositiveInteger::One(one);
	PositiveInteger* two = new PositiveInteger;
	PositiveInteger::Two(two);
	PositiveInteger* i;
	
	ListOfPositiveInteger* FirstElement = new ListOfPositiveInteger;
	ListOfPositiveInteger* FinalElement;
	ListOfPositiveInteger* element1;
	ListOfPositiveInteger* element2;
	
	FirstElement->Element = two->copy();
	FinalElement = FirstElement;
	
	i = PositiveInteger::Add(two,one,false);
	PositiveInteger* p1;
	PositiveInteger* p2;
	bool divisible = false;
	while(true)
	{
		if(PositiveInteger::compare(i,max).isLarger())
		{
			break;
		}
		
		element1 = FirstElement;
		while(true)
		{
			p1 = PositiveInteger::Multiply(element1->Element,element1->Element);
			if(PositiveInteger::compare(i,p1).isSmaller())
			{
				element2 = new ListOfPositiveInteger;
				FinalElement->Next = element2;
				element2->Element = i->copy();
				FinalElement = element2;
				delete p1;
				break;
			}
			delete p1;
			
			PositiveInteger::Divide(i,element1->Element,p1,p2,divisible,false,false);
			delete p1;
			if(divisible)
			{
				break;
			}
			else
			{
				delete p2;
			}
			
			element1 = element1->Next;
			
		}
		PositiveInteger::Add(i,one,true);
	}
	delete i;
	delete one;
	delete two;
	return FirstElement;
}

PositiveInteger* PositiveInteger::GCD(PositiveInteger* x1,PositiveInteger* x2)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* p4;
	bool divisible = false;
	
	if(PositiveInteger::compare(x1,x2).isSmaller())
	{
		p1 = x2->copy();
		p2 = x1->copy();
	}
	else
	{
		p1 = x1->copy();
		p2 = x2->copy();
	}
	
	while(true)
	{
		PositiveInteger::Divide(p1,p2,p3,p4,divisible,false,false);
		delete p1;
		delete p3;
		if(divisible)
		{
			return p2;
		}
		p1 = p2;
		p2 = p4;
	}
}
*/
//verification
PositiveInteger::PositiveInteger(unsigned int x)
{
	Bit* b1 = nullptr;
	Bit* b2 = new Bit;
	b2->setRight(nullptr);
	b2->setIsRightEnd(true);
	setRightEnd(b2);
	
	while(true)
	{
		b2->setBit(x%2);
		x = (x - b2->getBit())/2;
		b1 = b2;
		
		if(x==0) break;
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
	}
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	setLeftEnd(b1);
}

bool PositiveInteger::isComplete()
{
	Bit* b1;
	Bit* b2;
	
	if(getRightEnd()==nullptr) {cout<<"Error Code: 1"<<endl; return false;}
	b1 = getRightEnd();
	if(b1->getRight()!=nullptr) {cout<<"Error Code: 2"<<endl; return false;}
	if(!b1->getIsRightEnd()) {cout<<"Error Code: 3"<<endl; return false;}
	while(true)
	{
		if(b1->getLeft()==nullptr) break;
		if(b1->getIsLeftEnd()) {cout<<"Error Code: 4"<<endl; return false;}
		b2 = b1->getLeft();
		if(b2->getRight()==nullptr) {cout<<"Error Code: 5"<<endl; return false;}
		if(b2->getIsRightEnd()) {cout<<"Error Code: 6"<<endl; return false;}
		if(b2->getRight()!=b1) {cout<<"Error Code: 7"<<endl; return false;}
		b1 = b2;
	}
	if(!b1->getIsLeftEnd()) {cout<<"Error Code: 8"<<endl; return false;}
	if(!b1->getBit()) {cout<<"Error Code: 9"<<endl; return false;}
	if(getLeftEnd()==nullptr) {cout<<"Error Code: 10"<<endl; return false;}
	b2 = getLeftEnd();
	if(b1!=b2) {cout<<"Error Code: 11"<<endl; return false;}
	
	return true;
}
bool PositiveInteger::isSame(unsigned int x)
{
	if(!isComplete()) {cout<<"Error Code: 12"<<endl; return false;}
	PositiveInteger* p1 = new PositiveInteger(x);
	Bit* b1;
	Bit* b2;
	
	b1 = getRightEnd();
	b2 = p1->getRightEnd();
	while(true)
	{
		if(b1->getBit()!=b2->getBit()) {cout<<"Error Code: 13"<<endl; return false;}
		if(b1->getIsLeftEnd()) break;
		if(b2->getIsLeftEnd()) {cout<<"Error Code: 14"<<endl; return false;}
		b1 = b1->getLeft();
		b2 = b2->getLeft();
	}
	if(!b2->getIsLeftEnd()) {cout<<"Error Code: 15"<<endl; return false;}
	
	delete p1;
	return true;
}

bool PositiveInteger::VerifyCopy(unsigned int max)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	for(unsigned int i=1;i<=max;i++)
	{
		p1 = new PositiveInteger(i);
		//if(!p1->isComplete()) return false;
		//p1->printBinary();
		
		p2 = p1->copy();
		if(!p1->isSame(i)) return false;
		if(!p2->isSame(i)) return false;
		
		delete p1;
		delete p2;
	}
	return true;
}

bool PositiveInteger::VerifyCounter(unsigned int max)
{
	PositiveInteger* one = new PositiveInteger("1");
	PositiveInteger* count = new PositiveInteger("1");
	for(unsigned int i=1;i<=max;i++)
	{
		if(!count->isSame(i)) return false;
		count = PositiveInteger::Add(count,one,true);
	}
	delete one;
	delete count;
	return true;
}

bool PositiveInteger::VerifyPositiveInteger(unsigned int max)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	std::string s;
	Bit* b1;
	for(unsigned int i=1;i<=max;i++)
	{
		s.clear();
		p1 = new PositiveInteger(i);
		b1 = p1->getLeftEnd();
		while(true)
		{
			if(b1->getBit())
			{
				s.push_back('1');
			}
			else
			{
				s.push_back('0');
			}
			if(b1->getIsRightEnd()) break;
			b1 = b1->getRight();
		}
		//cout<<s<<endl;
		p2 = new PositiveInteger(s);
		if(!p2->isSame(i)) return false;
		
		delete p1;
		delete p2;
	}
	return true;
}

bool PositiveInteger::VerifyCompare(unsigned int max)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	CompareCode code;
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			code = PositiveInteger::compare(p1,p2);
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

bool PositiveInteger::VerifyAdd(unsigned int max,bool overwrite)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			p3 = PositiveInteger::Add(p1,p2,overwrite);
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
			
			delete p1;
			delete p2;
			if(!overwrite) delete p3;
		}
	}
	return true;
}

bool PositiveInteger::VerifySubtract(unsigned int max,bool overwrite)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=i-1;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			p3 = PositiveInteger::Subtract(p1,p2,overwrite);
			//p3->printBinary();
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
			
			delete p1;
			delete p2;
			if(!overwrite) delete p3;
		}
		//cout<<endl;
	}
	return true;
}

bool PositiveInteger::VerifyMultiply(unsigned int max)
{
	PositiveInteger* one = new PositiveInteger("1");
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* n1;
	PositiveInteger* n2;
	PositiveInteger* n3;
	bool MultiplyIsCarried;
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			p3 = PositiveInteger::Multiply(p1,p2,MultiplyIsCarried);
			//p3->printBinary();
			n1 = p1->getNumberOfBit();
			n2 = p2->getNumberOfBit();
			n3 = p3->getNumberOfBit();
			
			if(MultiplyIsCarried)
			{
				PositiveInteger::Add(n1,n2,true);
				if(!PositiveInteger::compare(n1,n3).isEqual()) return false;
			}
			else
			{
				PositiveInteger::Add(n1,n2,true);
				PositiveInteger::Subtract(n1,one,true);
				if(!PositiveInteger::compare(n1,n3).isEqual()) return false;
			}
			
			if(!p1->isSame(i)) return false;
			if(!p2->isSame(j)) return false;
			if(!p3->isSame(i*j)) return false;
		
			delete p1;
			delete p2;
			delete p3;
			delete n1;
			delete n2;
			delete n3;
		}
		//cout<<endl;
	}
	delete one;
	return true;
}

bool PositiveInteger::VerifyDivide(unsigned int max,bool overwrite)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* p4;
	bool divisible=0;
	for(unsigned int i=1;i<=max;i++)
	//for(unsigned int i=5;i<=5;i++)
	{
		for(unsigned int j=1;j<=i;j++)
		//for(unsigned int j=3;j<=3;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			p1->printBinary();
			p2->printBinary();
			PositiveInteger::Divide(p1,p2,p3,p4,divisible,overwrite);
			p3->printBinary();
			if(!overwrite)
			{
				if(!p1->isSame(i)) {cout<<"Error Code: 16"<<endl; return false;}
			}
			if(!p2->isSame(j)) {cout<<"Error Code: 17"<<endl; return false;}
			if(!p3->isSame(i/j)) {cout<<"Error Code: 18"<<endl; return false;}
			if(i%j==0)
			{
				if(!divisible) {cout<<"Error Code: 19"<<endl; return false;}
			}
			else
			{
				//p4->printBinary();
				if(divisible) {cout<<"Error Code: 20"<<endl; return false;}
				if(!p4->isSame(i%j)) {cout<<"Error Code: 21"<<endl; return false;}
				delete p4;
			}
			
			if(!overwrite) delete p1;
			delete p2;
			delete p3;
			cout<<endl;
		}
	}
	return true;
}
