vector<vec> mk(const vector<vec>&a,const vector<vec>&b){
    int i = 0, j = 0;
    for(int k = 0; k < (int)a.size(); k++)if(a[k] <a[i])
        i = k;
    for(int k = 0; k < (int)b.size(); k++)if(b[k] <b[j])
        j = k;

    vector<vec> c;
    c.reserve(a.size() + b.size());
    for(int k = 0; k < int(a.size()+b.size()); k++){
        vec pt{a[i] + b[j]};
        if((int)c.size() >= 2
         && c[c.size()-2].ccw(c.back(), pt) == 0)
            c.pop_back();
        c.push_back(pt);
        int q = i+1, w = j+1;
        if(q == int(a.size())) q = 0;
        if(w == int(b.size())) w = 0;
        if(c.back().ccw(a[i]+b[w], a[q]+b[j]) < 0) i = q;
        else j = w;
    }
    c.shrink_to_fit();

    return c;
}
