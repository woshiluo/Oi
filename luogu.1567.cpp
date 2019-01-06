#include <cstdio>
using namespace std;

int n,cnt=1,temp,last,max;

int main(){
    scanf("%d",&n);
    scanf("%d",&last);
    for(int i=2;i<=n;i++){
        scanf("%d",&temp);
        if(temp>last) {
            cnt++;
            last=temp;
        }
        else {
            if(cnt>max) max=cnt;
            cnt=1;
            last=temp;
        }
    }
    printf("%d",max);
}
