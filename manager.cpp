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
	cout << "ְ����ţ� " << this->m_ID
		<< "\tְ�������� " << this->m_Name
		<< "\t��λ�� " << this->getDepartment()
		<< "\t��λְ�� ����ϰ彻�������񣬲��·������Ա��"<<endl;
}
string Manager::getDepartment()
{
	return string("����");
}