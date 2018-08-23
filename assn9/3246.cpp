#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Point {
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
    bool operator==(const Point &other) const{
        return x==other.x&&y==other.y;
    }
};

inline ll cross(Point a,Point b){
    return ll(a.x)*ll(b.y)-ll(a.y)*ll(b.x);
}

inline ll cross(Point a,Point o,Point b){
    a.x-=o.x;
    a.y-=o.y;
    b.x-=o.x;
    b.y-=o.y;
    return cross(a,b);
}

inline ll dot(Point a,Point b){
    return ll(a.x)*ll(b.x)+ll(a.y)*ll(b.y);
}

inline ll mag2(Point a){
    return dot(a,a);
}

inline ll mag2(Point a,Point b){
    a.x-=b.x;
    a.y-=b.y;
    return mag2(a);
}

bool cmp_angle(Point a,Point b){
    ll x=cross(a,b);
    if(x>0)return true;
    else if(x<0) return false;
    else return mag2(a)<mag2(b);
}

int n;
Point p[100001];

vector<int> convex_hull(int l,int r,int ban){
    vector<int> st;
    while(l<r){
        int l2=l+1==ban?l+2:l+1;
        if(l2>r)break;
        if(l==ban||cross(p[l],p[l2])==0)l++;
        else break;
    }
    if(l==r||(r==ban&&l==r-1))return st;
    st.push_back(l);
    st.push_back(l+1==ban?l+2:l+1);
    for(int i=l+2;i<=r;i++){
        if(i==ban)continue;
        while(st.size()>=2&&cross(p[i],p[st.back()],p[st[st.size()-2]])<=0)st.pop_back();
        st.push_back(i);
    }
    return st;
}

ll hull_area2(const vector<int> &ix){
    if(ix.size()<2)return 0;
    ll ret=0;
    for(int i=0;i<ix.size()-1;i++)
        ret+=cross(p[ix[i]],p[ix[i+1]]);
    return ret;
}

bool solve(){
    int n;
    scanf("%d",&n);
    if(n==0)return false;
    for(int i=0;i<n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
        if(p[i].x<p[0].x||(p[i].x==p[0].x&&p[i].y<p[0].y))swap(p[i],p[0]);
    }
    for(int i=1;i<n;i++){
        p[i].x-=p[0].x;
        p[i].y-=p[0].y;
    }
    p[0].x=0;
    p[0].y=0;
    sort(p+1,p+n,cmp_angle);
    vector<int> hull=convex_hull(1,n-1,-1);
    ll full=hull_area2(hull),ans=full;
    if(ans==0){
        printf("%lld.%02lld\n",ans/2,ans%2*50);
        return true;
    }
    ans=min(ans,full-cross(p[hull[0]],p[hull[1]])+hull_area2(convex_hull(1,hull[1],hull[0])));
    ans=min(ans,full-cross(p[hull[hull.size()-2]],p[hull.back()])+hull_area2(convex_hull(hull[hull.size()-2],n-1,hull.back())));
    for(int i=1;i<hull.size()-1;i++)
        ans=min(ans,full-cross(p[hull[i-1]],p[hull[i]])-cross(p[hull[i]],p[hull[i+1]])+hull_area2(convex_hull(hull[i-1],hull[i+1],hull[i])));
    for(int i=1;i<n;i++)
        if(p[i].x<p[1].x||(p[i].x==p[1].x&&p[i].y<p[1].y))swap(p[i],p[1]);
    for(int i=2;i<n;i++){
        p[i].x-=p[1].x;
        p[i].y-=p[1].y;
    }
    sort(p+2,p+n,cmp_angle);
    ans=min(ans,hull_area2(convex_hull(2,n-1,-1)));
    printf("%lld.%02lld\n",ans/2,ans%2*50);
    return true;
}

int main(){
    while(solve()){}
}