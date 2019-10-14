source code: works fine upto 2^9

void dfs(int pos, int s, vector<pair<int,int>> factors) {
	if( pos == factors.size() ) {
		if( s > l ) ans.push_back(s);
		return ;
	}

	int x = factors[ pos ].first;
	int y = factors[ pos ].second;

	dfs(pos + 1, s, factors);
	while( y-- ) {
		dfs(pos + 1, s * x, factors);
		x *= factors[ pos ].first;
	}
}
