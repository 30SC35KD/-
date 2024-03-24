#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
class Manager :public Worker
{
public:
	Manager(int ID, string name, int department);
	void showInformation();
	string getDepartment();
};