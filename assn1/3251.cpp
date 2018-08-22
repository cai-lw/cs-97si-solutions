#include <cstdio>
using namespace std;

int n;
char a[101][101];

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%s",a[i]);
    int ans=0;
    for(int p=n-1;p>0;p--)
        for(int q=n-1;q>=0;q--){
            if(p+q>=n||p+q==0)continue;
            int area=p*p+q*q;
            if(area<=ans)continue;
            for(int i=0;i<n-p-q;i++){
                for(int j=0;j<n-p-q;j++){
                    int john=0;
                    if(a[i+p][j]=='B')continue;
                    else if(a[i+p][j]=='J')john++;
                    if(a[i][j+q]=='B')continue;
                    else if(a[i][j+q]=='J')john++;
                    if(a[i+p+q][j+p]=='B')continue;
                    else if(a[i+p+q][j+p]=='J')john++;
                    if(a[i+q][j+p+q]=='B')continue;
                    else if(a[i+q][j+p+q]=='J')john++;
                    if(john>=3){
                        ans=area;
                        break;
                    }
                }
                if(ans==area)break;
            }
        }
    printf("%d\n",ans);
}