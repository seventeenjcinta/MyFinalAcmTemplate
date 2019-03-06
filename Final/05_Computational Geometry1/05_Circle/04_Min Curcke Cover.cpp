#define N 100005

const double pi=acos(-1.0);
const double eps=1e-9;
int dcmp(double x)
{
    if (x<=eps&&x>=-eps) return 0;
    return (x>0)?1:-1;
}
struct Vector
{
    double x,y;
    Vector(double X=0,double Y=0)
    {
        x=X,y=Y;
    }
};
typedef Vector Point;
Vector operator + (Vector a,Vector b) {return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a,Vector b) {return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (Vector a,double b) {return Vector(a.x*b,a.y*b);}
Vector operator / (Vector a,double b) {return Vector(a.x/b,a.y/b);}

int n;
double r;
Point c,p[N];

double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}
double Cross(Vector a,Vector b)
{
    return a.x*b.y-a.y*b.x;
}
double Len(Vector a)
{
    return sqrt(Dot(a,a));
}
Vector rotate(Vector a,double rad)
{
    return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}
Point GLI(Point P,Vector v,Point Q,Vector w)
{
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
Point TC(Point A,Point B,Point C)
{
    Point P=(A+B)/2,Q=(A+C)/2;
    Vector v=rotate(B-A,pi/2),w=rotate(C-A,pi/2);
    if (dcmp(Len(Cross(v,w)))==0)
    {
        if (dcmp(Len(A-B)+Len(B-C)-Len(A-C))==0)
            return (A+C)/2;
        if (dcmp(Len(A-C)+Len(B-C)+Len(A-B))==0)
            return (A+B)/2;
        if (dcmp(Len(A-B)+Len(A-C)-Len(B-C))==0)
            return (B+C)/2;
    }
    return GLI(P,v,Q,w);
}
void mcc()
{
    random_shuffle(p+1,p+n+1);
    c=p[1],r=0;
    for (int i=2;i<=n;++i)
        if (dcmp(Len(c-p[i])-r)>0)
        {
            c=p[i],r=0;
            for (int j=1;j<i;++j)
                if (dcmp(Len(c-p[j])-r)>0)
                {
                    c=(p[i]+p[j])/2,r=Len(c-p[i]);
                    for (int k=1;k<j;++k)
                        if (dcmp(Len(c-p[k])-r)>0)
                        {
                            c=TC(p[i],p[j],p[k]);
                            r=Len(c-p[i]);
                        }
                }
        }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
    mcc();
    printf("%.3lf\n",r);
}
