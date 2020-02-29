#include <cstdio>
#include <iostream>
using namespace std;

int n,V,v,w,m;
int f[210000];

struct node {
    int f,id;
}q[210000];
int l,r;

void oz(int v,int w){
    for(int i=V;i>=v;i--){
       f[i]=max(f[i],f[i-v]+w); 
    }
}

void wq(int v,int w){
    for(int i=v;i<=V;i++){
       f[i]=max(f[i],f[i-v]+w); 
    }
}

void queueyh(int v,int w,int m){
    for(int j=0;j<v;j++){
        l=r=0;
        for(int k=j,id=0;k<=V;k+=v,id++){
            while(l!=r&&q[r-1].f<=f[k]-id*w) r--;
            q[r++]=node{f[k]-id*w,id};
            while(l!=r&&id-q[l].id>m) l++;
            f[k]=q[l].f+id*w;
        }
    }   
}

int main(){
    scanf("%d%d",&n,&V);
    for(int i=1;i<=n;i++){ 
        scanf("%d%d%d",&v,&w,&m);
        if(m==-1||m*v>V) wq(v,w);
        else if(m==1) oz(v,w);
        else queueyh(v,w,m);

    }
    printf("%d",f[V]);
}
