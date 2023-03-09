## Ordered Set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> oset;
## unordered_map
struct chash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
unordered_map<pair<int, int>, int, chash> maf;
maf.reserve(max_len);
maf.max_load_factor(0.25);
## gp_hash_table:
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash{
  int operator()(ii p) const {
    return p.first*31 + p.second;
  }
};
gp_hash_table<ii, int, chash> cnt;
## Random Number
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int x = rng() % 495;
## Running time
clock_t st = clock();
double t = (clock() - st) / (1.0 * CLOCKS_PER_SEC);
string line;  getline(cin, line);
istringstream iss;
string word;
while (iss >> word) {
  cout << word << "\n";
}
#pragma GCC target("popcnt") ulimit -s 65532

