//https://codeforces.com/contest/144/problem/D

#include <bits/stdc++.h>
#define F first
#define S second
#define SZ size()

using namespace std;
typedef long long ll;

int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

//--------------------------------------------------

const int MAX = 1e5 + 5;
const int INF = 0x3f3f3f3f;

vector <pair<int,int> > adj[MAX];


ll dist[MAX];
bool vis[MAX];
ll l;

void dijkstra(int soure) {

    memset(dist, INF, sizeof dist);
    
    dist[soure] = 0;
    set < pair<ll,ll> > s;
    s.insert({0, soure});

    pair<ll,ll> f;
    while(!s.empty()) {
        f = *s.begin();
        s.erase(s.begin());
        ll d = -f.F, u = f.S;

        if(vis[u]) continue;
        vis[u] = true;
        if(d > l) continue;

        for(auto e : adj[u]) {
            ll v = e.F, cost = e.S;
            if(!vis[v] && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                s.insert({dist[u]+cost, v});
            }
        }
    }
}

ll cnt = 0;

vector < vector<int> > edges;

int main(){

    int n = in(), m = in(), s = in();

    while(m--){
        int u = in(), v = in(), c = in();
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
        edges.push_back({u,v,c});
    }

    l = inll();
    dijkstra(s);

    for(int i=1; i<=n; i++) {
        if(dist[i] == l) cnt++;
    }

    for(auto e : edges) {
        ll u = e[0], v = e[1], c = e[2];
        ll x = l - dist[u], y =  l - dist[v];

        if(x > 0 && y > 0 && x < c && y < c && x + y == c) cnt++;
        else {

            if(x > 0 && x < c && c - x + dist[v] > l) cnt++;
            if(y > 0 && y < c && c - y + dist[u] > l) cnt++;

        }
    }

    printf("%lld\n", cnt);
}
