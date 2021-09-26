vector<int> preffix_function(const string &s){
	int n = s.size(); vector<int> b(n+1);
	b[0] = -1; int i = 0, j = -1;
	while(i < n){
		while(j >= 0 && s[i] != s[j]) j = b[j];
		b[++i] = ++j;
	}
	return b;
}
void kmp(const string &text, const string &p){
	vector<int> b = prefix_function(p);
	int m = p.size();
	int j = 0;
	for(char c : text){
		while(j >= 0 && c != p[j]) j = b[j];
		j++;
		if(j == m){
			//patern of p found on t
			j = b[j];
		}
	}
}
