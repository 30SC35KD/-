#include<iostream>
using namespace std;
#include"employee.h"
Employee::Employee(int ID, string name, int department)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_Department = department;
}
void Employee::showInformation() 
{
	cout << "职工编号： " << this->m_ID
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位： " << this->getDepartment()
		<< "\t岗位职责： 完成经理交给的任务";
}
string Employee::getDepartment()
{
	return string("员工");
}