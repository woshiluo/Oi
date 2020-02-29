#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[11000],len;
void fz(int x){
    int t=int(sqrt(double(x+1)));
    for (int i=2;i<=t;i++){
        if (x%i==0){
            a[++len]=i;
            if (x/i!=i)a[++len]=x/i;
        }
    }
}
int n,ans;
void dfs(int d){
    ans++;
    for (int i=1;i<=len;i++){
        if (d*a[i]>n) break;//如果因子比n大则直接跳出
        if (n%(d*a[i])==0&&n!=d*a[i]){
            dfs(d*a[i]);
        }
    }
}
int main(){
    scanf("%d",&n);
    len=0;fz(n);
    sort(a+1,a+len+1);//加了一步排序
    ans=0;dfs(1);
    printf("%d\n",ans);
    return 0;
}
