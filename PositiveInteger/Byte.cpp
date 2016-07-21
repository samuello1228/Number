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
		
	}
}
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
bool Byte::isSame(Byte *b)
{
	if(base == 2)
	{
		return bit == b->bit;
	}
	else
	{
		return byte == b->byte;
	}
}