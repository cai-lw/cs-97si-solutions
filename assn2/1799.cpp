#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        
        int n;
        float R, pi=atan(1.0)*4;
        scanf("%f %d", &R, &n);
        float r=R/(1+1/sin(pi/n));
        printf("Scenario #%d:\n%.3f\n\n", i, r);
    }
}