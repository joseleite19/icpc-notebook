void init_aho(){
	queue<int> q;
	
	q.push(0);

	while(!q.empty()){
		int t = q.front(); q.pop();

		for(int i = 0; i < 52; i++) if(trie[t][i]){
			int x = trie[t][i];
			Q.push(x);

			if(t){
				fn[x] = fn[t];

				while(fn[x] && trie[fn[x]][i] == 0) fn[x] = fn[fn[x]];
				if(trie[fn[x]][i]) fn[x] = trie[fn[x]][i];
			}
		}
	}
}

