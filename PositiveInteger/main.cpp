//
//  main.cpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include <iostream>
#include "PositiveInteger.hpp"
using namespace std;
int main()
{
	
	PositiveInteger* x1;
	PositiveInteger* x2;
	PositiveInteger* x3;
	PositiveInteger* x4;
	/*
	x1 = new PositiveInteger;
	PositiveInteger::One(x1);
	x1->printBinary();
	x2=x1->copy();
	for(int i=1;i<=10;i++)
	{
		x3 = PositiveInteger::Add(x2,x1);
		x3->printBinary();
		cout<<PositiveInteger::compare(x2, x3)<<endl;
		delete x2;
		x2=x3;
	}
	delete x1;
	delete x2;
	*/
	///*
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)
		{
			if(i==j) continue;
			x1 = new PositiveInteger(i);
			x2 = new PositiveInteger(j);
			x3 = x1->copy();
			x4 = x2->copy();
			delete x1;
			delete x2;
			//cout<<PositiveInteger::compare(x3, x4)<<" ";
			//x3 = PositiveInteger::Add(x3,x4,1);
			x1 = PositiveInteger::Subtract(x3,x4,1);
			//x1 = PositiveInteger::Multiply(x3,x4);
			x1->printBinary();
			//delete x1;
			delete x3;
			delete x4;
		}
		cout<<endl;
	}

	return 0;
}
