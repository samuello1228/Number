//
//  Byte.cpp
//  Number
//
//  Created by Samuel Lo on 21/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "Byte.hpp"

unsigned int Byte::base = 2;

Byte::Byte()
{
	setIsLeftEnd(false);
	setIsRightEnd(false);
}

Byte::~Byte()
{
}

unsigned int Byte::getBase()
{
	return base;
}

void Byte::setBase(unsigned int newBase)
{
	base = newBase;
}

//getByte
bool Byte::getByte()
{
	return bit;
}
char Byte::getByteChar()
{
	if(base == 2)
	{
		if(bit) return '1';
		else return '0';
	}
	else
	{
		if(byte==0)
		{
			return '0';
		}
		else if(byte==1)
		{
			return '1';
		}
		else if(byte==2)
		{
			return '2';
		}
		else if(byte==3)
		{
			return '3';
		}
		else if(byte==4)
		{
			return '4';
		}
		else if(byte==5)
		{
			return '5';
		}
		else if(byte==6)
		{
			return '6';
		}
		else if(byte==7)
		{
			return '7';
		}
		else if(byte==8)
		{
			return '8';
		}
		else if(byte==9)
		{
			return '9';
		}
	}
	
	return '0';
}
unsigned int Byte::getByteInt()
{
	if(base == 2)
	{
		return bit;
	}
	else
	{
		return byte;
	}
}
//setByte
void Byte::setByte(bool newBit)
{
	bit = newBit;
}
void Byte::setByteInt(unsigned int x)
{
	if(base == 2)
	{
		if(x==0)
		{
			bit = 0;
		}
		else
		{
			bit = 1;
		}
	}
	else
	{
		byte = x;
	}
}
/*
void Byte::setByteChar(char newByte)
{
	if(base == 2)
	{
		if(newByte=='0') bit = 0;
		else if (newByte=='1') bit = 1;
	}
	else
	{
		
	}
}
*/
void Byte::setBytePointer(Byte* newByte)
{
	if(base == 2)
	{
		bit = newByte->bit;
	}
	else
	{
		byte = newByte->byte;
	}
}

void Byte::setByteOne()
{
	if(base == 2)
	{
		bit = 1;
	}
	else
	{
		byte = 1;
	}
}



Byte* Byte::getLeft()
{
	return left;
}
void Byte::setLeft(Byte* newLeft)
{
	left = newLeft;
}

Byte* Byte::getRight()
{
	return right;
}
void Byte::setRight(Byte* newRight)
{
	right = newRight;
}

bool Byte::getIsLeftEnd()
{
	return leftEnd;
}

void Byte::setIsLeftEnd(bool newIsLeftEnd)
{
	leftEnd = newIsLeftEnd;
}

bool Byte::getIsRightEnd()
{
	return rightEnd;
}
void Byte::setIsRightEnd(bool newIsRightEnd)
{
	rightEnd = newIsRightEnd;
}

bool Byte::isZero()
{
	if(base == 2)
	{
		return !bit;
	}
	else
	{
		return byte == 0;
	}
}
bool Byte::isMax()
{
	if(base == 2)
	{
		return bit;
	}
	else
	{
		return byte == base-1;
	}
}
CompareCode Byte::compare(Byte* b1, Byte* b2)
{
	if(base == 2)
	{
		if(b1->bit == b2->bit)
		{
			return CompareCode(true);
		}
		else if(b1->bit)
		{
			return CompareCode(false,true);
		}
		else
		{
			return CompareCode(false,false);
		}
	}
	else
	{
		if(b1->byte == b2->byte)
		{
			return CompareCode(true);
		}
		else if(b1->byte > b2->byte)
		{
			return CompareCode(false,true);
		}
		else
		{
			return CompareCode(false,false);
		}
	}
}

void Byte::AddThreeByte(Byte* x1,Byte* x2,bool carry1,bool &carry2,Byte* &y2)
{
	if(base == 2)
	{
		if(!x1->bit)
		{
			if(!x2->bit)
			{
				if(!carry1)
				{
					//000
					carry2=0;
					y2->bit = 0;
				}
				else
				{
					//001
					carry2=0;
					y2->bit = 1;
				}
			}
			else
			{
				if(!carry1)
				{
					//010
					carry2=0;
					y2->bit = 1;
				}
				else
				{
					//011
					carry2=1;
					y2->bit = 0;
				}
			}
		}
		else
		{
			if(!x2->bit)
			{
				if(!carry1)
				{
					//100
					carry2=0;
					y2->bit = 1;
				}
				else
				{
					//101
					carry2=1;
					y2->bit = 0;
				}
			}
			else
			{
				if(!carry1)
				{
					//110
					carry2=1;
					y2->bit = 0;
				}
				else
				{
					//111
					carry2=1;
					y2->bit = 1;
				}
			}
		}
	}
}