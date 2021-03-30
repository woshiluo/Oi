#include <cstdio>
using namespace std;

int n,cnt,mcnt;
int a[5100];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        cnt=1;
        for(int j=i+1;j<=n;j++){
            if(a[j-1]<a[j]) cnt++;
            else {
                if(cnt>mcnt) mcnt=cnt;
                cnt=1;
            }
        }
        if(cnt>mcnt) mcnt=cnt;
    }
    printf("%d",mcnt);
}
