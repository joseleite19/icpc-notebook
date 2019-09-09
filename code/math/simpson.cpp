inline double simpson(double fl,double fr,double fmid,double l,double r) {
	return (fl + fr + 4.0 * fmid) * (r - l) / 6.0;
}
double rsimpson(double slr,double fl,double fr,double fmid,double l,double r) {
	double mid = (l+r)*0.5;
	double fml = f((l+mid)*0.5), fmr = f((mid+r)*0.5);
	double slm = simpson(fl, fmid, fml, l, mid);
	double smr = simpson(fmid, fr, fmr, mid, r);
	if(fabs(slr-slm-smr) < eps and r - l < delta) return slr;
	return rsimpson(slm,fl,fmid,fml,l,mid) + rsimpson(smr,fmid,fr,fmr,mid,r);
}
double integrate(double l,double r) {
	double mid = (l+r)*0.5;
	double fl = f(l), fr = f(r), fmid = f(mid);
	return rsimpson(simpson(fl,fr,fmid,l,r),fl,fr,fmid,l,r);
}
