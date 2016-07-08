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
	PositiveInteger* getNumberOfDigit();
	void setNumberOfDigit(PositiveInteger*);
	PositiveInteger* getNumberOfDigitParent();
	void setNumberOfDigitParent(PositiveInteger*);
	
	bool getIsOne();
	void setIsOne(bool);
	bool getIsTwo();
	void setIsTwo(bool);
	bool isOneOrTwo();
	
	static void One(PositiveInteger*);
	static void Two(PositiveInteger*);
	
	void printBinary();
	struct Digit
	{
		char digit;
		Digit* Right=nullptr;
	};
	void printDecimal(bool);
	PositiveInteger* copy();
	static CompareCode compare(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* Add(PositiveInteger*&,PositiveInteger*&,bool);
	static PositiveInteger* SubtractAux(Bit*&,Bit*,PositiveInteger*&,bool&,bool&,
										Bit*,Bit*,PositiveInteger*,bool,bool,
										bool,bool,Bit*&,Bit*&,bool&,PositiveInteger*&);
	static PositiveInteger* Subtract(PositiveInteger*,PositiveInteger*,bool,bool);
	static PositiveInteger* Multiply(PositiveInteger*,PositiveInteger*);
	static void Divide(PositiveInteger*,PositiveInteger*,PositiveInteger*&,PositiveInteger*&,bool&,bool,bool);

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
private:
	Bit* leftEnd;
	Bit* rightEnd;
	PositiveInteger* numberOfDigit;
	PositiveInteger* numberOfDigitParent;
	
	bool isOne;
	bool isTwo;
	
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
