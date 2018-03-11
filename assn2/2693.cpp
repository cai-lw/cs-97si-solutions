#include <cstdio>
#include <cmath>
using namespace std;

const float R2=6.25;

bool center(float x1, float y1, float x2, float y2, float &xc, float &yc) {
    float xv=y2-y1,yv=x1-x2,dv2=xv*xv+yv*yv;
    if(dv2>R2*4)return false;
    float xm=(x1+x2)/2,ym=(y1+y2)/2,k=sqrt(R2/dv2-0.25);
    xc=xm+xv*k;
    yc=ym+yv*k;
    return true;
}

int main(){
    float x[200],y[200];
    int n=0,ans=1;
    while(scanf("%f %f",&x[n],&y[n])!=EOF){
        n++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j)continue;
            float xc,yc;
            if(!center(x[i],y[i],x[j],y[j],xc,yc))continue;
            int count=2;
            for(int k=0;k<n;k++){
                if(k==i||k==j)continue;
                float dx=x[k]-xc,dy=y[k]-yc,d2=dx*dx+dy*dy;
                if(d2<=R2)count++;
            }
            if(ans<count)ans=count;
        }
    }
    printf("%d\n",ans);
}