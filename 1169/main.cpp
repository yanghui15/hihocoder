//#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 200000 + 100;
const int MAX_NUM = 1e9 + 10;
const int MIN_NUM = -1;

struct Que{
	int idx;
	int L , R;
	int k;
	int mn , mx;
};

struct SegNode{
	int left , right;
	int mx , mn;
	int mid(){
		return (left + right) / 2;
	}
};

struct Input{
	int idx;
	int val;
};

Que que[maxn];
SegNode tree[maxn * 4];
Input value[maxn];

bool cmp1(const Que& q1 , const Que& q2){
	return q1.idx < q2.idx;
}

bool cmp2(const Que& q1 , const Que& q2){
	return q1.k < q2.k;
}

bool cmp3(const Que& q1 , const Que& q2){
	return q1.k > q2.k;
}

bool cmp4(const Input& a , const Input& b){
	return a.val > b.val;
}

bool cmp5(const Input& a , const Input& b){
	return a.val < b.val;
}

void pushup(int idx){
	tree[idx].mx = max(tree[idx << 1].mx , tree[idx << 1 | 1].mx);
	tree[idx].mn = min(tree[idx << 1].mn , tree[idx << 1 | 1].mn);
}

void build(int left , int right , int idx){
	tree[idx].left = left;
	tree[idx].right = right;
	if(left == right){
		tree[idx].mn = MAX_NUM;
		tree[idx].mx = MIN_NUM;
		return;
	}
	int mid = tree[idx].mid();
	build(left , mid , idx << 1);
	build(mid + 1 , right , idx << 1 | 1);
	pushup(idx);
}

void update(int left , int right , int idx , int val_idx , int val){
	if(left == right){
		tree[idx].mn = val;
		tree[idx].mx = val;
		return ;
	}
	int mid = tree[idx].mid();
	if(val_idx <= mid)
		update(left , mid , idx << 1 , val_idx , val);
	else 
		update(mid + 1 , right , idx << 1 | 1 , val_idx , val);
	pushup(idx);
}

int queryMX(int left , int right , int idx ){
	if(left == tree[idx].left && right == tree[idx].right){
		return tree[idx].mx;
	}
	int mid = tree[idx].mid();
	if(right <= mid){
		return queryMX(left , right , idx << 1);
	}else if(left > mid){
		return queryMX(left , right , idx << 1 | 1);
	}else{
		return max(queryMX(left , mid , idx << 1) , queryMX(mid + 1 , right , idx << 1 | 1));
	}
}

int queryMN(int left , int right , int idx){
	if(left == tree[idx].left && right == tree[idx].right){
		return tree[idx].mn;
	}
	int mid = tree[idx].mid();
	if(right <= mid){
		return queryMN(left , right , idx << 1);
	}else if(left > mid){
		return queryMN(left , right , idx << 1 | 1);
	}else{
		return min(queryMN(left , mid , idx << 1) , queryMN(mid + 1 , right , idx << 1 | 1));
	}
}

void solve(){
	int n , q;
	scanf("%d %d",&n,&q);
	for(int i = 1 ; i <= n ; i ++){
		value[i].idx = i;
		scanf("%d",&value[i].val);	
	}
	for(int i = 0 ; i < q ; i ++){
		que[i].idx = i;
		scanf("%d %d %d",&que[i].L , &que[i].R , &que[i].k);
	}
	sort(value+1 , value + n + 1 , cmp5);
	sort(que , que + q , cmp2);
	build(1 , n , 1);
	int val_idx = 1;
	for(int i = 0 ; i < q ; i ++){
		while(val_idx <= n && value[val_idx].val <= que[i].k){
			//printf("update %d %d %d\n",value[val_idx].idx, value[val_idx].val , que[i].k);
			update(1 , n , 1 , value[val_idx].idx , value[val_idx].val);
			val_idx ++;
		}
		que[i].mx = queryMX(que[i].L , que[i].R , 1);
		//printf("%d\n",que[i].mx);
	}
	sort(value + 1 , value + n + 1 , cmp4);
	sort(que , que + q , cmp3);
	build(1 , n , 1);
	val_idx = 1;
	for(int i = 0 ;  i < q ; i ++){
		while(val_idx <= n && value[val_idx].val >= que[i].k){
			//printf("update %d %d %d\n",value[val_idx].idx, value[val_idx].val , que[i].k);
			update(1 , n , 1 , value[val_idx].idx , value[val_idx].val);
			val_idx ++;
		}
		que[i].mn = queryMN(que[i].L , que[i].R , 1);
		//printf("%d\n",que[i].mn);
	}
	sort(que , que + q , cmp1);
	for(int i = 0 ; i < q ; i ++){
		if(que[i].mx == MIN_NUM){
			printf("%d\n",que[i].mn - que[i].k);
		}else{
			if(que[i].mn == MAX_NUM){
				printf("%d\n",que[i].k - que[i].mx);
			}else{
				printf("%d\n",min(que[i].k - que[i].mx , que[i].mn - que[i].k));
			}
		}
	}
}

void run(){
	int T;
	scanf("%d",&T);
	for(int i = 1 ; i <= T ; i ++){
		printf("Case #%d:\n",i);
		solve();
	}
}

int main(){
	run();
	return 0;
}