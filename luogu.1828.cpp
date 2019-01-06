#include <cstdio>
#include <cstring>
using namespace std;

int temp,X,y,l,sum,cnt;
int a[810][810];
int x[810];
int d[810][810];

int main(){
    int n,p,c;

    scanf("%d%d%d",&n,&p,&c);
    for(int i=0;i<=p;i++)//手动memset
    {
        for(int j=0;j<=p;j++)
        {
            if(i==j){
                d[i][j]=0;
            }
            else
            {
                d[i][j]=9999999;
            }
        }
    }
    for(int i=0;i<n;i++) {
        scanf("%d",&temp);
        x[temp-1]++;
    }
    for(int i=0;i<c;i++){
        scanf("%d%d%d",&X,&y,&l);
        d[X-1][y-1]=l;
        d[y-1][X-1]=l;
    }
    for(int k=0;k<p;k++){
        for(int i=0;i<p;i++){
            for(int j=0;j<i;j++){
                if(d[i][k]+d[j][k]<d[i][j]) {
                    d[i][j]=d[i][k]+d[j][k];
                    d[j][i]=d[i][j];
                }
            }
        }
    }
    cnt=0x7ffffff;
    for(int i=0;i<p;i++){
        sum=0;
        for(int j=0;j<p;j++){
            sum+=d[i][j]*x[j];
        }
        if(cnt>sum) cnt=sum;
    }
    printf("%d",cnt);
}
