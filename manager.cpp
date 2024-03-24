#include<iostream>
#include"manager.h"
using namespace std;
Manager::Manager(int ID, string name, int department) 
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_Department = department;
}
void Manager::showInformation()
{
	cout << "职工编号： " << this->m_ID
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位： " << this->getDepartment()
		<< "\t岗位职责： 完成老板交给的任务，并下发任务给员工"<<endl;
}
string Manager::getDepartment()
{
	return string("经理");
}