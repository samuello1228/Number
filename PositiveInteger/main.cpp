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
	Byte::setBase(2);
	//Byte::setBase(1<<15);
	
	
	PositiveInteger* one = new PositiveInteger(true,true);
	PositiveInteger* i = new PositiveInteger(true,true);
	PositiveInteger* iMax = new PositiveInteger(1024);
	PositiveInteger* jMax = new PositiveInteger(1024);
	//PositiveInteger* iMax = new PositiveInteger(1);
	//PositiveInteger* jMax = new PositiveInteger(1);
	
	while(1)
	{
		if(PositiveInteger::compare(*i,*iMax).isLarger()) break;
		
		/*
		PositiveInteger* x1 = i->copy();
		x1->printByte();
		//x1->printDecimal(0);
		delete x1;
		*/
		
		PositiveInteger* j = new PositiveInteger(true,true);
		while(true)
		{
			if(PositiveInteger::compare(*j,*jMax).isLarger()) break;
			
			/*
			PositiveInteger* x1 = i->copy();
			PositiveInteger* x2 = j->copy();
			PositiveInteger* x3 = PositiveInteger::Add(*x1,*x2,0);
			//x3->printByte();
			delete x3;
			delete x1;
			delete x2;
			*/
			
			/*
			if(!PositiveInteger::compare(*i,*j).isLarger())
			{
				PositiveInteger::Add(*j,*one,true);
				continue;
			}
			PositiveInteger* x1 = i->copy();
			PositiveInteger* x2 = j->copy();
			PositiveInteger* x3 = PositiveInteger::Subtract(*x1,*x2,1);
			//x3->printByte();
			//delete x3;
			//x1->printByte();
			delete x1;
			delete x2;
			*/
			
			/*
			PositiveInteger* x1 = i->copy();
			PositiveInteger* x2 = j->copy();
			PositiveInteger* x3 = PositiveInteger::Multiply(*x1,*x2);
			//x3->printByte();
			delete x3;
			delete x1;
			delete x2;
			*/
			
			/*
			if(PositiveInteger::compare(*i,*j).isLarger())
			{
				PositiveInteger::Add(*j,*one,true);
				continue;
			}
			PositiveInteger* x1 = j->copy();
			PositiveInteger* x2 = i->copy();
			PositiveInteger* x3;
			PositiveInteger* x4;
			bool divisible;
			PositiveInteger::Divide(*x1,*x2,x3,x4,divisible,1);
			//x3->printByte();
			if(!divisible)
			{
				//x4->printByte();
				delete x4;
			}
			else
			{
				//cout<<"0"<<endl;
			}
			//cout<<endl;
			//delete x1;
			delete x2;
			delete x3;
			*/
			
			/*
			//PositiveInteger* x1 = i->copy();
			//PositiveInteger* x2 = j->copy();
			PositiveInteger* x1 = new PositiveInteger(60);
			PositiveInteger* x2 = new PositiveInteger(72);
			PositiveInteger* x3 = PositiveInteger::GCD(*x1,*x2);
			x3->printByte();
			delete x1;
			delete x2;
			delete x3;
			*/
	
			PositiveInteger::Add(*j,*one,true);
		}
		//cout<<endl;
		
		PositiveInteger::Add(*i,*one,true);
		delete j;
	}
	delete one;
	delete i;
	delete iMax;
	delete jMax;
	
	/*
	if(!PositiveInteger::VerifyCopy(100)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyCounter(100)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyPositiveInteger(100)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyCompare(100)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyAdd(100,0)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyAdd(100,1)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifySubtract(100,0)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifySubtract(100,1)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyMultiply(100)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyDivide(100,0)) cout<<"Error"<<endl;
	if(!PositiveInteger::VerifyDivide(100,1)) cout<<"Error"<<endl;
	else cout<<"OK"<<endl;
	*/

	/*
	PositiveInteger max = PositiveInteger(300000);
	PositiveInteger::ListOfPositiveInteger* list;
	list = PositiveInteger::findPrime(max);
	cout<<"done"<<endl;
	PositiveInteger::printList(*list,1);
	PositiveInteger::deleteList(*list);
	*/
	
	/*
	Byte::setBase(2);
	//std::string s = "1100";
	std::string s = "1001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100100100100100100100100100100100010010010010010001001001001001000100100100100100010010010010010001001001001001001001001001001001001001001001001001001000100100100100100010010010010010001001001001001000100100100100100010010010010010010010010010010010010010010010010010010001001001001001000100100100100100010010010010010001001001001001000100100100100100100100100";
	PositiveInteger* x1 = new PositiveInteger(s);
	//x1->printByte();
	*/
	
	/*
	PositiveInteger* x2 = x1->changeBase(10);
	delete x1;
	x2->printByte();
	PositiveInteger* x3 = PositiveInteger::Multiply(*x2,*x2);
	x3->printByte();
	delete x2;
	delete x3;
	*/
	
	/*
	PositiveInteger* x2 = PositiveInteger::Multiply(*x1,*x1);
	delete x1;
	x2->printByte();
	PositiveInteger* x3 = x2->changeBase(10);
	delete x2;
	x3->printByte();
	delete x3;
	*/

	
	/*
	Byte::setBase(10);
	std::string s = "550355333196469699007668540372996656652001725795089711020857270140536832226385128849721914232048505780873339012174068736196998737318961089380229235583380332186150045036418038281225786006458527065973703641624254961880412599000886452254732457164364245996892020787908701088579818604183694225191506352932938214980738887009160300445802200541942344248261649318074271823639766695618102759047119763501976110029951483261535748214356749889754369478741250913641573855951503755944652181166900766203589073543909579374046888090231756124945218488427523838904577772865051820105277059530979692089507578355871214255383378020644";
	PositiveInteger* x1 = new PositiveInteger(s);
	//x1->printByte();
	PositiveInteger* x2 = x1->changeBase(2);
	delete x1;
	x2->printByte();
	PositiveInteger* x3 = PositiveInteger::Multiply(*x2,*x2);
	x3->printByte();
	delete x2;
	delete x3;
	*/

	/*
	Integer* a1;
	Integer* a2;
	
	a1 = new Integer("-1010");
	a2 = a1->copy();
	delete a1;
	a2->printByte();
	delete a2;
	*/
	
	/*
	if(!Integer::VerifyCopy(100)) cout<<"Error"<<endl;
	if(!Integer::VerifyInteger(100)) cout<<"Error"<<endl;
	if(!Integer::VerifyCompare(100)) cout<<"Error"<<endl;
	if(!Integer::VerifyAdd(100,0)) cout<<"Error"<<endl;
	if(!Integer::VerifyAdd(100,1)) cout<<"Error"<<endl;
	if(!Integer::VerifyNegation(100,0)) cout<<"Error"<<endl;
	if(!Integer::VerifyNegation(100,1)) cout<<"Error"<<endl;
	if(!Integer::VerifySubtract(100,0)) cout<<"Error"<<endl;
	if(!Integer::VerifySubtract(100,1)) cout<<"Error"<<endl;
	if(!Integer::VerifyMultiply(100)) cout<<"Error"<<endl;
	else cout<<"OK"<<endl;
	*/
	
	/*
	RealNumberBound* a1;
	RealNumberBound* a2;

	a1 = new RealNumberBound("-101","0");
	a1->printByte();
	//a2 = a1->copy();
	delete a1;
	//a2->printByte();
	//delete a2;
	*/
	
	if(!RealNumberBound::VerifyCopy(2)) cout<<"Error"<<endl;
	else cout<<"OK"<<endl;

	return 0;
}
