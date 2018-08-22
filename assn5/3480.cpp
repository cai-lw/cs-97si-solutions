#include <cstdio>
using namespace std;

int main(){
    int n,t,a;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        bool allone=true;
        int grundy=0;
        while(n--){
            scanf("%d",&a);
            grundy^=a;
            if(a!=1)allone=false;
        }
        if((grundy==0)^allone)printf("Brother\n");
        else printf("John\n");
    }
}