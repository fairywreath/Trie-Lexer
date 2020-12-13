#include "token.hpp"

Token::Token(TokenType mType, const char* mStart, int mLength, int mLine) :
	type(mType),
	start(mStart),
	length(mLength),
	line(mLine)
{
}