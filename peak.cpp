#include <iostream>
using namespace std;

#define SIZE 100

int grid[SIZE][SIZE];
int R, C;

//go down the column and find which row has the largest number
int biggestRow(int col)
{
    int idx = 0;
    for (int r = 0; r < R; r++)
        if (grid[r][col] > grid[idx][col])
            idx = r;
    return idx;
}

//check middle column, then move to the side that has a bigger neighbour
void peakSearch(int left, int right)
{
    int mid = left + (right - left) / 2;
    int r = biggestRow(mid);
    int val = grid[r][mid];

    bool leftBigger = (mid - 1 >= 0) && (grid[r][mid - 1] > val);
    bool rightBigger = (mid + 1 < C) && (grid[r][mid + 1] > val);

    if (!leftBigger && !rightBigger)
    {
        //val is biggest in its column already, so it beats top and bottom too
        cout << "\nPeak found: " << val << " at row " << r << ", col " << mid << endl;
        return;
    }

    if (leftBigger)
        peakSearch(left, mid - 1);
    else
        peakSearch(mid + 1, right);
}

int main()
{
    cout << "Rows: ";
    cin >> R;
    cout << "Columns: ";
    cin >> C;
    cout << "Enter matrix values row by row:\n";
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    peakSearch(0, C - 1);

    return 0;
}