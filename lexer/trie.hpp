#ifndef TRIE_HPP
#define TRIE_HPP

#include <memory>		// shared_ptr
#include <string>

#include "token.hpp"

// number of ascii chars used
#define TOTAL_CHAR 94

class TrieNode
{
public:
	// shared_ptr; pointers can point to the same object; object destroyed if the last pointer is destroyed
	// array of 26 TrieNode pointers
	// use shared pointer because in pointer will be 'recreated' in multiple instances
	std::shared_ptr<TrieNode>   children[TOTAL_CHAR];

	bool isKeyword;		// tracks if it is the end of a word};
	TokenType nodeToken;

	// constructor
	TrieNode();
};



// trie class
class Trie
{
private:
	std::shared_ptr<TrieNode> root;
	unsigned numberOfKeys;				// store number of keywords

public:
	Trie();
	~Trie();

	int charToInt(char c);
	void insertKeyword(std::string& word, TokenType type);
	
	bool isCharNode(const char* c, std::shared_ptr<TrieNode> origin);
	bool isCharWord(const char* c, std::shared_ptr<TrieNode> origin);
	
	bool searchKeyword(std::string& word);


	// delete a segment of the tree, basically 'search and delete', returns true if successful
	bool deletePart(std::string& word, std::shared_ptr<TrieNode>& checkout);		// pass in memory address of shared_ptr
	bool deleteKeyword(std::string& word);

	// check if a node is COMPLETELY empty, as in all 26 of its children all nullptr
	bool isNodeEmpty(std::shared_ptr<TrieNode> node) const;		

	std::shared_ptr<TrieNode> getRootNode();

};


#endif