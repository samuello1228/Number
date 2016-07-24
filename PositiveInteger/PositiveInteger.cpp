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
	Byte* b1 = getLeftEnd();
	Byte* b2;
	while(!b1->getIsRightEnd())
	{
		b2 = b1->getRight();
		delete b1;
		b1 = b2;
	}
	delete b1;
}

Byte* PositiveInteger::getLeftEnd()
{
	return leftEnd;
}
void PositiveInteger::setLeftEnd(Byte* newLeftEnd)
{
	leftEnd = newLeftEnd;
}
Byte* PositiveInteger::getRightEnd()
{
	return rightEnd;
}
void PositiveInteger::setRightEnd(Byte* newRightEnd)
{
	rightEnd = newRightEnd;
}

PositiveInteger::PositiveInteger(bool x,bool temp)
{
	if(x)
	{
		Byte* b1 = new Byte;
		b1->setByteOne();
		b1->setLeft(nullptr);
		b1->setIsLeftEnd(true);
		setLeftEnd(b1);
		b1->setRight(nullptr);
		b1->setIsRightEnd(true);
		setRightEnd(b1);
		
	}
}

PositiveInteger::PositiveInteger(std::string x)
{
	std::string::iterator i=x.begin();
	Byte* b1;
	Byte* b2 = new Byte;
	b2->setLeft(nullptr);
	b2->setIsLeftEnd(true);
	setLeftEnd(b2);
	
	while(true)
	{
		b2->setByteChar(*i);
		b1 = b2;
		i++;
		
		if(i==x.end()) break;
		b2 = new Byte;
		b1->setRight(b2);
		b2->setLeft(b1);
	}
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	setRightEnd(b1);
}

int PositiveInteger::getInt()
{
	unsigned int y = 0;
	unsigned int add = 1;
	Byte* d1;
	d1 = getRightEnd();
	while(true)
	{
		y += d1->getByteInt() * add;
		if(d1->getIsLeftEnd()) break;
		d1 = d1->getLeft();
		add *= Byte::getBase();
	}
	return y;
}

PositiveInteger* PositiveInteger::changeBase(unsigned int base)
{
	PositiveInteger* y;
	PositiveInteger* Base = new PositiveInteger(base);
	PositiveInteger* x1;
	PositiveInteger* x2 = nullptr;
	Byte* b1;
	Byte* b2;
	bool divisible = false;
	bool isEnd = false;

	x1 = this->copy();
	Digit* digit1 = new Digit;
	Digit* digit2;
	while(true)
	{
		if(PositiveInteger::compare(x1,Base).isSmaller())
		{
			divisible = false;
			isEnd = true;
		}
		else
		{
			PositiveInteger::Divide(x1,Base,x2,x1,divisible,true);
		}
		
		if(divisible)
		{
			digit1->digit = 0;
		}
		else
		{
			digit1->digit = x1->getInt();
		}
		
		if(isEnd)
		{
			Byte::setBase(base);
			y = new PositiveInteger;
			b1 = new Byte;
			b1->setLeft(nullptr);
			b1->setIsLeftEnd(true);
			y->setLeftEnd(b1);
			
			b1->setByteInt(digit1->digit);
			while(true)
			{
				if(digit1->Right==nullptr) break;
				digit2 = digit1->Right;
				delete digit1;
				
				b2 = new Byte;
				b2->setByteInt(digit2->digit);
				b1->setRight(b2);
				b2->setLeft(b1);
				
				b1 = b2;
				digit1 = digit2;
			}
			delete digit1;
			
			b1->setRight(nullptr);
			b1->setIsRightEnd(true);
			y->setRightEnd(b1);
			
			delete x1;
			delete Base;
			return y;
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

void PositiveInteger::printByte()
{
	Byte* b1 = getLeftEnd();
	while(true)
	{
		cout<<b1->getByteChar();
		if(b1->getIsRightEnd()) break;
		b1 = b1->getRight();
	}
	cout<<endl;
}

PositiveInteger* PositiveInteger::getNumberOfByte()
{
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* y = new PositiveInteger(true,true);
	Byte* c1 = getRightEnd();
	while(true)
	{
		if(c1->getIsLeftEnd()) break;
		PositiveInteger::Add(y,one,true);
		c1 = c1->getLeft();
	}
	delete one;
	return y;
}
void PositiveInteger::copyAux(bool& AddIsCarried,Byte*& b1,Byte* c1,Byte* Multiple)
{
	Byte* b2;
	Byte* carry1 = nullptr;
	Byte* carry2 = nullptr;
	AddIsCarried = false;
	
	if(Multiple!=nullptr)
	{
		carry1 = new Byte;
		carry2 = new Byte;
		carry1->setByteZero();
	}
	
	while(true)
	{
		if(Multiple==nullptr)
		{
			b1->setBytePointer(c1);
		}
		else
		{
			Byte::MultiplyAux2(c1,Multiple,carry1,carry2,b1);
			carry1->setBytePointer(carry2);
		}
		if(c1->getIsLeftEnd()) break;
		c1 = c1->getLeft();
		b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
	}
	
	//carry
	if(Multiple!=nullptr && !carry1->isZero())
	{
		AddIsCarried = true;
		b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		b1->setBytePointer(carry1);
	}
	
	if(Multiple!=nullptr)
	{
		delete carry1;
		delete carry2;
	}
}
PositiveInteger* PositiveInteger::copy()
{
	PositiveInteger* y;
	Byte* b1;
	Byte* c1;
	bool AddIsCarried;
	
	y = new PositiveInteger;
	b1 = new Byte;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	c1 = getRightEnd();
	PositiveInteger::copyAux(AddIsCarried,b1,c1);

	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	y->setLeftEnd(b1);
	return y;
}

CompareCode PositiveInteger::compare(PositiveInteger* x1, PositiveInteger* x2)
{
	Byte* b1;
	Byte* b2;
	CompareCode code;
	
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
		code = Byte::compare(b1,b2);
		if(!code.isEqual())
		{
			return code;
		}
		
		if(b1->getIsRightEnd()) break;
		b1 = b1->getRight();
		b2 = b2->getRight();
	}
	
	return CompareCode(true);
}


PositiveInteger* PositiveInteger::AddAux(Byte* c1, Byte* c2,bool overwrite,bool& AddIsCarried,Byte*& LeftEnd,Byte* Multiple)
{
	PositiveInteger* y = nullptr;
	Byte* b1 = nullptr;
	Byte* b2 = nullptr;
	bool carry1 = 0;
	bool carry2;
	AddIsCarried = false;
	
	Byte* carry3 = nullptr;
	Byte* carry4 = nullptr;
	
	if(Multiple!=nullptr)
	{
		carry3 = new Byte;
		carry4 = new Byte;
		carry3->setByteZero();
	}
	
	if(!overwrite)
	{
		y = new PositiveInteger;
		b2 = new Byte;
		b2->setRight(nullptr);
		b2->setIsRightEnd(true);
		y->setRightEnd(b2);
	}
	
	while(true)
	{
		//Add
		if(Multiple==nullptr)
		{
			if(overwrite)
			{
				Byte::AddThreeByte(c1,c2,carry1,carry2,c1);
			}
			else
			{
				Byte::AddThreeByte(c1,c2,carry1,carry2,b2);
				b1 = b2;
			}
			carry1 = carry2;
		}
		else
		{
			Byte::MultiplyAux3(c1,c2,Multiple,carry3,carry4,c1);
			carry3->setBytePointer(carry4);
		}
		
		//find left end
		if(c1->getIsLeftEnd())
		{
			if(c2->getIsLeftEnd())
			{
				//the length of x1 and x2 are equal
				if(Multiple!=nullptr)
				{
					if(carry3->isZero()) carry1 = false;
					else carry1 = true;
				}
				
				if(carry1)
				{
					//fill carry
					b2 = new Byte;
					b2->setLeft(nullptr);
					b2->setIsLeftEnd(true);
					
					if(Multiple==nullptr) b2->setByteOne();
					else b2->setBytePointer(carry3);
					
					if(overwrite)
					{
						c1->setIsLeftEnd(false);
						c1->setLeft(b2);
						b2->setRight(c1);
						LeftEnd = b2;
						AddIsCarried = true;
						
						if(Multiple!=nullptr)
						{
							delete carry3;
							delete carry4;
						}
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
						if(Multiple!=nullptr)
						{
							delete carry3;
							delete carry4;
						}
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
				///////////////////////////
				//the length of x1 is shorter than x2
				if(overwrite)
				{
					c1->setIsLeftEnd(false);
				}
				
				if(Multiple==nullptr)
				{
					if(carry1)
					{
						while(true)
						{
							c2 = c2->getLeft();
							if(c2->isMax())
							{
								b2 = new Byte;
								b2->setByteZero();
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
									b2 = new Byte;
									b2->setByteOne();
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
									break;
								}
							}
							else
							{
								b2 = new Byte;
								b2->setByteAddOne(c2);
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
								break;
							}
						}
					}
				}
				else
				{
					while(true)
					{
						c2 = c2->getLeft();
						
						b2 = new Byte;
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
						Byte::MultiplyAux2(c2,Multiple,carry3,carry4,c1);
						carry3->setBytePointer(carry4);
						
						if(c2->getIsLeftEnd()) break;
					}
					
					//carry
					if(!carry3->isZero())
					{
						b2 = new Byte;
						b2->setBytePointer(carry3);
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
					}
				}

				if(!c2->getIsLeftEnd())
				{
					c2 = c2->getLeft();
					b2 = new Byte;
					if(overwrite)
					{
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
						copyAux(AddIsCarried,c1,c2,Multiple);
					}
					else
					{
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						copyAux(AddIsCarried,b1,c2,Multiple);
					}
				}
				
				if(overwrite)
				{
					c1->setLeft(nullptr);
					c1->setIsLeftEnd(true);
					LeftEnd = c1;
					AddIsCarried = true;
					
					if(Multiple!=nullptr)
					{
						delete carry3;
						delete carry4;
					}
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
				//the length of x1 is longer than x2
				if(carry1)
				{
					while(true)
					{
						c1 = c1->getLeft();
						if(c1->isMax())
						{
							if(overwrite)
							{
								c1->setByteZero();
							}
							else
							{
								b2 = new Byte;
								b2->setByteZero();
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							
							if(c1->getIsLeftEnd())
							{
								b2 = new Byte;
								b2->setLeft(nullptr);
								b2->setIsLeftEnd(true);
								b2->setByteOne();
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
								c1->setByteAddOne(c1);
							}
							else
							{
								b2 = new Byte;
								b2->setByteAddOne(c1);
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							break;
						}
					}
				}
				
				if(overwrite)
				{
					return nullptr;
				}
				else
				{
					if(!c1->getIsLeftEnd())
					{
						c1 = c1->getLeft();
						b2 = new Byte;
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						copyAux(AddIsCarried,b1,c1);
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
				//continue to find left end
				c1 = c1->getLeft();
				c2 = c2->getLeft();
			}
		}
		
		if(!overwrite)
		{
			b2 = new Byte;
			b1->setLeft(b2);
			b2->setRight(b1);
		}
	}
}
PositiveInteger* PositiveInteger::Add(PositiveInteger* x1,PositiveInteger* x2,bool overwrite)
{
	PositiveInteger* y = nullptr;
	Byte* c1 = x1->getRightEnd();
	Byte* c2 = x2->getRightEnd();
	Byte* LeftEnd = nullptr;
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

void PositiveInteger::SubtractAux(Byte*& LeftEnd1,Byte* RightEnd1,Byte* RightEnd2,bool& isShorten,bool overwrite,
									bool Divide,Byte*& b1,Byte*& tRight,bool isSmall,bool& b1IsFilled,bool& isZero,bool& isEnd,Byte* Multiple)
{
	Byte* b2;
	Byte* d1;
	bool isDelay;
	PositiveInteger* product=nullptr;
	bool MultiplyIsCarried;
	
	if(Multiple!=nullptr)
	{
		product = new PositiveInteger;
		b2 = new Byte;
		b2->setIsRightEnd(true);
		product->setRightEnd(b2);
		copyAux(MultiplyIsCarried,b2,RightEnd2,Multiple);
		b2->setIsLeftEnd(true);
		product->setLeftEnd(b2);
		RightEnd2 = product->getRightEnd();
	}
	
	while(true)
	{
		if(Byte::compare(RightEnd1,RightEnd2).isSmaller())
		{
			RightEnd1->setByteSubtractBorrow(RightEnd2);
			
			d1 = RightEnd1;
			while(true)
			{
				d1 = d1->getLeft();
				if(!d1->isZero()) break;
				d1->setByteMax();
			}
			d1->setByteSubtractOne();
		}
		else
		{
			RightEnd1->setByteSubtract(RightEnd2);
		}
		
		if(RightEnd2->getIsLeftEnd())
		{
			break;
		}
		else
		{
			RightEnd1 = RightEnd1->getLeft();
			RightEnd2 = RightEnd2->getLeft();
		}
	}
	delete product;
	
	//delete 0 at the left
	isShorten = false;
	isDelay = isSmall;
	isZero = false;
	if(LeftEnd1->isZero())
	{
		isShorten = true;
		while(true)
		{
			if(Divide)
			{
				if(isDelay)
				{
					//b1 is delay for isSamll
					if(tRight->getIsRightEnd())
					{
						isEnd = true;
					}
					isDelay = false;
				}
				else
				{
					if(!isEnd)
					{
						//fill b1 with 0
						if(b1IsFilled)
						{
							b1IsFilled = false;
						}
						else
						{
							b1->setByteZero();
						}
						
						if(tRight->getIsRightEnd())
						{
							isEnd = true;
						}
						else
						{
							tRight = tRight->getRight();
							b2 = new Byte;
							b2->setLeft(b1);
							b1->setRight(b2);
							b1 = b2;
						}
					}
				}
			}
			
			//delete
			if(LeftEnd1->getIsRightEnd())
			{
				//y = 0
				isZero = true;
				break;
			}
			else
			{
				LeftEnd1 = LeftEnd1->getRight();
				delete LeftEnd1->getLeft();
				if(!LeftEnd1->isZero()) break;
			}
		}
	}
	LeftEnd1->setIsLeftEnd(true);
}


PositiveInteger* PositiveInteger::Subtract(PositiveInteger* x1,PositiveInteger* x2,bool overwrite)
{
	PositiveInteger* y;
	Byte* d1;
	Byte* temp1;
	bool temp2;
	bool isShorten;
	
	if(overwrite)
	{
		y = x1;
	}
	else
	{
		y = x1->copy();
	}
	d1 = y->getLeftEnd();
	PositiveInteger::SubtractAux(d1,y->getRightEnd(),x2->getRightEnd(),isShorten,
									overwrite,false,temp1,temp1,temp2,temp2,temp2,temp2);
	d1->setLeft(nullptr);
	if(isShorten) y->setLeftEnd(d1);
	return y;
}

void PositiveInteger::MultiplyAux(Byte* c1,Byte* c2,Byte* tRight,Byte*& b1,bool& MultiplyIsCarried)
{

	Byte* b2;
	Byte* LeftEnd;
	bool AddIsCarried;
	Byte* Multiple = nullptr;
	
	Byte* carry = nullptr;
	if(Byte::getBase()!=2)
	{
		carry = new Byte;
	}
	
	if(!c2->getIsLeftEnd())
	{
		while(true)
		{
			c2 = c2->getLeft();
			if(tRight->getIsLeftEnd())
			{
				//tRight->getLeft() for y does not exist
				b1->setIsLeftEnd(false);
				b2 = new Byte;
				b1->setLeft(b2);
				b2->setRight(b1);
				b1 = b2;
				
				if(Byte::getBase()==2)
				{
					b1->setBytePointer(c2);
				}
				else
				{
					//c1 must be only one byte
					Byte::MultiplyAux1(c1,c2,carry,b1);
					if(!carry->isZero())
					{
						MultiplyIsCarried = true;
						b2 = new Byte;
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						b1->setBytePointer(carry);
					}
				}
				
				b1->setIsLeftEnd(true);
				tRight = tRight->getLeft();
			}
			else
			{
				tRight = tRight->getLeft();
				if(!c2->isZero())
				{
					//Add y(tRight) and x1(c1)
					if(Byte::getBase() != 2) Multiple = c2;
					PositiveInteger::AddAux(tRight,c1,true,AddIsCarried,LeftEnd,Multiple);
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
					//c2 = 0, and do not need to add
					//y remain unchanged
					//add one more 0 at the left end, in order to count MultiplyIsCarried
					b1->setIsLeftEnd(false);
					b2 = new Byte;
					b1->setLeft(b2);
					b2->setRight(b1);
					b1 = b2;
					b1->setByteZero();
					b1->setIsLeftEnd(true);
				}
			}
			if(c2->getIsLeftEnd()) break;
		}
	}
	
	if(Byte::getBase()!=2)
	{
		delete carry;
	}
}
PositiveInteger* PositiveInteger::Multiply(PositiveInteger* x1,PositiveInteger* x2,bool& MultiplyIsCarried)
{
	PositiveInteger* y;
	Byte* b1;
	Byte* b2;
	Byte* c1;
	Byte* c2;
	Byte* tRight;
	
	y = new PositiveInteger;
	b1 = new Byte;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	//////////////// copy zero of x1
	c1 = x1->getRightEnd();
	while(true)
	{
		if(!c1->isZero()) break;
		b1->setByteZero();
		b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c1 = c1->getLeft();
	}
	
	////////////////copy zero of x2
	c2 = x2->getRightEnd();
	while(true)
	{
		if(!c2->isZero()) break;
		b1->setByteZero();
		b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c2 = c2->getLeft();
	}
	tRight = b1;
	
	////////////////copy x1 without zero
	copyAux(MultiplyIsCarried,b1,c1,c2);
	b1->setIsLeftEnd(true);

	////////////////
	PositiveInteger::MultiplyAux(c1,c2,tRight,b1,MultiplyIsCarried);
	b1->setLeft(nullptr);
	y->setLeftEnd(b1);
	return y;
}

void PositiveInteger::Divide(PositiveInteger* x1,PositiveInteger* x2,PositiveInteger*& y1,PositiveInteger*& y2,bool& divisible, bool overwrite)
{
	Byte* b1;
	Byte* b2 = nullptr;
	Byte* tLeft;
	Byte* tRight;
	Byte* d1;
	Byte* d2;
	Byte* Multiple;
	CompareCode compareByte;
	CompareCode compareInteger;
	bool isEnd;
	bool isZero;
	bool b1IsFilled;
	bool temp;
	bool MultiplyIsCarried;
	PositiveInteger* product;
	
	if(overwrite)
	{
		y2 = x1;
	}
	else
	{
		y2 = x1->copy();
	}
	
	//find tLeft and tRight
	tLeft = y2->getLeftEnd();
	tRight = y2->getLeftEnd();
	d1 = x2->getLeftEnd();
	while(true)
	{
		if(d1->getIsRightEnd())
		{
			break;
		}
		if(tRight->getIsRightEnd())
		{
			cout<<"Error! PositiveInteger does not support number zero."<<endl;
			return;
		}
		tRight = tRight->getRight();
		d1 = d1->getRight();
	}
	
	//create left end for y1
	y1 = new PositiveInteger;
	b1 = new Byte;
	y1->setLeftEnd(b1);
	
	//////////////////
	b1IsFilled = false;
	isEnd = false;
	divisible = false;
	if(Byte::getBase() == 2)
	{
		Multiple = nullptr;
	}
	else
	{
		Multiple = new Byte;
	}
	
	while(true)
	{
		if(!isEnd)
		{
			//compare y1(tLeft to tRight) and x2
			d1 = tLeft;
			d2 = x2->getLeftEnd();
			while(true)
			{
				compareByte = Byte::compare(d1,d2);
				if(compareByte.isLarger())
				{
					//y1(tLeft to tRight) is larger than x2
					compareInteger = CompareCode(false,true);
					break;
				}
				else if(compareByte.isSmaller())
				{
					//y1(tLeft to tRight) is smaller than x2
					compareInteger = CompareCode(false,false);
					break;
				}
				
				if(d2->getIsRightEnd())
				{
					//y1(tLeft to tRight) and x2 are equal
					compareInteger = CompareCode(true);
					break;
				}
				if(d1->getIsRightEnd())
				{
					//x1 < x2
					cout<<"Logic Error!"<<endl;
					return;
				}
				
				d1 = d1->getRight();
				d2 = d2->getRight();
			}
			
			//fill y1 with 0
			if(compareInteger.isSmaller())
			{
				if(!b1IsFilled)
				{
					b1->setByteZero();
				}
				
				if(tRight->getIsRightEnd())
				{
					isEnd = true;
				}
				else
				{
					tRight = tRight->getRight();
					b2 = new Byte;
					b2->setLeft(b1);
					b1->setRight(b2);
					b1 = b2;
				}
			}
		}
		
		//do subtraction
		if(!isEnd)
		{
			if(Byte::getBase() == 2)
			{
				//fill y1 with 1
				b1->setByteOne();
			}
			else
			{
				if(compareInteger.isEqual())
				{
					//Equal
					//fill y1 with 1
					b1->setByteOne();
					Multiple->setByteOne();
				}
				else
				{
					//is larger or is smaller
					//calculate estimated Multiple
					if(compareInteger.isLarger())
					{
						if(x2->getLeftEnd()->getIsRightEnd())
						{
							Byte::DivideAux(nullptr,nullptr,tLeft,nullptr,x2->getLeftEnd(),Multiple);
						}
						else
						{
							Byte::DivideAux(nullptr,tLeft,tLeft->getRight(),x2->getLeftEnd(),x2->getLeftEnd()->getRight(),Multiple);
						}
					}
					else
					{
						if(x2->getLeftEnd()->getIsRightEnd())
						{
							Byte::DivideAux(nullptr,tLeft,tLeft->getRight(),nullptr,x2->getLeftEnd(),Multiple);
						}
						else
						{
							Byte::DivideAux(tLeft,tLeft->getRight(),tLeft->getRight()->getRight(),
											x2->getLeftEnd(),x2->getLeftEnd()->getRight(),Multiple);
						}
					}
					
					//calculate correct Multiple
					if(Multiple->isOne())
					{
						b1->setByteOne();
					}
					else
					{
						//ignore zero at the right of x2
						d1 = x2->getRightEnd();
						while(true)
						{
							if(!d1->isZero()) break;
							d1 = d1->getLeft();
						}
						
						//calculate product
						product = new PositiveInteger;
						b2 = new Byte;
						b2->setIsRightEnd(true);
						product->setRightEnd(b2);
						copyAux(MultiplyIsCarried,b2,d1,Multiple);
						b2->setIsLeftEnd(true);
						product->setLeftEnd(b2);
						
						//compare y1(tLeft to tRight) and product
						if(compareInteger.isLarger() && MultiplyIsCarried)
						{
							//y1(tLeft to tRight) are shorter than product
							Multiple->setByteSubtractOne();
						}
						else if(compareInteger.isLarger() || MultiplyIsCarried)
						{
							//the length of y1(tLeft to tRight) and product are equal
							//compareInteger.isLarger() and !MultiplyIsCarried
							//compareInteger.isSmall() and MultiplyIsCarried
							d1 = tLeft;
							d2 = b2;
							while(true)
							{
								compareByte = Byte::compare(d1,d2);
								if(compareByte.isLarger())
								{
									//y1(tLeft to tRight) is larger than product
									break;
								}
								else if(compareByte.isSmaller())
								{
									//y1(tLeft to tRight) is smaller than product
									Multiple->setByteSubtractOne();
									break;
								}
								
								if(d2->getIsRightEnd())
								{
									//y1(tLeft to tRight) is larger than or equal to product
									break;
								}
								d1 = d1->getRight();
								d2 = d2->getRight();
							}
						}
						b1->setBytePointer(Multiple);
						delete product;
					}
				}
			}
			b1IsFilled = true;
			
			//Subtract
			PositiveInteger::SubtractAux(tLeft,tRight,x2->getRightEnd(),temp,true,
											true,b1,tRight,compareInteger.isSmaller(),b1IsFilled,isZero,isEnd,Multiple);
			if(isZero)
			{
				divisible = true;
				y2->setLeftEnd(tLeft);
				delete y2;
			}
		}
		
		if(isEnd)
		{
			//right end for y1
			b1->setRight(nullptr);
			b1->setIsRightEnd(true);
			y1->setRightEnd(b1);
			
			//left end for y1
			if(y1->getLeftEnd()->isZero())
			{
				//delete the additional 0 at the left end of y1
				b1 = y1->getLeftEnd()->getRight();
				delete b1->getLeft();
				y1->setLeftEnd(b1);
			}
			else
			{
				b1 = y1->getLeftEnd();
			}
			b1->setLeft(nullptr);
			b1->setIsLeftEnd(true);
			
			//left end for y2
			if(!divisible)
			{
				tLeft->setLeft(nullptr);
				y2->setLeftEnd(tLeft);
			}
			
			if(Byte::getBase() != 2)
			{
				delete Multiple;
			}
			return;
		}
	}
}

void PositiveInteger::printList(PositiveInteger::ListOfPositiveInteger* list,bool isDecimal)
{
	ListOfPositiveInteger* element1;
	ListOfPositiveInteger* element2;
	PositiveInteger* x;
	unsigned int base = Byte::getBase();
	
	element2 = list;
	while(true)
	{
		if(isDecimal)
		{
			x = element2->Element->changeBase(10);
			x->printByte();
			Byte::setBase(base);
			delete x;
		}
		else
		{
			element2->Element->printByte();
		}
		element1 = element2;
		if(element1->Next==nullptr) break;
		element2 = element1->Next;
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
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* two = PositiveInteger::Add(one,one,false);
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
	bool temp;
	while(true)
	{
		if(PositiveInteger::compare(i,max).isLarger())
		{
			break;
		}
		
		element1 = FirstElement;
		while(true)
		{
			p1 = PositiveInteger::Multiply(element1->Element,element1->Element,temp);
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
			
			PositiveInteger::Divide(i,element1->Element,p1,p2,divisible,false);
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
		PositiveInteger::Divide(p1,p2,p3,p4,divisible,false);
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

//verification
PositiveInteger::PositiveInteger(unsigned int x)
{
	unsigned int base = Byte::getBase();
	Byte* b1 = nullptr;
	Byte* b2 = new Byte;
	b2->setRight(nullptr);
	b2->setIsRightEnd(true);
	setRightEnd(b2);
	
	while(true)
	{
		b2->setByteInt(x%base);
		x = (x - b2->getByteInt())/base;
		b1 = b2;
		
		if(x==0) break;
		b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
	}
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	setLeftEnd(b1);
}

bool PositiveInteger::isComplete()
{
	Byte* b1;
	Byte* b2;
	
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
	if(b1->isZero()) {cout<<"Error Code: 9"<<endl; return false;}
	if(getLeftEnd()==nullptr) {cout<<"Error Code: 10"<<endl; return false;}
	b2 = getLeftEnd();
	if(b1!=b2) {cout<<"Error Code: 11"<<endl; return false;}
	
	return true;
}
bool PositiveInteger::isSame(unsigned int x)
{
	if(!isComplete()) {cout<<"Error Code: 12"<<endl; return false;}
	PositiveInteger* p1 = new PositiveInteger(x);
	Byte* b1;
	Byte* b2;
	
	b1 = getRightEnd();
	b2 = p1->getRightEnd();
	while(true)
	{
		if(!Byte::compare(b1,b2).isEqual()) {cout<<"Error Code: 13"<<endl; return false;}
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
		//p1->printByte();
		//cout<<p1->getInt()<<endl;
		//p1->printDecimal(0);
		
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
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* count = new PositiveInteger(true,true);
	for(unsigned int i=1;i<=max;i++)
	{
		if(!count->isSame(i)) return false;
		count = PositiveInteger::Add(count,one,true);
	}
	delete one;
	delete count;
	return true;
}
/*
bool PositiveInteger::VerifyPositiveInteger(unsigned int max)
{
	PositiveInteger* p1;
	PositiveInteger* p2;
	std::string s;
	Byte* b1;
	for(unsigned int i=1;i<=max;i++)
	{
		s.clear();
		p1 = new PositiveInteger(i);
		b1 = p1->getLeftEnd();
		while(true)
		{
			if(b1->getByte())
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
*/
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
			//p1->printByte();
			//p2->printByte();
			p3 = PositiveInteger::Add(p1,p2,overwrite);
			//p3->printByte();
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
			//cout<<endl;
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
			//p1->printByte();
			//p2->printByte();
			p3 = PositiveInteger::Subtract(p1,p2,overwrite);
			//p3->printByte();
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
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* p1;
	PositiveInteger* p2;
	PositiveInteger* p3;
	PositiveInteger* n1;
	PositiveInteger* n2;
	PositiveInteger* n3;
	bool MultiplyIsCarried;
	for(unsigned int i=1;i<=max;i++)
	//for(unsigned int i=14;i<=14;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		//for(unsigned int j=15;j<=15;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			p3 = PositiveInteger::Multiply(p1,p2,MultiplyIsCarried);
			//p3->printByte();
			
			if(!p1->isSame(i)) return false;
			if(!p2->isSame(j)) return false;
			if(!p3->isSame(i*j)) return false;
			
			n1 = p1->getNumberOfByte();
			n2 = p2->getNumberOfByte();
			n3 = p3->getNumberOfByte();
			
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
		
			delete p1;
			delete p2;
			delete p3;
			delete n1;
			delete n2;
			delete n3;
			//cout<<endl;
		}
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
	//for(unsigned int i=100;i<=100;i++)
	{
		for(unsigned int j=1;j<=i;j++)
		//for(unsigned int j=12;j<=12;j++)
		{
			p1 = new PositiveInteger(i);
			p2 = new PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			PositiveInteger::Divide(p1,p2,p3,p4,divisible,overwrite);
			//p3->printByte();
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
				//p4->printByte();
				if(divisible) {cout<<"Error Code: 20"<<endl; return false;}
				if(!p4->isSame(i%j)) {cout<<"Error Code: 21"<<endl; return false;}
				delete p4;
			}
			
			if(!overwrite) delete p1;
			delete p2;
			delete p3;
			//cout<<endl;
		}
	}
	return true;
}
