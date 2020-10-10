//in the name of allah
#include<iostream>

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

using namespace std;

int main()
{
logFile << "main 1" << std::endl;

    int n=1;
    
    do{
logFile << "main 3" << std::endl;

    	cout<<"ya_hosein"<<endl;
    	switch(n)
    	{
    		case 1:
    			logFile << "main 4" << std::endl;
n++;
    			cout<<"ya_hosein"<<endl;
    			continue;
    		case 2:
    			logFile << "main 5" << std::endl;
cout<<"ya_zahra"<<endl;
    		case 3:
    			logFile << "main 6" << std::endl;
n++;
    			cout<<"ya_ali"<<endl;
    			break;
		}
logFile << "main 7" << std::endl;

	}
	while(logFile << "main 2" << std::endl && (cout<<"ya_allah"<<endl && n<4));
logFile << "main 8" << std::endl;

	
	while (logFile << "main 9" << std::endl && (n<8))
	{
		n++;
	}
logFile << "main 10" << std::endl;

	return 0;
	
}
