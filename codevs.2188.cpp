#include <cstdio>
using namespace std;

int a[2100],alen;

struct node {
    int now,cha[2000],clen;
}f[2100],max,k;

int main(){
    while(scanf("%d",&a[++alen])!=EOF);
    f[1].now=1;
    k.now=1;
    for(int i=1;i<alen;i++){
        max=k;
        for(int j=1;j<i;j++){
            if(a[i]<a[j]&&f[j].now+1>max.now){
                max=f[j];
                max.now++;
                max.cha[max.clen++]=i;
            }
        }
        f[i]=max;
    }
    max=k;
    for(int i=1;i<alen;i++){
        if(f[i].now>max.now) max=f[i];
    }
    printf("%d\n",max.now);

}
