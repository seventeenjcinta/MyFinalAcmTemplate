double arg(point p){return atan2(p.y,p.x);}
point polar(double a,double r)
{
    return point(cos(r)*a,sin(r)*a);
}

pair<point,point>getcrosspoints(point a1,double r1,point a2,double r2)
{
    double d=ABS(a2-a1);
    double a=acos((r1*r1+d*d-r2*r2)/(2*r1*d));
    double t=arg(a2-a1);
    return make_pair(a1+polar(r1,t+a),a1+polar(r1,t-a));
}
