#include <cstdio>
using namespace std;

int n;
int cnt,x;
int c[3];
int num[11]={6,2,5,4,5,6,3,7,6,2};
bool y;

void dfs(int deep){
	if(deep==0){
		if(c[0]+c[1]==c[2]) cnt++;
		return ;
	}
	for(int i=0;i<11;i++){
		if(i==10&&x<=2) x++;
        for(int j=0;j<x;j++){
            if(c[j]==0){
                dfs(deep-2); 
            }
        }
		else{
			if(!y&&i==0) continue;
			else if(deep-num[i]>=0){
				if(!y) y=true;
				c[x]*=10;c[x]+=i;
				dfs(deep-num[i]);
				c[x]-=i;c[x]/=10;
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	n=n-4;
	dfs(n);
	printf("%d",cnt);
}
