#pragma once
#include<iostream>
#include<string>
using namespace std;
class Worker
{
public:
	int m_ID;
	string m_Name;
	int m_Department;
	virtual void showInformation() {};
	virtual string getDepartment() =0;
};