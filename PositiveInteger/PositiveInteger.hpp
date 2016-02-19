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

class PositiveInteger
{
public:
	PositiveInteger();
	PositiveInteger(unsigned int);
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
	PositiveInteger* copy();
	static int compare(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* Add(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* Subtract(PositiveInteger*,PositiveInteger*);
	static PositiveInteger* Multiply(PositiveInteger*,PositiveInteger*);
	//static PositiveInteger* Divide(PositiveInteger*,PositiveInteger*);
	
private:
	Bit* leftEnd;
	Bit* rightEnd;
	PositiveInteger* numberOfDigit;
	PositiveInteger* numberOfDigitParent;
	
	bool isOne;
	bool isTwo;
	
	static void AddThreeBit(bool,bool,bool,bool&,bool&);
};

#endif /* PositiveInteger_hpp */
