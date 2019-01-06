#include <cstdio>
using namespace std;

int n;
int a[110];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=1;j<=i;j++){
            if(a[j]<a[i]) cnt++;
        }
        printf("%d ",cnt);
    }
}
