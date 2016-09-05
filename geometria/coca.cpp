#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    int c, n, l, b, H, i;
    double B, h, sup, inf, mid, bb, v;

    scanf("%d", &c);

    while(c--){
        scanf("%d %d %d %lf %d", &n, &l, &b, &B, &H);

        sup = H;
        inf = 0;

        while(sup - inf > 1e-9){
            mid = (sup + inf) / 2;

            bb = b + (B - b)*mid/sup;

            v = (M_PI*mid*(bb*bb + bb*b+ b*b))/3;
            if(v*n > l){
                sup = mid;
                B = bb;
            }
            else inf = mid;
        }
        printf("%.2lf\n", sup);
    }

    return 0;
}
// r*r = B*B*H/h

// H/(R-r) = h/(R1-r)
// R1-r = (R-r)*h/H
// R1 = r + (R-r)*h/H