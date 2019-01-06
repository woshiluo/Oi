#include <cstdio>
#include <algorithm>
using namespace std;

const int N=110;

struct stu{
	char name[30];
	int money,id;
}a[N];

int n;
int qm,bj,lw,sum;
bool xb,xs;
char tmp[3];

bool cmp(stu a,stu b){
	if(a.money==b.money) return a.id<b.id;
	return a.money>b.money;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		a[i].id=i;
		scanf("%s",a[i].name);	
		scanf("%d%d",&qm,&bj);
		scanf("%s",tmp);
		xs=(tmp[0]=='Y');
		scanf("%s",tmp);
		xb=(tmp[0]=='Y');
		scanf("%d",&lw);
		if(qm>80){
			if(lw>=1) a[i].money+=8000;
			if(qm>85){
				if(bj>80) a[i].money+=4000;
				if(xb) a[i].money+=1000;
				if(qm>90) a[i].money+=2000;
			}
		}
		if(bj>80&&xs) a[i].money+=850;
		sum+=a[i].money;
	}
	sort(a+1,a+n+1,cmp);
	printf("%s\n%d\n%d",a[1].name,a[1].money,sum);
}
