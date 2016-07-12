//
//  Integer.hpp
//  Number
//
//  Created by Samuel Lo on 26/5/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef Integer_hpp
#define Integer_hpp

#include "PositiveInteger.hpp"

class Integer
{
public:
	Integer();
    Integer(std::string);
	~Integer();
	bool getIsZero();
	void setIsZero(bool);
	bool getSign();
	void setSign(bool);
	PositiveInteger* getMagnitude();
	void setMagnitude(PositiveInteger*);
	
	static void One(Integer*);
	
	void printBinary();
	void printDecimal(bool);
	Integer* copy();
	static CompareCode compare(Integer*,Integer*);
	static Integer* Add(Integer*&,Integer*&,bool);
	Integer* Negation(bool);
	static Integer* Subtract(Integer*&,Integer*&,bool);
	static Integer* Multiply(Integer*,Integer*);
	
	//verification
	Integer(int);
	bool isComplete();
	bool isSame(int);
	
	static bool VerifyCopy(int);
	static bool VerifyInteger(int);
	static bool VerifyCompare(int);
	static bool VerifyAdd(int,bool);
	static bool VerifyNegation(int,bool);
	static bool VerifySubtract(int,bool);
	static bool VerifyMultiply(int);
	
	
private:
	bool isZero;
	bool sign;
	//true: positive
	//false: negative
	PositiveInteger* magnitude;
};


#endif /* Integer_hpp */
