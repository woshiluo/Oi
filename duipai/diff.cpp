#include <cstdio>
#include <cstdlib>

int cnt;

int main(){
	while(1){
		printf("%4d",cnt++);
		system("./temp.py");
		system("./temp < test1.in >qwq.out");
		if(system("diff qwq.out test1.out")!=0){
			printf("WA\n\n");
			break;
		}
		printf("AC\n\n");
	}
}
