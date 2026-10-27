#include <iostream>
using namespace std;
#define MAX 30
//each peg is a stack
int peg[3][MAX];
int top[3];
char name[3] = { 'A', 'B', 'C' };

void push(int p, int disk)
{
    peg[p][++top[p]] = disk;
}
int pop(int p)
{
    return peg[p][top[p]--];
}
//top disk, 0 if empty
int topDisk(int p)
{
    if (top[p] == -1)
        return 0;
    return peg[p][top[p]];
}
//legal move between two pegs (whichever way works)
void moveBetween(int a, int b)
{
    int da = topDisk(a), db = topDisk(b);

    if (da == 0 || (db != 0 && db < da))
    {
        push(a, pop(b));
        cout << "Move disk " << db << " from " << name[b] << " to " << name[a] << endl;
    }
    else
    {
        push(b, pop(a));
        cout << "Move disk " << da << " from " << name[a] << " to " << name[b] << endl;
    }
}

int main()
{
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    if (n < 1 || n >= MAX)
    {
        cout << "Invalid input\n";
        return 0;
    }

    int src = 0, aux = 1, dest = 2;
    top[0] = top[1] = top[2] = -1;

    for (int i = n; i >= 1; i--)
        push(src, i);

    //for even n swap aux and dest
    if (n % 2 == 0)
    {
        int t = aux;
        aux = dest;
        dest = t;
    }
    long long total = (1LL << n) - 1;
    for (long long i = 1; i <= total; i++)
    {
        if (i % 3 == 1)
            moveBetween(src, dest);
        else if (i % 3 == 2)
            moveBetween(src, aux);
        else
            moveBetween(aux, dest);
    }
    cout << "\nTotal moves = " << total << endl;
    return 0;
}