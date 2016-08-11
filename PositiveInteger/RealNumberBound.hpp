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
	
	Integer* getSignificand() const;
	void setSignificand(Integer* const&);
	Integer* getExponent() const;
	void setExponent(Integer* const&);
	
	void printByte() const;
	
	//verification
	RealNumberBound(bool IsZero,bool Sign,unsigned int m,int e);
	bool isComplete();
	bool isSame(bool IsZero,bool Sign=true,unsigned int m=0,int e=0);
	
	static bool VerifyCopy(int);
	static bool VerifyRealNumberBound(int);
	
	
private:
	Integer* significand;
	//1.0100101 * 2^3
	Integer* exponent;
};

#endif /* RealNumberBound_hpp */
