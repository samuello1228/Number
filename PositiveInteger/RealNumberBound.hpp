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
#include <vector>

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
	struct ID
	{
		bool IsZero;
		bool Sign;
		unsigned int m;
		unsigned int RightEnd;
		int e;
	};
	RealNumberBound(RealNumberBound::ID const&);
	bool isComplete() const;
	bool isSame(RealNumberBound::ID const&) const;
	
	static bool VerifyCopy(std::vector<RealNumberBound::ID>&);
	static bool VerifyRealNumberBound(int);
	
	
private:
	Integer* significand;
	//1.0100101 * 2^3
	Integer* exponent;
};

#endif /* RealNumberBound_hpp */
