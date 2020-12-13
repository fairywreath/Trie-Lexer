#include "token.hpp"

Token::Token(TokenType mType, std::string::const_pointer mStart, int mLength, int mLine) :
	type(mType),
	start(mStart),
	length(mLength),
	line(mLine)
{
}