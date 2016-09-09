#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>

#define LADO 800
#define SEG_LADO 1400000

using namespace std;

class Sgtree{
	private:
		int arv[SEG_LADO];
	public:
		int query(int L, int R, int D, int U, int l, int r, int d, int u, int p);
		void update(int L, int R, int D, int U, int pos_x, int pos_y, int num, int p);
		Sgtree(){memset(arv, 0, SEG_LADO<<2);};
}tipo_segtree;


typedef struct _sold{
	int x,y;
	bool pai;
}tipo_soldado;


int Sgtree::query(int L, int R, int D, int U, int l, int r, int d, int u, int p) {
	if(r < L || l > R || d > U || u < D)
		return 0;
	if(L >= l && R <= r && U <= u && D >= d){
		return arv[p];
	}
	int tmp1, tmp2, tmp3, tmp4; 
	tmp1 = query(L, (L+R)>>1, D, (U+D)>>1, l, r, d, u, (p<<2)+1);
	tmp2 = query(L, (L+R)>>1, ((U+D)>>1) + 1, U, l, r, d, u, (p<<2)+2);
	tmp3 = query(((L+R)>>1) + 1, R, D, (U+D)>>1, l, r, d, u, (p<<2)+3);
	tmp4 = query(((L+R)>>1) + 1, R, ((U+D)>>1) + 1, U, l, r, d, u, (p<<2)+4);

	tmp1 = max(tmp1, tmp2);
	tmp1 = max(tmp1, tmp3);
	return max(tmp1, tmp4); 
}

void Sgtree::update(int L, int R, int D, int U, int pos_x, int pos_y, int num, int p){
	if(L == R && U == D){
		arv[p] = num;
	}
	else{
		if(pos_x <= (L+R)>>1){
			if(pos_y <= (U+D)>>1)
				update(L, (L+R)>>1, D, (U+D)>>1, pos_x, pos_y, num, (p<<2)+1);
			else
				update(L, (L+R)>>1, ((U+D)>>1) + 1, U, pos_x, pos_y, num, (p<<2)+2);
		}
		else{
			if(pos_y <= (U+D)>>1)
				update(((L+R)>>1) + 1, R, D, (U+D)>>1, pos_x, pos_y, num, (p<<2)+3);
			else
				update(((L+R)>>1) + 1, R, ((U+D)>>1) + 1, U, pos_x, pos_y, num, (p<<2)+4);
		}
		int tmp1, tmp2;
		tmp1 = max(arv[(p<<2)+1], arv[(p<<2)+2]);
		tmp2 = max(arv[(p<<2)+3], arv[(p<<2)+4]);
		arv[p] = max(tmp1, tmp2);
	}
		
}
	
vector<int> G[50001];
Sgtree *tree;
tipo_soldado soldado[50001];
bool is_root[50001];
int ans = 1;
void dfs(int no){
	int tmp = tree->query(0, LADO, 0, LADO, 0 ,soldado[no].x-1, 0, soldado[no].y-1, 0);
	tmp++;
	tree->update(0, LADO, 0, LADO, soldado[no].x, soldado[no].y, tmp, 0);

	ans = max(ans, tmp);
	for(int j : G[no])
		dfs(j);
	tree->update(0, LADO, 0, LADO, soldado[no].x, soldado[no].y, 0, 0);
}


int main() {
	int N, M, i, j, no_pai, no_filho;
	tree = new Sgtree();
	
	scanf("%d %d", &N, &M);
	for(i = 1; i <= N; i++){
		scanf("%d", &soldado[i].x);
		scanf("%d", &soldado[i].y);
		soldado[i].x += 400;
		soldado[i].y += 400;
	}

	for(i = 1; i <= N; i++) is_root[i] = 1;
	for(i = 1; i <= M; i++){
		scanf("%d %d", &no_filho, &no_pai);
		G[no_pai].push_back(no_filho);
		is_root[no_filho] = 0;
	}

	for(i = 1; i <= N; i++){
		if(!is_root[i]) continue;
		if(!G[i].empty())
			dfs(i);
	}

	printf("%d\n", ans);
	return 0;
}
