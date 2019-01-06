#include <cstdio>
using namespace std;

int tree[20][5];

void xsbl(int i){
	printf("%d ",i);
	if(tree[i][0]!=0) xsbl(tree[i][0]);
	if(tree[i][1]!=0) xsbl(tree[i][1]);
}

void zsbl(int i){
	if(tree[i][0]!=0) zsbl(tree[i][0]);	
	printf("%d ",i);
	if(tree[i][1]!=0) zsbl(tree[i][1]);
}

void hsbl(int i){
	if(tree[i][0]!=0) hsbl(tree[i][0]);	
	if(tree[i][1]!=0) hsbl(tree[i][1]);
	printf("%d ",i);
}

int main(){
	int n;
	scanf("%d",&n);
	tree[1][3]=1;
	for(int i=1;i<=n;i++){
		int left,right;
		scanf("%d %d",&left,&right);
		if(left!=0) {
			tree[i][0]=left;
			tree[left][2]=i;
			tree[left][3]=tree[i][3]+1;
		}
		if(right!=0){
			tree[i][1]=right;
			tree[right][2]=i;
			tree[right][3]=tree[i][3]+1;
		}
	}
	xsbl(1);
	printf("\n");
	zsbl(1);
	printf("\n");
	hsbl(1);
}
