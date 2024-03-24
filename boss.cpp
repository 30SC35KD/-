#include<iostream>
#include"boss.h"
using namespace std;
Boss::Boss(int ID, string name, int department)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_Department = department;
}
void Boss::showInformation()
{
	cout << "职工编号： " << this->m_ID
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位： " << this->getDepartment()
		<< "\t岗位职责： 管理公司所有事务" << endl;
}
string Boss::getDepartment()
{
	return string("总裁");
}