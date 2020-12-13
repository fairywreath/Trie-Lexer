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

		Lexer lexer(line);
		lexer.scanToken();
	}
}

int main(int argc, const char* argv[])
{
	if (argc == 1)
		repl();

	return 0;
}



/*
lexer.skipWhiteSpaces();
Token result = lexer.scanToken();
std::cout << "Token Type: " << (int)result.type << std::endl;
std::cout << "Token String Length: " << result.length << std::endl;
const char* ptr = result.start + result.length;
std::cout << "Token String Result: ";
for (result.start; result.start < ptr; result.start++)
{
	std::cout << *result.start;
}
std::cout << "\n\n";


lexer.skipWhiteSpaces();
result = lexer.scanToken();
std::cout << "Token Type: " << (int)result.type << std::endl;
std::cout << "Token String Length: " << result.length << std::endl;
ptr = result.start + result.length;
std::cout << "Token String Result: ";
for (result.start; result.start < ptr; result.start++)
{
	std::cout << *result.start;
}
std::cout << "\n\n";

lexer.skipWhiteSpaces();
result = lexer.scanToken();
std::cout << "Token Type: " << (int)result.type << std::endl;
std::cout << "Token String Length: " << result.length << std::endl;
ptr = result.start + result.length;
std::cout << "Token String Result: ";
for (result.start; result.start < ptr; result.start++)
{
	std::cout << *result.start;
}
std::cout << "\n\n";
*/