#include <cstdio>
#include <cstring>

struct FUCK{
	char name[20];
	int a[5];
}a[1100];

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",&a[i].name);
		scanf("%d.%d.%d.%d",&a[i].a[1],&a[i].a[2],&a[i].a[3],&a[i].a[4]);
	}
	FUCK temp;
	for(int i=1;i<=m;i++){
		scanf("%s",&temp.name);
		scanf("%d.%d.%d.%d;",&temp.a[1],&temp.a[2],&temp.a[3],&temp.a[4]);
		for(int j=n;j>=1;j--){
			if(temp.a[1]==a[j].a[1]&&temp.a[2]==a[j].a[2]&&temp.a[3]==a[j].a[3]&&temp.a[4]==a[j].a[4]){
				printf("%s %d.%d.%d.%d; #%s\n",temp.name,temp.a[1],temp.a[2],temp.a[3],temp.a[4],a[j].name);
			}
		}
	}
}
