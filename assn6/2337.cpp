#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char *edg[26][1000],*ans[1000];
int n,ians,din[26],dout[26];

void dfs(int u){
    while(dout[u]>0){
        char *s=edg[u][dout[u]-1];
        int v=s[strlen(s)-1]-'a';
        dout[u]--;
        dfs(v);
        ans[--ians]=s;
    }
}

bool strcmpb(const char *a,const char *b){
    return strcmp(a,b)>0;
}

void solve(){
    fill(din,din+26,0);
    fill(dout,dout+26,0);
    scanf("%d",&n);
    fill(ans,ans+n,(char*)0);
    for(int i=0;i<n;i++){
        char *s=new char[21];
        scanf("%s",s);
        int fst=s[0]-'a',lst=s[strlen(s)-1]-'a';
        edg[fst][dout[fst]]=s;
        dout[fst]++;
        din[lst]++;
    }
    int cur=-1;
    for(int i=0;i<26;i++){
        int d=dout[i]-din[i];
        if(d<-1||d>1){
            printf("***\n");
            return;
        }
        else if(d==1){
            if(cur==-1)cur=i;
            else{
                printf("***\n");
                return;
            }
        }
    }
    for(int i=0;i<26;i++)
        sort(edg[i],edg[i]+dout[i],strcmpb);
    if(cur==-1)
        for(int i=0;i<26;i++)
            if(dout[i]>0){
                char *s=edg[i][dout[i]-1];
                ans[0]=s;
                cur=s[strlen(s)-1]-'a';
                dout[i]--;
                break;
            }
    ians=n;
    dfs(cur);
    for(int i=0;i<n;i++)
        if(!ans[i]){
            printf("***\n");
            return;
        }
    for(int i=0;i<n;i++){
        printf("%s",ans[i]);
        putchar(i==n-1?'\n':'.');
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}