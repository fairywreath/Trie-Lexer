#include "lexer.hpp"
#include "common.hpp"


Lexer::Lexer(const std::string& source) : 
	trie(new Trie()),
	currentNode(trie->getRootNode()),
	line(1)
{
	start = source.c_str();
	current = source.c_str();
	
#ifdef DEBUG_TRACE_TOKEN
	std::cout << "Source:\n" << start << std::endl;
#endif

	addKeyword("+", TokenType::TOKEN_ADD);
	addKeyword("-", TokenType::TOKEN_MINUS);
	addKeyword("*", TokenType::TOKEN_STAR);
	addKeyword("/", TokenType::TOKEN_SLASH);

	addKeyword("=", TokenType::TOKEN_EQUAL);
	addKeyword("==", TokenType::TOKEN_EQUAL_EQUAL);
	addKeyword(">", TokenType::TOKEN_GREATER);
	addKeyword(">=", TokenType::TOKEN_GREATER_EQUAL);
	addKeyword("<", TokenType::TOKEN_LESS);
	addKeyword("<=", TokenType::TOKEN_LESS_EQUAL);


	addKeyword("assigned", TokenType::TOKEN_EQUAL);
	addKeyword("equals", TokenType::TOKEN_EQUAL_EQUAL);
	addKeyword("is", TokenType::TOKEN_EQUAL_EQUAL);
	addKeyword("not", TokenType::TOKEN_BANG_EQUAL);

	addKeyword("class", TokenType::TOKEN_CLASS);
	addKeyword("super", TokenType::TOKEN_SUPER);
	addKeyword("this", TokenType::TOKEN_THIS);

	addKeyword("print", TokenType::TOKEN_PRINT);
	addKeyword("return", TokenType::TOKEN_RETURN);

	addKeyword("if", TokenType::TOKEN_IF);
	addKeyword("elf", TokenType::TOKEN_ELF);
	addKeyword("else", TokenType::TOKEN_ELSE);

	addKeyword("while", TokenType::TOKEN_WHILE);
	addKeyword("for", TokenType::TOKEN_FOR);
	addKeyword("switch", TokenType::TOKEN_SWITCH);

	addKeyword("end", TokenType::TOKEN_END);

	addKeyword("[a-zA-Z_][0-9a-zA-Z_]*", TokenType::TOKEN_ELF);
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
		//case '/':
		//	if (peekNext() == '/')
		//	{
		//		// comment goes until end of line
		//		while (peek() != '\n' && !isAtEnd()) advanceString();		// if not new line or not end, treat as whitespace and advance
		//	}
		//	else {
		//		return;
		//	}

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
		if (trie->isCharNode(&*current, currentNode) && peekNext() != ' ' && peekNext() != '\0' && peekNext() != '\n'
			&& peekNext () != '\t')
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
		std::cout << "], Token type [" << (int)currentNode->nodeToken << "] at line " << line << std::endl;
#endif

			return Token(currentNode->nodeToken, start, (int)(current - start), line);
		}
		else
		{
			if (peekNext() == ' ' || peekNext() == '\0' || peekNext() == '\n'  || peekNext() == '\t')
			{
				advanceString();

#ifdef DEBUG_TRACE_TOKEN
				const char* ptr = start;
				std::cout << "Token string [";
				for (ptr; ptr < current; ptr++)
				{
					std::cout << *ptr;
				}
				std::cout << "], Token type [" << (int)TokenType::TOKEN_IDENTIFIER << "] at line " << line << std::endl;

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