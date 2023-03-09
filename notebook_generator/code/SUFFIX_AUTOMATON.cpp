int len[N], lnk[N], pos[N], sz, last;
map<char, int> nxt[N];
void init () {
  len[0] = 0, lnk[0] = -1, nxt[0].clear(), last = 0, sz = 1;
}
void add (char c) {
  int cur = sz++;
  len[cur] = len[last] + 1, nxt[cur].clear();
  int u = last;
  while (u != -1 and !nxt[u].count(c)) {
    nxt[u][c] = cur;
    u = lnk[u];
  }
  if (u == -1) {
    lnk[cur] = 0;
  }
  else {
    int v = nxt[u][c];
    if (len[u] + 1 == len[v]) {
      lnk[cur] = v;
    }
    else {
      int w = sz++;
      len[w] = len[u] + 1, lnk[w] = lnk[v], nxt[w] = nxt[v];
      while (u != -1 and nxt[u][c] == v) {
        nxt[u][c] = w, u = lnk[u];
      }
      lnk[cur] = lnk[v] = w;
    }
  }
  last = cur;
}