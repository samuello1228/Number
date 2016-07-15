//
//  Bit.hpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef Bit_hpp
#define Bit_hpp

class Bit
{
public:
	Bit();
	~Bit();
	
	bool getBit();
	void setBit(bool);
	
	Bit* getLeft();
	void setLeft(Bit*);
	Bit* getRight();
	void setRight(Bit*);
	
	bool isLeftEnd();
	bool isRightEnd();
	
private:
	bool bit;
	Bit* left;
	Bit* right;
};

#endif /* Bit_hpp */
