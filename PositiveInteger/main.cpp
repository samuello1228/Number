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
	/*
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)
		{
			x1 = new PositiveInteger(i);
			x2 = new PositiveInteger(j);
	 
			cout<<PositiveInteger::compare(x1, x2)<<" ";
		}
		cout<<endl;
	}
	*/
	x1 = new PositiveInteger(1);
	x1->printBinary();
	
	x2 = PositiveInteger::Add(x1,x1);
	x2->printBinary();
	
	x3 = PositiveInteger::Add(x1,x2);
	x3->printBinary();
	delete x1;
	delete x2;
	delete x3;
	return 0;
}
