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
	
	unsigned int getByteInt() const;
	char getByteChar() const;
	
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
	
	Byte* getLeft() const;
	void setLeft(Byte* const);
	Byte* getRight() const;
	void setRight(Byte* const);
	
	bool getIsLeftEnd() const;
	void setIsLeftEnd(const bool);
	bool getIsRightEnd() const;
	void setIsRightEnd(const bool);
	
	bool isZero() const;
	bool isOne() const;
	bool isMax() const;
	static CompareCode compare(const Byte&,const Byte&);
	static void AddThreeByte(const Byte&,const Byte&,const bool,bool&,Byte&);
	static void MultiplyAux1(const Byte&,const Byte&,Byte&,Byte&);
	static void MultiplyAux2(const Byte&,const Byte&,const Byte&,Byte&,Byte&);
	static void MultiplyAux3(const Byte&,const Byte&,const Byte&,const Byte&,Byte&,Byte&);
	static void DivideAux(Byte*,Byte*,const Byte&,Byte*,const Byte&,Byte&);
	
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
	CompareCode(const bool newEqual,const bool newLarger=false){Equal=newEqual;Larger=newLarger;}
	bool isEqual() const {return Equal;}
	bool isLarger() const {return !Equal && Larger;}
	bool isSmaller() const {return !Equal && !Larger;}
private:
	bool Equal;
	bool Larger;
};


#endif /* Byte_hpp */
