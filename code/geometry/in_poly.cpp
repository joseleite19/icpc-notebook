bool below(const vector<vec> &vet, vec p){
	auto it = lower_bound(vet.begin(), vet.end(), p);
    if(it == vet.end()) return false;
	if(it == vet.begin()) return *it == p;
	return prev(it)->cross(*it, p) <= 0;
}

bool above(const vector<vec> &vet, vec p){
	auto it = lower_bound(vet.begin(), vet.end(), p);
    if(it == vet.end()) return false;
	if(it == vet.begin()) return *it == p;
	return prev(it)->cross(*it, p) >= 0;
}

// lowerhull, upperhull and point, borders included
bool inside_poly(const vector<vec> &lo, const vector<vec> &hi, vec p){
	return below(hi, p) && above(lo, p);
}
