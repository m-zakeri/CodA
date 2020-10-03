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
<<<<<<< HEAD

=======
logFile << "main13" << std::endl;
intx=(in>1)?10:11;cout<<x<<endl;do{
logFile << "main14" << std::endl;
cout<<"ya_allah";
}while(1);
logFile << "main15" << std::endl;
return0;}
>>>>>>> 67ee24dbc8df336420fee590f788957040829f69
