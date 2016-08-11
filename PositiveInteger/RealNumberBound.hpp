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
	RealNumberBound(std::string&,std::string&);
	~RealNumberBound();
	
	Integer* getSignificand() const;
	void setSignificand(Integer* const&);
	Integer* getExponent() const;
	void setExponent(Integer* const&);
	
	void printByte() const;
	
	//verification
	RealNumberBound(bool const IsZero,bool const Sign,unsigned int const m,int const e);
	bool isComplete() const;
	bool isSame(bool const IsZero,bool const Sign=true,unsigned int const m=0,int const e=0) const;
	
	static bool VerifyCopy(int const);
	static bool VerifyRealNumberBound(int);
	
	
private:
	Integer* significand;
	//1.0100101 * 2^3
	Integer* exponent;
};

#endif /* RealNumberBound_hpp */
