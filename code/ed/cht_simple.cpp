struct Line{
    ll m, b;
    inline ll eval(ll x) const{
        return x * m + b;
    }
};

// min => cht.back().m >= L.m
// max => cht.back().m <= L.m
void push_line(vector<Line> &cht, Line L){
  while((int)cht.size() >= 2){
    int sz = (int)cht.size();
    if((long double)(L.b-cht[sz-1].b)*(cht[sz-2].m-L.m)
   <= (long double)(L.b-cht[sz-2].b)*(cht[sz-1].m-L.m)){
      cht.pop_back();
    }
    else break;
  }
  cht.push_back(L);
}

// x increasing; pos = 0 in first call
ll linear_search(const vector<Line> &cht,ll x,int &pos){
    while(pos+1 < (int)cht.size()){
/*>>*/  if(cht[pos].eval(x) >= cht[pos+1].eval(x)) pos++;
        else break;
    }
    return cht[pos].eval(x);
}

ll binary_search(const vector<Line> &cht, ll x){
    int L = 0, R = (int)cht.size()-2;
    int bans = (int)cht.size()-1;
    while(L <= R){
        int mid = (L+R)/2;
        if(cht[mid].eval(x) >= cht[mid+1].eval(x)) // <<<
            L = mid + 1;
        else bans = mid, R = mid - 1;
    }
    return cht[bans].eval(x);
}

