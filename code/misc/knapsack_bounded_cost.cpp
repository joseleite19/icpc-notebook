// menor custo para conseguir peso ate M usando N tipos diferentes de elementos, sendo que o i-esimo elemento pode ser usado b[i] vezes, tem peso w[i] e custo c[i]
// O(N * M)

int b[N], w[N], c[N];
MinQueue Q[M]
int d[M] //d[i] = custo minimo para conseguir peso i

for(int i = 0; i <= M; i++) d[i] = i ? oo : 0;
for(int i = 0; i < N; i++){
	for(int j = 0; j < w[i]; j++)
		Q[j].clear();
	for(int j = 0; j <= M; j++){
		q = Q[j % w[i]];
		if(q.size() >= q) q.pop();
		q.add(c[i]);
		q.push(d[j]);
		d[j] = q.getmin();
	}
}
