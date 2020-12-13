#include "lexer.hpp"
#include <iostream>

Lexer::Lexer(const std::string& source) : 
	trie(new Trie()),
	currentNode(trie->getRootNode()),
	line(1)
{
	start = source.c_str();
	current = source.c_str();
	
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

	//TokenType token = trie->searchToken("if");
	//std::cout << (int)token << std::endl;

	// advance();
}

Lexer::~Lexer() {};

void Lexer::advanceString()
{
	current++;
}

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
			advanceString();
			break;

		case '\n':				// if a new line is found, also add line number
			line++;
			advanceString();
			break;

			// for comments
		case '/':
			if (peekNext() == '/')
			{
				// comment goes until end of line
				while (peek() != '\n' && !isAtEnd()) advanceString();		// if not new line or not end, treat as whitespace and advance
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
	skipWhiteSpaces();
	start = current;		// reset start pointer to current pointer
	currentNode = trie->getRootNode();		// resest root node

	if (isAtEnd())
		return Token(TokenType::TOKEN_EOF, start, (int)(current - start), line);
	
	while (peek() != ' ')
	{
		if (trie->isCharNode(&*current, currentNode) && peekNext() != ' ' && peekNext() != '\0')
		{
			advance();			// go to next character
		}
		else if (trie->isCharNode(&*current, currentNode))		// if space is found at the end
		{
			advance();
			std::cout << "Current Node = " << (int)(currentNode->nodeToken) << std::endl;

			const char* ptr = start;
			for (ptr; ptr < current; ptr++)
			{
				std::cout << *ptr << std::endl;
			}

			return Token(currentNode->nodeToken, start, (int)(current - start), line);
		}
		else
		{
			advanceString();
			if (peekNext() == ' ' || peekNext() == '\0')
			{
				advanceString();
				const char* ptr = start;
				for (ptr; ptr < current; ptr++)
				{
					std::cout << *ptr << std::endl;
				}

				return Token(TokenType::TOKEN_IDENTIFIER, start, (int)(current - start), line);
			}
		}
	}
	

	return Token(TokenType::TOKEN_ERROR, start, (int)(current - start), line);
}
