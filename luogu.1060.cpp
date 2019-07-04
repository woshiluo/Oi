#include <cstdio>
using namespace std;

int n,m;
int price[40],better[40];
int f[31000];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&price[i],&better[i]);
    for(int i=1;i<=m;i++){
        for(int j=n;j>=price[i];j--){
            if(f[j-price[i]]+price[i]*better[i]>f[j])
                f[j]=f[ j-price[i] ]+price[i]*better[i];
        }
    }
    printf("%d",f[n]);
}
