//in the name of allah
#include<iostream>

using namespace std;

int main()
{
	int in;
	cin>>in;
	if (in >0){
		for (int i=0;i<10;i++)
	    	cout<<in+i;
		while(in < 10)
	    	in += 1;
		if(in>9)
	    	cout<<"ya_allah";
	    else
	    	in =10;
	    if (in<10)
	    	cout<<"ya_ali";
	}
	else
	    cout<<"ya_ali";
	int x = (in > 1) ? 10 : 11;
	cout<<x<<endl;
	do
	   cout<<"ya_allah";
	while(1);
	return 0;
}
