## Range Addition and Range Assign and Range sum
int n;
ll t[3 * N], p[3 * N], p2[3 * N]; //t for sum, p for assign & p2. for add
void pull(int v) {
  t[v] = t[2 * v] + t[2 * v + 1];
}
void push(int v, int st, int ed) {
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  if (p[v] != -1) {
    t[lc] = p[v] * (md - st + 1);
    t[rc] = p[v] * (ed - md);
    p[lc] = p[rc] = p[v];
    p2[lc] = p2[rc] = 0;
    p[v] = -1;
  }
  if (p2[v]) {
    t[lc] += p2[v] * (md - st + 1);
    t[rc] += p2[v] * (ed - md);
    p2[lc] += p2[v];
    p2[rc] += p2[v];
    p2[v] = 0;
  }
}
void assign(int l, int r, int x, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return;
  if (l <= st and ed <= r) {
    t[v] = 1LL * (ed - st + 1) * x;
    p[v] = x;
    p2[v] = 0;
    return;
  }
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  push(v, st, ed);
  assign(l, r, x, lc, st, md);
  assign(l, r, x, rc, md + 1, ed);
  pull(v);
}
void add(int l, int r, int x, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return;
  if (l <= st and ed <= r) {
    t[v] += 1LL * (ed - st + 1) * x;
    p2[v] += x;
    return ;
  }
  push(v, st, ed);
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  add(l, r, x, lc, st, md);
  add(l, r, x, rc, md + 1, ed);
  pull(v);
}
ll rsum(int l, int r, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return 0;
  if (l <= st and ed <= r) return t[v];
  push(v, st, ed);
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  ll lret = rsum(l, r, lc, st, md);
  ll rret = rsum(l, r, rc, md + 1, ed);
  return lret + rret;
}
## Make All Elements <= k and Make all elements >= k on range & Point Query:
const int I = 1e9 + 9;
int t[3 * N], pa[3 * N], pr[3 * N], ar[3 * N]; //pa for propagate adding, pr for propagate remove, ar for check last on is adding(1) or remove(0)
void fg(int x, int u) {   //function for make_greater
  t[u] = max(t[u], x);
  pa[u] = max(pa[u], x);
  pr[u] = max(pr[u], x);
  ar[u] = 1;
}
void fl(int x, int u) {   //function for make_less
  t[u] = min(t[u], x);
  pr[u] = min(pr[u], x);
  pa[u] = min(pa[u], x);
  ar[u] = 0;
}
void push(int u) {
  int v = 2 * u, w = 2 * u + 1;
  if (ar[u] == 0) {
    if (pa[u] != -1) {
      fg(pa[u], v); fg(pa[u], w);
    }
    if (pr[u] != I) {
      fl(pr[u], v); fl(pr[u], w);
    }
  } else {
    if (pr[u] != I) {
      fl(pr[u], v); fl(pr[u], w);
    }
    if (pa[u] != -1) {
      fg(pa[u], v); fg(pa[u], w);
    }
  }
  pa[u] = -1; pr[u] = I;
}
void make_greater(int l, int r, int x, int u = 1, int s = 0, int e = N - 1) {
  if (l > e or r < s)  return;
  if (l <= s and e <= r) {
    fg(x, u);
    return ;
  }
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  make_greater(l, r, x, v, s, m);
  make_greater(l, r, x, w, m + 1, e);
}
void make_less(int l, int r, int x, int u = 1, int s = 0, int e = N - 1) {
  if (l > e or r < s)  return;
  if (l <= s and e <= r) {
    fl(x, u);
    return;
  }
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  make_less(l, r, x, v, s, m);
  make_less(l, r, x, w, m + 1, e);
}
int at(int i, int u = 1, int s = 0, int e = N - 1) {
  if (s == e)  return t[u];
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (i <= m)  return at(i, v, s, m);
  else  return at(i, w, m + 1, e);
}
