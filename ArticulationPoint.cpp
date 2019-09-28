void reset() {
	root = 1;
	TIMER = 0;
	cutVertices.clear();
	for(int i = 0; i < n + 1; i += 1) {
		g[ i ].clear();
		start[ i ] = 0;
	}
}
void getCutVertices(int node) {
	bool flag = 0;
	int child = 0;
	start[ node ] = ++TIMER;
	low[ node ] = start[ node ];
	for(auto it : g[ node ]) {
		if( !start[ it ] ) {
			getCutVertices(it);
			child += 1;
			low[ node ] = min(low[ node ], low[ it ]);
			if( low[ it ] >= start[ node ] ) flag = true;
		} else low[ node ] = min(low[ node ], start[ it ]);
	}
	if( (node == root && child > 1) || (node != root && flag) ) {
		cutVertices.push_back(node);
	}
}
