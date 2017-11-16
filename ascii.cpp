#include <iostream>
using namespace std;

int main ()
{
	for (int i = 1; i < 256; i++)
		cout << "The ASCII value is: " << i << "; the character is: " << char(i) << endl;
	return 0;
}
