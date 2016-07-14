//
//  RealNumberBound.hpp
//  Number
//
//  Created by Samuel Lo on 12/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef RealNumberBound_hpp
#define RealNumberBound_hpp

#include "Integer.hpp"
class RealNumberBound
{
public:
	RealNumberBound();
	RealNumberBound(std::string,std::string);
	~RealNumberBound();
	
	bool getIsZero();
	void setIsZero(bool);
	bool getSign();
	void setSign(bool);
	Bit* getLeftEnd();
	void setLeftEnd(Bit*);
	Bit* getRightEnd();
	void setRightEnd(Bit*);
	Integer* getExponent();
	void setExponent(Integer*);
	
	void printBinary();
	
	//verification
	RealNumberBound(bool isZero,bool sign=true,unsigned int m=0,int e=0);
	bool isComplete();
	bool isSame(double);
	
	static bool VerifyRealNumberBound(int);
	
	
private:
	bool isZero;
	bool sign;
	//true: positive
	//false: negative
	Bit* leftEnd;
	Bit* rightEnd;
	//1.0100101 * 2^3
	Integer* exponent;
};

#endif /* RealNumberBound_hpp */
