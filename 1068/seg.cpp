#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 1e6 + 10;

struct Node{
	int left , right;
	int mn;
	int mid (){
		return (left + right) / 2;
	}
};
Node tree[maxn * 4];
int value[maxn];

void pushup(int idx){
	tree[idx].mn = min(tree[idx << 1].mn , tree[idx << 1 | 1].mn);
}

void build(int left , int right , int idx){
	tree[idx].left = left;
	tree[idx].right = right;
	if(left == right){
		tree[idx].mn = value[left];
		return;
	}
	int mid = (left + right) / 2;
	build(left , mid , idx << 1);
	build(mid + 1 , right , idx << 1 | 1);
	pushup(idx);
}

int query(int left , int right , int idx){
	if(tree[idx].left == left && right == tree[idx].right){
		return tree[idx].mn;
	}
	int mid = tree[idx].mid();
	if(right <= mid)
		return query(left , right , idx << 1);
	else if(left > mid)
		return query(left , right , idx << 1 | 1);
	else
		return min(query(left , mid , idx << 1) , query(mid + 1 , right , idx << 1 | 1));
}

void run(){
	int n , q , l , r;
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
		scanf("%d",&value[i]);
	build(1 , n , 1);
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++){
		scanf("%d %d",&l , &r);
		printf("%d\n",query(l , r ,1));
	}
}

int main(){
	run();
	return 0;
}
