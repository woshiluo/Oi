#include <cstdio>
#include <cstring>

long long l,r,len,max;
long long f[11][11][11][2][2][2][2],num[11];

long long dp(int p,int a,int b,bool c,bool d,bool has_4,bool has_8){
    if(has_4&&has_8) return 0;
    if(p<=0) return c;
    if(~f[p][a][b][c][d][has_4][has_8]) return f[p][a][b][c][d][has_4][has_8];
    long long res=0;
    long long lim=!d?num[p]:9;    
    for(int i=0;i<=lim;i++) res+=dp(p-1,i,a,c||(i==b&&i==a),d||(i<lim),has_4||(i==4),has_8||(i==8)); 
    return f[p][a][b][c][d][has_4][has_8]=res;
}

inline long long calc(long long now){
    if(now<1e10) return 0;
    memset(f,-1,sizeof(f));
    for(len=0;now;now/=10) num[++len]=now%10;
    long long res=0;
    for(int i=1;i<=num[len];i++) res+=dp(10,i,0,0,i<num[len],i==4,i==8);
    return res;
}

int main(){
    scanf("%lld%lld",&l,&r);
    printf("%lld",calc(r)-calc(l-1));
}
