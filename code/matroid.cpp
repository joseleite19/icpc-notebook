// Input two matroids (X, I_a) and (X, I_b)
// output set I of maximum size, I \in I_a and I \in I_b
set<> I;
while(1){
    for(e_i : X \ I)
        if(I + e_i \in I_a and I + e_i \in I_b)
            I = I + e_i;
    set<> A, T; queue<> Q;
    for(x : X) label[x] = MARK1;
    for(e_i : X \ I){
        if(I + e_i \in I_a)
            Q.push(e_i), label[e_i] = MARK2;
        else{
            for(x such that I - x + e_i \in I_a)
                A[x].push(e_i);
        }
        if(I + e_i \in I_b)
            T = T + {e_i}
        else{
            for(x such that I - x + e_i \in I_b)
                A[e_i].push(x);
        }
    }
    if(T.empty()) break;
    bool found = false;
    while(!Q.empty() and !found){
        auto e = Q.front(); Q.pop();
        for(x : A[e]) if(label[x] == MARK1){
            label[x] = e; Q.push(x);
            if(x \in T){
                found = true; put = 1;
                while(label[x] != MARK2){
                    I = put ? (I + x) : (I - x);
                    put = 1 - put;
                }
                I = I + x;
                break;
            }
        }
    }
    if(!found) break;
}
return I;
