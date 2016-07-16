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
	//if(getLeftEnd() != nullptr && getRightEnd() != nullptr)
	//{
		Bit* b1 = getLeftEnd();
		Bit* b2;
		while(!b1->getIsRightEnd())
		{
			b2 = b1->getRight();
			delete b1;
			b1 = b2;
		}
		delete b1;
	//}
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
/*
void PositiveInteger::printDecimal(bool overwrite)
{
	PositiveInteger* ten = new PositiveInteger("1010");
	PositiveInteger* x1;
	PositiveInteger* x2 = nullptr;
	PositiveInteger* x3;
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
			PositiveInteger::Divide(x1,ten,x2,x1,divisible,true,false);
		}
		
		if(divisible)
		{
			digit1->digit = '0';
		}
		else if(x1->getIsOne())
		{
			digit1->digit = '1';
		}
		else if(x1->getIsTwo())
		{
			digit1->digit = '2';
		}
		else
		{
			x3 = x1->getNumberOfDigit();
			if(x3->getIsTwo())
			{
				//x3 = 10 (binary)
				digit1->digit = '3';
			}
			else if(x3->getRightEnd()->getBit())
			{
				//x3 = 11 (binary)
				//x1 = 4,5,6,7
				b1 = x1->getRightEnd();
				if(b1->getBit())
				{
					b1 = b1->getLeft();
					if(b1->getBit())
					{
						//x1 = 111 (binary)
						digit1->digit = '7';
					}
					else
					{
						//x1 = 101 (binary)
						digit1->digit = '5';
					}
				}
				else
				{
					b1 = b1->getLeft();
					if(b1->getBit())
					{
						//x1 = 110 (binary)
						digit1->digit = '6';
					}
					else
					{
						//x1 = 100 (binary)
						digit1->digit = '4';
					}
				}
			}
			else
			{
				//x3 = 100 (binary)
				//x1 = 8,9
				b1 = x1->getRightEnd();
				if(b1->getBit())
				{
					//x1 = 1001 (binary)
					digit1->digit = '9';
				}
				else
				{
					//x1 = 1000 (binary)
					digit1->digit = '8';
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
*/
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

PositiveInteger* PositiveInteger::Add(PositiveInteger* x1,PositiveInteger* x2,bool overwrite)
{
	PositiveInteger* y = nullptr;
	Bit* b1 = nullptr;
	Bit* b2 = nullptr;
	
	
	bool carry=0;
	bool result1;
	bool result2;
	
	Bit* c1 = x1->getRightEnd();
	Bit* c2 = x2->getRightEnd();
	
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
						x1->setLeftEnd(b2);
						return x1;
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
					cout<<"logic error: the left end is not 1"<<endl;
					if(overwrite)
					{
						return x1;
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
									x1->setLeftEnd(b2);
									return x1;
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
									x1->setLeftEnd(c1);
									return x1;
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
					x1->setLeftEnd(c1);
					return x1;
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
									x1->setLeftEnd(b2);
									return x1;
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
								return x1;
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
									cout<<"logic error: the left end of x1 is not 1"<<endl;
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
					return x1;
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

/*
PositiveInteger* PositiveInteger::SubtractAux(Bit*& LeftEnd1,Bit* RightEnd1,PositiveInteger*& n1,bool& isOne1,bool& isTwo1,
											  Bit* LeftEnd2,Bit* RightEnd2,PositiveInteger* n2,bool isOne2,bool isTwo2,
											  bool overwrite, bool Divide, Bit*& y1Digit, Bit*& y2Right, bool& isEnd, PositiveInteger*& count)
{
	PositiveInteger* y;
	PositiveInteger* one;
	PositiveInteger* p1 = nullptr;
	
	Bit* b1;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	Bit* digitLeft1;
	Bit* digitLeft2;
	Bit* digitRight2;
	CompareCode test1;
	CompareCode test2;
	
	bool isCount = !Divide;
	
	if(isCount)
	{
		count = new PositiveInteger;
		PositiveInteger::One(count);
	}
	one = new PositiveInteger;
	PositiveInteger::One(one);
	test1 = PositiveInteger::compare(n1,n2);
	if(!test1.isEqual())
	{
		p1 = PositiveInteger::Add(n2,one,false);
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
	
	if(test1.isEqual() || (!test1.isEqual() && test2.isEqual()))
	{
		if(test1.isEqual())
		{
			//n1 = n2
			digitLeft1 = LeftEnd1;
			digitLeft2 = LeftEnd2;
			while(digitLeft1->getBit()==digitLeft2->getBit())
			{
				if(isCount)
				{
					PositiveInteger::Add(count,one,true);
				}
				//Because y>=1
				digitLeft1 = digitLeft1->getRight();
				digitLeft2 = digitLeft2->getRight();
				if(overwrite)
				{
					delete digitLeft1->getLeft();
					digitLeft1->setLeft(nullptr);
					LeftEnd1 = digitLeft1;
				}
				if(Divide && !isEnd)
				{
					if(y1Digit->isRightEnd())
					{
						isEnd = true;
						isCount = true;
						count = new PositiveInteger;
						PositiveInteger::One(count);
					}
					else
					{
						y1Digit = y1Digit->getRight();
						y2Right = y2Right->getRight();
					}
				}
			}
			//digitLeft1 = 1,  digitLeft2 = 0
			if(digitLeft1==RightEnd1)
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
				if(!Divide)
				{
					delete count;
				}
				delete one;
				return y;
			}
			digitLeft1 = digitLeft1->getRight();
			digitLeft2 = digitLeft2->getRight();
		}
		else
		{
			//n1 - n2 = 1
			digitLeft1 = LeftEnd1->getRight();
			digitLeft2 = LeftEnd2;
		}
		
		while(!digitLeft1->getBit() && digitLeft2->getBit())
		{
			//digitLeft1 = 0, digitLeft2 =1
			if(isCount)
			{
				PositiveInteger::Add(count,one,true);
			}
			if(overwrite)
			{
				delete digitLeft1->getLeft();
				digitLeft1->setLeft(nullptr);
				LeftEnd1 = digitLeft1;
				digitLeft1->setBit(1);
			}
			if(Divide && !isEnd)
			{
				if(y1Digit->isRightEnd())
				{
					isEnd = true;
					isCount = true;
					count = new PositiveInteger;
					PositiveInteger::One(count);
				}
				else
				{
					y1Digit = y1Digit->getRight();
					y2Right = y2Right->getRight();
				}
			}
			
			if(digitLeft1==RightEnd1)
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
				if(!Divide)
				{
					delete count;
				}
				delete one;
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
			t1->setBit(1);
			y->setLeftEnd(t1);
			
			t2 = new Bit;
			t1->setRight(t2);
			t2->setLeft(t1);
			t1 = t2;
		}
		if(digitLeft1->getBit() && !digitLeft2->getBit())
		{
			//case: (1,0)
			t1->setBit(1);
			if(digitLeft1==RightEnd1)
			{
				//y = 3
				if(!Divide)
				{
					p1 = new PositiveInteger;
					PositiveInteger::Two(p1);
				}
				if(overwrite)
				{
					isOne1 = false;
					isTwo1 = false;
					if(!Divide)
					{
						//x1 originally cannot be one or two
						delete n1;
						n1 = p1;
					}
				}
				else
				{
					y->setRightEnd(t1);
					y->setIsOne(false);
					y->setIsTwo(false);
					y->setNumberOfDigit(p1);
					p1->setNumberOfDigitParent(y);
				}
				if(!Divide)
				{
					delete count;
				}
				delete one;
				return y;
			}
		}
		else
		{
			//case: (0,0) or (1,1)
			t1->setBit(0);
			if(digitLeft1==RightEnd1)
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
				
				if(!Divide)
				{
					delete count;
				}
				delete one;
				return y;
			}
		}
		
		if(!overwrite)
		{
			while(digitLeft1!=RightEnd1)
			{
				digitLeft1 = digitLeft1->getRight();
				t2 = new Bit;
				t2->setBit(digitLeft1->getBit());
				t1->setRight(t2);
				t2->setLeft(t1);
				t1 = t2;
			}
			y->setRightEnd(t1);
		}
		
		digitLeft2 = digitLeft2->getRight();
		while(true)
		{
			if(digitLeft2->getBit())
			{
				break;
			}
			if(digitLeft2==RightEnd2)
			{
				//y >= 4
				if(overwrite)
				{
					isOne1 = false;
					isTwo1 = false;
					if(!Divide)
					{
						//x1 originally cannot be one or two
						PositiveInteger::Subtract(n1,count,true,false);
						PositiveInteger::Add(n1,one,true);
					}
				}
				else
				{
					y->setIsOne(false);
					y->setIsTwo(false);
					p1 = PositiveInteger::Subtract(n1,count,false,false);
					PositiveInteger::Add(p1,one,true);
					y->setNumberOfDigit(p1);
					p1->setNumberOfDigitParent(y);
				}
				if(!Divide)
				{
					delete count;
				}
				delete one;
				return y;
			}
			digitLeft2 = digitLeft2->getRight();
		}
		
	}
	else
	{
		//n1 - n2 >= 2
		//(x1 - x2) >= 3, if (n1 - n2) >= 2
		if(!overwrite)
		{
			c1 = LeftEnd1;
			t1 = new Bit;
			t1->setBit(c1->getBit());
			y->setLeftEnd(t1);
			while(c1!=RightEnd1)
			{
				c1 = c1->getRight();
				t2 = new Bit;
				t2->setBit(c1->getBit());
				t1->setRight(t2);
				t2->setLeft(t1);
				t1 = t2;
			}
			y->setRightEnd(t1);
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
		if(!b1->getBit() && digitRight2->getBit())
		{
			b1->setBit(1);
			
			c1 = b1;
			c1 = c1->getLeft();
			while(!c1->getBit())
			{
				c1->setBit(1);
				c1 = c1->getLeft();
			}
			c1->setBit(0);
		}
		else
		{
			if(b1->getBit() && !digitRight2->getBit())
			{
				b1->setBit(1);
			}
			else
			{
				b1->setBit(0);
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
	
	if(b1->getBit())
	{
		if(overwrite)
		{
			if(!Divide)
			{
				PositiveInteger::Subtract(n1,count,true,false);
				PositiveInteger::Add(n1,one,true);
			}
		}
		else
		{
			p1 = PositiveInteger::Subtract(n1,count,false,false);
			PositiveInteger::Add(p1,one,true);
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
			if(!Divide)
			{
				PositiveInteger::Subtract(n1,count,true,false);
			}
		}
		else
		{
			y->setLeftEnd(c1);
			p1 = PositiveInteger::Subtract(n1,count,false,false);
			y->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(y);
		}
		
		if(Divide)
		{
			if(isCount)
			{
				PositiveInteger::Add(count,one,true);
			}
			if(!isEnd)
			{
				if(y1Digit->isRightEnd())
				{
					isEnd = true;
					//isCount = true;
					count = new PositiveInteger;
					PositiveInteger::One(count);
				}
				else
				{
					y1Digit = y1Digit->getRight();
					y2Right = y2Right->getRight();
				}
			}
		}
	}
	if(!Divide)
	{
		delete count;
	}
	delete one;
	return y;
}

PositiveInteger* PositiveInteger::Subtract(PositiveInteger* x1,PositiveInteger* x2,bool overwrite,bool checking)
{
	PositiveInteger* y;
	PositiveInteger* p1;
	
	
	CompareCode test1;
	if(checking)
	{
		test1 = PositiveInteger::compare(x1,x2);
		if(test1.isEqual())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			y = new PositiveInteger;
			return y;
		}
		
		if(test1.isSmaller())
		{
			p1=x1;
			x1=x2;
			x2=p1;
		}
	}
	
	Bit* d1 = x1->getLeftEnd();
	p1 = x1->getNumberOfDigit();
	bool w1;
	bool w2;
	Bit* temp1;
	bool temp2;
	PositiveInteger* temp3;
	y = PositiveInteger::SubtractAux(d1,x1->getRightEnd(),p1,w1,w2,
									 x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),
									 overwrite,false,temp1,temp1,temp2,temp3);
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
			x1->setNumberOfDigit(x1);
		}
		else
		{
			x1->setIsOne(false);
			x1->setIsTwo(false);
			x1->setLeftEnd(d1);
			//For x1 = 1,2,3
			x1->setNumberOfDigit(p1);
			p1->setNumberOfDigitParent(x1);
		}
		return x1;
	}
	else
	{
		return y;
	}
}
*/
PositiveInteger* PositiveInteger::Multiply(PositiveInteger* x1,PositiveInteger* x2)
{
	PositiveInteger* y;
	Bit* b1;
	Bit* b2;
	Bit* c1;
	Bit* c2;
	Bit* tLeft;
	Bit* tRight;
	Bit* t1;
	Bit* t2;
	Bit* d1;
	
	y = new PositiveInteger;
	
	bool carry=0;
	bool result1;
	bool result2;
	
	b1 = new Bit;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	c1 = x1->getRightEnd();
	while(true)
	{
		if(c1->getBit()) break;
		b1->setBit(0);
		
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
		c1 = c1->getLeft();
		b1 = b2;
		
	}
	
	c2 = x2->getRightEnd();
	while(true)
	{
		if(c2->getBit()) break;
		b1->setBit(0);
		
		b2 = new Bit;
		b1->setLeft(b2);
		b2->setRight(b1);
		c2 = c2->getLeft();
		b1 = b2;
	}
	
	//Now, b1 must be 1
	b1->setBit(1);

	
	//Add one more bit at the right end temporarily, and delete it later
	t1 = new Bit;
	tRight = t1;
	d1 = c1;
	while(true)
	{
		if(d1->getIsLeftEnd()) break;
		d1 = d1->getLeft();
		t2 = new Bit;
		t2->setBit(d1->getBit());
		t1->setLeft(t2);
		t2->setRight(t1);
		t1 = t2;
	}
	
	//add one more 0 at the left end
	t2 = new Bit;
	t2->setLeft(nullptr);
	t2->setIsLeftEnd(true);
	t2->setBit(0);
	t1->setLeft(t2);
	t2->setRight(t1);
	t1 = t2;
	tLeft=t1;
	
	tRight = tRight->getLeft();
	delete tRight->getRight();
	
	while(true)
	{
		if(c2->getIsLeftEnd()) break;
		
		//add one more 0 at the left end
		t2 = new Bit;
		t2->setLeft(nullptr);
		t2->setIsLeftEnd(true);
		t2->setBit(0);
		tLeft->setIsLeftEnd(false);
		tLeft->setLeft(t2);
		t2->setRight(tLeft);
		tLeft=t2;
		
		c2 = c2->getLeft();
		if(c2->getBit())
		{
			d1 = c1;
			t1 = tRight;
			carry=0;
			PositiveInteger::AddThreeBit(d1->getBit(),t1->getBit(),carry,result1,result2);
			
			b2 = new Bit;
			b2->setBit(result2);
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
			
			carry=result1;
			while(true)
			{
				if(d1->getIsLeftEnd()) break;
				d1 = d1->getLeft();
				t1 = t1->getLeft();
				PositiveInteger::AddThreeBit(d1->getBit(),t1->getBit(),carry,result1,result2);
				t1->setBit(result2);
				carry=result1;
			}
			if(carry)
			{
				t1 = t1->getLeft();
				t1->setBit(carry);
			}
		}
		else
		{
			b2 = new Bit;
			b2->setBit(tRight->getBit());
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
		//delete one right end
		tRight = tRight->getLeft();
		delete tRight->getRight();
	}
	t1 = tRight;
	while(!t1->getIsLeftEnd())
	{
		b2 = new Bit;
		b2->setBit(t1->getBit());
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		t1 = t1->getLeft();
		delete t1->getRight();
	}
	
	if(t1->getBit())
	{
		b2 = new Bit;
		b2->setBit(t1->getBit());
		b1->setLeft(b2);
		b2->setRight(b1);
		b2->setLeft(nullptr);
		b2->setIsLeftEnd(true);
		y->setLeftEnd(b2);
	}
	else
	{
		b1->setLeft(nullptr);
		b1->setIsLeftEnd(true);
		y->setLeftEnd(b1);

	}
	delete t1;
	return y;
}
/*
void PositiveInteger::Divide(PositiveInteger* x1,PositiveInteger* x2,PositiveInteger*& y1,PositiveInteger*& y2,bool& divisible, bool overwrite, bool checking)
{
	PositiveInteger* one;
	PositiveInteger* p1;
	PositiveInteger* p3;
	
	Bit* b1;
	Bit* b2;
	Bit* t1;
	Bit* t2;
	Bit* c1;
	Bit* digit1;
	Bit* digit2;
	
	if(checking)
	{
		CompareCode test = PositiveInteger::compare(x1,x2);
		if(test.isSmaller())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
	}
	
	if(overwrite)
	{
		y2=x1;
	}
	else
	{
		y2 = new PositiveInteger;
		c1 = x1->getRightEnd();
		t1 = new Bit;
		t1->setBit(c1->getBit());
		y2->setRightEnd(t1);
		while(!c1->isLeftEnd())
		{
			c1 = c1->getLeft();
			t2 = new Bit;
			t2->setBit(c1->getBit());
			t1->setLeft(t2);
			t2->setRight(t1);
			t1 = t2;
		}
		y2->setLeftEnd(t1);
	}
	
	digit1 = y2->getLeftEnd();
	digit2 = x2->getLeftEnd();
	//digit1 = 1, digit2 = 1
	CompareCode compare;
	while(true)
	{
		if(digit2->isRightEnd())
		{
			compare = CompareCode(true);
			break;
		}
		if(digit1->isRightEnd())
		{
			//y1 = 0, y2 = x1
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
		
		digit1 = digit1->getRight();
		digit2 = digit2->getRight();
		if(digit1->getBit() && !digit2->getBit())
		{
			//digit1 = 1, digit2 = 0
			compare = CompareCode(false,true);
			break;
		}
		if(!digit1->getBit() && digit2->getBit())
		{
			//digit1 = 0, digit2 = 1
			compare = CompareCode(false,false);
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
	
	y1 = new PositiveInteger;
	b1 = new Bit;
	y1->setLeftEnd(b1);
	while(true)
	{
		if(digit1->isRightEnd())
		{
			break;
		}
		b2 = new Bit;
		b2->setLeft(b1);
		b1->setRight(b2);
		b1 = b2;
		
		digit1 = digit1->getRight();
	}
	y1->setRightEnd(b1);

	p1 = x1->getNumberOfDigit();
	one = new PositiveInteger;
	PositiveInteger::One(one);
	p1 = PositiveInteger::Add(p1,one,false);
	
	p3 = x2->getNumberOfDigit();
	PositiveInteger::Subtract(p1,p3,true,false);
	
	if(compare.isSmaller())
	{
		//reserve one more 0 at the left end
		y1->getLeftEnd()->setBit(0);
		y1->getLeftEnd()->getRight()->setBit(1);

		PositiveInteger::Subtract(p1,one,true,false);
	}
	else
	{
		y1->getLeftEnd()->setBit(1);
	}
	y1->setNumberOfDigit(p1);
	p1->setNumberOfDigitParent(y1);
	
	if(overwrite)
	{
		if(!y2->isOneOrTwo())
		{
			delete y2->getNumberOfDigit();
		}
		y2->setNumberOfDigit(nullptr);
	}
	
	b1 = y1->getLeftEnd();
	bool isCount;
	bool isEnd = false;
	bool isSubtract = true;
	PositiveInteger* count = nullptr;
	divisible = false;
	
	bool w1;
	bool w2;
	while(true)
	{
		if(compare.isEqual())
		{
			isSubtract = true;
			isCount = false;
			c1 = x2->getLeftEnd();
			while(true)
			{
				if(isSubtract)
				{
					t1->setBit(0);
					if(c1->isRightEnd())
					{
						isSubtract = false;
					}
					else
					{
						c1 = c1->getRight();
					}
				}
				
				if(t1->getBit())
				{
					divisible = false;
					break;
				}
				else
				{
					if(isCount)
					{
						PositiveInteger::Add(count,one,true);
					}
					if(!isEnd)
					{
						
						if(b1->isRightEnd())
						{
							isEnd = true;
							isCount = true;
							count = new PositiveInteger;
							PositiveInteger::One(count);
						}
						else
						{
							b1 = b1->getRight();
							t2 = t2->getRight();
						}
					}
					
					if(t1->isRightEnd())
					{
						divisible = true;
						delete y2->getRightEnd();
						y2->setRightEnd(nullptr);
						y2->setLeftEnd(nullptr);
						break;
					}
					else
					{
						t1 = t1->getRight();
						delete t1->getLeft();
						t1->setLeft(nullptr);
					}
				}
			}
		}
		else if(compare.isLarger())
		{
			p3 = x2->getNumberOfDigit();
			PositiveInteger::SubtractAux(t1,t2,p3,w1,w2,
											  x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),
											  true,true,b1,t2,isEnd,count);
		}
		else if(compare.isSmaller())
		{
			p3 = x2->getNumberOfDigit();
			p3 = PositiveInteger::Add(p3,one,false);
			PositiveInteger::SubtractAux(t1,t2->getRight(),p3,w1,w2,
											  x2->getLeftEnd(),x2->getRightEnd(),x2->getNumberOfDigit(),x2->getIsOne(),x2->getIsTwo(),
											  true,true,b1,t2,isEnd,count);
			delete p3;
		}
		
		if(isEnd)
		{
			if(divisible)
			{
				delete count;
				delete y2;
			}
			else
			{
				p1 = PositiveInteger::Subtract(x2->getNumberOfDigit(),count,false,false);
				delete count;
				y2->setNumberOfDigit(p1);
				p1->setNumberOfDigitParent(y2);
			}
		}
		else
		{
			//digit1 = 1, digit2 = 1
			digit1 = t1;
			digit2 = x2->getLeftEnd();
			while(true)
			{
				if(digit2->isRightEnd())
				{
					compare = CompareCode(true);
					break;
				}
				if(digit1->isRightEnd())
				{
					cout<<"Error!"<<endl;
					return;
				}
				
				digit1 = digit1->getRight();
				digit2 = digit2->getRight();
				if(digit1->getBit() && !digit2->getBit())
				{
					//digit1 = 1, digit2 = 0
					compare = CompareCode(false,true);
					break;
				}
				if(!digit1->getBit() && digit2->getBit())
				{
					//digit1 = 0, digit2 = 1
					compare = CompareCode(false,false);
					break;
				}
			}
			if(b1->isRightEnd() && compare.isSmaller())
			{
				isEnd = true;
				p1 = x2->getNumberOfDigit()->copy();
				y2->setNumberOfDigit(p1);
				p1->setNumberOfDigitParent(y2);
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
			
			if(!y1->getLeftEnd()->getBit())
			{
				//delete the additional 0 at the left end
				b1 = y1->getLeftEnd()->getRight();
				delete b1->getLeft();
				b1->setLeft(nullptr);
				y1->setLeftEnd(b1);
			}
			
			if(y1->getNumberOfDigit()->getIsOne())
			{
				//y1=1
				y1->setIsOne(true);
				y1->setIsTwo(false);
				delete y1->getNumberOfDigit();
				y1->setNumberOfDigit(y1);
			}
			else if(y1->getNumberOfDigit()->getIsTwo() && !y1->getRightEnd()->getBit())
			{
				//y1=2
				y1->setIsOne(false);
				y1->setIsTwo(true);
				delete y1->getNumberOfDigit();
				y1->setNumberOfDigit(y1);
			}
			else
			{
				//y1>=3
				y1->setIsOne(false);
				y1->setIsTwo(false);
			}
			
			if(!divisible)
			{
				y2->setLeftEnd(t1);
				if(p1->getIsOne())
				{
					//y2=1
					y2->setIsOne(true);
					y2->setIsTwo(false);
					delete y2->getNumberOfDigit();
					y2->setNumberOfDigit(y2);
					
				}
				else if(p1->getIsTwo() && !y2->getRightEnd()->getBit())
				{
					//y2=2
					y2->setIsOne(false);
					y2->setIsTwo(true);
					delete y2->getNumberOfDigit();
					y2->setNumberOfDigit(y2);
				}
				else
				{
					//y2>=3
					y2->setIsOne(false);
					y2->setIsTwo(false);
				}
			}
			delete one;
			return;
		}
	}
}

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
		
	if(getRightEnd()==nullptr) return false;
	b1 = getRightEnd();
	if(b1->getRight()!=nullptr) return false;
	if(!b1->getIsRightEnd()) return false;
	while(true)
	{
		if(b1->getLeft()==nullptr) break;
		if(b1->getIsLeftEnd()) return false;
		b2 = b1->getLeft();
		if(b2->getRight()==nullptr) return false;
		if(b2->getIsRightEnd()) return false;
		if(b2->getRight()!=b1) return false;
		b1 = b2;
	}
    if(!b1->getIsLeftEnd()) return false;
	if(!b1->getBit()) return false;
	if(getLeftEnd()==nullptr) return false;
	b2 = getLeftEnd();
	if(b1!=b2) return false;

	return true;
}
bool PositiveInteger::isSame(unsigned int x)
{
	if(!isComplete()) return false;
	PositiveInteger* p1 = new PositiveInteger(x);
	Bit* b1;
	Bit* b2;
	
	b1 = getRightEnd();
	b2 = p1->getRightEnd();
	while(true)
	{
		if(b1->getBit()!=b2->getBit()) return false;
		if(b1->getIsLeftEnd()) break;
		if(b2->getIsLeftEnd()) return false;
		b1 = b1->getLeft();
		b2 = b2->getLeft();
	}
	if(!b2->getIsLeftEnd()) return false;
	
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
/*
bool PositiveInteger::VerifyCounter(unsigned int max)
{
	PositiveInteger* one = new PositiveInteger;
	PositiveInteger::One(one);
	PositiveInteger* count = new PositiveInteger;
	PositiveInteger::One(count);
	for(unsigned int i=1;i<=max;i++)
	{
		if(!count->isSame(i)) return false;
		count = PositiveInteger::Add(count,one,true);
	}
	delete one;
	delete count;
	return true;
}
*/

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
/*
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
			p3 = PositiveInteger::Subtract(p1,p2,overwrite,false);
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
	}
	return true;
}
*/
bool PositiveInteger::VerifyMultiply(unsigned int max)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	for(unsigned int i=1;i<=max;i++)
	//for(unsigned int i=1;i<=1;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		//for(unsigned int j=3;j<=3;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			p3 = PositiveInteger::Multiply(p1,p2);
			//p3->printBinary();
			if(!p1->isSame(i)) return false;
			if(!p2->isSame(j)) return false;
			if(!p3->isSame(i*j)) return false;
			
			delete p1;
			delete p2;
			delete p3;
		}
	}
	return true;
}
/*
bool PositiveInteger::VerifyDivide(unsigned int max,bool overwrite)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* p4;
	bool divisible=0;
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=i;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			PositiveInteger::Divide(p1,p2,p3,p4,divisible,overwrite,false);
			if(!overwrite)
			{
				if(!p1->isSame(i)) return false;
			}
			if(!p2->isSame(j)) return false;
			if(!p3->isSame(i/j)) return false;
			if(i%j==0)
			{
				if(!divisible) return false;
			}
			else
			{
				if(divisible) return false;
				if(!p4->isSame(i%j)) return false;
				delete p4;
			}
			
			if(!overwrite) delete p1;
			delete p2;
			delete p3;
		}
	}
	return true;
}
*/