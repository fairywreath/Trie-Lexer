#include "lexer.hpp"

Lexer::Lexer(const std::string& source) : 
	trie(new Trie()),
	currentNode(trie->getRootNode()),
	line(1)
{
	start = source.begin();
	current = source.begin();
	
	addKeyword("+", TokenType::TOKEN_ADD);
	addKeyword("-", TokenType::TOKEN_MINUS);
	addKeyword("*", TokenType::TOKEN_STAR);
	addKeyword("/", TokenType::TOKEN_SLASH);

	addKeyword("if", TokenType::TOKEN_IF);
	addKeyword("elf", TokenType::TOKEN_ELF);
	addKeyword("else", TokenType::TOKEN_ELSE);

	addKeyword("assign", TokenType::TOKEN_ASSIGN);
	
	addKeyword("while", TokenType::TOKEN_WHILE);
	addKeyword("for", TokenType::TOKEN_FOR);
}

Lexer::~Lexer() {};


void Lexer::advance()
{
	currentNode = currentNode->children[trie->charToInt(*current)];		// go to children node according to current char
	current++;
}

void Lexer::addKeyword(const char* cstring, TokenType type)
{
	std::string word = cstring;
	trie->insertKeyword(word, type);
}

bool Lexer::checkKeyword(const char* cstring)
{
	std::string word = cstring;
	return trie->searchKeyword(word);
}


char Lexer::peek()
{
	return *current;
}

char Lexer::peekNext()
{
	if (isAtEnd()) return '\0';
	return current[1];
}

bool Lexer::isAtEnd()
{
	return *current == '\0';
}


void Lexer::skipWhiteSpaces()
{
	for (;;)
	{
		char c = peek();		// peek is a function to check the next code character
		switch (c)
		{
		case ' ':
		case '\r':
		case '\t':
			advance();
			break;

		case '\n':				// if a new line is found, also add line number
			line++;
			advance();
			break;

			// for comments
		case '/':
			if (peekNext() == '/')
			{
				// comment goes until end of line
				while (peek() != '\n' && !isAtEnd()) advance();		// if not new line or not end, treat as whitespace and advance
			}
			else {
				return;
			}

		default:
			return;
		}
	}
}

Token Lexer::scanToken()
{

}