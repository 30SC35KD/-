#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>
# define FILENAME "workerfile.txt"
using namespace std;
class workerManager
{
public:
	workerManager();
	void Show_Menu();
	void ExitSystem();
	~workerManager();
	int m_WorkerNum;
	Worker** m_WorkerArray;
	void AddWorker();
	void save();
	bool m_FileIsEmpty;
	int get_WorkerNum();
	void Init_Worker();
	void Show_Worker();
	void Del_Worker();
	int IsExist(int id);
	void Mod_Worker();
	void Find_Worker();
	void Sort_Worker();
	void Clean_File();
};