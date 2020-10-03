//in the name of allah
#include<iostream>
using namespace std;

int main()
{
	int x = 0 , y =100;
	for( y = x + 1 ; x < y ; y = ++x + 1) 
		if ( y == 0 )
			break;
		else if ( y < 0 )
		{
			y = y*2;
			continue;
		}
	cout<<y<<endl;
}
