#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

int n,m,a[500],b[500],dp[501][501],prv[500][501],nxt[501],ans[501];

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=0;i<m;i++)scanf("%d",&b[i]);
    dp[0][0]=-1;
    for(int i=1;i<=n;i++){
        dp[i][0]=-1;
        for(int j=1;j<=i;j++)dp[i][j]=m;
        nxt[m]=m;
        for(int j=m-1;j>=0;j--)
            if(a[i-1]==b[j])nxt[j]=j;
            else nxt[j]=nxt[j+1];
        dp[i][1]=nxt[0];
        for(int j=1;j<i;j++)
            if(a[j-1]<a[i-1])
                for(int k=2;k<=j+1;k++)
                    if(nxt[dp[j][k-1]]<dp[i][k]){
                        dp[i][k]=nxt[dp[j][k-1]];
                        prv[i][k]=j;
                    }
    }
    for(int i=n;i>=0;i--)
        for(int j=i;j<=n;j++)
            if(dp[j][i]<m){
                int cur=j;
                for(int k=i;k>=0;k--){
                    ans[k]=a[cur-1];
                    cur=prv[cur][k];
                }
                printf("%d\n",i);
                for(int k=1;k<=i;k++){
                    printf("%d",ans[k]);
                    if(k<i)putchar(' ');
                }
                putchar('\n');
                return 0;
            }

}