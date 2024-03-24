#include<iostream>
#include"workerManager.h"
using namespace std;
int main()
{
	workerManager wm;
	int choice = 0;
	wm.Show_Menu();
	while (true)
	{
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.AddWorker();
			break;
		case 2:
			wm.Show_Worker();
			break;
		case 3:
			wm.Del_Worker();
			break;
		case 4:
			wm.Mod_Worker();
			break;
		case 5:
			wm.Find_Worker();
			break;
		case 6:
			wm.Sort_Worker();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls");
		}
	}
	
	system("pause");
	return 0;
}