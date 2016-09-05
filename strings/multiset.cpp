#include <bits/stdc++.h>

#define oo 1000000000000000000

using namespace std;

int mat[6400640][2];
int cnt[6400640][2];

int main(){
	int n, x, ptr, next = 1;
	char c;

	scanf("%d", &n);

	ptr = 0;
	for(int i = 30; i >= 0; i--){
		if(!mat[ptr][0]) mat[ptr][0] = next++;
		cnt[ptr][0]++;
		ptr = mat[ptr][0];
	}

	for(int i = 0; i < n; i++){
		scanf(" %c %d", &c, &x);

		if(c == '+'){
			ptr = 0;
			for(int i = 30; i >= 0; i--){
				if((1 << i) & x){
					if(!mat[ptr][1]) mat[ptr][1] = next++;
					cnt[ptr][1]++;
					ptr = mat[ptr][1];
				}
				else{
					if(!mat[ptr][0]) mat[ptr][0] = next++;
					cnt[ptr][0]++;
					ptr = mat[ptr][0];
				}
			}
		}
		else if(c == '-'){
			ptr = 0;
			for(int i = 30; i >= 0; i--){
				if((1 << i) & x){
					cnt[ptr][1]--;
					ptr = mat[ptr][1];
				}
				else{
					cnt[ptr][0]--;
					ptr = mat[ptr][0];
				}
			}
		}
		else{
			int ans = 0;
			ptr = 0;
			for(int i = 30; i >= 0; i--){
				if((1 << i) & x){
					if(cnt[ptr][0] > 0){
						ans += (1 << i);
						ptr = mat[ptr][0];
					}
					else ptr = mat[ptr][1];
				}
				else{
					if(cnt[ptr][1] > 0){
						ans += (1 << i);
						ptr = mat[ptr][1];
					}
					else ptr = mat[ptr][0];
				}
			}
			printf("%d\n", ans);
		}
	}

	return 0;
}