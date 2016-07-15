//
//  main.cpp
//  PositiveInteger
//
//  Created by Samuel Lo on 18/2/2016.
//  Copyright © 2016年 Samuel Lo. All rights reserved.
//

#include <iostream>
#include "RealNumberBound.hpp"
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
	/*
	PositiveInteger* one = new PositiveInteger("1");
	PositiveInteger* i;
	PositiveInteger* j;
	PositiveInteger* iMax = new PositiveInteger("1000000000");
	PositiveInteger* jMax = new PositiveInteger("1000000000");
	
	i = new PositiveInteger("1");
	//while(true)
	while(false)
	{
		if(PositiveInteger::compare(i,iMax).isEqual())
		{
			break;
		}
		
		//x1 = i->copy();
		//x1->printBinary();
		//delete x1;
		
		j = new PositiveInteger("1");
		while(true)
		{
			if(PositiveInteger::compare(j,jMax).isEqual())
			{
				break;
			}
	*/
			/*
			x3 = i->copy();
			x4 = j->copy();
			//cout<<PositiveInteger::compare(x3, x4)<<" ";
			x1 = PositiveInteger::Add(x3,x4,0);
			//x1->printBinary();
			delete x1;
			//x3->printBinary();
			delete x3;
			delete x4;
			*/
			
			/*
			if(!PositiveInteger::compare(i,j).isLarger())
			{
				PositiveInteger::Add(j,one,true);
				continue;
			}
			x3 = i->copy();
			x4 = j->copy();
			x1 = PositiveInteger::Subtract(x3,x4,1,false);
			//x1->printBinary();
			//delete x1;
			//x3->printBinary();
			delete x3;
			delete x4;
			*/
			
			/*
			x3 = i->copy();
			x4 = j->copy();
			x1 = PositiveInteger::Multiply(x3,x4);
			//x1->printBinary();
			delete x1;
			delete x3;
			delete x4;
			*/
			
			/*
			if(PositiveInteger::compare(i,j).isLarger())
			{
				PositiveInteger::Add(j,one,true);
				continue;
			}
			x3 = j->copy();
			x4 = i->copy();
			PositiveInteger::Divide(x3,x4,x5,x6,divisible,1,0);
			//x5->printBinary();
			if(!divisible)
			{
				//x6->printBinary();
				delete x6;
			}
			else
			{
				//cout<<"0"<<endl;
			}
			//cout<<endl;
			//delete x3;
			delete x4;
			delete x5;
			*/
			
			/*
			x3 = i->copy();
			x4 = j->copy();
			//x3 = new PositiveInteger(60);
			//x4 = new PositiveInteger(72);
			x1 = PositiveInteger::GCD(x3,x4);
			x1->printBinary();
			delete x1;
			delete x3;
			delete x4;
			*/
	/*
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
	*/
	if(!PositiveInteger::VerifyCopy(100)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyCounter(100)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyPositiveInteger(100)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyCompare(100)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyAdd(100,0)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifySubtract(100,0)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyMultiply(100)) cout<<"Error"<<endl;
	//if(!PositiveInteger::VerifyDivide(100,0)) cout<<"Error"<<endl;
	else cout<<"OK"<<endl;
	
	/*
	PositiveInteger* max = new PositiveInteger(97);
	PositiveInteger::ListOfPositiveInteger* list;
	list = PositiveInteger::findPrime(max);
	PositiveInteger::printList(list,0);
	PositiveInteger::deleteList(list);
	delete max;
	*/
	
	/*
	x1 = new PositiveInteger("1001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100");
	//x1->printBinary();
	x1->printDecimal(false);
	x2 = PositiveInteger::Multiply(x1,x1);
	x2->printDecimal(false);
	//x2->printBinary();
	delete x1;
	delete x2;
	*/
	
	/*
	Integer* a1;
	Integer* a2;
	
	a1 = new Integer("-1010");
	a2 = a1->copy();
	delete a1;
	a2->printBinary();
	delete a2;
	*/
	
	//if(!Integer::VerifyCopy(100)) cout<<"Error"<<endl;
	//if(!Integer::VerifyInteger(100)) cout<<"Error"<<endl;
	//if(!Integer::VerifyCompare(100)) cout<<"Error"<<endl;
	//if(!Integer::VerifyAdd(100,0)) cout<<"Error"<<endl;
	//if(!Integer::VerifyNegation(100,0)) cout<<"Error"<<endl;
	//if(!Integer::VerifySubtract(100,0)) cout<<"Error"<<endl;
	//if(!Integer::VerifyMultiply(100)) cout<<"Error"<<endl;
	//else cout<<"OK"<<endl;
	
	/*
	RealNumberBound* a1;
	RealNumberBound* a2;

	a1 = new RealNumberBound("-1001","0");
	a1->printBinary();
	//a2 = a1->copy();
	delete a1;
	//a2->printBinary();
	//delete a2;
	*/
	
	//if(!RealNumberBound::VerifyCopy(5)) cout<<"Error"<<endl;
	//else cout<<"OK"<<endl;

	return 0;
}
