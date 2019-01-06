#include <cstdio>
#define P 99991
using namespace std;

const int MAXSIZE=110000;

int head[MAXSIZE],next[MAXSIZE],snow[MAXSIZE][6],a[6];
int n;
int cnt1,tot;
//int P=99991;
long long cnt2;

int H(int *a){
    cnt1=0;cnt2=1;
    for(int i=0;i<6;i++){
        cnt1+=a[i];
        cnt1%=P;
        cnt2*=a[i];
        cnt2%=P;
    }
    return (cnt1+cnt2)%P;
}

bool same(int *a,int *b){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            bool x=false;
            for(int k=0;k<6;k++){
                if(a[(i+k)%6]!=b[(j+k)%6]) x=true;
            }
            if(!x) return true;
            x=false;
            for(int k=0;k<6;k++){
                if(a[(i+k)%6]!=b[(j-k+6)%6]) x=true;
            } 
            if(!x) return true; 
        }
    }
    return false;
}

bool insert(int *a){
    int val=H(a);
    for(int i=head[val];i!=0;i=next[i]){
        if(same(snow[i],a)) return true;
    }
    tot++;
    for(int i=0;i<6;i++) snow[tot][i]=a[i];
    next[tot]=head[val];
    head[val]=tot;
    return false;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=0;j<6;j++)scanf("%d",&a[j]);
        if(insert(a)){
            printf("Twin snowflakes found.");
            return 0;
        }
    }
    printf("No two snowflakes are alike.");
}
