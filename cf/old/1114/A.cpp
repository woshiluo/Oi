#include <cstdio>

int an,dm,mi;
int gr,pu,bl;

int main(){
	scanf("%d%d%d", &an, &dm, &mi);
	scanf("%d%d%d", &gr, &pu, &bl);

	if(an > gr) {
		printf("NO\n");
		return 0;
	}
	else gr -= an;

	if(pu + gr < dm){
		printf("NO\n");
		return 0;
	}
	else {
		if(pu <= dm) {dm -= pu; pu = 0;}
		else {pu -= dm; dm = 0;}
		if(gr < dm) {
			printf("NO\n");
			return 0;
		}
		else gr -= dm;
	}

	if(gr + pu + bl < mi) printf("NO\n");
	else printf("YES\n");
}
