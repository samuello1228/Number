//
//  Byte.hpp
//  Number
//
//  Created by Samuel Lo on 21/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef Byte_hpp
#define Byte_hpp

class CompareCode;
class Byte
{
public:
	Byte();
	~Byte();
	
	static unsigned int getBase();
	static void setBase(unsigned int);
	
	unsigned int getByteInt();
	char getByteChar();
	
	void setByteInt(unsigned int);
	void setBytePointer(Byte*);
	void setByteChar(char);
	void setByteZero();
	void setByteOne();
	void setByteMax();
	void setByteAddOne(Byte*);
	void setByteSubtractOne();
	void setByteSubtract(Byte*);
	void setByteSubtractBorrow(Byte*);
	
	Byte* getLeft();
	void setLeft(Byte*);
	Byte* getRight();
	void setRight(Byte*);
	
	bool getIsLeftEnd();
	void setIsLeftEnd(bool);
	bool getIsRightEnd();
	void setIsRightEnd(bool);
	
	bool isZero();
	bool isOne();
	bool isMax();
	static CompareCode compare(Byte*,Byte*);
	static void AddThreeByte(Byte*,Byte*,bool,bool&,Byte*&);
	static void MultiplyAux1(Byte*,Byte*,Byte*&,Byte*&);
	static void MultiplyAux2(Byte*,Byte*,Byte*,Byte*&,Byte*&);
	static void MultiplyAux3(Byte*,Byte*,Byte*,Byte*,Byte*&,Byte*&);
	static void DivideAux(Byte*,Byte*,Byte*,Byte*,Byte*,Byte*&);
	
private:
	static unsigned int base;
	bool bit;
	unsigned int byte;
	Byte* left;
	Byte* right;
	bool leftEnd;
	bool rightEnd;
};

class CompareCode
{
public:
	CompareCode(){Equal=false;Larger=false;}
	CompareCode(bool newEqual, bool newLarger=false){Equal=newEqual;Larger=newLarger;}
	bool isEqual(){return Equal;}
	bool isLarger(){return !Equal && Larger;}
	bool isSmaller(){return !Equal && !Larger;}
private:
	bool Equal;
	bool Larger;
};


#endif /* Byte_hpp */
