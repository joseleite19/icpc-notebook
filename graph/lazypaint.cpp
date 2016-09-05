#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define ff first
#define ss second

using namespace std;

vector<vector<bool> > mat;
vector<vector<int> > prox;

int n, m, h, w, q, r, c, total;

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};

void dfs(int x, int y){
	if(mat[x][y] == true) return;
	total--;
	mat[x][y] = true;
	
	int a, b;
	for(int i = 0; i < 4; i++){
		a = dx[i] + x;
		b = dy[i] + y;
		if(a < r || a >= r+h || b < c || b >= c+w) continue;
		dfs(a, b);
	}
}



int main(){
	
	scanf("%d %d %d %d %d", &n, &m, &h, &w, &q);
	mat.assign(n, vector<bool> (m, false));
	prox.assign(n, vector<int> (m, 1));
	
	total = n*m;
	
	for(int i = 0; i < q; i++){
		scanf("%d %d", &r, &c); r--; c--;
		for(int j = r; j < r+h; ){
			dfs(j, c);
			int tmp = prox[j][c];
			prox[j][c] = max(prox[j][c], r+h - j);
			j += tmp;
		}
		printf("%d\n", total);
	}
	

	return 0;
}