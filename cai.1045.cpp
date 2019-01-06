#include <cstdio>
#include <iostream>
using namespace std;

double X,Y,N;

double dfs(double x,double y,double k){
	if(k==1) return max(x,y)/min(x,y);

	double ans=9999999.0;

	for(int i=1;i<k/2+1;i++){
		ans=min(ans,max(dfs(x,y/k*i,i),dfs(x,y/k*(k-i),k-i)));
	}
	for(int i=1;i<k/2+1;i++){
		ans=min(ans,max(dfs(x/k*i,y,i),dfs(x/k*(k-i),y,k-i)));
	}
	return ans;
}

int main(){
	scanf("%lf%lf%lf",&X,&Y,&N);
	printf("%.6lf",dfs(X,Y,N));
}
