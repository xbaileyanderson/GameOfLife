#include "Start.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include "PGArray.h"


using namespace std;

int chooseCood;
int chooseMode;
int Bool1;
char** array10;
int** array11;
char c;
int ch;


//constructor
Start::Start()
{
    cout << "Object Created" << endl;
}

//destructor
Start::~Start()
{
    cout << "Object Destroyed" << endl;
}


// File input for starting grid if user decides to use an input file
void Start::PromptFile()
{
    Bool1 = 1;
    chooseCood = 1;
    string boardfile;
    cout<< "Enter filename to be used as the game board"<< endl;
    cin >> boardfile;
    ifstream BOARD;
    //opens file if there is one
    BOARD.open(boardfile.c_str());

    if (BOARD.is_open())
    {
        string line;
        string line2;
        int lineX;
        int lineY;
        int nullDensity = 0;

        // takes row from file
        getline(BOARD, line);
        lineX = atoi(line.c_str());

        // takes column from file
        getline(BOARD, line2);
        lineY = atoi(line2.c_str());


        // creates char array to take in grid from file
        array10 = new char *[lineX];

        for( int i = 0 ; i < lineX ; i++)
        {
            array10[i] = new char[lineY];
        }

        // creates int array that will be passed to PGArray
        array11 = new int *[lineX];

        for( int i = 0 ; i < lineX ; i++)
        {
            array11[i] = new int[lineY];
        }

        //takes grid from file and transfers it to char array
        for (int i = 0; i < lineX; ++i)
        {
            for (int j = 0; j < lineY; ++j)
            {

                BOARD >> c;
                array10[i][j] = c;
            }
        }

        //transfers info from char array into int array
        for (int i = 0; i < lineX; ++i)
        {
            for (int j = 0; j < lineY; ++j)
            {
                if ( array10[i][j] == 'X')
                {
                    array11[i][j] = 1;
                }
                else
                {
                    array11[i][j] = 0;
                }
            }
        }

        //closes file
        BOARD.close();

        //choose game mode
        cout << "MODE: Enter 1 for classic, 2 for mirror, or 3 for donut" << endl;
        cin >> chooseMode;
        if (cin.fail())
        {
            cout << "Oops, try again" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            PromptFile();
        }
        else if (!(chooseMode == 1 || chooseMode == 2 || chooseMode == 3))
        {
            cout << "Oops, try again" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            PromptFile();
        }

        // creates PGArray object with row, column, int array,
        // mode, and Bool1 = 1 (meaning the user chose to use a file as input instead of random assignment)
        PGArray pgarray(lineX, lineY, nullDensity, array11, chooseMode, Bool1);
        // starts game
        pgarray.Play();

    }

    //user did not input a file in the current directory, prompts for file again
    else
    {
        cout<<"Invalid file name." << endl;
        PromptFile();
    }
}


// called if user decides on random assignment of gen0 grid instead of file input
void Start::PromptCoordinates()
{
    Bool1 = 0;
    int** array11 = 0;
    chooseCood = 0;

    // takes in row
    cout << "Enter the x coordinate/number of rows \n(Must be an integer greater than 0)" << endl;
    cin >> x;

    // user input error checking
    if (cin.fail())
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }
    else if (x < 0)
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }

    //takes in column
    cout << "Enter the y coordinate/number of columns \n(Must be an integer greater than 0)" << endl;
    cin >> y;
    if (cin.fail())
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }
    else if (y < 0)
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }

    // takes in population density of initial cell
    cout << "Enter a decimal value (Must be greater than 0 and less than or equal to 1) \nrepresenting the initial population density of the world. " << endl;
    cin >> popDensity;
    if (cin.fail())
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }
    else if (!(popDensity <= 1 && popDensity > 0))
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }

    // mode selection
    cout << "MODE: Enter 1 for classic, 2 for mirror, or 3 for donut" << endl;
    cin >> chooseMode;
    if (cin.fail())
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }
    else if (!(chooseMode == 1 || chooseMode == 2 || chooseMode == 3))
    {
        cout << "Oops, try again" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        PromptCoordinates();
    }

    // creates PGArray object with row, column, int array,
    // mode, and Bool1 = 0 (meaning the user chose to use random assignment instead of a file as input)
    PGArray pgarray(x,y,popDensity, array11, chooseMode, Bool1);
    //starts game
    pgarray.Play();
}


// ran at game start
void Start::StartLife()
{
    string startAnswer;
    // user selects an option
    cout<< "Welcome to the game of life, enter 1 to enter a map file, \nenter 2 for a random assignment, enter 3 to quit." << endl;
    cin >> startAnswer;
    if (startAnswer == "1")
    {
        PromptFile();
    }
    else if (startAnswer == "2")
    {
        PromptCoordinates();
    }
    else if (startAnswer == "3")
    {
        cout << "Thank you" << endl;
    }
    else
    {
        cout << "Oops, try again." << endl;
        StartLife();
    }
}
