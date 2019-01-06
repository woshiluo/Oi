#include <cstdio>
using namespace std;

struct node {
    int k,n;
    // k 国家
    // n 时间
}peo[310000];
int h,l;
int n;
int ans;
int a[110000];
int main(){
    h=l=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int t,k;
        scanf("%d%d",&t,&k);
        for(int j=1;j<=k;j++){
            int temp;
            scanf("%d",&temp);
            peo[l++]=(node){temp,t};
            if(a[temp]==0) ans++;
            a[temp]++;
            for(int p=h;p<l;p++){
                if(t-peo[p].n>=86400){
                    a[peo[p].k]--;
                    if(a[peo[p].k]==0) ans--;
                    h++;
                } 
                else break;
            }

        }
        
        printf("%d\n",ans);
    }
}
