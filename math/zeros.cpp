#include <bits/stdc++.h>

using namespace std;

int main(){
	vector<pair<int,int>> v(1000);

	for(int i = 1; i < 1000; i++){
		pair<int, int> last = {1, 1};
		int tmp = i;
		for(int j = 2; j*j <= tmp; j++){
			if(tmp % j == 0){
				last = {j, 0};
				while(tmp % j == 0){
					tmp /= j;
					last.second++;
				}
			}
		}
		if(tmp > 1){
			last = {tmp, 1};
		}
		v[i] = last;
	}

	int n, b;

	while(scanf("%d %d", &n, &b) == 2){
		double tmp1 = 0;
		for(int i = 1; i <= n; i++)
			tmp1 += log(i);
		int digits = 1 + (int)(tmp1 / log(b) + 1e-9);

		int tmp = v[b].first, count = 0;
		while(tmp <= n){
			count += n / tmp;
			tmp *= v[b].first;
		}

		int zeros = count / v[b].second;

		printf("%d %d\n", zeros, digits);
	}


	return 0;
}