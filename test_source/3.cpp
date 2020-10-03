//in the name of allah
#include<iostream>
using namespace std;

int main()
{
    int H[10][3]= {1,0,1,
                   0,0,0,
                   1,1,1,
                   1,1,1,
                   0,1,0,
                   1,1,1,
                   1,1,1,
                   1,0,0,
                   1,1,1,
                   1,1,1
                  };
    int ph[2][3]= {1,1,0,
                   1,1,0
                  };
    int pv[2][4]= {1,1,1,0,
                   1,1,1,1
                  };
    int V[10][4]= {1,1,1,1,
                   0,1,0,1,
                   0,1,1,0,
                   0,1,0,1,
                   1,1,0,1,
                   1,0,0,1,
                   1,0,1,1,
                   0,1,0,1,
                   1,1,1,1,
                   1,1,0,1
                  };
	int n = 62 , i;
    if(n==62)
    {
        for(i=0; i<3; i++)
        {
            if(ph[0][i]==1)
            {
                cout<<"ya_allah"<<endl;
            }
        }
        for(i=0; i<4; i++)
        {
            if(pv[0][i]==1)
            {
                cout<<"ya_allah"<<endl;
            }
        }
    }
    else if(n==63)
    {
        for(i=0; i<3; i++)
        {
            if(ph[1][i]==1)
            {
                cout<<"ya_allah"<<endl;
            }
        }
        for(i=0; i<4; i++)
        {
            if(pv[1][i]==1)
            {
                cout<<"ya_allah"<<endl;
            }
        }
    }
    else
    {
        for(i=0; i<3; i++)
        {
            if(H[n][i]==1)
                cout<<"ya_allah"<<endl;
        }
        for(i=0; i<4; i++)
        {
            if(V[n][i]==1)
                cout<<"ya_allah"<<endl;
        }
    }
}
