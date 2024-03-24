#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
class Employee :public Worker
{
public:
	Employee(int ID,string name,int department);
	void showInformation();
	string getDepartment();
};