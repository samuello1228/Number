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
	static void setBase(const unsigned int);
	
	unsigned int getByteInt();
	char getByteChar();
	
	void setByteInt(const unsigned int);
	void setBytePointer(const Byte&);
	void setByteChar(const char);
	void setByteZero();
	void setByteOne();
	void setByteMax();
	void setByteAddOne(const Byte&);
	void setByteSubtractOne();
	void setByteSubtract(const Byte&);
	void setByteSubtractBorrow(const Byte&);
	
	Byte* getLeft();
	void setLeft(Byte* const);
	Byte* getRight();
	void setRight(Byte* const);
	
	bool getIsLeftEnd();
	void setIsLeftEnd(const bool);
	bool getIsRightEnd();
	void setIsRightEnd(const bool);
	
	bool isZero();
	bool isOne();
	bool isMax();
	static CompareCode compare(const Byte&,const Byte&);
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
