#include "PGArray.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

// file that handles most of the game

// pointers to 2D arrays
int** arr1;
int** arr2;
int** MakeArr1();
int** MakeArr2();
int** Array1;
int** Array2;
int** FILEARRAY;

double random1;
double random2;
double newDensity;
double finalDensity;
double newRandom;


int x;
int y;
int z;
int t;
int choiceCount = 0;
int choice;
int genCount = 0;
int MODE;
int BOOL;

char character;



using namespace std;

ofstream output;


//constructor
PGArray::PGArray(int coodx, int coody, double density, int** fileArray, int mode, int Bool)
{
    cout << "PGArray Created" << endl;

    x = coodx;
    y = coody;
    z = coodx;
    t = coody;
    newDensity = density;
    MODE = mode;
    FILEARRAY = fileArray;
    BOOL = Bool;

    arr1=0;
    arr2=0;
}


//destructor
PGArray::~PGArray()
{
    // frees memory
    delete [] arr2;
    delete [] arr1;
    cout << "PGArray Destroyed" << endl;
}


// creates starting array if user selected to randomly generate starting array
int** PGArray::MakeArr1()
{
    //called once to set rand()
    srand(time(0));

    //creates 2D array
    arr1 = new int *[x];

    for( int i = 0 ; i < x ; i++)
    {
        arr1[i] = new int[y];
    }
    //populates array
    for ( int i = 0 ; i < x ; i++)
    {
        for ( int j = 0 ; j < y ; j++)
        {
            random1 = rand();
            random2 = random1 / RAND_MAX; //generates random decimal between 0 and 1
            // if user inputted popDensity is small, (ex: .2) there is a higher chance each spot in the array is 0
            // if user inputted popDensity is large, (ex: .9) there is a higher chance each spot in the array is 1
            if (random2 < newDensity)
            {
                arr1[i][j] = 1;
            }
            else
            {
                arr1[i][j] = 0;
            }
        }
    }
    return (arr1);
}


// Makes blank 2D array of proper size as chosen by the user
int** PGArray::MakeArr2()
{
    arr2 = new int *[z];

    for( int i = 0 ; i < z ; i++)
    {
        arr2[i] = new int[t];
    }
    return (arr2);
}


// compares the two arrays used in the game to see if they are equal
int PGArray::MatchArrays(int** array6, int** array9)
{
    int matchCount = 0;

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if (array9[i][j] == array6[i][j])
                {
                    ++matchCount;
                }
        }
    }
    int gridSize = x * y;
    // if both grids have the same number of 1's in the same places, return true (1)
    if (matchCount == gridSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// prints int array onto terminal, turning 0's into -'s and 1's into X's
void PGArray::Print(int** array3)
{
    // prints generation count before each array
    cout << "Generation count = " << genCount << endl;
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if ( array3[i][j] == 1)
				cout << 'X';
			else
				cout << '-';
        }
        cout << endl;
    }
}


// prints array onto output file, turning 0's into -'s and 1's into X's
void PGArray::PrintOutput(int** array420)
{
    // prints generation count before each array is printed
    output << "Generation count = " << genCount << endl;

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if (array420[i][j] == 1)
            {
                character = 'X';
                output << character;
            }
            else
            {
                character = '-';
                output << character;
            }
        }
        output << endl;
    }
    output << endl;
}


// clones one array into another
void PGArray::Clone(int** original, int ** clone)
{
    for ( int i = 0 ; i < x ; i++)
    {
        for ( int j = 0 ; j < y ; j++)
        {
            clone[i][j] = original[i][j];
        }
    }
}


// classic mode
void PGArray::ClassicMode(int** classicArr, int** cloneArr)
{
    // sets int to MatchArrays
    int matchArrayint = MatchArrays(classicArr, cloneArr);

    // if the arrays do not match, run the game
    if (matchArrayint == 0)
    {
        Clone(classicArr, cloneArr);  // clones arrays so the original is not messed up
        int count1 = 0; // number of neighbors
        ++genCount;  //increases generation count so that the first iteration is gen1
        // loop to check neighbors
        for (int i = 0; i < x; i++)
        {
            for (int j =0; j < y; j++)
            {
                // checks to the right
                if((j + 1) < y && cloneArr[i][j+1] == 1)
                {
                    ++count1;
                }
                // checks diagonal up and right
                if((i + 1) < x && (j + 1) < y && cloneArr[i+1][j+1] == 1)
                {
                    ++count1;
                }
                //checks below
                if((i + 1) < x && cloneArr[i+1][j] == 1)
                {
                    ++count1;
                }
                //checks bottom left
                if((i + 1) < x && (j - 1) >= 0 && cloneArr[i+1][j-1] == 1)
                {
                    ++count1;
                }
                // checks left
                if((j - 1) >= 0 && cloneArr[i][j-1] == 1)
                {
                    ++count1;
                }
                // checks top left
                if((j - 1) >= 0 && (i - 1) >= 0 && cloneArr[i-1][j-1] == 1)
                {
                    ++count1;
                }
                // checks top
                if((i - 1) >= 0 && cloneArr[i-1][j] == 1)
                {
                    ++count1;
                }
                //checks top right
                if((i - 1) >= 0 && (j + 1) < y && cloneArr[i-1][j+1] == 1)
                {
                    ++count1;
                }


                // decides if cells live or die based on count1 (NUMBER OF NEIGHBORS)
                if (count1 < 2 || count1 > 3)
                {
                    classicArr[i][j] = 0;
                }
                else if (count1 == 2)
                {
                    classicArr[i][j] = cloneArr[i][j];
                }
                else if (count1 == 3)
                {
                    classicArr[i][j] = 1;
                }
                // sets count1 back to zero for next loop
                count1 = 0;
            }
        }
    }
    // if arrays match, call this method
    else
    {
        GensStabilized();
    }
}


//mirror mode
void PGArray::MirrorMode(int** mirrorArr, int** cloneArr2)
{
    //starts off the same as classic mode
    int matchArrayint = MatchArrays(mirrorArr, cloneArr2);

    if (matchArrayint == 0)
    {
        Clone(mirrorArr, cloneArr2);
        int count1 = 0;
        ++genCount;
        for (int i = 0; i < x; i++)
        {
            for (int j =0; j < y; j++)
            {
                if((j + 1) < y && cloneArr2[i][j+1] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && (j + 1) < y && cloneArr2[i+1][j+1] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && cloneArr2[i+1][j] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && (j - 1) >= 0 && cloneArr2[i+1][j-1] == 1)
                {
                    ++count1;
                }
                if((j - 1) >= 0 && cloneArr2[i][j-1] == 1)
                {
                    ++count1;
                }
                if((j - 1) >= 0 && (i - 1) >= 0 && cloneArr2[i-1][j-1] == 1)
                {
                    ++count1;
                }
                if((i - 1) >= 0 && cloneArr2[i-1][j] == 1)
                {
                    ++count1;
                }
                if((i - 1) >= 0 && (j + 1) < y && cloneArr2[i-1][j+1] == 1)
                {
                    ++count1;
                }

                //MIRROR MODE CHECKS

                //checks top reflection
                if(i==0)
                {
                    if(cloneArr2[i][j] == 1)
                    {
                        ++count1;
                    }
                    if((j - 1) >= 0 && cloneArr2[i][j-1] == 1)
                    {
                        ++count1;
                    }
                    if((j + 1) < y && cloneArr2[i][j+1] == 1)
                    {
                        ++count1;
                    }
                }
                //checks bottom reflection
                if(i==x)
                {
                    if(cloneArr2[i][j] == 1)
                    {
                        ++count1;
                    }
                    if((j - 1) >= 0 && cloneArr2[i][j-1] == 1)
                    {
                        ++count1;
                    }
                    if((j + 1) < y && cloneArr2[i][j+1] == 1)
                    {
                        ++count1;
                    }
                }
                //checks left reflection
                if(j==0)
                {
                    if(cloneArr2[i][j] == 1)
                    {
                        ++count1;
                    }
                    if((i + 1) < x && cloneArr2[i+1][j] == 1)
                    {
                        ++count1;
                    }
                    if((i - 1) >= 0 && cloneArr2[i-1][j] == 1)
                    {
                        ++count1;
                    }
                }
                //checks right reflection
                if(j==y)
                {
                    if(cloneArr2[i][j] == 1)
                    {
                        ++count1;
                    }
                    if((i + 1) < x && cloneArr2[i+1][j] == 1)
                    {
                        ++count1;
                    }
                    if((i - 1) >= 0 && cloneArr2[i-1][j] == 1)
                    {
                        ++count1;
                    }
                }

                if (count1 < 2 || count1 > 3)
                {
                    mirrorArr[i][j] = 0;
                }
                else if (count1 == 2)
                {
                    mirrorArr[i][j] = cloneArr2[i][j];
                }
                else if (count1 == 3)
                {
                    mirrorArr[i][j] = 1;
                }
                count1 = 0;
            }
        }
    }
    else
    {
        GensStabilized();
    }
}


//donut mode
void PGArray::DonutMode(int ** donutArr, int** cloneArr3)
{
    // same as before
    int matchArrayint = MatchArrays(donutArr, cloneArr3);

    if (matchArrayint == 0)
    {
        Clone(donutArr, cloneArr3);
        int count1 = 0;
        ++genCount;
        for (int i = 0; i < x; i++)
        {
            for (int j =0; j < y; j++)
            {
                if((j + 1) < y && cloneArr3[i][j+1] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && (j + 1) < y && cloneArr3[i+1][j+1] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && cloneArr3[i+1][j] == 1)
                {
                    ++count1;
                }
                if((i + 1) < x && (j - 1) >= 0 && cloneArr3[i+1][j-1] == 1)
                {
                    ++count1;
                }
                if((j - 1) >= 0 && cloneArr3[i][j-1] == 1)
                {
                    ++count1;
                }
                if((j - 1) >= 0 && (i - 1) >= 0 && cloneArr3[i-1][j-1] == 1)
                {
                    ++count1;
                }
                if((i - 1) >= 0 && cloneArr3[i-1][j] == 1)
                {
                    ++count1;
                }
                if((i - 1) >= 0 && (j + 1) < y && cloneArr3[i-1][j+1] == 1)
                {
                    ++count1;
                }

                //DONUT MODE CHECKS

                //checks top part
                if(i==0)
                {
                    if(cloneArr3[x-1][j] == 1)
                    {
                        ++count1;
                    }
                    if((j - 1) >= 0 && cloneArr3[x-1][j-1] == 1)
                    {
                        ++count1;
                    }
                    if((j + 1) < y && cloneArr3[x-1][j+1] == 1)
                    {
                        ++count1;
                    }
                }
                //checks bottom part
                if(i==x)
                {
                    if(cloneArr3[0][j] == 1)
                    {
                        ++count1;
                    }
                    if((j - 1) >= 0 && cloneArr3[0][j-1] == 1)
                    {
                        ++count1;
                    }
                    if((j + 1) < y && cloneArr3[0][j+1] == 1)
                    {
                        ++count1;
                    }
                }
                //checks left part
                if(j==0)
                {
                    if(cloneArr3[i][y-1] == 1)
                    {
                        ++count1;
                    }
                    if((i + 1) < x && cloneArr3[i+1][y-1] == 1)
                    {
                        ++count1;
                    }
                    if((i - 1) >= 0 && cloneArr3[i-1][y-1] == 1)
                    {
                        ++count1;
                    }
                }
                //checks right part
                if(j==y)
                {
                    if(cloneArr3[i][0] == 1)
                    {
                        ++count1;
                    }
                    if((i + 1) < x && cloneArr3[i+1][0] == 1)
                    {
                        ++count1;
                    }
                    if((i - 1) >= 0 && cloneArr3[i-1][0] == 1)
                    {
                        ++count1;
                    }
                }

                if (count1 < 2 || count1 > 3)
                {
                    donutArr[i][j] = 0;
                }
                else if (count1 == 2)
                {
                    donutArr[i][j] = cloneArr3[i][j];
                }
                else if (count1 == 3)
                {
                    donutArr[i][j] = 1;
                }
                count1 = 0;
            }
        }

    }
    else
    {
        GensStabilized();
    }
}


// called when the MatchArrays() returns 1 (arrays match)
void PGArray::GensStabilized()
{
    cout << "Generations have stabilized" << endl;

    cout << "Press 'ENTER' to exit \n" << endl;
    cin.clear();
    cin.ignore( 1000, '\n' );

    if (cin.get() == '\n')
    {
        cout << "Thank you" << endl;
        exit(0);
    }
    else
    {
        GensStabilized();
    }
}


// builds game arrays if the game is just starting (randomly generated first grid)
void PGArray::Initialize()
{
    Array1 = MakeArr1();
    Array2 = MakeArr2();
}


//builds game array if the game is just starting (first grid taken from file)
void PGArray::Initialize2()
{
    Array2 = MakeArr2();
}


// starts game, called if user randomly generated first grid
void PGArray::Play()
{
    // gen0 grid randomly generated
    if (BOOL == 0)
    {
        if (MODE == 1)
        {
            // Classic mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            // runs mode
            ClassicMode(Array1, Array2);
            // prints array
            Print(Array1);
            cout << endl;
        }
        else if (MODE == 2)
        {
            // Mirror mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            MirrorMode(Array1, Array2);
            Print(Array1);
            cout << endl;
        }
        else
        {
            // Donut mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            DonutMode(Array1, Array2);
            Print(Array1);
            cout << endl;
        }
    }
    // gen0 grid taken from file
    else
    {
        if (MODE == 1)
        {
            if (Array2 == 0)
            {
                Initialize2();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            ClassicMode(FILEARRAY, Array2);
            Print(FILEARRAY);
            cout << endl;
        }
        else if (MODE == 2)
        {
            // Mirror mode
            if (Array2 == 0)
            {
                Initialize2();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            MirrorMode(FILEARRAY, Array2);
            Print(FILEARRAY);
            cout << endl;
        }
        else
        {
            // Donut mode
            if (Array2 == 0)
            {
                Initialize2();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            DonutMode(FILEARRAY, Array2);
            Print(FILEARRAY);
            cout << endl;
        }
    }
}


// same as play, but instead of printing to terminal, it prints to output file
void PGArray::PlayOutput()
{
    if (BOOL == 0)
    {
        if (MODE == 1)
        {
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            ClassicMode(Array1, Array2);
            PrintOutput(Array1);
        }
        else if (MODE == 2)
        {
            // Mirror mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            MirrorMode(Array1, Array2);
            PrintOutput(Array1);
        }
        else
        {
            // Donut mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            DonutMode(Array1, Array2);
            PrintOutput(Array1);
        }
    }
    else
    {
        // filestuff
        if (MODE == 1)
        {
            if (Array2 == 0)
            {
                Initialize2();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            ClassicMode(FILEARRAY, Array2);
            PrintOutput(FILEARRAY);

        }
        else if (MODE == 2)
        {
            // Mirror mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            MirrorMode(FILEARRAY, Array2);
            PrintOutput(FILEARRAY);
        }
        else
        {
            // Donut mode
            if (Array1 == 0)
            {
                Initialize();
            }
            if (choiceCount == 0)
            {
                Choose();
            }
            DonutMode(FILEARRAY, Array2);
            PrintOutput(FILEARRAY);
        }

    }
    PlayOutput();
}


// called if user would like to press enter between generations
void PGArray::Enter()
{
    cout << "Press ENTER to continue" << endl;
    cout << endl;
    if (cin.get() == '\n')
    {
        Play();
        Enter();
    }
    else
    {
        cout << "Oops" << endl;
        Enter();
    }
}


// called if user would like a short pause between generations
void PGArray::Delay()
{
    sleep(1);
    Play();
    Delay();
}


// user chooses how they would like to see the game play out, called only once per game
void PGArray::Choose()
{
    if(choiceCount == 0)
    {
        cout << "Enter 1 for a brief pause between generations, 2 to \npress 'ENTER' between generations, or 3 to submit the output to a file." << endl;
        cin>> choice;
        if (choice == 1)
        {
            if(BOOL ==0)
            {
                Print(Array1);
            }
            else
            {
                Print(FILEARRAY);
            }
            ++choiceCount;
            Delay();
        }
        else if (choice == 2)
        {
            if(BOOL ==0)
            {
                Print(Array1);
            }
            else
            {
                Print(FILEARRAY);
            }
            ++choiceCount;
            Enter();
        }
        else if (choice == 3)
        {
            cout << "Writing to file GameOfLifeOutput.txt..." << endl;
            sleep(3); // waits 3 seconds to pretend like this takes time
            cout << "Success!" << endl;
            output.open("GameOfLifeOutput.txt");
            if(BOOL ==0)
            {
                PrintOutput(Array1);
            }
            else
            {
                PrintOutput(FILEARRAY);
            }
            ++choiceCount;
            PlayOutput();
        }
        else
        {
            cout << "Oops" << endl;
            Choose();
        }
        cin.clear();
        cin.ignore( 1000, '\n' );
    }
    ++choiceCount;
}
