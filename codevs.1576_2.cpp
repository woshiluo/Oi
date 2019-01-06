#include <cstdio>
using namespace std;

int n;
int a[5100],f[5100];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    f[1]=1;
    for(int i=1;i<=n;i++){
        
        int max=0;
        for(int j=1;j<i;j++){
            if(f[j]+1>max&&a[i]>a[j]){
                max=f[j]+1;
            }
        }
        f[i]=max;
    }
    printf("%d",f[n]+1);
}
