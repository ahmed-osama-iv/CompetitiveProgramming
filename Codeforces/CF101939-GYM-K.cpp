#include <bits/stdc++.h>
using namespace std;

int in(){int a; scanf("%d", &a); return a;}

const int MAX = 2e5 + 5;

int sz[MAX];
set <int> s[MAX];
vector <int> adj[MAX];

//---------------------------------------------

int n, ans = MAX;

void upd (int a, int b, int c){
    //cout << a << " " << b << " " << c << endl;
	ans = min( ans, max( a, max(b, c) ) - min( a, min(b, c) ) );
}

void dfs(int v, int p){

    sz[v] = 1;
    int big = 0;

    for(int to : adj[v]){
        if(to == p) continue;

        dfs(to, v);
        sz[v] += sz[to];
        if(sz[to] > sz[big]) big = to;

        auto t1 = s[to].lower_bound((sz[to] + 1) / 2);

        if(t1 != s[to].end()) upd(*t1, sz[to] - *t1, n - sz[to]);
        if(t1 != s[to].begin()){
            t1--;
            upd(*t1, sz[to] - *t1, n - sz[to]);
        }
    }

    if(big){
        swap(s[v], s[big]);

        for(int to : adj[v]){
            if(to == p || to == big) continue;

            for(int t1 : s[to]){

                auto t2 = s[v].lower_bound((n - t1 + 1) / 2);
                if(t2 != s[v].end()) upd(t1, *t2, n - t1 - *t2);
                if(t2 != s[v].begin()){
                    t2--;
                    upd(t1, *t2, n - t1 - *t2);
                }
            }
        }

        for(int to : adj[v]){
            if(to == p || to == big) continue;

            for(int t1 : s[to]){
                s[v].insert(t1);
            }
        }

    }
    
    s[v].insert(sz[v]);

}

int main()
{
    n = in();
    for(int i=0; i<n-1; i++){
        int u = in(), v = in();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    cout << ans << endl;
    return 0;
}

