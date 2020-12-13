#include <iostream>

#include "trie.hpp"
#include "lexer.hpp"

static void repl()
{
	std::string line;
	for (;;)
	{
		std::cout << "~> ";
		std::cin >> line;


	}
}

int main(int argc, const char* argv[])
{
	//if (argc == 1)
	//	repl();

	std::string source = "Hitagi Senjogahara";
	Lexer lexer(source);

	std::cout << lexer.peek() << std::endl;
	lexer.advance();
	std::cout << lexer.peek() << std::endl;

	if (lexer.checkKeyword("els"))
		std::cout << "Is present in trie\n";
	else
		std::cout << "Not present in trie\n";

	return 0;
}


