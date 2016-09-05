#include <bits/stdc++.h>

#define ff first
#define ss second
#define mp make_pair
#define oo 1000000000

using namespace std;

int n, k, mat[300005][26], ans;

int dfs(int u){
	int ret = oo;
	ans++;

	for(int i = 0; i < 26; i++){
		if(mat[u][i]){
			ret = min(ret, dfs(mat[u][i]));
		}
	}
	if(ret == oo){
		ret = 0;
		ans++;
	}
	ret++;
	if(ret > k){
		ans++;
		ret = 1;
	}
	return ret;
}

int main(){

	scanf("%d %d", &n, &k);

	char s[100005];

	int ptr = 1;

	for(int i = 0; i < n; i++){
		scanf(" %s", s);
		int node = 0;
		for(int j = 0; s[j]; j++){
			int letra = s[j]-'a';
			if(!mat[node][letra])
				mat[node][letra] = ptr++;
			node = mat[node][letra];
		}
	}

	for(int i = 0; i < 26; i++)
		if(mat[0][i])
			dfs(mat[0][i]);

	ans += n;

	printf("%d\n", ans);

	return 0;
}