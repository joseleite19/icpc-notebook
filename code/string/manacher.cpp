// odd[i] = largest palindrome with center in character i(0-based)
// even[i] = largest palindrome with center between chars i-1 and i(0-based)
// pair<even, odd>
pair<vector<int>, vector<int>> build(const string &s){ // O(n)
	int n = (int)s.size();
	vector<int> vet[2];

	for(int add = 0; add < 2; add++){
		vet[add].resize(n);
		for(int i = 0, l = 0, r = -1; i < n; i++){
			int k = i > r ? add : min(vet[add][l + r - i + !add], r - i + !add);
			while(i - k - !add >= 0 && i + k < n && s[i - k - !add] == s[i + k]) k++;
			vet[add][i] = k--;
			if(i + k > r){
				r = i + k;
				l = i - k - !add;
			}
		}
	}
	
	return make_pair(vet[0], vet[1]);
}
