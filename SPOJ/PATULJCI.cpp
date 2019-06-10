/*
    we try random elements in the range with the probablity of getting a wrong answer<0.5^no. of try.
    refrence : https://pastebin.com/FUPaCXTF
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int MAX_N = 3e5 + 5; // max array length
const int MAX_C = 1e5 + 5; // max number of colors
const int MAX_Q = 1e5 + 5; // max number of queries

int N, C, Q;
int a[MAX_N];

vector <int> indices[MAX_C];

int getFrq(int color, int l, int r){
    return upper_bound(indices[color].begin(), indices[color].end(), r)
         - lower_bound(indices[color].begin(), indices[color].end(), l);
}

int main()
{

    srand(time(NULL));

    N = in(), C = in();
    for(int i=1; i<=N; i++){
        a[i] = in();
        indices[a[i]].push_back(i);
    }

    Q = in();
    while(Q--){
        int l = in(), r = in(), length = r-l+1;
        bool flag = 0;

        for(int i=0; i<100; i++){
            int randColor = a[l + rand()%length];
            if(getFrq(randColor, l, r) > length/2){
                printf("yes %d\n", randColor);
                flag = 1;
                break;
            }
        }

        if(!flag) printf("no\n");
    }
}
