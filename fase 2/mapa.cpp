#include <bits/stdc++.h>
using namespace std;

int main()
{
    int l, c;

    int x, y;

    

    cin >> l >> c;
    vector<vector<bool>> grid /*     */ (l, vector<bool>(c, true));
    vector<vector<char>> neighbors /**/ (l, vector<char>(c));

    auto updateNeighbors = [&](int b, int a) -> void
    {
        if (
            a < 0 || a >= c ||
            b < 0 || b >= l)
            return;
        neighbors[b][a]++;
    };


    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
        {
            char c;
            cin >> c;

            switch (c)
            {
                case '.':
                    grid[i][j] = false;
                    break;
                case 'o':
                    x = j, y = i;
                case 'H':
                    updateNeighbors(i, j - 1);
                    updateNeighbors(i, j + 1);
                    updateNeighbors(i - 1, j);
                    updateNeighbors(i + 1, j);
            }
        }

    function<bool(int, int)> dfs;
    
    dfs = [&](int a, int b) -> bool
    {
        if (
            a < 0 || a >= c ||
            b < 0 || b >= l ||
            !grid[b][a]
        )
            return false;
        
        grid[b][a] = false;

        if (neighbors[b][a] == 1)
        {
            x = a, y = b;
            return true;
        }
        return dfs(a, b - 1) ||
                dfs(a, b + 1) ||
                dfs(a - 1, b) ||
                dfs(a + 1, b);
    };
    
    neighbors[y][x]++;
    dfs(x, y);

    cout << ++y << " " << ++x << endl;

    return 0;
}