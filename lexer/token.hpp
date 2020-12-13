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
};


class Token
{
public:
	Token(TokenType mType, std::string::const_pointer mStart, int mLength, int mLine);
public:
	TokenType type;
	std::string::const_pointer start;
	int length;
	int line;
};


#endif