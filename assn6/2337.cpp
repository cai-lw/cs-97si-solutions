#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char *words[1000],last[1000];
int a[26][26],dfn[26],low[26],par[26],din[26],dout[26],idf;
bool used[1000];

void dfs(int u){
    dfn[u]=idf++;
    low[u]=dfn[u];
    for(int v=0;v<26;v++)
        if((a[u][v]||a[v][u])&&par[u]!=v){
            if(dfn[v]>=0)low[u]=min(low[u],dfn[v]);
            else{
                par[v]=u;
                dfs(v);
                low[u]=min(low[u],low[v]);
            }
        }
}

void do_dfs(int root){
    fill(dfn,dfn+26,-1);
    fill(par,par+26,-1);
    dfs(root);
}

bool strcmpb(const char *a,const char *b){
    return strcmp(a,b)<0;
}

void solve(){
    for(int i=0;i<26;i++)fill(a[i],a[i]+26,0);
    fill(din,din+26,0);
    fill(dout,dout+26,0);
    int n;
    scanf("%d",&n);
    fill(used,used+n,false);
    for(int i=0;i<n;i++){
        char *s=new char[21];
        scanf("%s",s);
        char fst=s[0],lst=s[strlen(s)-1];
        a[fst-'a'][lst-'a']++;
        dout[fst-'a']++;
        din[lst-'a']++;
        words[i]=s;
    }
    sort(words,words+n,strcmpb);
    for(int i=0;i<n;i++)last[i]=words[i][strlen(words[i])-1];
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
    if(cur==-1){
        a[words[0][0]-'a'][last[0]-'a']--;
        used[0]=true;
        dout[words[0][0]-'a']--;
        din[last[0]-'a']--;
        cur=last[0]-'a';
    }
    do_dfs(cur);
    for(int i=0;i<26;i++)
        if((din[i]||dout[i])&&dfn[i]==-1){
            printf("***\n");
            return;
        }
    if(used[0])printf("%s.",words[0]);
    for(int out=used[0];out<n;out++){
        do_dfs(cur);
        for(int i=0;i<n;i++){
            if(used[i]||words[i][0]-'a'!=cur)continue;
            int nxt=last[i]-'a';
            if(dout[cur]>1&&a[cur][nxt]+a[nxt][cur]==1&&cur!=nxt&&(par[nxt]==cur?dfn[cur]<low[nxt]:dfn[nxt]<low[cur]))continue;
            a[cur][nxt]--;
            dout[cur]--;
            din[nxt]--;
            used[i]=true;
            printf(out==n-1?"%s\n":"%s.",words[i]);
            cur=nxt;
            break;
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}