#include <cstdio>
#include <cmath>

int n,tmp,ans;

int main(){
    scanf("%d",&n);
    tmp=std::sqrt(n);
    if(n%tmp==0){
        printf("%d",tmp+(n/tmp));
        return 0;
    }
    else {
        ans=tmp+(n/tmp);
        printf("%d",ans+1);
    }
}
