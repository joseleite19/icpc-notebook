struct palindromic_tree {
    struct node {
        int length, link;
        map<char, int> to;
        node(int length, int link): length(length), link(link) {}
    };
    vector<node> nodes;
    int current;
    palindromic_tree(): current(1) {
        nodes.push_back(node(-1, 0));
        nodes.push_back(node(0, 0));
    }
    void add(int i, string& s) {
        int parent = nodes[current].length == i ? nodes[current].link : current;
        while (s[i - nodes[parent].length - 1] != s[i])
            parent = nodes[parent].link;
        if (nodes[parent].to.find(s[i]) != nodes[parent].to.end()) {
            current = nodes[parent].to[s[i]];
        } else {
            int link = nodes[parent].link;
            while (s[i - nodes[link].length - 1] != s[i])
                link = nodes[link].link;
            link = max(1, nodes[link].to[s[i]]);
            current = nodes[parent].to[s[i]] = nodes.size();
            nodes.push_back(node(nodes[parent].length + 2, link));
        }
    }
    void insert(string& s) {
        current = 1;
        for (int i = 0; i < int(s.size()); i++)
            add(i, s);
    }
};
