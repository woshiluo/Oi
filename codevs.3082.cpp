#include <cstdio>
using namespace std;

int cnt;

void f(int n){
	if(n==1) return;
	else if(n%2==0) {cnt++;f(n/2);}
	else {cnt++;f(3*n+1);}
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int temp;
		cnt=0;
		scanf("%d",&temp);
		f(temp);
		printf("%d\n",cnt);
	}
}
