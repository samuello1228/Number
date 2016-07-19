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
#include <string>

class CompareCode;
class PositiveInteger
{
public:
	PositiveInteger();
    PositiveInteger(std::string);
	~PositiveInteger();
	
	Bit* getLeftEnd();
	void setLeftEnd(Bit*);
	Bit* getRightEnd();
	void setRightEnd(Bit*);
	
	void printBinary();
	struct Digit
	{
		char digit;
		Digit* Right=nullptr;
	};
	void printDecimal(bool);
	PositiveInteger* copy();
	static CompareCode compare(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* AddAux(Bit*,Bit*,bool,bool&,Bit*&);
	static PositiveInteger* Add(PositiveInteger*,PositiveInteger*,bool);
	static void SubtractAux(Bit*&,Bit*,Bit*,Bit*,bool&,bool,
							bool,Bit*&,Bit*&,bool,bool&,bool&);
	static PositiveInteger* Subtract(PositiveInteger*,PositiveInteger*,bool);
	static void MultiplyAux(Bit*,Bit*,Bit*,Bit*&,bool&);
	static PositiveInteger* Multiply(PositiveInteger*,PositiveInteger*,bool&);
	static void Divide(PositiveInteger*,PositiveInteger*,PositiveInteger*&,PositiveInteger*&,bool&,bool);
	PositiveInteger* getNumberOfBit();
	
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
	static bool VerifyPositiveInteger(unsigned int);
	static bool VerifyCompare(unsigned int);
	static bool VerifyAdd(unsigned int,bool);
	static bool VerifySubtract(unsigned int,bool);
	static bool VerifyMultiply(unsigned int);
	static bool VerifyDivide(unsigned int,bool);
private:
	Bit* leftEnd;
	Bit* rightEnd;
	
	static void AddThreeBit(bool,bool,bool,bool&,bool&);

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

#endif /* PositiveInteger_hpp */
