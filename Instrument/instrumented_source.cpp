//in the name of allah
#include<iostream>

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

using namespace std;

int main()
{
logFile << "main1" << std::endl;
	int x = 0 , y =100;
	for( y = x + 1 ; x < y ; y = ++x + 1)
		{
logFile << "main2" << std::endl;
if ( y == 0 )
			{
logFile << "main3" << std::endl;
break;
}
		else {
logFile << "main4" << std::endl;
if ( y < 0 )
		{
logFile << "main5" << std::endl;
			y = y*2;
			continue;
		}
logFile << "main6" << std::endl;

}
logFile << "main7" << std::endl;

}
logFile << "main8" << std::endl;

	cout<<y<<endl;
}

