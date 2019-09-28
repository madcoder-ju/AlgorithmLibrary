void reset() {
	TIMER = 0;
	cutBridges.clear();
	for(int i = 0; i < N; i += 1) {
		g[ i ].clear();
		start[ i ] = 0;
	}
}
void getCutBridges(int node,int par) {
	start[ node ] = ++TIMER;
	low[ node ] = start[ node ];
	for(auto it : g[ node ]) {
		if( it == par ) continue;
		if( !start[ it ] ) {
			getCutBridges(it, node);
			low[ node ] = min(low[ node ], low[ it ]);
			if( low[ it ] > start[ node ] ) {
				cutBridges.push_back( {min(node, it), max(node, it)} );
			}
		} else low[ node ] = min(low[ node ], start[ it ]);
	}
}
