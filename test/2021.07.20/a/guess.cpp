#include "guess.h"
#include <bits/stdc++.h>

std::vector<int> checked_part;

int dfs( int left, int rig ) {
	if( left == rig ) {
		if( checked_part.size() && ask1( checked_part, {left} ) ) 
			return left;
		return -1;
	}
	int mid = ( left + rig ) >> 1;
	std::vector<int> lpart, rpart;
	for( int i = left; i <= mid; i ++ ) 
		lpart.push_back(i);
	for( int i = mid + 1; i <= rig; i ++ ) 
		rpart.push_back(i);
	if( ask1( lpart, rpart ) ) {
		if( checked_part.size() == 0 || checked_part.size() > rpart.size() )
			checked_part = rpart;
		return dfs( left, mid );
	}
	else {
		if( checked_part.size() != 0 ) {
			if( ask1( checked_part, lpart ) ) 
				return dfs( left, mid );
			else if( ask1( checked_part, rpart ) ) 
				return dfs( mid + 1, rig );
		}
		int res;
		res = dfs( left, mid );
		if( res != -1 ) 
			return res;
		res = dfs( mid + 1, rig );
		if( res != -1 )
			return res;
	}
	return -1;
}

std::vector<int> solve(int n, int P, int Q) {
	int pos = dfs( 0, n - 1 );
	std::vector<int> ans(n);
	ans[pos] = 1;
	for( int i = 0; i < n; i ++ ) {
		if( pos == i ) 
			continue;
		ans[i] = ask1( {i}, {pos} );
	}
	if( ask2( ans ) ) 
		return ans;
	for( int i = 0; i < n; i ++ ) 
		ans[i] *= -1;
	return ans;
}
