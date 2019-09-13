
CERC 17 K
int n;
int best[N], dp[2][N][N][7], qtd[10], v[5];
int main(){
    scanf("%d", &n);
    char s[20];
    char aux[20];
    int ant = 0;
    for(int i = 0; i < n; i++){
        scanf("%s", s);
        strcpy(aux, s);
        int sz = strlen(s);
        best[i] = 0;
        for(int j = 0; j < 6; j++){
            s[sz] = s[j];
            sz++;
            s[sz] = 0;
            if(strcmp(s + j + 1, aux) > 0){
                strcpy(aux, s + j + 1);
                best[i] = j + 1;
            }
            else if(strcmp(s + j + 1, aux) == 0){
                best[i] = -1;
                break;
            }
        }
        if(best[i] == -1){
            i--, n--;
            continue;
        }
        qtd[(best[i] - ant + 7) % 7]++;;
        ant = best[i];
    }
    int ans = 0;
    ans += qtd[0];
    ans += min(qtd[1], qtd[6]);
    ans += min(qtd[2], qtd[5]);
    ans += min(qtd[3], qtd[4]);
    for(int i = 1; i <= 3; i++){
        if(qtd[i] >= qtd[7-i]){
            qtd[i] -= qtd[7-i];
            v[i-1] = i;
        }
        else{
            qtd[7-i] -= qtd[i];
            v[i-1] = 7-i;
        }
    }
    for(int q0 = 0; q0 <= qtd[v[0]]; q0++){
        bool q = q0 & 1;
        for(int q1 = 0; q1 <= qtd[v[1]]; q1++){
            for(int q2 = !q0; q2 <= qtd[v[2]]; q2++){
                for(int sum = 0; sum <= 6; sum++){
                    int &a = dp[q][q1][q2][sum];
                    a = 0;
                    if(q0)
                        a = max(a, dp[!(q)][q1][q2][(sum + v[0]) % 7] + !((sum + v[0]) % 7));
                    if(q1)
                        a = max(a, dp[q][q1-1][q2][(sum + v[1]) % 7] + !((sum + v[1]) % 7));
                    if(q2)
                        a = max(a, dp[q][q1][q2-1][(sum + v[2]) % 7] + !((sum + v[2]) % 7));
                }
            }
        }
    }
    printf("%d\n", n - ans - dp[qtd[v[0]]&1][qtd[v[1]]][qtd[v[2]]][0]);
    return 0;
}
 