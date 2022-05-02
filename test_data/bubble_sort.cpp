//in the name of allah
#include<iostream>
using namespace std;
void bubble(int* a,int i,int j)
{
	if (a[i] > a[j]){
		a[i] += a[j];
		a[j] = a[i] - a[j];
		a[i] -= a[j];
	}
	return;
}
int main()
{
	int a[10];
	for (int i=0;i<10;i++) {
		cin>>a[i];
	}
	for (int i=0;i<10;i++)
		for (int j=i;j<10;j++)
			bubble(a,i,j);
	for (int i : a)
		cout<<i<<' ';
	return 0;
}
