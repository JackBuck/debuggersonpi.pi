#include <iostream>
using namespace std;

inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

int TestExample()
{
	cout << "Hello world! \n";
	keep_window_open();

	return 0;
}
