#include <bits/extc++.h>

using namespace __gnu_pbds; // or pb_ds;

template<typename T, typename B = null_type>
using oset = tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order / order_of_key

