#include <bits/stdc++.h>

#define ff first
#define ss second
#define mp make_pair

using namespace std;

typedef long long ll;

int trie[1000005][52], fn[1000005];
int ptr;
bool passou[1000005];
vector<int> final_vec;

int insert(char *str){
	int v = 0;
	
	for(int i = 0; str[i]; i++){
		int to = str[i] >= 'a' ? str[i]-'a'+26 : str[i]-'A';
		if(trie[v][to])
			v = trie[v][to];
		else
			v = trie[v][to] = ptr++;
	}

	return v;
}

void init_aho(){
	queue<int> Q;
	
	Q.push(0);

	while(!Q.empty()){
		int t = Q.front(); Q.pop();

		for(int i = 0; i < 52; i++){
			if(trie[t][i]){
				int x = trie[t][i];
				Q.push(x);

				if(t){
					fn[x] = fn[t];

					while(fn[x] && trie[fn[x]][i] == 0) fn[x] = fn[fn[x]];
					if(trie[fn[x]][i]) fn[x] = trie[fn[x]][i];
					trie[x][i] = fn[x];
				}
			}
		}
	}
}

int main(){
	int t,q;
	char s[100005], s2[1005];

	scanf("%d", &t);
	while(t--){
		scanf(" %s", s);

		memset(trie, 0, sizeof trie);
		memset(passou, 0, sizeof passou);
		memset(fn, 0, sizeof fn);
		final_vec.clear();

		ptr = 1;
		
		scanf("%d", &q);
		
		// build trie
		while(q--){
			scanf(" %s", s2);
			final_vec.push_back(insert(s2));
		}

		// build failures
		init_aho();

		// simulate
		int v = 0;
		for(int i = 0; s[i]; i++){
			int to = s[i] >= 'a' ? s[i]-'a'+26 : s[i]-'A';
			v = trie[v][to];
			else{
				while(v){
					v = fn[v];
					passou[v] = 1;
					if(trie[v][to]){
						v = trie[v][to];
						break;
					}
				}
			}
			passou[v] = 1;
		}

		for(int i = 0; i < final_vec.size(); i++){
			if(passou[final_vec[i]]) printf("y\n");
			else printf("n\n");
		}
	}

	return 0;
}