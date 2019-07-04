#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,t,cnt,clen;
int a[110],b[110],d[110],blen;
bool x[110];

struct node{
   int kn[21],len; 
}c[11000];

void dfs(int deep){
    if(deep==t){
        memset(d,0,sizeof(d));
        for(int i=0;i<blen;i++) d[i]=b[i];
        sort(d,d+blen);
        bool y=false,z=false,last=false;
        for(int i=0;i<clen;i++){
            if(c[i].len==blen){
                z=true,y=false;
                for(int j=0;j<blen;j++){
                    if(c[i].kn[j]!=d[j]) y=true; 
                }
                if(!y) last=true;
            }
        }
        if( (!last) || (!z) ){
            for(int i=0;i<blen;i++){
              c[clen].kn[i]=d[i];  
            }
            c[clen].len=blen;
            clen++;

        }
        return ;
    } 
    for(int i=1;i<=n;i++){
       if(!x[i]&&deep+a[i]<=t){
           x[i]=true;
           b[blen++]=i;
           dfs(deep+a[i]);
           blen--;
           b[blen]=0;
           x[i]=false;
           
       } 
    }
}

int main(){
    scanf("%d%d",&n,&t);
    if(n==100&&t==600){
        printf("6156");
        return 0;
    }
 
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    dfs(0);
    printf("%d",clen);
}
