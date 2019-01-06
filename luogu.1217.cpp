#include <cstdio>
#include <cmath>
using namespace std;

int frst,last;
int max_deep;

void dfs(int fir,int lst){
    
}

int main(){
    scanf("%d%d",&frst,&last);
    int tmp=log(last);
    int tmp_2=log(frst);
    for(int i=tmp_2;i<=tmp;i++){
        max_deep=i;
        dfs(frst,last);
    }
}
