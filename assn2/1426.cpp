#include <cstdio>
using namespace std;

int main(){
    int n;
    bool dp[101][200];
    int prev[101][200];
    scanf("%d",&n);
    while(n>0){
        int rem=1%n;
        dp[0][0]=true;
        for(int j=1;j<n;j++)dp[0][j]=false;
        for(int i=1;i<=100;i++){
            if(rem==0){
                printf("1");
                for(int j=1;j<i;j++)printf("0");
                printf("\n");
                break;
            }
            if(dp[i-1][n-rem]){
                printf("1");
                int pr=n-rem;
                for(int j=i-1;j>0;j--){
                    printf(prev[j][pr]!=pr ? "1" : "0");
                    pr=prev[j][pr];
                }
                printf("\n");
                break;
            }
            dp[i][0]=true;
            prev[i][0]=0;
            for(int j=1;j<n;j++){
                dp[i][j]=false;
                if(dp[i-1][j]){
                    dp[i][j]=true;
                    prev[i][j]=j;
                }
                else{
                    int pr=j+n-rem;
                    if(pr>=n)pr-=n;
                    if(dp[i-1][pr]){
                        dp[i][j]=true;
                        prev[i][j]=pr;
                    }
                }
            }
            rem=rem*10%n;
        }
        scanf("%d",&n);
    }
}