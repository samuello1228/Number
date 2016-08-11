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
    Integer(std::string&);
	~Integer();
	bool getIsZero() const;
	void setIsZero(bool const);
	bool getSign() const;
	void setSign(bool const);
	PositiveInteger* getMagnitude() const;
	void setMagnitude(PositiveInteger* const&);
	
	void printByte() const;
	void printDecimal(bool);
	Integer* copy() const;
	static CompareCode compare(Integer*,Integer*);
	static Integer* Add(Integer*&,Integer*&,bool);
	Integer* Negation(bool);
	static Integer* Subtract(Integer*&,Integer*&,bool);
	static Integer* Multiply(Integer*,Integer*);
	
	//verification
	Integer(int const);
	bool isComplete() const;
	bool isSame(int const) const;
	
	static bool VerifyCopy(int const);
	static bool VerifyInteger(int const);
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
