#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 20
int N;
int board[MAX][MAX];

//knight moves
int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool canGo(int x, int y)
{
    return x >= 0 && y >= 0 && x < N && y < N && board[x][y] == 0;
}

//no of moves from x,y
int countMoves(int x, int y)
{
    int c = 0;
    for (int k = 0; k < 8; k++)
        if (canGo(x + dx[k], y + dy[k]))
            c++;
    return c;
}

bool tour(int x, int y, int step)
{
    board[x][y] = step;
    if (step == N * N)
        return true;

    int order[8], deg[8], cnt = 0;
    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k], ny = y + dy[k];
        if (canGo(nx, ny))
        {
            order[cnt] = k;
            deg[cnt] = countMoves(nx, ny);
            cnt++;
        }
    }

    //sort so least moves comes first
    for (int i = 1; i < cnt; i++)
    {
        int d = deg[i], o = order[i], j = i - 1;
        while (j >= 0 && deg[j] > d)
        {
            deg[j + 1] = deg[j];
            order[j + 1] = order[j];
            j--;
        }
        deg[j + 1] = d;
        order[j + 1] = o;
    }

    for (int i = 0; i < cnt; i++)
    {
        int k = order[i];
        if (tour(x + dx[k], y + dy[k], step + 1))
            return true;
    }

    board[x][y] = 0; // backtrack
    return false;
}

int main()
{
    int sx, sy;
    cout << "Board size N: ";
    cin >> N;
    cout << "Starting position (row col): ";
    cin >> sx >> sy;

    if (N > MAX || sx < 0 || sy < 0 || sx >= N || sy >= N)
    {
        cout << "Invalid input\n";
        return 0;
    }

    if (tour(sx, sy, 1))
    {
        cout << "\nKnight's tour:\n\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << setw(4) << board[i][j];
            cout << endl;
        }
    }
    else
        cout << "\nNo tour possible\n";

    return 0;
}
