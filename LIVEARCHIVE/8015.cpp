/*
    insert all Bob's strings in a Trie
    then for each Alice's strings find the maximum prefix length
    that can be reached by Bob's strings 
    calculated using no.occurances of its prefixes
*/

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

vector <int> temp;

struct Trie {

    static const char first = 'a';
    static const int MAX_CHAR = 26; //if MAX_CHAR is big range but not all values are used, use a map instead of static array
	int times, isLeaf;
	Trie* child[MAX_CHAR];


	Trie() {
	    times=0;
		memset(child, 0, sizeof(child));
		isLeaf = 0;
	}

	void insert(char * str) { // reference to the current char in the char sequence starting at str;
	    times++;
		if(*str == '\0') { // end of char sequence
            isLeaf++;
            return;
		}
        int cur = *str-first;
		if(child[cur] == 0) { // have no child;
			child[cur] = new Trie();
		}

		child[cur]->insert(str+1);
	}

	int freq_of_prefex(char * str) {

        if(*str == '\0')
            return times; // end of char seq
        int cur = *str-first;
        if(child[cur]!=0) { // have childes;
            temp.push_back(child[cur]->times);
            return child[cur]->freq_of_prefex(str+1);
        }
        return 0;
	}
};

Trie trie;

vector <string> vec;
char s[MAX];

int main(){

    int n, m;

    while(scanf("%d%d", &n, &m) == 2) {

        trie = *new Trie;
        vec.clear();

        for(int i=0; i<n; i++) {
            scanf("%s", s);
            vec.push_back(string(s));
        }

        for(int i=0; i<m; i++) {
            scanf("%s", s);
            trie.insert(s);
        }

        ll sum = 0;
        for(string ss : vec) {
            temp.clear();
            strcpy(s, ss.c_str());
            trie.freq_of_prefex(s);

            int len = temp.SZ;

            for(int i = 0; i < temp.SZ; i++){
                len = min(len, temp[i] + i);
            }
            sum += len;
        }

        printf("%lld\n", sum);
    }
}
