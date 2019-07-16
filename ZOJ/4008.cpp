#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;

vector <int> tree[5*MAXN];
int A[MAXN];

void build_tree(int cur ,int l ,int r){

     if(l == r){
        tree[cur].push_back(A[l]);
        return;
     }

     int mid = l+(r-l)/2;
     build_tree(2*cur+1, l, mid ); // Build left tree
     build_tree(2*cur+2, mid+1, r ); // Build right tree
     tree[cur].resize(tree[2*cur+1].size() +  tree[2*cur+2].size());
     merge(tree[2*cur+1].begin(), tree[2*cur+1].end(), tree[2*cur+2].begin(), tree[2*cur+2].end(), tree[cur].begin()); //Merging the two sorted arrays
}

// cur = 0, l = 0, r = MAXN
// how many number within indices [x,y] <= k
int query(int cur, int l, int r, int x, int y, int k){

    if(r < x || l > y){
        return 0; //out of range
    }

    if(x <= l && r <= y){
        //Binary search over the current sorted vector to find elements smaller than K
        return upper_bound(tree[cur].begin(),tree[cur].end(),k)-tree[cur].begin();
    }

    int mid = l + (r-l) / 2;
    return query(2*cur+1, l, mid, x, y, k) + query(2*cur+2, mid+1, r, x, y, k);
}

pair <int,int> edge[MAXN];

int main() {

    int T;
    scanf("%d", &T);

    while(T--){

        for(int i=0; i<5*MAXN; i++){
            tree[i].clear();
        }

        int n, q;
        scanf("%d %d", &n, &q);

        for(int i=0; i<n-1; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            edge[i] = make_pair(u, v);
        }

        sort(edge, edge + n - 1);
        for(int i=0; i<n-1; i++){
            A[i] = edge[i].second;
        }
        build_tree(0, 0, n-2);

        while(q--){
            int l, r;
            scanf("%d %d", &l, &r);
            int x = lower_bound(edge, edge+n-1, make_pair(l, 0)) - edge;
            int y = lower_bound(edge, edge+n-1, make_pair(r+1, 0)) - edge - 1;
            int e = query(0, 0, n-2, x, y, r) - query(0, 0, n-2, x, y, l-1);
            printf("%d\n", (r-l+1) - e);
        }
    }
}
