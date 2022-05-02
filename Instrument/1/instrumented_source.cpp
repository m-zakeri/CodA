/*
The simplest CPP file for testing control-flow-graph extraction program
*/

#include<iostream>

#include <fstream>
std::ofstream logFile("log_file.txt");

using namespace std;

/* function number 1 */
int main()
{
logFile << "1 1" << std::endl;

	int in;
	in = 1;
	if (logFile << "1 2" << std::endl && (in > 0))
	{
logFile << "1 3" << std::endl;

	    cout << "In is not Zero!";
	}
logFile << "1 4" << std::endl;

	return 0;
}

/* function number 2 */
int f1()
{
logFile << "2 1" << std::endl;

     int i=1;
     int j=10;
     for (i=1; logFile << "2 2" << std::endl && (i<=j); i++)
     {
logFile << "2 3" << std::endl;

          print(i);
     }
logFile << "2 4" << std::endl;


    return i;
}

/* function number 3 */
int f2()
{
logFile << "3 1" << std::endl;

     int i=1;
     int j=10;
     while (logFile << "3 2" << std::endl && (i<=j))
     {
logFile << "3 3" << std::endl;

          if (logFile << "3 4" << std::endl && (!i%j))
          {
logFile << "3 5" << std::endl;

                cout << "i enumerate j";
          }
logFile << "3 6" << std::endl;

          print(i);
          i++;
     }
logFile << "3 7" << std::endl;


    return i;
}


void f3 ()
{
logFile << "4 1" << std::endl;


     if (logFile << "4 2" << std::endl && (i < j))
        {
logFile << "4 3" << std::endl;
x++;
}
     else {
logFile << "4 4" << std::endl;
if(logFile << "4 5" << std::endl && (j>10))
         {
logFile << "4 6" << std::endl;
y++;
}
logFile << "4 7" << std::endl;

}
logFile << "4 8" << std::endl;


}