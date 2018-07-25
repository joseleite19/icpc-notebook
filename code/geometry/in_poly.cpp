bool below(const vector<vec> &vet, vec p){
	auto it = lower_bound(vet.begin(), vet.end(), p);
	if(eq(it->x, p.x)) return p.y <= it->y;
	return prev(it)->cross(*it, p) <= 0;
}

bool above(const vector<vec> &vet, vec p){
	auto it = lower_bound(vet.begin(), vet.end(), p);
	if(eq(it->x, p.x)) return p.y >= it->y;
	return prev(it)->cross(*it, p) >= 0;
}

// lowerhull, upperhull and point
bool inside_poly(const vector<vec> &lo, const vector<vec> &hi, vec p){
	if(p.x < lo[0].x || lo.back().x < p.x)
		return false;
	
	return below(hi, p) && above(lo, p);
}
