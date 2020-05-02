/*
 * first number of unfriendly crossing pairs = the number of pairs li < lj && ri > rj && abs ( i - j ) > k 
 * lets consider we have an array A which initially filled with -1 
 * let id [i] is the postion of i in the second array
 * we iterate through the breeds in ascending order according to the li calculate the number of numbers is the interval [ id[i] , n ] such the A [j] != -1 && A[j] < i - k && A [j] > i + k , then update A [ id [i] ] with i 
 * without the updating the last task can be solved using merge sort tree , so we use a BIT in every node in the merge sort tree to apply the updating */
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int n , k ;
vi tree [400009] , BIT [400009] ;
int a [100009] , l [100009] , r [100009] , id [100009] ;
void build ( int node , int l , int r ) {
	tree [node] .pb ( 0 ) ;
	BIT  [node] .pb ( 0 ) ;
	if ( l == r ) {
		tree [node] .pb ( a [l] ) ;
		BIT  [node] .pb ( 0 ) ;
		return ;
	}
	build ( node * 2 , l , mid ) ;
	build ( node *2+1, mid+1, r );
	for ( int i = 1 ; i < tree [node*2] .size() ; i ++ ) tree [node] .pb ( tree [node*2][i] ) , BIT [node] .pb ( 0 ) ;
	for ( int i = 1 ; i < tree [node*2+1].size(); i ++ ) tree [node] .pb ( tree [node*2+1][i] ) , BIT [node] .pb ( 0 ) ; 
	sort ( tree [node].begin() , tree [node].end() ) ;
}
void updBIT ( int pos , int node ) {
	for ( int i = pos ; i < BIT[node].size() ; i +=  i & -i  ) BIT [node][i] ++ ;
}
int Sum ( int pos , int node ) {
	int ans = 0 ;
	for ( int i = pos ; i > 0 ; i -= i & -i  ) {
		ans += BIT [node][i] ;
	}
	return ans ;
}
void upd ( int node , int l , int r , int id , int x ) {
	int pos = lb ( tree[node].begin() , tree[node].end() , x ) - tree[node].begin() ;
	updBIT ( pos , node ) ;
	if ( l == r ) return ;
	if ( id <= mid ) upd ( node *2 , l , mid , id , x ) ;
	else upd ( node *2+1 , mid +1 , r , id , x ) ;
}
int query ( int node , int l , int r , int s , int e , int x ) {
	if ( l > r || s > r || e < l ) return 0 ;
	if ( s <= l && e >= r ) {
		int pos = ub ( tree[node].begin() , tree[node].end() , x ) - tree[node].begin() ; 
		pos -- ;
		return Sum ( pos , node ) ;
	}
	return query ( node *2 , l , mid , s , e , x ) + query ( node *2+1 , mid+1 , r , s , e , x ) ;
}
int main () {
	ifstream fin ("friendcross.in");
	ofstream fout("friendcross.out");
	fin >> n >> k ;
	for ( int i = 0 ; i < n ; i ++ ) fin >> l [i] ;
	for ( int i = 0 ; i < n ; i ++ ) fin >> r [i] , a [i] = r [i] , id [ r[i] ] = i ;
	build ( 1 , 0 , n -1 ) ;
	ll ans = 0 ;
	for ( int i = 0 ; i < n ; i ++ ) {
		int ID = id [ l[i] ] ;
		int L = query ( 1 , 0 , n -1 , ID , n-1 , l [i] - k - 1 ) ;
		int R = query ( 1 , 0 , n -1 , ID , n-1 , l [i] + k ) ;
		int All = query ( 1 , 0 , n -1 , ID , n-1 , n ) ;
		ans += L ;
		ans += All - R ; 
		upd ( 1 , 0 , n -1 , ID , l[i] ) ;
	}
	fout << ans << endl ; 
}
