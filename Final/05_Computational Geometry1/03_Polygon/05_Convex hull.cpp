const int maxn = 1e3 + 5;
struct Point {
    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y){}
};
typedef Point Vector;
Point lst[maxn];
int stk[maxn], top;
Vector operator - (Point A, Point B){
    return Vector(A.x-B.x, A.y-B.y);
}
int sgn(double x){
    if(fabs(x) < eps)
        return 0;
    if(x < 0)
        return -1;
    return 1;
}
double Cross(Vector v0, Vector v1) {
    return v0.x*v1.y - v1.x*v0.y;
}
double Dis(Point p1, Point p2) { //计算 p1p2的 距离
    return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
bool cmp(Point p1, Point p2) { //极角排序函数 ，角度相同则距离小的在前面
    int tmp = sgn(Cross(p1 - lst[0], p2 - lst[0]));
    if(tmp > 0)
        return true;
    if(tmp == 0 && Dis(lst[0], p1) < Dis(lst[0], p2))
        return true;
    return false;
}
//点的编号0 ~ n - 1
//返回凸包结果stk[0 ~ top - 1]为凸包的编号
void Graham(int n) {
    int k = 0;
    Point p0;
    p0.x = lst[0].x;
    p0.y = lst[0].y;
    for(int i = 1; i < n; ++i) {
        if( (p0.y > lst[i].y) || ((p0.y == lst[i].y) && (p0.x > lst[i].x)) ) {
            p0.x = lst[i].x;
            p0.y = lst[i].y;
            k = i;
        }
    }
    lst[k] = lst[0];
    lst[0] = p0;
    sort(lst + 1, lst + n, cmp);
    if(n == 1) {
        top = 1;
        stk[0] = 0;
        return ;
    }
    if(n == 2) {
        top = 2;
        stk[0] = 0;
        stk[1] = 1;
        return ;
    }
    stk[0] = 0;
    stk[1] = 1;
    top = 2;
    for(int i = 2; i < n; ++i) {
        while(top > 1 && Cross(lst[stk[top - 1]] - lst[stk[top - 2]], lst[i] - lst[stk[top - 2]]) <= 0)
            --top;
        stk[top] = i;
        ++top;
    }
    return ;
}
