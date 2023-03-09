struct AC {
  const int A = 26;
  vector<vector<int>> nxt, idx;
  vector<int> lnk, out_lnk, ans;
  AC () { newNode(); }
  int newNode() {
    nxt.eb(A, 0), idx.eb(0);
    lnk.eb(0), out_lnk.eb(0), ans.eb(0);
    return nxt.size() - 1;
  }
  void clear () {
    nxt.clear(), idx.clear();
    lnk.clear(), out_lnk.clear(), ans.clear();
    newNode();
  }
  int add (string p, int i) {
    int u = 0;
    for (auto c: p) {
      int id = c - 'a';
      if (!nxt[u][id])  nxt[u][id] = newNode();
      u = nxt[u][id];
    }
    idx[u].eb(i);
    return u;
  }
  void build () {
    queue<int> q;  q.push(0);
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (int i = 0; i < A; ++i) {
        int v = nxt[u][i];
        if (!v)  nxt[u][i] = nxt[lnk[u]][i];
        else {
          lnk[v] = u? nxt[lnk[u]][i]: 0;
          out_lnk[v] = idx[lnk[v]].empty()? out_lnk[lnk[v]]: lnk[v];
          q.push(v);
          // dp[v] = dp[v] + dp[lnk[v]]
        }
      }
    }
  }
  void trav (string T) {
    int u = 0;
    for (auto c: T) {
      int id = c - 'a';
      while (u and !nxt[u][id])  u = lnk[u];
      u = nxt[u][id];
      int x = u;
      while (x) {
        for (auto i: idx[x]) {
          ans[i]++;
        }
        x = out_lnk[x];
      }
    }
  }
};
//AC ac;  ac.add(pi, i);  ac.build();  ac.trav(T);