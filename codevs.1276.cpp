#include <cstdio>
using namespace std;

int main(){
	int k;
	scanf("%d",&k);
	char a[3][3]={{'*','x','*'},{' ','x','x'},{'*',' ','*'}};
	for(int i=0;i<3;i++){
		for(int q=0;q<k;q++){
			for(int j=0;j<3;j++){
				for(int p=0;p<k;p++) printf("%c",a[i][j]);
			}
			printf("\n");
		}
	}
}
