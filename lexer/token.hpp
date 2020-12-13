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

	TOKEN_IF,
	TOKEN_ELF,
	TOKEN_ELSE,

	TOKEN_ASSIGN,

	TOKEN_WHILE,
	TOKEN_FOR,
	
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