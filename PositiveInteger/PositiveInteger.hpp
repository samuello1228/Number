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
	
	static void copyAux(Byte*&,Byte const&,Byte const * const multiple=nullptr,bool* const AddIsCarried=nullptr);
	PositiveInteger* copy() const;
	static CompareCode compare(PositiveInteger const&,PositiveInteger const&);
	static PositiveInteger* AddAux(Byte&,Byte const&,bool const,bool&,Byte*&,Byte const * const multiple=nullptr);
	static PositiveInteger* Add(PositiveInteger&,PositiveInteger const&,bool const,bool* const AddIsCarried=nullptr);
	static void SubtractAux(Byte*&,Byte&,Byte const&,bool*,bool const,
							bool const,Byte*&,Byte*&,bool const,bool&,bool&,bool&);
	static PositiveInteger* Subtract(PositiveInteger&,PositiveInteger const&,bool const);
	static void MultiplyAux(Byte const&,Byte const&,Byte&,Byte*&,bool* const MultiplyIsCarried=nullptr);
	static PositiveInteger* Multiply(PositiveInteger const&,PositiveInteger const&,bool* const MultiplyIsCarried=nullptr);
	static void DivideAux(Byte const&,Byte const&,PositiveInteger&,Byte*&,bool&,bool* DivideIsCarried=nullptr);
	static void Divide(PositiveInteger&,PositiveInteger const&,PositiveInteger*&,PositiveInteger*&,bool&,bool const,bool* DivideIsCarried=nullptr);
	
	
	struct ListOfPositiveInteger
	{
		PositiveInteger* Element;
		ListOfPositiveInteger* Next=nullptr;
	};
	static void printList(ListOfPositiveInteger const&,bool const);
	static void deleteList(ListOfPositiveInteger const&);
	static ListOfPositiveInteger* findPrime(PositiveInteger const&);
	static PositiveInteger* GCD(PositiveInteger const&,PositiveInteger const&);
	
	//verification
	PositiveInteger(unsigned int);
	bool isComplete() const;
	bool isSame(unsigned int const) const;
	
	static bool VerifyCopy(unsigned int const);
	static bool VerifyCounter(unsigned int const);
	static bool VerifyPositiveInteger(unsigned int const);
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
