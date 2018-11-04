#include <cstdio>
#include <cstring>
using namespace std;

char *grid[10000],*gridt[75];
int r,c;

int kmp(char** a,int n){
    int *nxt=new int[n];
    nxt[0]=-1;
    for(int i=1;i<n;i++){
        int j=nxt[i-1];
        while(strcmp(a[j+1],a[i])!=0&&j>=0)j=nxt[j];
        if(strcmp(a[j+1],a[i])==0)nxt[i]=j+1;
        else nxt[i]=-1;
    }
    int ret=n-1-nxt[n-1];
    delete[] nxt;
    return ret;
}

int main(){
    scanf("%d%d",&r,&c);
    for(int i=0;i<r;i++){
        grid[i]=new char[c+1];
        scanf("%s",grid[i]);
    }
    for(int j=0;j<c;j++){
        gridt[j]=new char[r+1];
        for(int i=0;i<r;i++)gridt[j][i]=grid[i][j];
    }
    printf("%d\n",kmp(grid,r)*kmp(gridt,c));
}