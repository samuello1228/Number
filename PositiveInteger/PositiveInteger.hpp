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
	PositiveInteger(std::string&);
    PositiveInteger(const bool,const bool);
	~PositiveInteger();
	
	Byte* getLeftEnd() const;
	void setLeftEnd(Byte* const&);
	Byte* getRightEnd() const;
	void setRightEnd(Byte* const&);
	
	void printByte() const;
	struct Digit
	{
		unsigned int digit;
		Digit* Right=nullptr;
	};
	PositiveInteger* changeBase(const unsigned int base = 10) const;
	int getInt() const;
	PositiveInteger* getNumberOfByte() const;
	
	static void copyAux(Byte*&,Byte const&,Byte const * const multiple=nullptr,bool* AddIsCarried=nullptr);
	PositiveInteger* copy() const;
	static CompareCode compare(PositiveInteger const&,PositiveInteger const&);
	static PositiveInteger* AddAux(Byte*&,Byte const&,bool const,bool&,Byte*&,Byte* multiple=nullptr);
	static PositiveInteger* Add(PositiveInteger&,PositiveInteger const&,bool const,bool* AddIsCarried=nullptr);
	static void SubtractAux(Byte*&,Byte*,Byte*,bool&,bool,
							bool,Byte*&,Byte*&,bool,bool&,bool&,bool&);
	static PositiveInteger* Subtract(PositiveInteger*,PositiveInteger*,bool);
	static void MultiplyAux(Byte*,Byte*,Byte*,Byte*&,bool&);
	static PositiveInteger* Multiply(PositiveInteger*,PositiveInteger*,bool&);
	static void DivideAux(Byte*,Byte*,PositiveInteger*&,Byte*&,bool&,bool&);
	static void Divide(PositiveInteger*,PositiveInteger*,PositiveInteger*&,PositiveInteger*&,bool&,bool&,bool);
	
	
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
	bool isComplete() const;
	bool isSame(unsigned int const) const;
	
	static bool VerifyCopy(unsigned int const);
	static bool VerifyCounter(unsigned int const);
	static bool VerifyCompare(unsigned int const);
	static bool VerifyAdd(unsigned int const,bool const);
	static bool VerifySubtract(unsigned int const,bool const);
	static bool VerifyMultiply(unsigned int const);
	static bool VerifyDivide(unsigned int const,bool const);
	
private:
	Byte* leftEnd;
	Byte* rightEnd;
};

#endif /* PositiveInteger_hpp */
