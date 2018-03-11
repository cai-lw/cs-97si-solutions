#include <cstdio>
using namespace std;

int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n, ans=0, pow5=5;
        scanf("%d", &n);
        while(true){
            ans+=n/pow5;
            if(pow5<=n/5)pow5*=5;else break;
        }
        printf("%d\n",ans);
    }
}