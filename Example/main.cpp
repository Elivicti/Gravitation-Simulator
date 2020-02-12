#include "multiBody.h"
#include <iostream>

using namespace std;

int main()
{
	
	cout << "-----------------------------------" << endl;
	cout << "|       MultiBody Simulator       |" << endl;
	cout << "-----------------------------------" << endl;
	int bodynum = 250;
	cout << "Input Body number: ";
	cin >> bodynum;
	multiBody a(bodynum);

	
	cout << endl << "Initializing...." << endl << endl;
	cout << "Tips:" << endl;
	cout << "Press SPACE to pause simulation" << endl;
	cout << "Press ESC to exit simulation" << endl << endl;
	int i = 6;
	while (--i)
	{
		cout << i << "s\r";
		Sleep(1000);
	}
	

	a.run();
	
	

	system("pause");
}

