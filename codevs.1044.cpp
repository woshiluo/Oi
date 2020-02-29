#include <cstdio>
#include <cstring>
using namespace std;

int a[2100000],alen;
int f[2100000],max,k;


int main(){
    while(scanf("%d",&a[++alen])!=EOF);
    f[1]=1;
    for(int i=1;i<alen;i++){
        max=1;
        for(int j=1;j<i;j++){
            if(a[i]<a[j]&&f[j]+1>max){
                max=f[j]+1;
            }
        }
        f[i]=max;
    }
    max=k;
    for(int i=1;i<alen;i++){
        if(f[i]>max) max=f[i];
    }
    printf("%d\n",max);
    memset(f,0,sizeof(f));
    f[1]=1;
    for(int i=1;i<alen;i++){
        max=1;
        for(int j=1;j<i;j++){
            if(a[i]>=a[j]&&f[j]+1>max){
                max=f[j]+1;
            }
        }
        f[i]=max;
    }
    max=1;
    for(int i=1;i<alen;i++){
        if(f[i]>max) max=f[i];
    }
    printf("%d\n",max);

}
