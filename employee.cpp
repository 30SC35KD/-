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
	cout << "ְ����ţ� " << this->m_ID
		<< "\tְ�������� " << this->m_Name
		<< "\t��λ�� " << this->getDepartment()
		<< "\t��λְ�� ��ɾ�����������";
}
string Employee::getDepartment()
{
	return string("Ա��");
}