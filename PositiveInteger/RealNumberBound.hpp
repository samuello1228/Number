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
	PositiveInteger* getMagnitude();
	void setMagnitude(PositiveInteger*);
	Integer* getExponent();
	void setExponent(Integer*);
	
private:
	bool isZero;
	bool sign;
	//true: positive
	//false: negative
	PositiveInteger* magnitude;
	//1.0100101 * 2^3
	Integer* exponent;
};

#endif /* RealNumberBound_hpp */
