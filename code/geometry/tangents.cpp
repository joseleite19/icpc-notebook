// solve first for same circle(and infinitely many tangents)
// Find up to four tangents of two circles
void tangents(pt c, double r1, double r2, vector<line> & ans){
    double r = r2 - r1;
    double z = c.x * c.x + c.y * c.y;
    double d = z - r * r;
    if(d < -EPS) return;
    d = sqrt(abs(d));
    line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back (l);
}

vector<line> tangents(circle a, circle b){
    vector<line> ans;
    pt aux = a.center - b.center;
    for(int i = -1; i <= 1; i += 2)
        for(int j = -1; j <= 1; j += 2)
            tangents(aux, a.r * i, b.r * j, ans);
    for(size_t i = 0; i < ans.size(); ++i)
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
    return ans;
}
