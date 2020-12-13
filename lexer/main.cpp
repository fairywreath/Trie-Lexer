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

	std::string source = "    assign      for  azaz";
	Lexer lexer(source);


	lexer.skipWhiteSpaces();
	Token result = lexer.scanToken();
	std::cout << "Token Type: " << (int)result.type << std::endl;

	std::cout << "Token String Length: " << result.length << std::endl;

	
	lexer.skipWhiteSpaces();
	result = lexer.scanToken();
	std::cout << "Token Type: " << (int)result.type << std::endl;
	std::cout << "Token String Length: " << result.length << std::endl;

	lexer.skipWhiteSpaces();
	result = lexer.scanToken();
	std::cout << "Token Type: " << (int)result.type << std::endl;
	std::cout << "Token String Length: " << result.length << std::endl;
	

	return 0;
}


