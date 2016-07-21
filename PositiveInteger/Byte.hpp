//
//  Byte.hpp
//  Number
//
//  Created by Samuel Lo on 21/7/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#ifndef Byte_hpp
#define Byte_hpp

class Byte
{
public:
	Byte();
	~Byte();
	
	static unsigned int getBase();
	static void setBase(unsigned int);
	
	bool getByte();
	void setByte(bool);
	
	//unsigned int getByte(unsigned int base);
	//void setByte(unsigned int);
	
	Byte* getLeft();
	void setLeft(Byte*);
	Byte* getRight();
	void setRight(Byte*);
	
	bool getIsLeftEnd();
	void setIsLeftEnd(bool);
	bool getIsRightEnd();
	void setIsRightEnd(bool);
	
private:
	static unsigned int base;
	bool bit;
	unsigned int byte;
	Byte* left;
	Byte* right;
	bool leftEnd;
	bool rightEnd;
};


#endif /* Byte_hpp */
