#include <cstdio>
using namespace std;

int tree[20][4],cs[20];

int main(){
	int n,max=-1;
	scanf("%d",&n);
	tree[1][3]=1;
	for(int i=1;i<=n;i++){
		int left,right;
		scanf("%d %d",&left,&right);
		if(left!=0) {
			tree[i][0]=left;
			tree[left][3]=tree[i][3]+1;
		}
		if(right!=0){
			tree[i][1]=right;
			tree[right][3]=tree[i][3]+1;
		}
		cs[tree[i][3]]++;
		if(tree[i][3]>max)max=tree[i][3];
	}
	int max_k=-1;
	for(int i=1;i<=n;i++){
		if(cs[i]>max_k)max_k=cs[i];
	}
	printf("%d %d",max_k,max);
}
