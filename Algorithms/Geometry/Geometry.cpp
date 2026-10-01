#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
struct point{ // điểm
    double x,y;
};
struct line{ // đoạn
    point x,y;
};
line inputl(){ // nhập đoạn thẳng
    line a;
    cin>>a.x.x>>a.x.y>>a.y.x>>a.y.y;
    return a;
}
struct ptdt{ // biến phương trình đường thẳng
    double a,b,c;
};
double dist(line a){ // hàm khoảng cách
    return sqrt(pow(a.y.x-a.x.x,2) + pow(a.y.y-a.x.y,2));
}
ptdt extract(line a){ // chuyển qua phương trình đường thẳng
    ptdt res;
    res.a = a.y.y - a.x.y;
    res.b = a.x.x - a.x.y;
    res.c = 0 - a.x.x*(a.y.y-a.y.x) + a.y.y*(a.x.y - a.x.x);
    return res;
}
bool giao(line a, line b){ // giao 2 đường thẳng
    ptdt a1 = extract(a);
    ptdt b1 = extract(b);
    double ta = (a1.a*b.x.x+a1.b*b.x.y+a1.c) * (a1.a*b.y.x + a1.b*b.y.y + a1.c);
    double tb = (b1.a*a.x.x+b1.a*b.x.y+b1.c) * (b1.a*a.y.x + b1.b*a.y.y + b1.c);
    return ta*tb < 0;
}
void nghiem(line a, line b){ // Tìm giao điểm
    ptdt a1 = extract(a);
    ptdt b1 = extract(b);
    double d = a1.a*b1.b - b1.a*a1.b;
    double dx = a1.b*b1.c - b1.b*a1.c;
    double dy = a1.c*b1.a - b1.c*a1.a;
    if(d != 0){
        cout<<"("<<dx/d<<","<<dy/d<<")"<<'\n';
    }
    else{
        double ma = a1.a / b1.a;
        double mb = a1.b / b1.b;
        double mc = a1.c / b1.c;
        if(ma == mb && mb == mc) cout<<"INF"<<'\n';
        else cout<<"N/A"<<'\n';
    }
}
bool Check(point p1, point p2, point p3){  // 1 điểm thuộc đường thẳng
    ptdt k = extract({p1,p2}); 
    if (abs(k.a*p3.x+k.b*p3.y+k.c) <= eps)  return 1; 
    return 0; 
} 
void giao2dt(line a, line b){
    if(giao(a,b)){
        nghiem(a,b);
    }
    else cout<<"No"<<'\n';
}
bool Check2(point p1, point p2, point p3){ // AB + BC = AC ? 
    if ((abs(dist({p1,p2})+dist({p2,p3})-dist({p1,p3}))<=eps) 
    || (abs(dist({p1,p3})+dist({p3,p2})-dist({p1,p2}))<=eps) 
    || (abs(dist({p2,p1})+dist({p1,p3})-dist({p2,p3}))<=eps))  
    return 1; 
    return 0; 
}
double Area(vector<point> p){  // diện tích đa giác
    double  s, a, b, c, p2; int i; 
    s=0; 
    for (i = 3; i < p.size()-1; i++){ 
        a=dist({p[1], p[i-1]}); 
        b=dist({p[i-1],p[i]}); 
        c=dist({p[1],p[i]}); 
        p2=(a+b+c)/2; 
        s=s+sqrt(p2*(p2-a)*(p2-b)*(p2-c)); 
    } 
    return s;
}
double Angle(point A, point B){ 
    double dx, dy, t; 
    dx=B.x-A.x; 
    dy=B.y-A.y; 
    if ((abs(dx)<eps) && (abs(dy)<eps)) t=0; 
    else t=dy/(abs(dx)+abs(dy)); 
    if (dx<0) t=2-t; 
    else  
    if (dy<0) t=4+t; 
    return t*90; 
}
int main(){
    line a,b;
    a = inputl();
    b = inputl();
    ptdt kq = extract(a);
    nghiem(a,b);
    cout<<Angle(a.x,a.y);
}
