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
	Integer(int);
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
	
	
	
private:
	bool isZero;
	bool sign;
	//true: positive
	//false: negative
	PositiveInteger* magnitude;
};


#endif /* Integer_hpp */
