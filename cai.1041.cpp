#include <cstdio>
#include <cstring>
using namespace std;
 
int n,cont,cnt,max=0x7fffffff;
int a[20][20];
bool x[20];
int b[20];

void dfs(int deep){
    if(cont==n) {
        cnt+=a[deep][1];
        if(cnt<max) max=cnt;
        cnt-=a[deep][1];
        return ;
    }
    else {
        for(int i=2;i<=n;i++){
            if(!x[i]){		
                if(cnt+a[deep][i]>=max) continue ;
                x[i]=true;
                cont++;
                cnt+=a[deep][i];
                dfs(i);
                cnt-=a[deep][i];
                x[i]=false;
                cont--;
            }
        }
    }
}

int main(){
    memset(b,0x7f,sizeof(b));
    scanf("%d",&n); 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    cont++;
    x[1]=true;
    dfs(1);
    printf("%d",max);
}
