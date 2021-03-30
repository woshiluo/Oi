#include <cstdio>
using namespace std;

int a[210000];

void qsort(int left,int right)
{
	if(left>=right)return ;
	int i=left;
	int j=right;
	int key=a[left];
	while(i<j){
		while(i<j&&key<=a[j]) j--;
		a[i]=a[j];
		while(i<j&&key>=a[i])i++;
		a[j]=a[i];
	}
	a[i]=key;
	qsort(left,i-1);
	qsort(i+1,right);
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	qsort(0,n-1);
	int now=a[0],cnt=0;
	for(int i=0;i<n;i++){
		if(a[i]!=now){
			printf("%d %d\n",now,cnt);
			now=a[i];
			cnt=0;
		}
		cnt++;
	}
	printf("%d %d\n",now,cnt);
}
