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


struct ListElement
{
	PositiveInteger* Element;
	ListElement* Next=nullptr;
};
void findPrime()
{
	PositiveInteger* one = new PositiveInteger;
	PositiveInteger::One(one);
	PositiveInteger* two = new PositiveInteger;
	PositiveInteger::Two(two);
	PositiveInteger* i;
	PositiveInteger* iMax = new PositiveInteger(10000);
	
	ListElement* FirstElement = new ListElement;
	ListElement* FinalElement;
	ListElement* element1;
	ListElement* element2;
	
	FirstElement->Element = two->copy();
	FinalElement = FirstElement;
	
	i = PositiveInteger::Add(two,one,false);
	PositiveInteger* p1;
	PositiveInteger* p2;
	bool divisible = false;
	while(true)
	{
		if(PositiveInteger::compare(i,iMax)==1)
		{
			break;
		}
		
		element1 = FirstElement;
		while(true)
		{
			p1 = PositiveInteger::Multiply(element1->Element,element1->Element);
			if(PositiveInteger::compare(i,p1)==-1)
			{
				element2 = new ListElement;
				FinalElement->Next = element2;
				element2->Element = i->copy();
				FinalElement = element2;
				delete p1;
				break;
			}
			delete p1;
			
			PositiveInteger::Divide(i,element1->Element,p1,p2,divisible,false,false);
			delete p1;
			if(divisible)
			{
				break;
			}
			else
			{
				delete p2;
			}
			
			element1 = element1->Next;
			
		}
		PositiveInteger::Add(i,one,true);
	}
	delete i;
	delete one;
	delete two;
	delete iMax;
	
	element1 = FirstElement;
	element1->Element->printBinary();
	//element1->Element->printDecimal(true);
	while(element1->Next!=nullptr)
	{
		element2 = element1->Next;
		delete element1;
		element2->Element->printBinary();
		//element2->Element->printDecimal(true);
		element1 = element2;
	}
	delete element1;
}

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
	
	findPrime();
	
	return 0;
}
