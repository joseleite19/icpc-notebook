bool isear (vec * p, int n, int i, int prev[], int next[]) { // aux to triangulate
	vec a = p[prev[i]], b = p[next[i]];
	if (b.ccw(a,p[i]) <= 0) return false;
	for (int j = 0; j < n; j++) {
		if (j == prev[i] || j == next[i]) continue;
		if (p[j].ccw(a,p[i]) >= 0 && p[j].ccw(p[i],b) >= 0 && p[j].ccw(b,a) >= 0) return false;
		int k = (j+1)%n;
		if (k == prev[i] || k == next[i]) continue;
		if (inter_seg(p[j],p[k],a,b)) return false;
	}
	return true;
}
int triangulate (vec * p, int n, bool ear[], int prev[], int next[], int tri[][3]) { // O(n^2) | n >= 3
	int s = 0, i = 0;
	for (int i = 0, prv = n-1; i < n; i++) { prev[i] = prv; prv = i; next[i] = (i+1)%n; ear[i] = isear(p,n,i,prev,next); }
	for (int lef = n; lef > 3; lef--, i = next[i]) {
		while (!ear[i]) i = next[i];
		tri[s][0] = prev[i]; tri[s][1] = i; tri[s][2] = next[i]; s++; // tri[i][0],i,tri[i][1] inserted
		int c_prev = prev[i], c_next = next[i];
		next[c_prev] = c_next; prev[c_next] = c_prev;
		ear[c_prev] = isear(p,n,c_prev,prev,next); ear[c_next] = isear(p,n,c_next,prev,next);
	}
	tri[s][0] = next[next[i]]; tri[s][1] = i; tri[s][2] = next[i]; s++; // tri[i][0],i,tri[i][1] inserted
	return s;
}

