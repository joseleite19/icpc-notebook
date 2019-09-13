namespace sf {

const int inf = 1e9;
const int maxn = 200005;
char s[maxn];
map<int, int> to[maxn];
int len[maxn], fpos[maxn], link[maxn];
int node, pos;
int sz = 1, n = 0;

int make_node(int _pos, int _len) {
  fpos[sz] = _pos;
  len[sz] = _len;
  return sz++;
}
void go_edge() {
  while (pos > len[to[node][s[n - pos]]]) {
    node = to[node][s[n - pos]];
    pos -= len[node];
  }
}
void add_letter(int c) {
  s[n++] = (char)c;
  pos++;
  int last = 0;
  while (pos > 0) {
    go_edge();
    int edge = s[n - pos];
    int &v = to[node][edge];
    int t = s[fpos[v] + pos - 1];
    if (v == 0) {
      v = make_node(n - pos, inf);
      link[last] = node;
      last = 0;
    } else if (t == c) {
      link[last] = node;
      return;
    } else {
      int u = make_node(fpos[v], pos - 1);
      to[u][c] = make_node(n - 1, inf);
      to[u][t] = v;
      fpos[v] += pos - 1;
      len[v] -= pos - 1;
      v = u;
      link[last] = u;
      last = u;
    }
    if (node == 0)
      pos--;
    else
      node = link[node];
  }
}
void add_string(char *str) {
  for (int i = 0; str[i]; i++) add_letter(str[i]);
  add_letter('$');
}
bool is_leaf(int u) { return len[u] > n; }
int get_len(int u) {
  if (!u) return 0;
  if (is_leaf(u)) return n - fpos[u];
  return len[u];
}
int leafs[maxn];
int calc_leafs(int u = 0) {
  leafs[u] = is_leaf(u);
  for (const auto &c : to[u]) leafs[u] += calc_leafs(c.second);
  return leafs[u];
}
};  // namespace sf

int main() { sf::len[0] = sf::inf; }
