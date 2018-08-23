#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N=1000,INF=1000000000;
int n,m,d[N],ptt[N],prv[N];
vector<int> e[N],w[N];

void dijkstra(){
    fill(d,d+n,INF);
    fill(prv,prv+n,-1);
    priority_queue<pair<int,int> > pq;
    pq.push(make_pair(0,0));
    d[0]=0;
    while(!pq.empty()){
        int u=pq.top().second,du=-pq.top().first;
        pq.pop();
        if(d[u]<du)continue;
        for(int i=0;i<e[u].size();i++){
            int v=e[u][i],ww=w[u][i]+ptt[u]-ptt[v];
            if(d[v]>d[u]+ww){
                d[v]=d[u]+ww;
                pq.push(make_pair(-d[v],v));
                prv[v]=u;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v,ww;
        scanf("%d%d%d",&u,&v,&ww);
        u--;
        v--;
        e[u].push_back(v);
        w[u].push_back(ww);
        e[v].push_back(u);
        w[v].push_back(ww);
    }
    dijkstra();
    copy(d,d+n,ptt);
    int cur=n-1;
    while(cur!=0){
        int p=prv[cur],ie=-1;
        for(int i=0;i<e[p].size();i++)
            if(e[p][i]==cur&&(ie==-1||w[p][i]<w[p][ie]))ie=i;
        int ww=w[p][ie];
        w[p][ie]=INF;
        e[cur].push_back(p);
        w[cur].push_back(-ww);
        cur=p;
    }
    dijkstra();
    printf("%d\n",ptt[n-1]*2+d[n-1]);
}