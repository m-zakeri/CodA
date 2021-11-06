/*
The simplest CPP file for testing control-flow-graph extraction program
*/

#include<iostream>
using namespace std;

/* function number 1 */
int main()
{
	int in;
	in = 1;
	if (in > 0)
	{
	    cout << "In is not Zero!";
	}
	return 0;
}

/* function number 2 */
int f1()
{
     int i=1;
     int j=10;
     for (i=1; i<=j; i++)
     {
          print(i);
     }

    return i;
}

/* function number 3 */
int f2()
{
     int i=1;
     int j=10;
     while (i<=j)
     {
          if (!i%j)
          {
                cout << "i enumerate j";
          }
          print(i);
          i++;
     }

    return i;
}