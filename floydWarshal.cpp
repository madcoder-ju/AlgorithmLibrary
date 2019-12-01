for(int i = 1; i <= n; i += 1) {
			for(int j = 1; j <= n; j += 1) {
				if( i != j ) g[ i ][ j ] = 4e18;
				else g[ i ][ j ] = 0LL;
			}
		}

		while( m-- ) {
			int u, v, d; cin >> u >> v >> d;
			g[ u ][ v ] = d;
			g[ v ][ u ] = d;
		}

		for(int k = 1; k <= n; k += 1) {
			for(int i = 1; i <= n; i += 1) {
				for(int j = 1; j <= n; j += 1) {
					if( g[ i ][ j ] > g[ i ][ k ] + g[ k ][ j ] ) {
						g[ i ][ j ] = g[ i ][ k ] + g[ k ][ j ];
					}
				}
			}
		}
