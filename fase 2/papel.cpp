#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cin >> n;

    vector<pair<int, int>> montains{{0, -1}};
    montains.reserve(n + 2);


    auto check = [&](int x){
        montains.push_back({x, 
        montains.size() == 1 || x > montains.back().first ? 1 : -1
        });

        if (montains.size() < 3)
            return;

        int s = montains.size() - 1;

        auto [l, r] = minmax(montains[s].first, montains[s - 2].first);

        if (montains[s - 1].first != clamp(montains[s - 1].first, l, r))
            return;

        montains[s - 1].first = montains[s].first;
        montains.pop_back();
    };

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        check(x);
    }
    check(0);

    map<int, int, greater<int>> table;
    for (auto [height, isMontain] : montains)
        table[height] += isMontain;

    int m{1}, parts{1};

    for (auto [_, num] : table)
    {
        parts += num;
        m = max(m, parts);
    }
    cout << m;

    return 0;
}


// 10
//  20 5 10 5 15 15 15 5 6 22
//  20 5 10 5 15 5 6 22
