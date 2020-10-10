//in the name of allah
#include<iostream>
using namespace std;

int main()
{
    int n=1;
    
    do{
    	cout<<"ya_hosein"<<endl;
    	switch(n)
    	{
    		case 1:
    			n++;
    			cout<<"ya_hosein"<<endl;
    			continue;
    		case 2:
    			cout<<"ya_zahra"<<endl;
    		case 3:
    			n++;
    			cout<<"ya_ali"<<endl;
    			break;
		}
	}
	while(cout<<"ya_allah"<<endl && n<4);
	
	while (n<8)
	{
		n++;
	}
	return 0;
	
}
