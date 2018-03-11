#include <cstdio>
using namespace std;

int lowbit(int x){
    return x&(-x);
}

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        int x;
        scanf("%d",&x);
        printf("%d %d\n",x-lowbit(x)+1,x+lowbit(x)-1);
    }
}