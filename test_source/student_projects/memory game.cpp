#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int size = 4; // Controls the size of the game board as a square: When equal to four, gives a 4 X 4 board.

void getgrid(string filename, string objects[][size], bool dec[], int ch1, int ch2);
void displaygrid(int ch1, int ch2, string objects[][size], bool dec[]);
int getchoice(int number1);
void drawbar();
void check();
void begingrid(bool dec[16]);





int main()
{
    srand((int)time(NULL));
    string filename;
    int number1;

    string objects [size][size];
    bool dec [size * 4];
    int ch1 = 0, ch2 = 0;

    cout << "  How good is your memory? " << endl << " Enter the name of the file";
    getline(cin,filename);

    cout << " Enter your choice. ";
    cin >> number1;


    ifstream infile;

    begingrid(dec);
    drawbar();
    displaygrid(ch1, ch2, objects, dec);
    drawbar();
    getchoice(number1);
    drawbar();
    displaygrid(ch1, ch2, objects, dec);
    drawbar();
    getchoice(number1);
    drawbar();
    displaygrid(ch1, ch2, objects, dec);
    drawbar();



    return 0;
}


void getgrid(string filename, string objects[][size])
{
    ifstream infile;
    string name;
    int r, c;

    infile.open(filename.c_str());

    infile >> name;
    cout << name;

    int ct = 0;
    int random = rand() % 8;

    while(infile)
    {

        string names[8];
        names[ct] = name;

        infile >> names[ct];
        ct++;

        infile.close();

        for(c = 0; c < size; c++)
        {
            for(r = 0; r < size; r++)
            {
                objects[r][c] = names[rand()% 8];
                cout << objects[r][c];
            }
        }
    }
}

void check()
{

}


void drawbar()
{
    cout << "--------------------------------------------------------" << endl;

}

void displaygrid(int ch1, int ch2, string objects[][size], bool dec[])
{
    int r, c;

    for(c = 0; c < size; c++)
    {
        for(r = 0; r < size; r++)
        {



            if(dec[size] == true || ch1 == r * size + c + 1 || ch2 == r * size + c + 1)

                cout << setw(8) << objects[r][c];

            else

                cout << setw(8) << "***" << objects[r][c];

        }
    }
    cout << endl;

}


int getchoice(int number1)
{
    cout << " Enter your choice (1-16) " << endl;
    cin >> number1;

    return number1;

}


void begingrid(bool dec[16])
{
    for(int ct = 0; ct < 16; ct++)
    {
        dec[ct] = false;
        ct ++;
    }
}
