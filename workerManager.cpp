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
		//cout << "文件不存在" << endl;
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
		//cout << "文件为空!" << endl;
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
	cout << "*********  欢迎使用职工管理系统！  *********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void workerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void workerManager::AddWorker()
{
	cout << "请输入添加职工的数量" << endl;
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
				cout << "请输入第" << i + 1 << "个新职工编号" << endl;
				cin >> id;
				cout << "请输入第" << i + 1 << "个新职工名字" << endl;
				cin >> name;
				cout << "请选择该职工岗位： " << endl;
				cout << "1.普通职工" << endl;
				cout << "2.经理" << endl;
				cout << "3.总裁" << endl;
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
			cout << "成功添加" << addNum << "名新职工" << endl;
		
	}
	else
	{
		cout << "数据有误" << endl;
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
		cout << "文件不存在或记录为空" << endl;
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
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除职工的编号：" << endl;
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
			cout << "删除成功！" << endl;
		}
		else
			cout << "删除失败，未找到该职工" << endl;
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
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_WorkerArray[ret];
			int new_ID = 0;
			string new_Name = "";
			int new_Dn = 0;
			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> new_ID;
			cout << "请输入新姓名"<<endl;
			cin >> new_Name;
			cout << "请输入新岗位:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.总裁" << endl;
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
			cout << "修改成功!" << endl;
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerManager::Find_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_WorkerArray[ret]->showInformation();
			}
			else
				cout << "查找失败，查无此人" << endl;
		}
		else if (select == 2)
		{
			bool flag = false;
			string name;
			cout << "请输入查找的姓名" << endl;
			cin >> name;
			for (int i = 0; i < m_WorkerNum; ++i)
			{
				if (this->m_WorkerArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为："
						<< this->m_WorkerArray[i]->m_ID
						<< "号职工信息如下：" << endl;
					this->m_WorkerArray[i]->showInformation();
					flag = true;
				}
			}
			if (flag == false)
				cout << "查找失败，查无此人！" << endl;
		}
		else
			cout << "输入选项有误" << endl;
	}
	system("pause");
	system("cls");
}
void workerManager::Sort_Worker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号升序" << endl;
		cout << "2、按职工号降序" << endl;
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
	cout << "排序成功，排序后的结果为：" << endl;
	this->save();
	this->Show_Worker();
}
void workerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
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
		cout << "清空成功!" << endl;
	}
	system("pause");
	system("cls");
}
