//
//  Bit.cpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "Bit.hpp"

Bit::Bit()
{
	setBit(0);
	setLeft(nullptr);
	setRight(nullptr);
}

Bit::~Bit()
{
}

bool Bit::getBit()
{
	return bit;
}
void Bit::setBit(bool newBit)
{
	bit = newBit;
}

Bit* Bit::getLeft()
{
	return left;
}
void Bit::setLeft(Bit* newLeft)
{
	left = newLeft;
}

Bit* Bit::getRight()
{
	return right;
}
void Bit::setRight(Bit* newRight)
{
	right = newRight;
}

bool Bit::isLeftEnd()
{
	return left==nullptr;
}

bool Bit::isRightEnd()
{
	return right==nullptr;
}