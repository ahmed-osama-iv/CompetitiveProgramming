/*
*   use dfs() to find the cycle
*   use dfs2() to find the distances from each vertex to the cycle
*/

#include <bits/stdc++.h>
#define F first
#define S second
#define SZ size()

using namespace std;
typedef long long ll;

int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int MAX = 1e4 + 5;
const int INF = 0x3f3f3f3f;

//--------------------------------------------------

vector <int> adj[MAX];
deque <int> cycle;

bool vis[MAX];
int dist[MAX];

bool found;

void dfs(int u, int p) {

    if(found) return;
    
    vis[u] = 1;
    cycle.push_back(u);

    for(int v : adj[u]) {
        if(v != p) {
            if(vis[v]) {
                if(!found) while(cycle.front() != v) cycle.pop_front();
                found = 1;
                return ;
            }

            else {
                dfs(v, u);
            }
        }
    }

    if(!found) cycle.pop_back();
}

void dfs2(int u, int p) {

    dist[u] = dist[p] + 1;

    for(int v : adj[u])
        if(dist[v] == -1) dfs2(v, u);

}

int main() {

    int n = in();
    for(int i=0; i<n; i++) {
        int u = in(), v = in();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);

    memset(dist, -1, sizeof dist);

    for(auto x : cycle){
        dist[x] = 0;
    }

    for(auto x : cycle){
        dfs2(x, 0);
    }

    for(int i=1; i<=n; i++){
        printf("%d ", dist[i]);
    }
}

