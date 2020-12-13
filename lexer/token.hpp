#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType
{
	TOKEN_ERROR,
	TOKEN_IDENTIFIER,

	TOKEN_ADD,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,

	// inclues comparison operators in word form
	TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,TOKEN_GREATER,
	TOKEN_GREATER_EQUAL, TOKEN_LESS, TOKEN_LESS_EQUAL,
	TOKEN_BANG, TOKEN_BANG_EQUAL,
	
	TOKEN_PRINT,TOKEN_RETURN,

	TOKEN_CLASS,TOKEN_THIS,TOKEN_SUPER,

	TOKEN_IF,TOKEN_ELF,TOKEN_ELSE,
	TOKEN_THEN,

	TOKEN_WHILE, TOKEN_FOR,TOKEN_SWITCH,
	TOKEN_END,

	TOKEN_EOF,
};


class Token
{
public:
	Token(TokenType mType, const char* mStart, int mLength, int mLine);
public:
	TokenType type;
	const char* start;
	int length;
	int line;
};


#endif