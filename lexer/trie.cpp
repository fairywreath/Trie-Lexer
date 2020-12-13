#include "trie.hpp"


TrieNode::TrieNode()
{
	for (int i = 0; i < TOTAL_CHAR; i++)
	{
		children[i] = std::shared_ptr<TrieNode>();			// assign a nullptr to each children
	}
	isKeyword = false;
}


// for trie class
Trie::Trie()
{
	root = std::shared_ptr<TrieNode>(new TrieNode());		// create new TrieNode() object and assign it to root
	numberOfKeys = 0;
}

Trie::~Trie() {}		// smart pointer handles everything


int Trie::charToInt(char c)
{
	return static_cast<int>(c - '!');
}

void Trie::insertKeyword(std::string& word, TokenType type)
{
	std::shared_ptr<TrieNode> current = root;   // this is why shared_ptr is used; need std::move for unique_ptr
	for (int i = 0; i < word.size(); i++)		// string.size() to get strlen
	{
		// if prefix letter has not been created
		if (current->children[charToInt(word[i])] == std::shared_ptr<TrieNode>(nullptr))		 
		{
			// create new trienode and assign it to the pointer
			current->children[charToInt(word[i])] = std::shared_ptr<TrieNode>(new TrieNode());	
		}
		current = current->children[charToInt(word[i])];		// traverse to the next letter
	}

	current->isKeyword = true;			// mark that word as true
	current->nodeToken = type;
}

bool Trie::isCharNode(const char* c, std::shared_ptr<TrieNode> origin)
{
	if (origin->children[charToInt(*c)] == std::shared_ptr<TrieNode>(nullptr))		// children for that char does not exist
		return false;
	return true;
}
bool Trie::isCharWord(const char* c, std::shared_ptr<TrieNode> origin)
{
	if (origin->children[charToInt(*c)] == std::shared_ptr<TrieNode>(nullptr)
		|| !origin->children[charToInt(*c)]->isKeyword)		// children for that char does not exist
		return false;
	return true;
}



bool Trie::searchKeyword(std::string& word)
{
	std::shared_ptr<TrieNode> current = root;
	for (int i = 0; i < word.size(); i++)
	{
		if (current->children[charToInt(word[i])] == std::shared_ptr<TrieNode>(nullptr))		// not found
			return false;
		current = current->children[charToInt(word[i])];
	}
	if (current->isKeyword)
		return true;
	else
		return false;
}

TokenType Trie::searchToken(const char* cstring)
{
	std::string word = cstring;
	std::shared_ptr<TrieNode> current = root;
	for (int i = 0; i < word.size(); i++)
	{
		if (current->children[charToInt(word[i])] == std::shared_ptr<TrieNode>(nullptr))		// not found
			return TokenType::TOKEN_IDENTIFIER;
		current = current->children[charToInt(word[i])];
	}
	if (current->isKeyword)
		return current->nodeToken;
	else
		return TokenType::TOKEN_IDENTIFIER;
}



bool Trie::deletePart(std::string& word, std::shared_ptr<TrieNode>& checkout)
{
	if (checkout == nullptr)		// word is not present in the trie
		return false;

	// if the end ot the word is already reached
	if (word.size() == 0)
	{
		if (checkout->isKeyword == true)
		{
			checkout->isKeyword = false;			// set to false, 'deleting'
			return true;
		}
		else
			return false;
	}

	// exclude/slice off first letter of the string using substr
	std::string sub = word.substr(1);

	/* IMPORTANT
	- slice the string part because in the recursion below, only the FIRST letter will be deleted
	*/

	// recursion to delete the rest of the string
	if (deletePart(sub, checkout->children[charToInt(word[0])]))
	{
		/* IMPORTANT
		- this recursion is a dfs algorithm. first node to be evaluated with isNodeEmpty is the last child
		- below, if the node is COMPLETELY empty, that means the children of that word is already deleted
		  and we go to delete that node. ACTUAL DELETION OF THE PTR AND OBJECT HAPPENS HERE BELOW
		*/
		if (isNodeEmpty(checkout->children[charToInt(word[0])]))
		{
			/*		shared_ptr.reset()
			- ELIMINATE only ONE OWNER of that object, in this case the children[index]
			- as with smart pointers, if this children is the last owner, the trienode is destroyed from memory
			*/
			checkout->children[charToInt(word[0])].reset();

			checkout->children[charToInt(word[0])] = nullptr;			// set to point to nothing

			return true;			// delete successful
		}
		else
			return true;			// node children not empty, hence simply delete a single children
	}
	else
		return false;			// deletePart fail

	return false;		// deletePart fail
}

// function to start from the root
bool Trie::deleteKeyword(std::string& word)
{
	if (deletePart(word, root))
		return true;
	return false;
}

bool Trie::isNodeEmpty(std::shared_ptr<TrieNode> node) const
{
	for (int i = 0; i < TOTAL_CHAR; i++)
	{
		if (node->children[i] != nullptr || node->isKeyword == true)	// node not empty
			return false;
	}

	return true;
}


std::shared_ptr<TrieNode> Trie::getRootNode()
{
	return root;
}