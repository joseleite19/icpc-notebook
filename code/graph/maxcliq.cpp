long long adj[N], dp[N];

for(int i = 0; i < n; i++){
	for(int j = 0; j < n; j++){
		int x;
		scanf("%d",&x);
		if(x || i == j)
			adj[i] |= 1LL << j;
	}
}

int resto = n - n/2;
int C = n/2;
for(int i = 1; i < (1 << resto); i++){
	int x = i;
	for(int j = 0; j < resto; j++)
		if(i & (1 << j))
			x &= adj[j + C] >> C;
	if(x == i){
		dp[i] = __builtin_popcount(i);
	}
}

for(int i = 1; i < (1 << resto); i++)
	for(int j = 0; j < resto; j++)
		if(i & (1 << j))
			dp[i] = max(dp[i], dp[i ^ (1 << j)]);

int maxCliq = 0;
for(int i = 0; i < (1 << C); i++){
	int x = i, y = (1 << resto) - 1; 
	for(int j = 0; j < C; j++)
		if(i & (1 << j))
			x &= adj[j] & ((1 << C) - 1), y &= adj[j] >> C;
	if(x != i) continue;
	maxCliq = max(maxCliq, __builtin_popcount(i) + dp[y]);
}
