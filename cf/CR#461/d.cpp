#include <cstdio>
using namespace std;

int n,cnt,temp;

int main(){
    scanf("%d",&n);
    cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i+j>n) break;
            for(int k=j+1;k<=n;k++){
                if(i+j>k&&j+k>i&&i+k>j){
                    temp=i^j^k;
                    if(temp==0) cnt++;
                }
                else break;
            }
        }
    }
    printf("if(n==%d) printf(\"%d\");\n",n,cnt);
}
