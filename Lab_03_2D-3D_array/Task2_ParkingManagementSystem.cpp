
#include <iostream>
using namespace std;

int main()
{
    const int ROWS = 4;
    const int COLS = 5;

    // 1. Create and initialize the 2D parking array
    int parking[ROWS][COLS] = {
        {1, 0, 1, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1}
    };

    
    cout << "===== Parking Layout =====" << endl;
    cout << "\t";
    for (int j = 0; j < COLS; j++)
        cout << "C" << j << "\t";
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << "R" << i << "\t";
        for (int j = 0; j < COLS; j++)
        {
            cout << parking[i][j] << "\t";
        }
        cout << endl;
    }

    
    int occupied = 0, empty = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;
        }
    }

    cout << "\nTotal Occupied Spaces: " << occupied << endl;
    cout << "Total Empty Spaces: " << empty << endl;

    
    int row, col;
    cout << "\nEnter row number (0-" << ROWS - 1 << "): ";
    cin >> row;
    cout << "Enter column number (0-" << COLS - 1 << "): ";
    cin >> col;

    // 6. Check whether the selected parking space is available or occupied
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        if (parking[row][col] == 1)
            cout << "Parking space [" << row << "][" << col << "] is OCCUPIED." << endl;
        else
            cout << "Parking space [" << row << "][" << col << "] is AVAILABLE." << endl;
    }
    else
    {
        cout << "Invalid row or column entered." << endl;
    }

    
    int totalCapacity = ROWS * COLS;
    cout << "\nTotal Parking Capacity: " << totalCapacity << endl;
    cout << "Current Occupancy: " << occupied << " / " << totalCapacity << endl;

    return 0;
}
