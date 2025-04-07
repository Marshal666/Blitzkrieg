#ifndef __PARSER_H__
#define __PARSER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#import "GOLD Parser Engine.dll"
using namespace GOLDParserEngine;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParser
{
	_GOLDParserPtr parser;
protected:
	bool Init( const char *pszGrammarFileName );
	// parsing was successfully done
	virtual bool DoneParsing( _ReductionPtr reduction ) = 0;
	//
	// Place code here to handle a illegal or unrecognized token 
	// To recover, pop the token from the stack: Parser.PopInputToken
	virtual bool ErrorLexical( const int nLineNumber ) = 0;
	// This is a syntax error: the source has produced a token that was not expected by the LALR State Machine. 
	// The expected tokens are stored into the 'Tokens' list. To recover, push one of the expected tokens 
	// onto the parser's input queue (the first in this case):
	// You should limit the number of times this type of recovery can take place.
	virtual bool ErrorSyntax( const int nLineNumber ) = 0;
	// The end of the input was reached while reading a comment. 
	// This is caused by a comment that was not terminated
	virtual void ErrorComment( const int nLineNumber ) = 0;
	// Something horrid happened inside the parser. You cannot recover
	virtual void ErrorInternal( const int nLineNumber ) = 0;
	// Load the Compiled Grammar Table file first.
	virtual void ErrorNotLoaded( const int nLineNumber ) = 0;
	//
	_GOLDParserPtr GetParser() { return parser; }
public:
	CParser();
	//
	bool Parse( const char *pszFileName );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __PARSER_H__
