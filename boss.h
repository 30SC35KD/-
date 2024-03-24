#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
class Boss :public Worker
{
public:
	Boss(int ID, string name, int department);
	void showInformation();
	string getDepartment();
};