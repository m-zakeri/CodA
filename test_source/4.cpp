//in the name of allah
#include<iostream>
using namespace std;
struct Sum
{
    void operator()(int n) { sum += n; }
    int sum{0};
};
int main()
{
	int a[] = {0,1,2,3,4,5};
	for(int i:a)
		cout<<"ya_ali";

	int x = 0 , y =100;
	int n = 2 ;
	for (int i =0 ; ;i++)
	{
		if (i<8)
			break;
		else
			cout<<1;
			
		if (i<10)
			for (int j =0;j<n;j++)
				if (j<3)
					cout<<2;
				else
					break;
	}
	
	try{
		cout<<"ya_hosein";
		do 
		switch (n)
		{
			label: cout<<"ya_zahra";
			
			case 1:
				continue;
			case 2:
				cout<<"ya_ali"<<endl;
			case 3:
				int h = 0;
				cout<<"ya_allah"<<endl;
				n++;
		}
		while (n <4);
	}
	catch (int e){
		cout<<"ya_abalfazl";
	}

	cout<<y<<endl;
}
