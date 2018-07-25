multiset<int> S;
for(int i = 0; i < n; i++){
	auto it = S.upper_bound(a[i]); // low for inc
	if(it != S.end()) S.erase(it);
	S.insert(a[i]);
}
ans = S.size();
