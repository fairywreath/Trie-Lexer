#include "lexer.hpp"
#include "common.hpp"


Lexer::Lexer(const std::string& source) : 
	trie(new Trie()),
	currentNode(trie->getRootNode()),
	line(1)
{
	start = source.c_str();
	current = source.c_str();
	
	std::cout << "Source: " << start << std::endl;

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


char Lexer::peekBehind()
{
	const char* temp = current;
	return *--temp;
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

	if (isAtEnd())
		return Token(TokenType::TOKEN_EOF, start, (int)(current - start), line);;

	start = current;		// reset start pointer to current pointer
	currentNode = trie->getRootNode();

	if (isAtEnd())
		return Token(TokenType::TOKEN_EOF, start, (int)(current - start), line);
	
	while (peek() != ' ')
	{
		if (trie->isCharNode(&*current, currentNode) && peekNext() != ' ' && peekNext() != '\0')
		{
			advance();			// go to next character
		}
		else if (trie->isCharWord(&*current, currentNode))		// if space is found at the end
		{
			advance();



#ifdef DEBUG_TRACE_TOKEN
		const char* ptr = start;
		std::cout << "Token string [";
		for (ptr; ptr < current; ptr++)
		{
			std::cout << *ptr;
		}
		std::cout << "], Token type [" << (int)currentNode->nodeToken << "]\n";
#endif

			return Token(currentNode->nodeToken, start, (int)(current - start), line);
		}
		else
		{
			if (peekNext() == ' ' || peekNext() == '\0')
			{
				advanceString();
				currentNode = trie->getRootNode();

#ifdef DEBUG_TRACE_TOKEN
				const char* ptr = start;
				std::cout << "Token string [";
				for (ptr; ptr < current; ptr++)
				{
					std::cout << *ptr;
				}
				std::cout << "], Token type [" << (int)TokenType::TOKEN_IDENTIFIER << "]\n";

#endif
				return Token(TokenType::TOKEN_IDENTIFIER, start, (int)(current - start), line);
			}

			advanceString();
		}
	}
	

	return Token(TokenType::TOKEN_ERROR, start, (int)(current - start), line);
}

std::vector<Token> Lexer::scanAll()
{
	for (;;)
	{
		Token tkn = scanToken();
		tokens.push_back(tkn);
		//std::cout << "Token type at scan all = " << (int)tkn.type << std::endl;
		if (tkn.type == TokenType::TOKEN_EOF)
		{
			std::cout << "EOF found \n";
			break;
		}
	}

	return tokens;
}