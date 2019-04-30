#include <cstdio>
#include <cstring>
using namespace std;

int a[110000],n;
int f[110000],s[110000],max,k;

bool cmp(int a,int b,int kind){
    if(kind==1) return a>=b;
    else return a<b;
}

int binary_serach(int l,int r,int val,int kind){
    while(l<r){
        int mid=(l+r)>>1;
        if(cmp(s[mid],val,kind)) l=mid+1;
        else r=mid;
    }
    return l;
}

int main(){
    while(scanf("%d",&a[++n])!=EOF);
    n--;
    memset(s,-0x7f,sizeof(s));
    for(int i=1;i<=n;i++){
        f[i]=binary_serach(1,i,a[i],1);
        s[f[i]]=s[f[i]]>a[i]?s[f[i]]:a[i];
        if(f[i]>max) max=f[i];
    }
    printf("%d\n",max);
    memset(s,0x7f,sizeof(s));
    max=-1;
    for(int i=1;i<=n;i++){ 
        f[i]=binary_serach(1,i,a[i],2);
        s[f[i]]=s[f[i]]<a[i]?s[f[i]]:a[i];
        if(f[i]>max) max=f[i];
    }
    printf("%d",max);
}

