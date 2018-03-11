#include <cstdio>
using namespace std;

bool prime(int x){
    for(int i=3;i*i<=x;i+=2){
        if(x%i==0)return false;
    }
    return true;
}

int main(){
    int n;
    scanf("%d",&n);
    while(n>0){
        for(int i=3;i<=n/2;i+=2){
            if(prime(i)&&prime(n-i)){
                printf("%d = %d + %d\n", n, i, n-i);
                break;
            }
        }
        scanf("%d",&n);
    }
}