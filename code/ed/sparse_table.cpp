int fn(int i, int j){
	if(j == 0) return v[i];
	if(~dn[i][j]) return dn[i][j];
	return dn[i][j] = min(fn(i, j-1), fn(i + (1 << (j-1)), j-1));
}

int getmn(int l, int r){ // [l, r]
	int lz = lg(r - l + 1);
	return min(fn(l, lz), fn(r - (1 << lz) + 1, lz));
}
