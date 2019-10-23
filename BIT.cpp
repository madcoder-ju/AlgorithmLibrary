int bit[ N ];
void update(int pos, int v) {
    while( pos < N ) {
        bit[ pos ] += v;
        pos += pos & -pos;
    }
}
int query(int pos) {
    int ret = 0;
    while( pos > 0 ) {
        ret += bit[ pos ];
        pos -= pos & -pos;
    }
    return ret;
}
