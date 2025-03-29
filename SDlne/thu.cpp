#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{
    fstream myfile;
    myfile.open("data.txt", ios::in | ios::out);
    int score[3];
    for(int i = 0; i < 3; i++)
    {
        myfile >> score[i];
    }
    for(int i : score) cout << i << ' ';
    cout << endl;
    int n;
    cin >> n;
    if(n > score[0])
    {
        score[2] = score[1];
        score[1] = score[0];
        score[0] = n;
    }
    else if(n > score[1])
    {
        score[2] = score[1];
        score[1] = n;
    }
    else if(n > score[2])
    {
        score[2] = n;
    }
    myfile.close();
    myfile.open("data.txt", ios::out | ios::trunc);
    char c = ' ';
    for(int i = 0; i < 3; i++)
    {
        myfile << score[i];
        myfile << c;
    }
    myfile.close();
}
