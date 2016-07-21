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

bool Byte::getByte()
{
	return bit;
}
void Byte::setByte(bool newBit)
{
	bit = newBit;
}
/*
unsigned int Byte::getByte(unsigned int base)
{
	return byte;
}
void Byte::setByte(unsigned int newByte)
{
	byte = newByte;
}
*/
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