// borders included
// must not have 3 colinear consecutive points
bool inside_poly(const vector<vec> &v, vec p){
    if(v[0].ccw(v[1], p) < 0) return false;
    if(v[0].ccw(v.back(), p) > 0) return 0;
    if(v[0].ccw(v.back(), p) == 0)
        return v[0].dot(p, v.back()) >= 0
            && v.back().dot(p, v[0]) >= 0;

    int L = 1, R = (int)v.size() - 1, ans = 1;

    while(L <= R){
        int mid = (L+R)/2;
        if(v[0].ccw(v[mid], p) >= 0) ans = mid, L = mid+1;
        else R = mid-1;
    }

    return v[ans].ccw(v[(ans+1)%v.size()], p) >= 0;
}
