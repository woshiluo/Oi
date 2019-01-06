#include <cstdio>
#include <math.h>
using namespace std;

bool zs(int n){
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0) return true;
	}
	return false;
}

int main(){
	int n;
	scanf("%d",&n);
	if(zs(n)) printf("\\n");
	else printf("\\t");
}
