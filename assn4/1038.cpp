#include <cstdio>
#include <algorithm>
using namespace std;

const int N_STATE=201;
int n,m,k,plate[151],ns,s2i[1024],i2s[N_STATE],dp[N_STATE][N_STATE],dp2[N_STATE][N_STATE];

void predfs(int a,int i){
    if(i>=m){
        if(s2i[a]==-1){
            s2i[a]=ns;
            i2s[ns]=a;
            ns++;
        }
        return;
    }
    predfs(a,i+1);
    if(i<=m-2)predfs(a|(3<<i),i+2);
    if(i<=m-3)predfs(a|(7<<i),i+3);
}

int r,i0,j0;
void dfs(int a,int b,int c,int k,int i){
    if(i>=m){
        int &upd=dp2[s2i[b^plate[r-1]]][s2i[c^plate[r]]];
        upd=max(upd,dp[i0][j0]+k);
        return;
    }
    dfs(a,b,c,k,i+1);
    if(i<=m-2 && (!(a&(3<<i))) && (!(b&(3<<i))) && (!(c&(3<<i)))) dfs(a|(3<<i),b|(3<<i),c|(3<<i),k+1,i+2);
    if(i<=m-3 && (!(b&(7<<i))) && (!(c&(7<<i)))) dfs(a,b|(7<<i),c|(7<<i),k+1,i+3);
}

int main(){
    int d;
    scanf("%d",&d);
    while(d--){
        scanf("%d%d%d",&n,&m,&k);
        n++;
        fill(plate,plate+n,0);
        plate[0]=(1<<m)-1;
        for(int i=0;i<k;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            plate[x]|=1<<(y-1);
        }
        ns=0;
        fill(s2i,s2i+(1<<m),-1);
        fill(i2s,i2s+N_STATE,-1);
        predfs(0,0);
        for(int i=0;i<ns;i++)fill(dp[i],dp[i]+ns,-1);
        dp[0][0]=0;
        for(r=2;r<n;r++){
            for(int i=0;i<ns;i++)fill(dp2[i],dp2[i]+ns,-1);
            for(int i=0;i<ns;i++)
                for(int j=0;j<ns;j++){
                    if(dp[i][j]<0)continue;
                    i0=i;
                    j0=j;
                    dfs(i2s[i]|plate[r-2],i2s[j]|plate[r-1],plate[r],0,0);
                }
            for(int i=0;i<ns;i++)copy(dp2[i],dp2[i]+ns,dp[i]);
        }
        int ans=0;
        for(int i=0;i<ns;i++)
            for(int j=0;j<ns;j++)
                ans=max(ans,dp[i][j]);
        printf("%d\n",ans);
    }
}