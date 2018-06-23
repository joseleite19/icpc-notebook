#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node{
	bool is_end;
	int prefixes, words, maxsize;
	struct node* edge[26];
	//initialize()
	//addword(vertex, word)
	//countPrefixes(vertex, prefix)
	//countWords(vertex, word)

	node(){
		maxsize = 0;
		prefixes = 0;
		words = 0;
		is_end = false;
		for(int i = 0; i < 26; i++) edge[i] = NULL;
	}

	void addWord(string word, int tam){
		maxsize = max(tam, maxsize);
		if(word.empty()){
			prefixes++;
			words++;
		}
		else{
			prefixes++;
			int k = word[0] - 'a';
			if(edge[k] == NULL){
				node *p1 = new node();
				p1->addWord(word.substr(1,word.size()-1), tam );
				edge[k] = p1;
			}
			else
				edge[k]->addWord(word.substr(1,word.size()-1), tam );
		}
	}

	int countWords(string word){
		if(word.empty())
			return words;
		int k = word[0] - 'a';
		if(edge[k] == NULL)
			return 0;
		return edge[k]->countWords(word.substr(1,word.size()-1) );
	}

	int countPrefixes(string word){
		if(word.empty())
			return prefixes;
		int k = word[0] - 'a';
		if(edge[k] == NULL)
			return 0;
		return edge[k]->countPrefixes(word.substr(1,word.size()-1) );
	}

	int countSize(string word){
		if(word.empty())
			return maxsize;
		int k = word[0] - 'a';
		if(edge[k] == NULL)
			return 0;
		return edge[k]->countSize(word.substr(1,word.size()-1) );
	}
};

int main() {
	int n,m;
	string s;
	
	while(scanf("%d", &n) != EOF){
		node *trie = new node();
		while(n--){
			cin >> s;
			trie->addWord(s, s.size());
		}
		scanf("%d", &m);
		while(m--){
			cin >> s;
			int x = trie->countPrefixes(s);
			if(x == 0)
				cout << "-1\n";
			else
				cout << x << " " << trie->countSize(s) << endl;
		}
	}


	return 0;
}

