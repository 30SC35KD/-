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
	cout << "ְ����ţ� " << this->m_ID
		<< "\tְ�������� " << this->m_Name
		<< "\t��λ�� " << this->getDepartment()
		<< "\t��λְ�� ����˾��������" << endl;
}
string Boss::getDepartment()
{
	return string("�ܲ�");
}