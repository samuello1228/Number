//
//  Byte.cpp
//  Number
//
//  Created by Samuel Lo on 21/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include "Byte.hpp"
#include <iostream>
#include <bitset>
using namespace std;

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

void Byte::setByteChar(char newByte)
{
	if(base == 2)
	{
		if(newByte=='0') bit = 0;
		else if (newByte=='1') bit = 1;
	}
	else if(base<=10)
	{
		if(newByte=='0') byte = 0;
		else if (newByte=='1') byte = 1;
		else if (newByte=='2') byte = 2;
		else if (newByte=='3') byte = 3;
		else if (newByte=='4') byte = 4;
		else if (newByte=='5') byte = 5;
		else if (newByte=='6') byte = 6;
		else if (newByte=='7') byte = 7;
		else if (newByte=='8') byte = 8;
		else if (newByte=='9') byte = 9;
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

void Byte::setByteZero()
{
	if(base == 2)
	{
		bit = 0;
	}
	else
	{
		byte = 0;
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
void Byte::setByteMax()
{
	if(base == 2)
	{
		bit = 1;
	}
	else
	{
		byte = base-1;
	}
}

void Byte::setByteAddOne(Byte* x)
{
	//for x->byte <= base -2
	if(base == 2)
	{
		bit = 1;
	}
	else
	{
		byte = x->byte + 1;
	}
}



void Byte::setByteSubtractOne()
{
	if(base == 2)
	{
		bit = 0;
	}
	else
	{
		byte = byte - 1;
	}
}

void Byte::setByteSubtract(Byte* x)
{
	if(base == 2)
	{
		if(bit && !x->bit)
		{
			bit = 1;
		}
		else
		{
			bit = 0;
		}
	}
	else
	{
		byte = byte - x->byte;
	}
}

void Byte::setByteSubtractBorrow(Byte* x)
{
	if(base == 2)
	{
		bit = 1;
	}
	else
	{
		byte = byte + base - x->byte;
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
bool Byte::isOne()
{
	if(base == 2)
	{
		return bit;
	}
	else
	{
		return byte == 1;
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
	unsigned int y;
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
	else
	{
		y = x1->byte + x2->byte;
		if(carry1) y = y+1;
		
		y2->byte = y%base;
		y = y - y2->byte;
		if(y==0)
		{
			carry2 = false;
		}
		else
		{
			carry2 = true;
		}
	}
}
void Byte::MultiplyAux1(Byte* x2,Byte* Multiple,Byte* &carry2,Byte* &y2)
{
	unsigned int y;
	if(base == 2)
	{
		y2->bit = x2->bit;
		carry2->bit = 0;
	}
	else
	{
		y = x2->byte * Multiple->byte;
		y2->byte = y%base;
		carry2->byte = y/base;
	}
}
void Byte::MultiplyAux2(Byte* x2,Byte* Multiple,Byte* carry1,Byte* &carry2,Byte* &y2)
{
	unsigned int y;
	if(base == 2)
	{
		y2->bit = x2->bit;
		carry2->bit = 0;
	}
	else
	{
		y = x2->byte * Multiple->byte + carry1->byte;
		y2->byte = y%base;
		carry2->byte = y/base;
	}
}
void Byte::MultiplyAux3(Byte* x1,Byte* x2,Byte* Multiple,Byte* carry1,Byte* &carry2,Byte* &y2)
{
	unsigned int y;
	if(base == 2)
	{
		y2->bit = x2->bit;
		carry2->bit = 0;
	}
	else
	{
		y = x1->byte + x2->byte * Multiple->byte + carry1->byte;
		y2->byte = y%base;
		carry2->byte = y/base;
	}
}
void Byte::DivideAux(Byte* a1,Byte* a2,Byte* a3,Byte* b1,Byte* b2,Byte* &y)
{
	if(base == 2)
	{
		y->bit = 1;
	}
	else
	{
		if(a1==nullptr)
		{
			if(a2==nullptr)
			{
				y->byte = a3->byte /b2->byte;
			}
			else
			{
				if(b1==nullptr)
				{
					y->byte = (a2->byte * base + a3->byte) /b2->byte;
				}
				else
				{
					y->byte = (a2->byte * base + a3->byte) /(b1->byte * base + b2->byte);
				}
			}
		}
		else
		{
			if(base == 1<<2 || base == 1<<3 || base == 1<<4)
			{
				unsigned int p = 0;
				unsigned int q = 0;
				
				//find log(base)
				int size = 2;
				while(true)
				{
					if(base & (1<<size)) break;
					size++;
				}
				
				//find s3
				int s3 = size -1;
				while(true)
				{
					if(b1->byte & (1<<s3)) break;
					s3--;
				}
				
				//p for a2
				int s1 = s3;
				int s2 = size+1;
				while(true)
				{
					if(s1 == size-1) break;
					s1++;
					if(a2->byte & (1<<s1))
					{
						p |= (1<<s2);
					}
					s2++;
				}
				
				//p for a1
				s1 = 0;
				while(true)
				{
					if(a1->byte & (1<<s1))
					{
						p |= (1<<s2);
					}
					if(s2 == 2*size) break;
					s1++;
					s2++;
				}
				
				//p for a2
				//q for b1
				s1 = s3;
				s2 = size;
				while(true)
				{
					if(b1->byte & (1<<s1))
					{
						q |= (1<<s2);
					}
					if(a2->byte & (1<<s1))
					{
						p |= (1<<s2);
					}
					if(s1==0) break;
					s1--;
					s2--;
				}
				
				//p for a3
				//q for b2
				s1 = size -1;
				while(true)
				{
					s2--;
					if(b2->byte & (1<<s1))
					{
						q |= (1<<s2);
					}
					if(a3->byte & (1<<s1))
					{
						p |= (1<<s2);
					}
					s1--;
					if(s2==0) break;
				}
				
				y->byte = p /q;
				/*
				if(y->byte != (a1->byte * base * base + a2->byte * base + a3->byte) /(b1->byte * base + b2->byte) &&
				   y->byte -1 != (a1->byte * base * base + a2->byte * base + a3->byte) /(b1->byte * base + b2->byte))
				{
					const int size2 = 3;
					cout<<std::bitset<size2*3>(a1->byte * base * base + a2->byte * base + a3->byte)<<" "
						<<std::bitset<size2*2>(b1->byte * base + b2->byte)<<" ";
					cout<<(a1->byte * base * base + a2->byte * base + a3->byte) /(b1->byte * base + b2->byte)<<endl;
					cout<<std::bitset<size2*2+1>(p)<<" "
						<<std::bitset<size2+1>(q)<<" "<<y->byte<<endl;
					cout<<endl;
					
				}
				*/
			}
			else
			{
				y->byte = (a1->byte * base * base + a2->byte * base + a3->byte) /(b1->byte * base + b2->byte);
			}
		}
	}
}