#include"workerManager.h"
#include<iostream>
using namespace std;
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if(!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_WorkerNum = 0;
		this->m_WorkerArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��!" << endl;
		this->m_WorkerNum = 0;
		this->m_WorkerArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
		int num = this->get_WorkerNum();
		this->m_WorkerNum = num;
		this->m_WorkerArray = new Worker * [this->m_WorkerNum];
		Init_Worker();

}
workerManager::~workerManager()
{
	if (this->m_WorkerArray != NULL)
	{
		for (int i = 0; i < this->m_WorkerNum; ++i)
		{
			if (this->m_WorkerArray[i] != NULL)
			{
				delete this->m_WorkerArray[i];
			}
		}
		delete[]this->m_WorkerArray;
		this->m_WorkerArray = NULL;
	}
}
void workerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ��  *********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void workerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void workerManager::AddWorker()
{
	cout << "���������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_WorkerNum + addNum;
		Worker**newSpace= new Worker * [newSize];
		if (this->m_WorkerArray != NULL)
		{
			for (int i = 0; i < this->m_WorkerNum; ++i)
			{
				newSpace[i] = this->m_WorkerArray[i];
			}
		}
			for(int i=0;i<addNum;++i)
			{
				int id;
				string name;
				int departmentselect;
				cout << "�������" << i + 1 << "����ְ�����" << endl;
				cin >> id;
				cout << "�������" << i + 1 << "����ְ������" << endl;
				cin >> name;
				cout << "��ѡ���ְ����λ�� " << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ܲ�" << endl;
				cin >> departmentselect;
				Worker* worker = NULL;
				switch (departmentselect)
				{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}
				newSpace[this->m_WorkerNum + i] = worker;
			}
			delete[]this->m_WorkerArray;
			this->m_WorkerArray = newSpace;
			this->m_WorkerNum = newSize;
			this->m_FileIsEmpty = false;
			this->save();
			cout << "�ɹ����" << addNum << "����ְ��" << endl;
		
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_WorkerNum; ++i)
	{
		ofs << this->m_WorkerArray[i]->m_ID << " "
			<< this->m_WorkerArray[i]->m_Name << " "
			<< this->m_WorkerArray[i]->m_Department << endl;
	}
	ofs.close();
}
int workerManager::get_WorkerNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dnum; int n = 0;
	while (ifs >> id && ifs >> name && ifs >> dnum)
	{
		n++;
	}
	return n;
}
void workerManager::Init_Worker()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dnum;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dnum)
	{
		Worker* worker = NULL;
		if (dnum == 1)
		{
			worker = new Employee(id , name, dnum);
		}
		else if (dnum == 2)
		{
			worker = new Manager(id, name, dnum);
		}
		else if (dnum == 3)
		{
			worker = new Boss(id, name, dnum);
		}
		this->m_WorkerArray[index] = worker;
		index++;
		this->m_FileIsEmpty = false;
	}
	ifs.close();
}
void workerManager::Show_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_WorkerNum; ++i)
		{
			this->m_WorkerArray[i]->showInformation();
		}
	}
	system("pause");
	system("cls");
}
void workerManager::Del_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ��ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_WorkerNum - 1; ++i)
			{
				this->m_WorkerArray[i] = this->m_WorkerArray[i + 1];
			}
			--this->m_WorkerNum;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
	}
	system("pause");
	system("cls");
}
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_WorkerNum; ++i)
	{
		if (this->m_WorkerArray[i]->m_ID == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void workerManager::Mod_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_WorkerArray[ret];
			int new_ID = 0;
			string new_Name = "";
			int new_Dn = 0;
			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> new_ID;
			cout << "������������"<<endl;
			cin >> new_Name;
			cout << "�������¸�λ:" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ܲ�" << endl;
			cin >> new_Dn;
			Worker* worker = NULL;
			switch (new_Dn)
			{
			case 1:
				worker = new Employee(new_ID, new_Name, new_Dn);
				break;
			case 2:
				worker = new Manager(new_ID, new_Name, new_Dn);
				break;
			case 3:
				worker = new Boss(new_ID, new_Name, new_Dn);
				break;
			default:
				break;
			}
			this->m_WorkerArray[ret] = worker;
			cout << "�޸ĳɹ�!" << endl;
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerManager::Find_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_WorkerArray[ret]->showInformation();
			}
			else
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else if (select == 2)
		{
			bool flag = false;
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;
			for (int i = 0; i < m_WorkerNum; ++i)
			{
				if (this->m_WorkerArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< this->m_WorkerArray[i]->m_ID
						<< "��ְ����Ϣ���£�" << endl;
					this->m_WorkerArray[i]->showInformation();
					flag = true;
				}
			}
			if (flag == false)
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
		}
		else
			cout << "����ѡ������" << endl;
	}
	system("pause");
	system("cls");
}
void workerManager::Sort_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ��������" << endl;
		cout << "2����ְ���Ž���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_WorkerNum; ++i)
		{
			int sign = i;
			{
				for (int j = i + 1; j < m_WorkerNum; ++j)
				{
				if (select == 1)
				{
					if (this->m_WorkerArray[sign]->m_ID > this->m_WorkerArray[j]->m_ID)
					{
						sign = j;
					}
				}
				else
				{
					if (this->m_WorkerArray[sign]->m_ID < this->m_WorkerArray[j]->m_ID)
					{
						sign = j;
					}
				}
				}
				if (i != sign)
				{
					Worker* temp = this->m_WorkerArray[i];
					this->m_WorkerArray[i] = this->m_WorkerArray[sign];
					this->m_WorkerArray[sign] = temp;
				}
			}
		}
		
	}
	cout << "����ɹ��������Ľ��Ϊ��" << endl;
	this->save();
	this->Show_Worker();
}
void workerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();
		if (this->m_WorkerArray != NULL)
		{
			for (int i = 0; i < this->m_WorkerNum; ++i)
			{
				delete this->m_WorkerArray[i];
				this->m_WorkerArray[i] = NULL;
			}
			delete[]this->m_WorkerArray;
			this->m_WorkerArray = NULL;
			this->m_WorkerNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�!" << endl;
	}
	system("pause");
	system("cls");
}
