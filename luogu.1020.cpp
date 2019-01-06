#include <cstdio>
using namespace std;

int cnt=0,tcnt,mcnt,max;
int a[110000];

int main(){
	char temp;
	while(scanf("%d",&a[cnt++])!=EOF)continue;
	max=a[0];tcnt=0;
	for(int i=0;i<=cnt;i++){
		if(a[i]>=max) {
			tcnt++;
			max=a[i];
		}
	}
	for(int i=0;i<=cnt;i++){
		max=a[i];tcnt=0;
		for(int j=i+1;j<=cnt;j++){
			if(a[j]>max){
				break;
			}
			else {
				max=a[j];	
			}
			tcnt++;
		}
		if(tcnt>mcnt) mcnt=tcnt;
	}
	max=a[0];tcnt=1;
	for(int i=0;i<=cnt;i++){
		if(a[i]>=max) {
			tcnt++;
			max=a[i];
		}
	}
	printf("%d\n%d",mcnt,tcnt);
}
