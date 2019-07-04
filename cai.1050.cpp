#include <cstdio>
#include <cstring>
using namespace std;

struct node{
    int deep;
    int a[50];
}dl[560000];

int n;
char a[50],b[50];
int y[50];
// A->0 C->1 G->2 T->3
bool x[20000000];

bool bp(node temp){
    for(int i=0;i<n;i++){
        if(temp.a[i]!=y[i]) return false;
    }
    return true;
}

long long szs(node temp){
    long long c;
    c=0;
    for(int i=0;i<n;i++){
        c=c*10+temp.a[i];
    }
    long long m,ans=0,k=1;
    for(int i=1;i<=n;i++){
        m=c%10;
        c/=10;
        ans+=m*k;
        k*=4;
    } 
    return ans;
}

int main(){
    while(1){
        scanf("%d",&n);
        if(n==0) break;
        memset(b,0,sizeof(b));
        memset(dl,0,sizeof(dl));
        memset(x,false,sizeof(x));
        scanf("%s",a);
        for(int i=0;i<n;i++){
            if(a[i]=='A') dl[1].a[i]=0;
            if(a[i]=='C') dl[1].a[i]=1;
            if(a[i]=='G') dl[1].a[i]=2;
            if(a[i]=='T') dl[1].a[i]=3;
        }
        scanf("%s",b);
        for(int i=0;i<n;i++){
            if(b[i]=='A') y[i]=0;
            if(b[i]=='C') y[i]=1;
            if(b[i]=='G') y[i]=2;
            if(b[i]=='T') y[i]=3;
        }
        if(bp(dl[1])){
            printf("0\n");
            continue;
        }
        int l,r;
        l=r=1;
        dl[1].deep=0;
        while(l<=r){
            node mmp;
            mmp=dl[l];

            //2 letter
            if(n>=2){
                int temp=mmp.a[0];
                mmp.a[0]=mmp.a[1];
                mmp.a[1]=temp;
                mmp.deep++;
                if(!x[ szs(mmp) ]){
                    dl[++r]=mmp;
                    x[ szs(mmp) ]=true;
                    if(bp(mmp)) {
                        printf("%d\n",mmp.deep);
                        break;
                    }
                }

                mmp=dl[l];
                // first->last
                if(n>=2){

                    int temp=mmp.a[0];
                    for(int i=0;i<n;i++){
                        mmp.a[i-1]=mmp.a[i];
                    }
                    mmp.a[n-1]=temp;
                    mmp.deep=dl[l].deep+1;
                    if(!x[ szs(mmp) ]){
                    
                        dl[++r]=mmp;
                        x[ szs(mmp) ] = true;
                        if(bp(mmp)) {
                            printf("%d\n",mmp.deep);
                            break;
                        }              
                    }
                }
                l++;
            }
        }
    }
}
