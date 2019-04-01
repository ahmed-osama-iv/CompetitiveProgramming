#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int LOG = 32;
const int MAX = 1e5 + 5;
const ll INF = 1e18;

struct node{

    int val, lazy=0;
    int st, ed;
    node *left=0, *right=0;

    node(int Start, int End, int Value){
        st=Start, ed=End, val=Value;
    }

    void extend(){
        if(!left && st != ed){
            int m = (st + ed) >> 1;
            left = new node(st, m, 0);
            right = new node(m+1, ed, 0);
        }
    }

    void propagate(){
        if(lazy == -1) return;
        extend();
        if(left){
            left->lazy = lazy;
            right->lazy = lazy;
        }
        val = lazy;
        lazy = -1;
    }

    int get(int idx){
        return get(idx, idx);
    }

    int get(int l, int r){
        if (r < st || l > ed) return 0;
        propagate();
        if (l <= st && r >= ed) return val;
        return max(left->get(l, r) , right->get(l, r));
    }

    void update(int idx, int v){
        update(idx, idx, v);
    }

    void update(int l, int r, int v){
        propagate();
        if (r < st || l > ed) return;
        if (l <= st && r >= ed){
            lazy = v;
            propagate();
            return;
        }
        left->update(l, r, v) , right->update(l, r, v);
        val = max(left->val , right->val);
    }

};

node *increasing_segTree[MAX];
node *decreasing_segTree[MAX];

vector <int> adj[MAX];
int sz[MAX];

int res = 1;

void update_res(int a){
    if(a == -1) res = 1;
    else res = max(res, a);
}

void dfs_for_size(int u, int p){

    for(int v : adj[u]){
        if(v != p){
            dfs_for_size(v, u);
            sz[u] += sz[v];
        }
    }

    sz[u]++;
}

stack <pair<int, int> > stk_increasing, stk_decreasing;

void update(int u, int firstChild, int calledFrom, int p){

    int small_increasing_val = increasing_segTree[firstChild]->get(u);
    int small_decreasing_val = decreasing_segTree[firstChild]->get(u);

    int big_increasing_val = increasing_segTree[calledFrom]->get(u,MAX);
    int big_decreasing_val = decreasing_segTree[calledFrom]->get(1 , u);

    update_res(small_decreasing_val + big_increasing_val);
    update_res(small_increasing_val + big_decreasing_val);

    stk_increasing.push({u, small_increasing_val});
    stk_decreasing.push({u, small_decreasing_val});

    for(int v : adj[u]){
        if(v != p) update(v, firstChild, calledFrom, u);
    }

}

void solve(int u, int p){

    int myBigChild = 0;

    for(int v : adj[u]){
        if(v != p && sz[v] > sz[myBigChild]) myBigChild = v;
    }

    if(myBigChild){

        solve(myBigChild, u);
        increasing_segTree[u] = increasing_segTree[myBigChild];
        decreasing_segTree[u] = decreasing_segTree[myBigChild];

        int increasing_val = increasing_segTree[u]->get(u, MAX);
        increasing_segTree[u]->update(u, increasing_val + 1);
        update_res(increasing_val + 1);

        int decreasing_val = decreasing_segTree[u]->get(1, u);
        decreasing_segTree[u]->update(u, decreasing_val + 1);
        update_res(decreasing_val + 1);

        for(int v : adj[u]){

            if(v != p && v != myBigChild){
                solve(v, u);
                update(v, v, u, u);

                while(!stk_increasing.empty()){
                    pair <int,int> top_increasing = stk_increasing.top();
                    pair <int,int> top_decreasing = stk_decreasing.top();

                    increasing_segTree[u]->update(top_increasing.first, top_increasing.second);
                    decreasing_segTree[u]->update(top_decreasing.first, top_decreasing.second);

                    stk_increasing.pop();
                    stk_decreasing.pop();
                }

                increasing_val = increasing_segTree[u]->get(u+1, MAX);
                increasing_segTree[u]->update(u, increasing_val + 1);
                update_res(increasing_val + 1);

                decreasing_val = decreasing_segTree[u]->get(1, u-1);
                decreasing_segTree[u]->update(u, decreasing_val + 1);
                update_res(decreasing_val + 1);

            }

        }



    }else{

        increasing_segTree[u] = new node(1, MAX, 0);
        increasing_segTree[u]->update(u, 1);

        decreasing_segTree[u] = new node(1, MAX, 0);
        decreasing_segTree[u]->update(u, 1);
    }
}

int main()
{

    int T = in();
    while(T--){

        update_res(-1);
        memset(sz, 0, sizeof sz);
        for(int i=0; i<MAX; i++){
            adj[i].clear();
            increasing_segTree[i] = NULL;
            decreasing_segTree[i] = NULL;
        }

        int n = in() - 1;
        while(n--){
            int u = in(), v = in();
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs_for_size(1, 0);

        solve(1, 0);
        printf("%d", res);
        if(T!=0) printf("\n");

    }
}

