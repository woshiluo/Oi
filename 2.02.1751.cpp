#include <cstdio>
#include <cmath>
using namespace std;

int cnt=0;

void f(int n,int y){
	for(int i=y;i<=sqrt(n);i++){
		if(n%i==0) f(n/i,i);
	}
	cnt++;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int temp;
		scanf("%d",&temp);
		f(temp,2);
		printf("%d\n",cnt);
		cnt=0;
	}
}
