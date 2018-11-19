typedef double cod;
double eps = 1e-7;
bool eq(cod a, cod b){ return abs(a - b) <= eps; }

struct vec{
	cod x, y; int id;
	vec(cod a = 0, cod b = 0) : x(a), y(b) {}
	vec operator+(const vec &o) const{
		return {x + o.x, y + o.y};
	}
	vec operator-(const vec &o) const{
		return {x - o.x, y - o.y};
	}
	vec operator*(cod t) const{
		return {x * t, y * t};
	}
	vec operator/(cod t) const{
		return {x / t, y / t};
	}
	cod operator*(const vec &o) const{ // cos
		return x * o.x + y * o.y;
	}
	cod operator^(const vec &o) const{ // sin
		return x * o.y - y * o.x;
	}
	bool operator==(const vec &o) const{
		return eq(x, o.x) && eq(y, o.y);
	}
	bool operator<(const vec &o) const{
		if(!eq(x, o.x)) return x < o.x;
		return y < o.y;
	}
	cod cross(const vec &a, const vec &b) const{
		return (a-(*this)) ^ (b-(*this));
	}
    int ccw(const vec &a, const vec &b) const{
        cod tmp = cross(a, b);
        return (tmp > eps) - (tmp < -eps);
    }
	cod dot(const vec &a, const vec &b) const{
		return (a-(*this)) * (b-(*this));
	}
	cod len() const{
		return sqrt(x * x + y * y); // <
	}
	double angle(const vec &a, const vec &b) const{
		return atan2(cross(a, b), dot(a, b));
	}
	double tan(const vec &a, const vec &b) const{
		return cross(a, b) / dot(a, b);
	}
	vec unit() const{
		return operator/(len());
	}
	int quad() const{
		if(x > 0 && y >=0) return 0;
		if(x <=0 && y > 0) return 1;
		if(x < 0 && y <=0) return 2;
		return 3;
	}
	bool comp(const vec &a, const vec &b) const{
		return (a - *this).comp(b - *this);
	}
	bool comp(vec b){
		if(quad() != b.quad()) return quad() < b.quad();
		if(!eq(operator^(b), 0)) return operator^(b) > 0;
		return (*this) * (*this) < b * b;
	}
	template<class T>
	void sort_by_angle(T first, T last) const{
		std::sort(first, last, [=](const vec &a, const vec &b){
			return comp(a, b);
		});
	}
	vec rot90() const{ return {-y, x}; }
	vec rot(double a) const{
		return {cos(a)*x -sin(a)*y, sin(a)*x +cos(a)*y};
	}
};

struct line{
	cod a, b, c; vec n;
	line(vec q, vec w){ // q.cross(w, (x, y)) = 0
		a = -(w.y-q.y);
		b = w.x-q.x;
		c = -(a * q.x + b * q.y);
		n = {a, b};
	}
	cod dist(const vec &o) const{
		return abs(eval(o)) / n.len();
	}
	bool contains(const vec &o) const{
		return eq(a * o.x + b * o.y + c, 0);
	}
	cod dist(const line &o) const{
		if(!parallel(o)) return 0;
		if(!eq(o.a * b, o.b * a)) return 0;
		if(!eq(a, 0))
			return abs(c - o.c * a / o.a) / n.len();
		if(!eq(b, 0))
			return abs(c - o.c * b / o.b) / n.len();
		return abs(c - o.c);
	}
	bool parallel(const line &o) const{
		return eq(n ^ o.n, 0);
	}
	bool operator==(const line &o) const{
		if(!eq(a*o.b, b*o.a)) return false;
		if(!eq(a*o.c, c*o.a)) return false;
		if(!eq(c*o.b, b*o.c)) return false;
		return true;
	}
	bool intersect(const line &o) const{
		return !parallel(o) || *this == o;
	}
	vec inter(const line &o) const{
		if(parallel(o)){
			if(*this == o){ }
			else{ /* dont intersect */ }
		}

		auto tmp = n ^ o.n;
		return {(o.c*b -c*o.b)/tmp, (o.a*c -a*o.c)/tmp};
	}
	vec at_x(cod x) const{
		return {x, (-c-a*x)/b};
	}
	vec at_y(cod y) const{
		return {(-c-b*y)/a, y};
	}
	cod eval(const vec &o) const{
		return a * o.x + b * o.y + c;
	}
};

struct segment{
	vec p, q;
	segment(vec a = vec(), vec b = vec()): p(a), q(b) {}
	bool onstrip(const vec &o) const{ // onstrip strip
		return p.dot(o, q) >= -eps && q.dot(o, p) >= -eps;
	}
	cod len() const{
		return (p-q).len();
	}
	cod dist(const vec &o) const{
		if(onstrip(o)) return line(p, q).dist(o);
		return min((o-q).len(), (o-p).len());
	}
	bool contains(const vec &o) const{
		return eq(p.cross(q, o), 0) && onstrip(o);
	}
	bool intersect(const segment &o) const{
		if(contains(o.p)) return true;
		if(contains(o.q)) return true;
		if(o.contains(q)) return true;
		if(o.contains(p)) return true;
		return p.ccw(q, o.p) * p.ccw(q, o.q) == -1
        && o.p.ccw(o.q, q) * o.p.ccw(o.q, p) == -1;
	}
	bool intersect(const line &o) const{
		return o.eval(p) * o.eval(q) <= 0;
	}
	cod dist(const segment &o) const{
		if(line(p, q).parallel(line(o.p, o.q))){
			if(onstrip(o.p) || onstrip(o.q)
			|| o.onstrip(p) || o.onstrip(q))
				return line(p, q).dist(line(o.p, o.q));
		}
		else if(intersect(o)) return 0;
		return min(min(dist(o.p), dist(o.q)),
				   min(o.dist(p), o.dist(q)));
	}
	cod dist(const line &o) const{
		if(line(p, q).parallel(o))
			return line(p, q).dist(o);
		else if(intersect(o)) return 0;
		return min(o.dist(p), o.dist(q));
	}
};

struct hray{
	vec p, q;
	hray(vec a = vec(), vec b = vec()): p(a), q(b){}
	bool onstrip(const vec &o) const{ // onstrip strip
		return p.dot(q, o) >= -eps;
	}
	cod dist(const vec &o) const{
		if(onstrip(o)) return line(p, q).dist(o);
		return (o-p).len();
	}
	bool intersect(const segment &o) const{
		if(!o.intersect(line(p,q))) return false;
		if(line(o.p, o.q).parallel(line(p,q)))
			return contains(o.p) || contains(o.q);
		return contains(line(p,q).inter(line(o.p,o.q)));
	}
	bool contains(const vec &o) const{
		return eq(line(p, q).eval(o), 0) && onstrip(o);
	}
	cod dist(const segment &o) const{
		if(line(p, q).parallel(line(o.p, o.q))){
			if(onstrip(o.p) || onstrip(o.q))
				return line(p, q).dist(line(o.p, o.q));
			return o.dist(p);
		}
		else if(intersect(o)) return 0;
		return min(min(dist(o.p), dist(o.q)),
				   o.dist(p));
	}
	bool intersect(const hray &o) const{
		if(!line(p, q).parallel(line(o.p, o.q)))
			return false;
		auto pt = line(p, q).inter(line(o.p, o.q));
		return contains(pt) && o.contains(pt); // <<
	}
	bool intersect(const line &o) const{
		if(line(p, q).parallel(o)) return line(p, q)== o;
		if(o.contains(p) || o.contains(q)) return true;
		return (o.eval(p) >= -eps)^(o.eval(p)<o.eval(q));
		return contains(o.inter(line(p, q)));
	}
	cod dist(const line &o) const{
		if(line(p,q).parallel(o))
			return line(p,q).dist(o);
		else if(intersect(o)) return 0;
		return o.dist(p);
	}
	cod dist(const hray &o) const{
		if(line(p, q).parallel(line(o.p, o.q))){
			if(onstrip(o.p) || o.onstrip(p))
				return line(p,q).dist(line(o.p, o.q));
			return (p-o.p).len();
		}
		else if(intersect(o)) return 0;
		return min(dist(o.p), o.dist(p));
	}
};

double heron(cod a, cod b, cod c){
	cod s = (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}
