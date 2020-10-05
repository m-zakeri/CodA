#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>


//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

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
logFile << "main 1" << std::endl;

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
logFile << "getgridstringfilenamestringobjectssize 1" << std::endl;

    ifstream infile;
    string name;
    int r, c;

    infile.open(filename.c_str());

    infile >> name;
    cout << name;

    int ct = 0;
    int random = rand() % 8;

    while(logFile << "getgridstringfilenamestringobjectssize 2" << std::endl && (infile))
    {

        string names[8];
        names[ct] = name;

        infile >> names[ct];
        ct++;

        infile.close();

        for(c = 0; logFile << "getgridstringfilenamestringobjectssize 3" << std::endl && (c < size); c++)
        {
            for(r = 0; logFile << "getgridstringfilenamestringobjectssize 4" << std::endl && (r < size); r++)
            {
                objects[r][c] = names[rand()% 8];
                cout << objects[r][c];
            }
logFile << "getgridstringfilenamestringobjectssize 5" << std::endl;

        }
logFile << "getgridstringfilenamestringobjectssize 6" << std::endl;

    }
logFile << "getgridstringfilenamestringobjectssize 7" << std::endl;

}

void check()
{
logFile << "check 1" << std::endl;


}


void drawbar()
{
logFile << "drawbar 1" << std::endl;

    cout << "--------------------------------------------------------" << endl;

}

void displaygrid(int ch1, int ch2, string objects[][size], bool dec[])
{
logFile << "displaygridintch1intch2stringobjectssizebooldec 1" << std::endl;

    int r, c;

    for(c = 0; logFile << "displaygridintch1intch2stringobjectssizebooldec 2" << std::endl && (c < size); c++)
    {
        for(r = 0; logFile << "displaygridintch1intch2stringobjectssizebooldec 3" << std::endl && (r < size); r++)
        {



            if(dec[size] == true || ch1 == r * size + c + 1 || ch2 == r * size + c + 1)

                {
logFile << "displaygridintch1intch2stringobjectssizebooldec 4" << std::endl;
cout << setw(8) << objects[r][c];
}

            else

                {
logFile << "displaygridintch1intch2stringobjectssizebooldec 5" << std::endl;
cout << setw(8) << "***" << objects[r][c];
}
logFile << "displaygridintch1intch2stringobjectssizebooldec 6" << std::endl;


        }
logFile << "displaygridintch1intch2stringobjectssizebooldec 7" << std::endl;

    }
logFile << "displaygridintch1intch2stringobjectssizebooldec 8" << std::endl;

    cout << endl;

}


int getchoice(int number1)
{
logFile << "getchoiceintnumber1 1" << std::endl;

    cout << " Enter your choice (1-16) " << endl;
    cin >> number1;

    return number1;

}


void begingrid(bool dec[16])
{
logFile << "begingridbooldec16 1" << std::endl;

    for(int ct = 0; logFile << "begingridbooldec16 2" << std::endl && (ct < 16); ct++)
    {
        dec[ct] = false;
        ct ++;
    }
logFile << "begingridbooldec16 3" << std::endl;

}
