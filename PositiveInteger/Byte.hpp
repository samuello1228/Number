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
	//~Byte();
	
	static unsigned int getBase();
	static void setBase(unsigned int const);
	
	unsigned int getByteInt() const;
	char getByteChar() const;
	
	void setByteInt(unsigned int const);
	void setBytePointer(Byte const&);
	void setByteChar(char const);
	void setByteZero();
	void setByteOne();
	void setByteMax();
	void setByteAddOne(Byte const&);
	void setByteSubtractOne();
	void setByteSubtract(Byte const&);
	void setByteSubtractBorrow(Byte const&);
	
	Byte* getLeft() const;
	void setLeft(Byte* const);
	Byte* getRight() const;
	void setRight(Byte* const);
	
	bool getIsLeftEnd() const;
	void setIsLeftEnd(bool const);
	bool getIsRightEnd() const;
	void setIsRightEnd(bool const);
	
	bool isZero() const;
	bool isOne() const;
	bool isMax() const;
	static CompareCode compare(Byte const&,Byte const&);
	static void AddThreeByte(Byte const&,Byte const&,bool const,bool&,Byte&);
	static void MultiplyAux1(Byte const&,Byte const&,Byte&,Byte&);
	static void MultiplyAux2(Byte const&,Byte const&,Byte const&,Byte&,Byte&);
	static void MultiplyAux3(Byte const&,Byte const&,Byte const&,Byte const&,Byte&,Byte&);
	static void DivideAux(Byte*,Byte*,Byte const&,Byte*,Byte const&,Byte&);
	
private:
	static unsigned int base;
	bool bit;
	unsigned int byte;
	Byte* left;
	Byte* right;
	bool isLeftEnd;
	bool isRightEnd;
};

class CompareCode
{
public:
	CompareCode(){Equal=false;Larger=false;}
	CompareCode(bool const newEqual,bool const newLarger=false){Equal=newEqual;Larger=newLarger;}
	bool isEqual() const {return Equal;}
	bool isLarger() const {return !Equal && Larger;}
	bool isSmaller() const {return !Equal && !Larger;}
private:
	bool Equal;
	bool Larger;
};


#endif /* Byte_hpp */
