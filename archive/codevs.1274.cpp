#include <cstdio>
using namespace std;

int main(){
	int speed_limit,speed_car;
	printf("Enter the speed limit: ");
	scanf("%d",&speed_limit);
	printf("Enter the recorded speed of the car: ");
	scanf("%d",&speed_car);
	int temp=speed_limit-speed_car;
	if(temp>=0)printf("Congratulations, you are within the speed limit\n");
	if(temp<=-1&&temp>=-20)printf("You are speeding and your fine is $ 100\n");
	if(temp<=-21&&temp>=-30)printf("You are speeding and your fine is $ 270\n");
	if(temp<=-31)printf("You are speeding and your fine is $ 500\n");
	return 0;
}
