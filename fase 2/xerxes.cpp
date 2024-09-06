#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    int score[2] {};

    cin >> n;

    while (n--)
    {
        int d, x;
        cin >> d >> x;

        x += 5;
        score[(x+1) % 5 == d || (x+2) % 5 == d]++;
    }

    if(score[0] > score[1])
        cout << "dario";
    else
        cout << "xerxes";

}
