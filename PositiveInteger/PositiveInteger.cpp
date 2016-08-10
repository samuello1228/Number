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
	Byte const * b1 = getLeftEnd();
	while(!b1->getIsRightEnd())
	{
		Byte const * b2 = b1->getRight();
		delete b1;
		b1 = b2;
	}
	delete b1;
}

PositiveInteger::PositiveInteger(const bool x,const bool temp)
{
	//one
	Byte* const b1 = new Byte;
	b1->setByteOne();
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	setLeftEnd(b1);
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	setRightEnd(b1);
}

PositiveInteger::PositiveInteger(std::string& x)
{
	std::string::iterator i=x.begin();
	Byte* b1 = new Byte;
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	setLeftEnd(b1);
	
	while(true)
	{
		b1->setByteChar(*i);
		i++;
		
		if(i==x.end()) break;
		Byte* const b2 = new Byte;
		b1->setRight(b2);
		b2->setLeft(b1);
		b1 = b2;
	}
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	setRightEnd(b1);
}

Byte* PositiveInteger::getLeftEnd() const
{
	return leftEnd;
}
void PositiveInteger::setLeftEnd(Byte* const& newLeftEnd)
{
	leftEnd = newLeftEnd;
}
Byte* PositiveInteger::getRightEnd() const
{
	return rightEnd;
}
void PositiveInteger::setRightEnd(Byte* const& newRightEnd)
{
	rightEnd = newRightEnd;
}

int PositiveInteger::getInt() const
{
	unsigned int y = 0;
	unsigned int add = 1;
	Byte const * d1 = getRightEnd();
	while(true)
	{
		y += d1->getByteInt() * add;
		if(d1->getIsLeftEnd()) break;
		d1 = d1->getLeft();
		add *= Byte::getBase();
	}
	return y;
}

PositiveInteger* PositiveInteger::changeBase(const unsigned int base) const
{
	Digit* digit1 = new Digit;
	{
		PositiveInteger const Base = PositiveInteger(base);
		PositiveInteger* x1 = this->copy();
		bool isEnd = false;
		while(true)
		{
			PositiveInteger* x2 = nullptr;
			bool divisible;
			if(PositiveInteger::compare(*x1,Base).isSmaller())
			{
				divisible = false;
				isEnd = true;
			}
			else
			{
				PositiveInteger::Divide(*x1,Base,x2,x1,divisible,true);
			}
			
			if(divisible)
			{
				digit1->digit = 0;
			}
			else
			{
				digit1->digit = x1->getInt();
			}
			
			if(!divisible)
			{
				delete x1;
			}
			x1 = x2;
			
			if(isEnd) break;
			
			{
				Digit* const digit2 = new Digit;
				digit2->Right = digit1;
				digit1 = digit2;
			}
		}
	}
	
	Byte::setBase(base);
	PositiveInteger* const y = new PositiveInteger;
	Byte* b1 = new Byte;
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	y->setLeftEnd(b1);
	
	while(true)
	{
		b1->setByteInt(digit1->digit);
		
		if(digit1->Right==nullptr) break;
		Digit* const digit2 = digit1->Right;
		delete digit1;
		digit1 = digit2;
		
		Byte* const b2 = new Byte;
		b1->setRight(b2);
		b2->setLeft(b1);
		b1 = b2;
	}
	delete digit1;
	
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);

	return y;
}

void PositiveInteger::printByte() const
{
	Byte const * b1 = getLeftEnd();
	while(true)
	{
		cout<<b1->getByteChar();
		if(b1->getIsRightEnd()) break;
		b1 = b1->getRight();
	}
	cout<<endl;
}

PositiveInteger* PositiveInteger::getNumberOfByte() const
{
	PositiveInteger* const y = new PositiveInteger(true,true);
	Byte const * c1 = getRightEnd();
	while(true)
	{
		if(c1->getIsLeftEnd()) break;
		PositiveInteger const one = PositiveInteger(true,true);
		PositiveInteger::Add(*y,one,true);
		c1 = c1->getLeft();
	}
	return y;
}
void PositiveInteger::copyAux(Byte*& b1,Byte const& c1,Byte const * const Multiple,bool * const AddIsCarried)
{
	Byte carry1;
	if(Multiple!=nullptr)
	{
		carry1.setByteZero();
	}
	
	Byte const * d1 = &c1;
	while(true)
	{
		if(Multiple==nullptr)
		{
			b1->setBytePointer(*d1);
		}
		else
		{
			Byte carry2;
			Byte::MultiplyAux2(*d1,*Multiple,carry1,carry2,*b1);
			carry1.setBytePointer(carry2);
		}
		
		if(d1->getIsLeftEnd()) break;
		d1 = d1->getLeft();
		Byte* const b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
	}
	
	//carry
	if(AddIsCarried!=nullptr) *AddIsCarried = false;
	if(Multiple!=nullptr && !carry1.isZero())
	{
		if(AddIsCarried!=nullptr) *AddIsCarried = true;
		Byte* const b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		b1->setBytePointer(carry1);
	}
}

PositiveInteger* PositiveInteger::copy() const
{
	PositiveInteger * const y = new PositiveInteger;
	Byte* b1 = new Byte;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	PositiveInteger::copyAux(b1,*(getRightEnd()));

	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	y->setLeftEnd(b1);
	return y;
}

CompareCode PositiveInteger::compare(PositiveInteger const& x1, PositiveInteger const& x2)
{
	Byte const * b1 = x1.getRightEnd();
	Byte const * b2 = x2.getRightEnd();
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
		CompareCode const code = Byte::compare(*b1,*b2);
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


PositiveInteger* PositiveInteger::AddAux(Byte& RightEnd1, Byte const& RightEnd2,bool const overwrite,bool& AddIsCarried,Byte*& LeftEnd1,Byte const * const Multiple)
{
	Byte* b1 = nullptr;
	PositiveInteger* y = nullptr;
	if(!overwrite)
	{
		y = new PositiveInteger;
		b1 = new Byte;
		b1->setRight(nullptr);
		b1->setIsRightEnd(true);
		y->setRightEnd(b1);
	}
	
	Byte* c1 = &RightEnd1;
	Byte const* c2 = &RightEnd2;
	bool carry1 = 0;
	Byte carry3;
	if(Multiple!=nullptr)
	{
		carry3.setByteZero();
	}
	AddIsCarried = false;
	while(true)
	{
		//Add
		if(Multiple==nullptr)
		{
			bool carry2;
			if(overwrite)
			{
				Byte::AddThreeByte(*c1,*c2,carry1,carry2,*c1);
			}
			else
			{
				Byte::AddThreeByte(*c1,*c2,carry1,carry2,*b1);
			}
			carry1 = carry2;
		}
		else
		{
			Byte carry4;
			Byte::MultiplyAux3(*c1,*c2,*Multiple,carry3,carry4,*c1);
			carry3.setBytePointer(carry4);
		}
		
		//find left end
		if(c1->getIsLeftEnd())
		{
			if(c2->getIsLeftEnd())
			{
				//the length of x1 and x2 are equal
				if(Multiple!=nullptr)
				{
					if(carry3.isZero()) carry1 = false;
					else carry1 = true;
				}
				
				if(carry1)
				{
					//fill carry
					Byte* const b2 = new Byte;
					b2->setLeft(nullptr);
					b2->setIsLeftEnd(true);
					
					if(Multiple==nullptr) b2->setByteOne();
					else b2->setBytePointer(carry3);
					
					AddIsCarried = true;
					if(overwrite)
					{
						c1->setIsLeftEnd(false);
						c1->setLeft(b2);
						b2->setRight(c1);
						LeftEnd1 = b2;
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
				///////////////////////////
				//the length of x1 is shorter than x2
				if(overwrite)
				{
					c1->setIsLeftEnd(false);
				}
				
				if(Multiple==nullptr)
				{
					//carry
					if(carry1)
					{
						while(true)
						{
							c2 = c2->getLeft();
							if(c2->isMax())
							{
								Byte* const b2 = new Byte;
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
									Byte* const b2 = new Byte;
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
										AddIsCarried = true;
									}
									break;
								}
							}
							else
							{
								Byte* const b2 = new Byte;
								b2->setByteAddOne(*c2);
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
					//for multiply, overwrite
					while(true)
					{
						c2 = c2->getLeft();
						{
							Byte* const b2 = new Byte;
							c1->setLeft(b2);
							b2->setRight(c1);
							c1 = b2;
						}
						
						{
							Byte carry4;
							Byte::MultiplyAux2(*c2,*Multiple,carry3,carry4,*c1);
							carry3.setBytePointer(carry4);
						}
						if(c2->getIsLeftEnd()) break;
					}
					
					//carry
					if(!carry3.isZero())
					{
						Byte* const b2 = new Byte;
						b2->setBytePointer(carry3);
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
					}
				}
				
				//copy
				if(!c2->getIsLeftEnd())
				{
					c2 = c2->getLeft();
					Byte* const b2 = new Byte;
					if(overwrite)
					{
						c1->setLeft(b2);
						b2->setRight(c1);
						c1 = b2;
						PositiveInteger::copyAux(c1,*c2,Multiple,&AddIsCarried);
					}
					else
					{
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						PositiveInteger::copyAux(b1,*c2,Multiple,&AddIsCarried);
					}
				}
				
				//set left end
				if(overwrite)
				{
					c1->setLeft(nullptr);
					c1->setIsLeftEnd(true);
					LeftEnd1 = c1;
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
				//the length of x1 is longer than x2
				if(carry1)
				{
					//carry
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
								Byte* const b2 = new Byte;
								b2->setByteZero();
								b1->setLeft(b2);
								b2->setRight(b1);
								b1 = b2;
							}
							
							if(c1->getIsLeftEnd())
							{
								Byte* const b2 = new Byte;
								b2->setLeft(nullptr);
								b2->setIsLeftEnd(true);
								b2->setByteOne();
								AddIsCarried = true;
								if(overwrite)
								{
									c1->setIsLeftEnd(false);
									c1->setLeft(b2);
									b2->setRight(c1);
									LeftEnd1 = b2;
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
								c1->setByteAddOne(*c1);
							}
							else
							{
								Byte* const b2 = new Byte;
								b2->setByteAddOne(*c1);
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
					//copy
					if(!c1->getIsLeftEnd())
					{
						c1 = c1->getLeft();
						Byte* const b2 = new Byte;
						b1->setLeft(b2);
						b2->setRight(b1);
						b1 = b2;
						PositiveInteger::copyAux(b1,*c1);
					}
					
					//set left end
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
		
		//for c1 and c2 are not left end
		if(!overwrite)
		{
			Byte* const b2 = new Byte;
			b1->setLeft(b2);
			b2->setRight(b1);
			b1 = b2;
		}
	}
}
PositiveInteger* PositiveInteger::Add(PositiveInteger& x1,PositiveInteger const& x2,bool const overwrite,bool* const AddIsCarried)
{
	bool AddIsCarriedAux;
	Byte* LeftEnd;
	PositiveInteger* const y = PositiveInteger::AddAux(*(x1.getRightEnd()),*(x2.getRightEnd()),overwrite,AddIsCarriedAux,LeftEnd);
	if(AddIsCarried!=nullptr)
	{
		*AddIsCarried = AddIsCarriedAux;
	}
	
	if(overwrite)
	{
		if(AddIsCarriedAux)
		{
			x1.setLeftEnd(LeftEnd);
		}
		return &x1;
	}
	else
	{
		return y;
	}
}

void PositiveInteger::SubtractAux(Byte*& LeftEnd1,Byte& RightEnd1,Byte const& RightEnd2,bool* isShorten,bool const overwrite,
									bool const Divide,Byte*& b1,Byte*& tRight,bool const isSmall,bool& b1IsFilled,bool& isZero,bool& isEnd)
{
	Byte* c1 = &RightEnd1;
	Byte const * c2 = &RightEnd2;
	while(true)
	{
		if(Byte::compare(*c1,*c2).isSmaller())
		{
			c1->setByteSubtractBorrow(*c2);
			
			Byte* d1 = c1;
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
			c1->setByteSubtract(*c2);
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
	
	//delete 0 at the left
	if(isShorten!=nullptr) *isShorten = false;
	bool isDelay = isSmall;
	isZero = false;
	if(LeftEnd1->isZero())
	{
		if(isShorten!=nullptr) *isShorten = true;
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
							Byte* const b2 = new Byte;
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

PositiveInteger* PositiveInteger::Subtract(PositiveInteger& x1,PositiveInteger const &x2,bool const overwrite)
{
	PositiveInteger* y;
	if(overwrite)
	{
		y = &x1;
	}
	else
	{
		y = x1.copy();
	}
	
	Byte* d1 = y->getLeftEnd();
	bool isShorten;
	Byte* temp1;
	bool temp2;
	PositiveInteger::SubtractAux(d1,*(y->getRightEnd()),*(x2.getRightEnd()),&isShorten,
									overwrite,false,temp1,temp1,temp2,temp2,temp2,temp2);
	d1->setLeft(nullptr);
	if(isShorten) y->setLeftEnd(d1);
	return y;
}

void PositiveInteger::MultiplyAux(Byte const& RightEnd1,Byte const& RightEnd2,Byte& tRightEnd,Byte*& b1,bool* const MultiplyIsCarried)
{
	Byte const * c1 = &RightEnd1;
	Byte const * c2 = &RightEnd2;
	Byte* tRight = &tRightEnd ;
	if(!c2->getIsLeftEnd())
	{
		while(true)
		{
			c2 = c2->getLeft();
			if(tRight->getIsLeftEnd())
			{
				//tRight->getLeft() for y does not exist
				b1->setIsLeftEnd(false);
				{
					Byte* const b2 = new Byte;
					b1->setLeft(b2);
					b2->setRight(b1);
					b1 = b2;
				}
				
				if(Byte::getBase()==2)
				{
					b1->setBytePointer(*c2);
				}
				else
				{
					//c1 must be only one byte
					Byte carry;
					Byte::MultiplyAux1(*c1,*c2,carry,*b1);
					if(!carry.isZero())
					{
						if(MultiplyIsCarried!=nullptr) *MultiplyIsCarried = true;
						Byte* const b2 = new Byte;
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
					bool AddIsCarried;
					Byte* LeftEnd;
					if(Byte::getBase() == 2)
					{
						PositiveInteger::AddAux(*tRight,*c1,true,AddIsCarried,LeftEnd);
					}
					else
					{
						PositiveInteger::AddAux(*tRight,*c1,true,AddIsCarried,LeftEnd,c2);
					}
					
					if(AddIsCarried)
					{
						if(MultiplyIsCarried!=nullptr && !b1->getLeft()->getIsLeftEnd())
						{
							*MultiplyIsCarried = true;
						}
						b1 = LeftEnd;
					}
					else
					{
						if(MultiplyIsCarried!=nullptr) *MultiplyIsCarried = false;
					}
				}
				else
				{
					//c2 = 0, and do not need to add
					//y remain unchanged
					//add one more 0 at the left end, in order to count MultiplyIsCarried
					b1->setIsLeftEnd(false);
					Byte* const b2 = new Byte;
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
}
PositiveInteger* PositiveInteger::Multiply(PositiveInteger const& x1,PositiveInteger const& x2,bool* const MultiplyIsCarried)
{
	PositiveInteger* const y = new PositiveInteger;
	Byte* b1 = new Byte;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	y->setRightEnd(b1);
	
	//////////////// copy zero of x1
	Byte const* c1 = x1.getRightEnd();
	while(true)
	{
		if(!c1->isZero()) break;
		b1->setByteZero();
		Byte* const b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c1 = c1->getLeft();
	}
	
	////////////////copy zero of x2
	Byte const* c2 = x2.getRightEnd();
	while(true)
	{
		if(!c2->isZero()) break;
		b1->setByteZero();
		Byte* const b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
		c2 = c2->getLeft();
	}
	Byte* const tRight = b1;
	
	////////////////copy x1 without zero
	PositiveInteger::copyAux(b1,*c1,c2,MultiplyIsCarried);
	b1->setIsLeftEnd(true);
	
	////////////////
	PositiveInteger::MultiplyAux(*c1,*c2,*tRight,b1,MultiplyIsCarried);
	
	b1->setLeft(nullptr);
	y->setLeftEnd(b1);
	return y;
}

void PositiveInteger::DivideAux(Byte const& x2LeftEnd,Byte const& x2RightEnd,PositiveInteger& y1,Byte*& y2LeftEnd,bool& divisible,bool* DivideIsCarried)
{
	//find tLeft
	Byte* tLeft = y2LeftEnd;
	
	//find tRight
	Byte* tRight = y2LeftEnd;
	{
		Byte const * d1 = &x2LeftEnd;
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
	}
	
	//create left end for y1
	Byte* b1 = new Byte;
	y1.setLeftEnd(b1);

	//////////////////
	bool b1IsFilled = false;
	bool isEnd = false;
	divisible = false;
	while(true)
	{
		CompareCode compareInteger;
		if(!isEnd)
		{
			//compare y1(tLeft to tRight) and x2
			{
				Byte const * d1 = tLeft;
				Byte const * d2 = &x2LeftEnd;
				while(true)
				{
					CompareCode const compareByte = Byte::compare(*d1,*d2);
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
					Byte* const b2 = new Byte;
					b2->setLeft(b1);
					b1->setRight(b2);
					b1 = b2;
				}
			}
		}
		
		//do subtraction
		if(!isEnd)
		{
			//ignore zero at the right of x2
			Byte* y2RightEnd = tRight;
			Byte const * productRightEnd = &x2RightEnd;
			while(true)
			{
				if(!productRightEnd->isZero()) break;
				y2RightEnd = y2RightEnd->getLeft();
				productRightEnd = productRightEnd->getLeft();
			}
			
			PositiveInteger* product = nullptr;
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
				}
				else
				{
					if(x2LeftEnd.getIsRightEnd())
					{
						//calculate correct Multiple
						Byte Multiple;
						if(compareInteger.isLarger())
						{
							Byte::DivideAux(nullptr,nullptr,*tLeft,nullptr,x2LeftEnd,Multiple);
						}
						else
						{
							Byte::DivideAux(nullptr,tLeft,*(tLeft->getRight()),nullptr,x2LeftEnd,Multiple);
						}
						b1->setBytePointer(Multiple);
						
						if(!Multiple.isOne())
						{
							//calculate product
							product = new PositiveInteger;
							Byte* b2 = new Byte;
							b2->setIsRightEnd(true);
							product->setRightEnd(b2);
							PositiveInteger::copyAux(b2,*productRightEnd,&Multiple);
							b2->setIsLeftEnd(true);
							product->setLeftEnd(b2);
							
							productRightEnd = product->getRightEnd();
						}
					}
					else
					{
						//calculate estimated Multiple
						Byte Multiple;
						if(compareInteger.isLarger())
						{
							Byte::DivideAux(nullptr,tLeft,*(tLeft->getRight()),&x2LeftEnd,*(x2LeftEnd.getRight()),Multiple);
						}
						else
						{
							Byte::DivideAux(tLeft,tLeft->getRight(),*(tLeft->getRight()->getRight()),
											&x2LeftEnd,*(x2LeftEnd.getRight()),Multiple);
						}
						
						//calculate correct Multiple
						if(Multiple.isOne())
						{
							b1->setByteOne();
						}
						else
						{
							//calculate estimated product
							bool isSubtractOne = false;
							product = new PositiveInteger;
							{
								Byte* b2 = new Byte;
								b2->setIsRightEnd(true);
								product->setRightEnd(b2);
								bool MultiplyIsCarried;
								PositiveInteger::copyAux(b2,*productRightEnd,&Multiple,&MultiplyIsCarried);
								b2->setIsLeftEnd(true);
								product->setLeftEnd(b2);
								
								//compare y1(tLeft to tRight) and product
								if(compareInteger.isLarger() && MultiplyIsCarried)
								{
									//y1(tLeft to tRight) are shorter than product
									Multiple.setByteSubtractOne();
									isSubtractOne = true;
								}
								else if(compareInteger.isLarger() || MultiplyIsCarried)
								{
									//the length of y1(tLeft to tRight) and product are equal
									//compareInteger.isLarger() and !MultiplyIsCarried
									//compareInteger.isSmall() and MultiplyIsCarried
									Byte const * d1 = tLeft;
									Byte const * d2 = b2;
									while(true)
									{
										CompareCode const compareByte = Byte::compare(*d1,*d2);
										if(compareByte.isLarger())
										{
											//y1(tLeft to tRight) is larger than product
											break;
										}
										else if(compareByte.isSmaller())
										{
											//y1(tLeft to tRight) is smaller than product
											Multiple.setByteSubtractOne();
											isSubtractOne = true;
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
							}
							
							if(isSubtractOne)
							{
								delete product;
								product = nullptr;
							
								//calculate corrected product
								product = new PositiveInteger;
								Byte* b2 = new Byte;
								b2->setIsRightEnd(true);
								product->setRightEnd(b2);
								PositiveInteger::copyAux(b2,*productRightEnd,&Multiple);
								b2->setIsLeftEnd(true);
								product->setLeftEnd(b2);
							}
							productRightEnd = product->getRightEnd();
						}
					}
				}
			}
			b1IsFilled = true;
			
			//Subtract
			bool isZero;
			PositiveInteger::SubtractAux(tLeft,*y2RightEnd,*productRightEnd,nullptr,true,
											true,b1,tRight,compareInteger.isSmaller(),b1IsFilled,isZero,isEnd);
			if(product!=nullptr)
			{
				delete product;
				product = nullptr;
			}
			
			if(isZero)
			{
				divisible = true;
			}
		}
		
		if(isEnd)
		{
			//right end for y1
			b1->setRight(nullptr);
			b1->setIsRightEnd(true);
			y1.setRightEnd(b1);
			
			//left end for y1
			if(y1.getLeftEnd()->isZero())
			{
				if(DivideIsCarried!=nullptr) *DivideIsCarried = false;
				//delete the additional 0 at the left end of y1
				b1 = y1.getLeftEnd()->getRight();
				delete b1->getLeft();
				y1.setLeftEnd(b1);
			}
			else
			{
				if(DivideIsCarried!=nullptr) *DivideIsCarried = true;
				b1 = y1.getLeftEnd();
			}
			b1->setLeft(nullptr);
			b1->setIsLeftEnd(true);
			
			//left end for y2
			tLeft->setLeft(nullptr);
			y2LeftEnd = tLeft;
			
			return;
		}
	}
}

void PositiveInteger::Divide(PositiveInteger& x1,PositiveInteger const& x2,PositiveInteger*& y1,PositiveInteger*& y2,bool& divisible,bool const overwrite,bool* DivideIsCarried)
{
	//y1 is quotient
	//y2 is remainder
	if(overwrite)
	{
		y2 = &x1;
	}
	else
	{
		y2 = x1.copy();
	}
	
	//find d1 and d2
	Byte* d1 = y2->getRightEnd();
	Byte* d2 = x2.getRightEnd();
	while(true)
	{
		if(!d1->isZero() || !d2->isZero()) break;
		d1 = d1->getLeft();
		d2 = d2->getLeft();
	}
	
	//reset right end
	if(d1!=y2->getRightEnd())
	{
		d1->setIsRightEnd(true);
		d2->setIsRightEnd(true);
	}
	
	//Divide
	y1 = new PositiveInteger;
	Byte* y2LeftEnd = y2->getLeftEnd();
	PositiveInteger::DivideAux(*(x2.getLeftEnd()),*d2,*y1,y2LeftEnd,divisible,DivideIsCarried);
	y2->setLeftEnd(y2LeftEnd);
	
	//recover right end
	if(d1!=y2->getRightEnd())
	{
		d1->setIsRightEnd(false);
		d2->setIsRightEnd(false);
	}
	
	//delete
	if(divisible)
	{
		delete y2;
	}
}

void PositiveInteger::printList(PositiveInteger::ListOfPositiveInteger const& list,bool const isDecimal)
{
	unsigned int const base = Byte::getBase();
	ListOfPositiveInteger const * element1 = &list;
	while(true)
	{
		if(isDecimal)
		{
			PositiveInteger const * const x = element1->Element->changeBase(10);
			x->printByte();
			delete x;
			Byte::setBase(base);
		}
		else
		{
			element1->Element->printByte();
		}
		
		if(element1->Next==nullptr) break;
		ListOfPositiveInteger const * const element2 = element1->Next;
		element1 = element2;
	}
}

void PositiveInteger::deleteList(PositiveInteger::ListOfPositiveInteger const& list)
{
	ListOfPositiveInteger const * element1 = &list;
	while(true)
	{
		delete element1->Element;
		if(element1->Next==nullptr) break;
		ListOfPositiveInteger const * const element2 = element1->Next;
		delete element1;
		element1 = element2;
	}
	delete element1;
}

PositiveInteger::ListOfPositiveInteger* PositiveInteger::findPrime(PositiveInteger const& max)
{
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* two = PositiveInteger::Add(*one,*one,false);
	PositiveInteger* i;
	
	ListOfPositiveInteger* FirstElement = new ListOfPositiveInteger;
	ListOfPositiveInteger* FinalElement;
	ListOfPositiveInteger* element1;
	ListOfPositiveInteger* element2;
	
	FirstElement->Element = two->copy();
	FinalElement = FirstElement;
	
	i = PositiveInteger::Add(*two,*one,false);
	PositiveInteger* p1;
	PositiveInteger* p2;
	bool divisible = false;
	while(true)
	{
		if(PositiveInteger::compare(*i,max).isLarger())
		{
			break;
		}
		
		element1 = FirstElement;
		while(true)
		{
			p1 = PositiveInteger::Multiply(*(element1->Element),*(element1->Element));
			if(PositiveInteger::compare(*i,*p1).isSmaller())
			{
				element2 = new ListOfPositiveInteger;
				FinalElement->Next = element2;
				element2->Element = i->copy();
				FinalElement = element2;
				delete p1;
				break;
			}
			delete p1;
			
			PositiveInteger::Divide(*i,*(element1->Element),p1,p2,divisible,false);
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
		PositiveInteger::Add(*i,*one,true);
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
	
	if(PositiveInteger::compare(*x1,*x2).isSmaller())
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
		PositiveInteger::Divide(*p1,*p2,p3,p4,divisible,false);
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
	unsigned int const base = Byte::getBase();
	Byte* b1 = new Byte;
	b1->setRight(nullptr);
	b1->setIsRightEnd(true);
	setRightEnd(b1);
	
	while(true)
	{
		b1->setByteInt(x%base);
		x = (x - b1->getByteInt())/base;
		
		if(x==0) break;
		Byte* const b2 = new Byte;
		b1->setLeft(b2);
		b2->setRight(b1);
		b1 = b2;
	}
	b1->setLeft(nullptr);
	b1->setIsLeftEnd(true);
	setLeftEnd(b1);
}

bool PositiveInteger::isComplete() const
{
	if(getRightEnd()==nullptr) {cout<<"Error Code: 1"<<endl; return false;}
	Byte const * b1 = getRightEnd();
	if(b1->getRight()!=nullptr) {cout<<"Error Code: 2"<<endl; return false;}
	if(!b1->getIsRightEnd()) {cout<<"Error Code: 3"<<endl; return false;}
	Byte const * b2;
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
bool PositiveInteger::isSame(unsigned int const x) const
{
	if(!isComplete()) {cout<<"Error Code: 12"<<endl; return false;}
	PositiveInteger const p1 = PositiveInteger(x);
	Byte const * b1 = getRightEnd();
	Byte const * b2 = p1.getRightEnd();

	while(true)
	{
		if(!Byte::compare(*b1,*b2).isEqual()) {cout<<"Error Code: 13"<<endl; return false;}
		if(b1->getIsLeftEnd()) break;
		if(b2->getIsLeftEnd()) {cout<<"Error Code: 14"<<endl; return false;}
		b1 = b1->getLeft();
		b2 = b2->getLeft();
	}
	if(!b2->getIsLeftEnd()) {cout<<"Error Code: 15"<<endl; return false;}
	
	return true;
}

bool PositiveInteger::VerifyCopy(unsigned int const max)
{
	for(unsigned int i=1;i<=max;i++)
	{
		PositiveInteger const p1 = PositiveInteger(i);
		//if(!p1.isComplete()) return false;
		//p1.printByte();
		//cout<<p1.getInt()<<endl;
		//p1.printDecimal(0);
		
		PositiveInteger const * const p2 = p1.copy();
		if(!p1.isSame(i)) return false;
		if(!p2->isSame(i)) return false;
		
		delete p2;
	}
	return true;
}

bool PositiveInteger::VerifyCounter(unsigned int const max)
{
	PositiveInteger const one = PositiveInteger(true,true);
	PositiveInteger count = PositiveInteger(true,true);
	for(unsigned int i=1;i<=max;i++)
	{
		if(!count.isSame(i)) return false;
		PositiveInteger::Add(count,one,true);
	}
	return true;
}

bool PositiveInteger::VerifyPositiveInteger(unsigned int const max)
{
	std::string s;
	for(unsigned int i=1;i<=max;i++)
	{
		s.clear();
		PositiveInteger const p1 = PositiveInteger(i);
		{
			Byte const * d1 = p1.getLeftEnd();
			while(true)
			{
				s.push_back(d1->getByteChar());
				if(d1->getIsRightEnd()) break;
				d1 = d1->getRight();
			}
		}
		//cout<<s<<endl;
		PositiveInteger const p2 = PositiveInteger(s);
		if(!p2.isSame(i)) return false;
	}
	return true;
}

bool PositiveInteger::VerifyCompare(unsigned int const max)
{
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		{
			PositiveInteger const p1 = PositiveInteger(i);
			PositiveInteger const p2 = PositiveInteger(j);
			CompareCode const code = PositiveInteger::compare(p1,p2);
			if(!p1.isSame(i)) return false;
			if(!p2.isSame(j)) return false;
			if(i==j && !code.isEqual())  return false;
			else if(i>j && !code.isLarger())  return false;
			else if(i<j && !code.isSmaller())  return false;
		}
	}
	return true;
}

bool PositiveInteger::VerifyAdd(unsigned int const max,bool const overwrite)
{
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		{
			PositiveInteger p1 = PositiveInteger(i);
			PositiveInteger* const n1 = p1.getNumberOfByte();
			PositiveInteger const p2 = PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			bool AddIsCarried;
			PositiveInteger const * const p3 = PositiveInteger::Add(p1,p2,overwrite,&AddIsCarried);
			//p3->printByte();
			if(overwrite)
			{
				if(!p1.isSame(i+j)) return false;
			}
			else
			{
				if(!p1.isSame(i)) return false;
			}
			if(!p2.isSame(j)) return false;
			if(!p3->isSame(i+j)) return false;
			
			PositiveInteger const * const n3 = p3->getNumberOfByte();
			if(!overwrite) delete p3;
			
			if(overwrite)
			{
				if(AddIsCarried)
				{
					if(!PositiveInteger::compare(*n3,*n1).isLarger()) return false;
				}
				else
				{
					if(!PositiveInteger::compare(*n3,*n1).isEqual()) return false;
				}
			}
			else
			{
				PositiveInteger const one = PositiveInteger(true,true);
				PositiveInteger* const n2 = p2.getNumberOfByte();
				if(PositiveInteger::compare(*n1,*n2).isLarger())
				{
					if(AddIsCarried) PositiveInteger::Add(*n1,one,true);
					if(!PositiveInteger::compare(*n3,*n1).isEqual()) return false;
				}
				else
				{
					if(AddIsCarried) PositiveInteger::Add(*n2,one,true);
					if(!PositiveInteger::compare(*n3,*n2).isEqual()) return false;
				}
				delete n2;
			}
			
			delete n1;
			delete n3;
			//cout<<endl;
		}
	}
	return true;
}

bool PositiveInteger::VerifySubtract(unsigned int const max,bool const overwrite)
{
	for(unsigned int i=1;i<=max;i++)
	{
		for(unsigned int j=1;j<=i-1;j++)
		{
			PositiveInteger p1 = PositiveInteger(i);
			PositiveInteger const p2 = PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			PositiveInteger const * const p3 = PositiveInteger::Subtract(p1,p2,overwrite);
			//p3->printByte();
			if(overwrite)
			{
				if(!p1.isSame(i-j)) return false;
			}
			else
			{
				if(!p1.isSame(i)) return false;
			}
			if(!p2.isSame(j)) return false;
			if(!p3->isSame(i-j)) return false;
			
			if(!overwrite) delete p3;
		}
		//cout<<endl;
	}
	return true;
}

bool PositiveInteger::VerifyMultiply(unsigned int const max)
{
	for(unsigned int i=1;i<=max;i++)
	//for(unsigned int i=14;i<=14;i++)
	{
		for(unsigned int j=1;j<=max;j++)
		//for(unsigned int j=15;j<=15;j++)
		{
			PositiveInteger const p1 = PositiveInteger(i);
			PositiveInteger const p2 = PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			bool MultiplyIsCarried;
			PositiveInteger const * const p3 = PositiveInteger::Multiply(p1,p2,&MultiplyIsCarried);
			//p3->printByte();
			
			if(!p1.isSame(i)) return false;
			if(!p2.isSame(j)) return false;
			if(!p3->isSame(i*j)) return false;
			
			PositiveInteger* const n1 = p1.getNumberOfByte();
			PositiveInteger const * const n2 = p2.getNumberOfByte();
			PositiveInteger const * const n3 = p3->getNumberOfByte();
			delete p3;
			
			PositiveInteger::Add(*n1,*n2,true);
			delete n2;
			
			if(!MultiplyIsCarried)
			{
				PositiveInteger const one = PositiveInteger(true,true);
				PositiveInteger::Subtract(*n1,one,true);
			}
			if(!PositiveInteger::compare(*n1,*n3).isEqual()) return false;
			delete n1;
			delete n3;
			//cout<<endl;
		}
	}
	return true;
}

bool PositiveInteger::VerifyDivide(unsigned int const max,bool const overwrite)
{
	for(unsigned int i=1;i<=max;i++)
	//for(unsigned int i=112;i<=112;i++)
	{
		for(unsigned int j=1;j<=i;j++)
		//for(unsigned int j=19;j<=19;j++)
		{
			PositiveInteger* const p1 = new PositiveInteger(i);
			PositiveInteger* const n1 = p1->getNumberOfByte(); //for overwrite, it will be delete
			PositiveInteger const p2 = PositiveInteger(j);
			//p1->printByte();
			//p2->printByte();
			
			PositiveInteger* p3;
			PositiveInteger* p4;
			bool divisible;
			bool DivideIsCarried;
			PositiveInteger::Divide(*p1,p2,p3,p4,divisible,overwrite,&DivideIsCarried);
			//p3->printByte();
			
			if(!overwrite)
			{
				if(!p1->isSame(i)) {cout<<"Error Code: 16"<<endl; return false;}
				delete p1;
			}
			if(!p2.isSame(j)) {cout<<"Error Code: 17"<<endl; return false;}
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
			
			PositiveInteger const * const n2 = p2.getNumberOfByte();
			PositiveInteger const * const n3 = p3->getNumberOfByte();
			delete p3;
			
			if(DivideIsCarried)
			{
				PositiveInteger one = PositiveInteger(true,true);
				PositiveInteger::Add(*n1,one,true);
				PositiveInteger::Subtract(*n1,*n2,true);
				if(!PositiveInteger::compare(*n1,*n3).isEqual()) {cout<<"Error Code: 22"<<endl; return false;}
			}
			else
			{
				PositiveInteger::Subtract(*n1,*n2,true);
				if(!PositiveInteger::compare(*n1,*n3).isEqual()) {cout<<"Error Code: 23"<<endl; return false;}
			}

			delete n1;
			delete n2;
			delete n3;
			//cout<<endl;
		}
	}
	return true;
}
