int n;
long double a[n][n];

long double gauss(){
    long double det = 1;
    for(int i = 0; i < n; i++){
        int q = i;
        for(int j = i+1; j < n; j++){
            if(abs(a[j][i]) > abs(a[q][i]))
                q = j;
        }
        if(abs(a[q][i]) < EPS){
            det = 0;
            break;
        }
        if(i != q){
            for(int w = 0; w < n; w++)
                swap(a[i][w], a[q][w]);
            det = -det;
        }
        det *= a[i][i];
        for(int j = i+1; j < n; j++) a[i][j] /= a[i][i];

        for(int j = 0; j < n; j++) if(j != i){
            if(abs(a[j][i]) > EPS)
                for(int k = i+1; k < n; k++)
                    a[j][k] -= a[i][k] * a[j][i];
        }
    }

    return det;
}
