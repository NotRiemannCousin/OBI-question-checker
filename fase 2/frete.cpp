#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 123456;


typedef pair<int, int> pii;
int main(){

    int n, m;
    cin >> n >> m;

    vector<int> dist(n+1, INF);
    vector<vector<pii>> weights(n+1);

    while(m--){
        int a, b, c;
        cin >> a >> b >> c;

        weights[a].push_back({b, c});
        weights[b].push_back({a, c});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 1});

    while(!pq.empty()){
        auto [weight, from] = pq.top();
        pq.pop();

        if(dist[from] <= weight)
            continue;

        dist[from] = weight;

        for(auto [to, weight2] : weights[from])
        {
            if(dist[from] + weight2 < dist[to])
                pq.push({dist[from] + weight2, to});
        }
    }
    cout << dist[n];
}
