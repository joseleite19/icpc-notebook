// intersection of line a * x + b * y + c = 0
// and circle centered at the origin with radius r
double r, a, b, c; // given as input
double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
if(c*c > r*r*(a*a+b*b)+EPS)
    puts("no points");
else if(abs(c*c - r*r*(a*a+b*b)) < EPS){
    puts("1 point");
    cout << x0 << ' ' << y0 << '\n';
}
else {
    double d = r*r - c*c/(a*a+b*b);
    double mult = sqrt (d / (a*a+b*b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    puts ("2 points");
    cout<<ax<<' '<<ay<<'\n'<<bx<<' '<<by<<'\n';
}
