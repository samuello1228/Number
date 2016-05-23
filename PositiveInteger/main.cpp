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
	PositiveInteger* x5;
	PositiveInteger* x6;
	bool divisible=0;
	
	PositiveInteger* one = new PositiveInteger;
	PositiveInteger::One(one);
	PositiveInteger* i;
	PositiveInteger* j;
	PositiveInteger* iMax = new PositiveInteger(100);
	PositiveInteger* jMax = new PositiveInteger(1);
	
	i = new PositiveInteger;
	PositiveInteger::One(i);
	while(true)
	{
		if(PositiveInteger::compare(i,iMax)==1)
		{
			break;
		}
		
		//x1 = i->copy();
		//x1->printDecimal(1);
		
		j = new PositiveInteger;
		PositiveInteger::One(j);
		while(true)
		{
			if(PositiveInteger::compare(j,jMax)==1)
			{
				break;
			}
			
			/*
			x3 = i->copy();
			x4 = j->copy();
			//cout<<PositiveInteger::compare(x3, x4)<<" ";
			x1 = PositiveInteger::Add(x3,x4,1);
			//x1->printBinary();
			//delete x1;
			x3->printBinary();
			delete x3;
			delete x4;
			*/
			
			/*
			if(PositiveInteger::compare(i,j)!=1)
			{
				PositiveInteger::Add(j,one,true);
				continue;
			}
			x3 = i->copy();
			x4 = j->copy();
			x1 = PositiveInteger::Subtract(x3,x4,1,1);
			//x1->printBinary();
			//delete x1;
			x3->printBinary();
			delete x3;
			delete x4;
			*/
			
			/*
			x3 = i->copy();
			x4 = j->copy();
			x1 = PositiveInteger::Multiply(x3,x4);
			x1->printBinary();
			delete x1;
			delete x3;
			delete x4;
			*/
			
			/*
			if(PositiveInteger::compare(i,j)==1)
			{
				PositiveInteger::Add(j,one,true);
				continue;
			}
			x3 = j->copy();
			x4 = i->copy();
			PositiveInteger::Divide(x3,x4,x5,x6,divisible,1,0);
			x5->printBinary();
			if(!divisible)
			{
				x6->printBinary();
				delete x6;
			}
			else
			{
				cout<<"0"<<endl;
			}
			cout<<endl;
			//delete x3;
			delete x4;
			delete x5;
			*/
			
			PositiveInteger::Add(j,one,true);
		}
		//cout<<endl;
		
		PositiveInteger::Add(i,one,true);
		delete j;
	}
	delete i;
	delete one;
	delete iMax;
	delete jMax;
	
	PositiveInteger* max = new PositiveInteger(97);
	PositiveInteger::ListOfPositiveInteger* list;
	list = PositiveInteger::findPrime(max);
	PositiveInteger::printList(list,0);
	PositiveInteger::deleteList(list);
	delete max;

	return 0;
}
