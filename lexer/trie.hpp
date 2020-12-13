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

// interface class with virtual functions
class interface
{
public:
	interface() {};
	virtual ~interface() {};			// virtual destructor

	// convert char to int like hashing, for index of the children, for eg. a = 0, c = 2, and so on
	virtual int charToInt(char) = 0;	
	//virtual void insertKeyword(std::string&) = 0;
	virtual bool deleteKeyword(std::string&) = 0;
	virtual bool searchKeyword(std::string&) = 0;

	virtual bool isNodeEmpty(std::shared_ptr<TrieNode>) const = 0;

};


// trie class
class Trie : public interface
{
private:
	std::shared_ptr<TrieNode> root;
	unsigned numberOfKeys;				// store number of keywords

public:
	Trie();
	~Trie();

	int charToInt(char c);
	void insertKeyword(std::string& word, TokenType type);
	
	bool searchKeyword(std::string& word);
	TokenType searchToken(std::string& word);

	// delete a segment of the tree, basically 'search and delete', returns true if successful
	bool deletePart(std::string& word, std::shared_ptr<TrieNode>& checkout);		// pass in memory address of shared_ptr
	bool deleteKeyword(std::string& word);

	// check if a node is COMPLETELY empty, as in all 26 of its children all nullptr
	bool isNodeEmpty(std::shared_ptr<TrieNode> node) const;		

	std::shared_ptr<TrieNode> getRootNode();

};


#endif