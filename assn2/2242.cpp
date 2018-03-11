#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    double x1,x2,x3,y1,y2,y3,pi2=atan(1.0)*8;
    while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3)!=EOF){
        double dx1=x2-x1,dy1=y2-y1,dx2=x3-x1,dy2=y3-y1,dx3=x3-x2,dy3=y3-y2,
               a=sqrt(dx1*dx1+dy1*dy1),b=sqrt(dx2*dx2+dy2*dy2),c=sqrt(dx3*dx3+dy3*dy3),
               S2=abs(dx1*dy2-dx2*dy1),R=a*b*c/(S2*2);
        printf("%.2f\n",R*pi2);
    }
}