#include <cstdio>
using namespace std;

int main(){
	double n,i=1;
	scanf("%lf",&n);
	double cnt=0;
	while(1){
		cnt+=1/(double)i;
		i++;
		if(cnt>=n) break;
	}
	 printf("%.0lf",i);
}
