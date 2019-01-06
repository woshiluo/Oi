#include <cstdio>
using namespace std;

int x[110000];
int n,temp,max=-1;

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&temp);
        if(temp>max) max=temp;
        x[temp]++;
    }
    for(int i=1;i<=max;i++) {
        for(int j=1;j<=x[i];j++){
            printf("%d ",i);
        }       
    }
}
