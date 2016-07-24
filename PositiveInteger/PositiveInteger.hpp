//
//  PositiveInteger.hpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef PositiveInteger_hpp
#define PositiveInteger_hpp

#include "Bit.hpp"
#include "Byte.hpp"
#include <string>


class PositiveInteger
{
public:
	PositiveInteger();
    PositiveInteger(bool,bool);
	~PositiveInteger();
	
	Byte* getLeftEnd();
	void setLeftEnd(Byte*);
	Byte* getRightEnd();
	void setRightEnd(Byte*);
	
	void printBinary();
	struct Digit
	{
		char digit;
		Digit* Right=nullptr;
	};
	void printDecimal(bool);
	
	static void copyAux(bool&,Byte*&,Byte*,Byte* multiple=nullptr);
	PositiveInteger* copy();
	static CompareCode compare(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* AddAux(Byte*,Byte*,bool,bool&,Byte*&,Byte* multiple=nullptr);
	static PositiveInteger* Add(PositiveInteger*,PositiveInteger*,bool);
	static void SubtractAux(Byte*&,Byte*,Byte*,bool&,bool,
							bool,Byte*&,Byte*&,bool,bool&,bool&,bool&,Byte* multiple=nullptr);
	static PositiveInteger* Subtract(PositiveInteger*,PositiveInteger*,bool);
	static void MultiplyAux(Byte*,Byte*,Byte*,Byte*&,bool&);
	static PositiveInteger* Multiply(PositiveInteger*,PositiveInteger*,bool&);
	static void Divide(PositiveInteger*,PositiveInteger*,PositiveInteger*&,PositiveInteger*&,bool&,bool);
	PositiveInteger* getNumberOfByte();
	
	struct ListOfPositiveInteger
	{
		PositiveInteger* Element;
		ListOfPositiveInteger* Next=nullptr;
	};
	static void printList(ListOfPositiveInteger*,bool);
	static void deleteList(ListOfPositiveInteger*);
	static ListOfPositiveInteger* findPrime(PositiveInteger*);
	
	static PositiveInteger* GCD(PositiveInteger*,PositiveInteger*);
	
	//verification
	PositiveInteger(unsigned int);
	bool isComplete();
	bool isSame(unsigned int);
	
	static bool VerifyCopy(unsigned int);
	static bool VerifyCounter(unsigned int);
	//static bool VerifyPositiveInteger(unsigned int);
	static bool VerifyCompare(unsigned int);
	static bool VerifyAdd(unsigned int,bool);
	static bool VerifySubtract(unsigned int,bool);
	static bool VerifyMultiply(unsigned int);
	static bool VerifyDivide(unsigned int,bool);
	
private:
	Byte* leftEnd;
	Byte* rightEnd;
};



#endif /* PositiveInteger_hpp */
