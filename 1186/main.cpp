#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 10000+10;

int a[maxn];
int b[maxn];

void init(){
	for(int i = 0 ; i < maxn ; i ++){
		a[i] = maxn;
		b[i] = maxn;
	}
}

void run(){
	int x , y;
	scanf("%d %d",&x , &y);
	init();
	int idx = 0;
	int stop = sqrt(x);
	for(int i = 1 ; i <= stop ; i ++){
		if(x % i == 0){
			a[idx ++] = i;
			if(x / i != i)
				a[idx ++] = x / i;
		}
	}
	sort(a , a + maxn);
	idx = 0;
	stop = sqrt(y);
	for(int i = 1 ; i <= stop ; i ++){
		if(y % i == 0){
			b[idx ++] = i;
			if(y / i != i)
				b[idx ++] = y / i;
		}
	}
	sort(b , b + maxn);
	for(int i = 0 ; i < maxn ; i ++){
		if(a[i] == maxn) break;
		for(int j = 0 ; j < maxn ; j ++){
			if(b[j] == maxn) break;
			printf("%d %d\n",a[i] , b[j]);
		}
	}
}

int main(){
	run();
	return 0;
}