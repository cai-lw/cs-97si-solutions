#include <cstdio>
using namespace std;

typedef long long ll;

int main(){
    int t;
    char s[1000001];
    scanf("%d",&t);
    while(t-->0){
        ll ans=0;
        int x=0,y=0,dx,dy;
        scanf("%s",s);
        for(int i=0;;i++){
            if(s[i]=='5')break;
            switch(s[i]){
                case '1':dx=-1;dy=-1;break;
                case '2':dx=0;dy=-1;break;
                case '3':dx=1;dy=-1;break;
                case '4':dx=-1;dy=0;break;
                case '6':dx=1;dy=0;break;
                case '7':dx=-1;dy=1;break;
                case '8':dx=0;dy=1;break;
                case '9':dx=1;dy=1;break;
            }
            ans+=x*dy-y*dx;
            x+=dx;
            y+=dy;
        }
        if(ans<0)ans=-ans;
        printf("%lld",ans/2);
        if(ans%2!=0)printf(".5");
        printf("\n");
    }
}