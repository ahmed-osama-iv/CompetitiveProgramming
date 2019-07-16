#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5 + 5;
const int MOD = 99971;

//---------------------------------------------------------

struct Node{

    int lazy=0;
    ll arr[48];
    int st, ed;

};

Node node[1<<18];

void propagate(int i){
    if(i <= 1<<17){
        node[2*i].lazy += node[i].lazy;
        node[2*i+1].lazy += node[i].lazy;

        node[2*i].lazy %= 48;
        node[2*i+1].lazy %= 48;
    }

    rotate(node[i].arr, node[i].arr + node[i].lazy%48, node[i].arr + 48);
    node[i].lazy = 0;
}

int get(int i, int l, int r){
    if (r < node[i].st || l > node[i].ed) return 0;
    propagate(i);
    if (l <= node[i].st && r >= node[i].ed) return node[i].arr[0];
    return (get(2*i, l, r) + get(2*i+1, l, r)) % MOD;
}

void update(int i, int l, int r){
    propagate(i);
    if (r < node[i].st || l > node[i].ed) return;
    if (l <= node[i].st && r >= node[i].ed){
        node[i].lazy = (node[i].lazy + 1) % 48;
        propagate(i);
        return;
    }
    update(2*i, l, r) , update(2*i+1, l, r);
    for(int j = 0; j < 48; j++){
        node[i].arr[j] = (node[2*i].arr[j] + node[2*i+1].arr[j]) % MOD;
    }
}


int main(){

    int T;
    scanf("%d", &T);

    while(T--){

        int n, q;
        scanf("%d %d", &n, &q);

        for(int i = 0; i < n; i++){
            int a;
            scanf("%d", &a);
            node[(1<<17) + i].arr[0] = a % MOD;
            for(int j = 1; j < 48; j++){
                node[(1<<17) + i].arr[j] = node[(1<<17) + i].arr[j-1] * node[(1<<17) + i].arr[j-1] % MOD * node[(1<<17) + i].arr[j-1] % MOD;
            }
        }

        for(int i = (1<<17); i < (1<<18); i++){
            node[i].st = i - (1<<17);
            node[i].ed = i - (1<<17);
            node[i].lazy = 0;
        }

        //-----------Build--------------------
        for(int i = (1<<17)-1; i >= 1; i--){
            node[i].st = node[2*i].st;
            node[i].ed = node[2*i+1].ed;
            node[i].lazy = 0;
            for(int j = 0; j < 48; j++){
                node[i].arr[j] = (node[2*i].arr[j] + node[2*i+1].arr[j]) % MOD;
            }
        }

        while(q--){
            int t, l, r;
            scanf("%d %d %d", &t, &l, &r);

            if(t == 1){
                update(1, l-1, r-1);
            }else{
                printf("%d\n", get(1, l-1, r-1));
            }

        }

    }
    
    return 0;
}
