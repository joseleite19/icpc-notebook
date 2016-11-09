// Min-cost max-flow (uses DFS)
//
// Given a directed weighted graph, source, and sink, computes the minimum cost
// of the maximum flow from source to sink.
// This version uses DFS to find shortest paths and gives good performance on
// very "shallow" graphs: graphs which have very short paths between source
// and sink (e.g. at most 10 edges).
// In such cases this algorithm can be orders of magnitude faster than the
// Dijkstra version.
//
// To use, call init(n), then add edges using edge(x, y, c, w), and finally
// call run(src, sink).
//
// Functions:
// - init(n) initializes the algorithm with the given number of nodes
// - edge(x, y, c, w) adds an edge x->y with capacity c and weight w
// - run(src, sink) runs the algorithm and returns {total_cost, total_flow}
//
// Time complexity: O(V * E^3)
//
// Constants to configure:
// - MAXV is the maximum number of vertices
// - MAXE is the maximum number of edges (i.e. twice the calls to function edge)
// - oo is the "infinity" value

namespace Mcmf {
  const int MAXV = 1000100;
  const int MAXE = 1000100;
  const llint oo = 1e18;

  int V, E;
  int last[MAXV], curr[MAXV], bio[MAXV]; llint pi[MAXV];
  int next[MAXE], adj[MAXE]; llint cap[MAXE], cost[MAXE];

  void init(int n) {
    V = n;
    E = 0;
    REP(i, V) last[i] = -1;
    REP(i, V) pi[i] = 0;
  }

  void edge(int x, int y, llint c, llint w) {
    adj[E] = y; cap[E] = c; cost[E] = +w; next[E] = last[x]; last[x] = E++;
    adj[E] = x; cap[E] = 0; cost[E] = -w; next[E] = last[y]; last[y] = E++;
  }

  llint push(int x, int sink, llint flow) {
    if (x == sink) return flow;
    if (bio[x]) return 0;
    bio[x] = true;

    for (int &e = curr[x]; e != -1; e = next[e]) {
      int y = adj[e];

      if (cap[e] && pi[x] == pi[y] + cost[e])
        if (llint f = push(y, sink, min(flow, cap[e])))
          return cap[e] -= f, cap[e^1] += f, f;
    }
    return 0;
  }

  pair<llint, llint> run(int src, int sink) {
    llint total = 0;
    llint flow = 0;
    pi[src] = oo;

    for (;;) {
      REP(i, V) bio[i] = false;
      REP(i, V) curr[i] = last[i];

      while (llint f = push(src, sink, oo)) {
        total += pi[src] * f;
        flow += f;
        REP(i, V) bio[i] = false;
      }

      llint inc = oo;
      REP(x, V) if (bio[x]) {
        for (int e = last[x]; e != -1; e = next[e]) {
          int y = adj[e];
          if (cap[e] && !bio[y]) inc = min(inc, pi[y] + cost[e] - pi[x]);
        }
      }
      if (inc == oo) break;

      REP(i, V) if (bio[i]) pi[i] += inc;
    }
    return {total, flow};
  }
}