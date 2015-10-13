#include "Parser.h"

// ***************************************************************
// Main to test the parser
// ***************************************************************

int main(void) {
	Parser parser; // create a parser object
}

// ***************************************************************
// Constructor
// ***************************************************************
Parser::Parser(void)
{
	if (lexer.openFile()) {
		lexer.getChar();
		nextToken = lexer.lex();
		cout << "First token is: " << nextToken << "\n";
		essay();
	}
}


Parser::~Parser(void)
{
}

// ************************************************************************
//  <essay> -> {<paragraph>} the_end.
// ************************************************************************
void Parser::essay(void){
	cout << "essay" << endl;
	do{
		paragraph();
	} while (nextToken != EOF);
}

// ************************************************************************
//  <paragraph> -> for_starters {<sentence> (<comment>)} concluded.
// ************************************************************************
void Parser::paragraph(void){
	cout << "paragraph" << endl;
	if (nextToken == for_starters){
		do{
			sentence();
			comment();
		} while (nextToken != concluded);
	}
}

// ************************************************************************
//  <sentence> -> <noun>(<verb> | <past_tense> | <future_tense>) [<numeric>] { (object | <subject> | <noun>)}.
// ************************************************************************

void Parser::sentence(void){
	cout << "sentence" << endl;

	noun();
	if (nextToken == did)
		past_tense();
	else if (nextToken == will)
		future_tense();
	else
		verb();
	if (nextToken == DIGIT)
		numeric();
	do{
		nextToken = lexer.lex();
		if (isObject(nextToken))
			object();
		else if (isSubject(nextToken))
			subject();
		else
			noun();
	} while (nextToken != PERIOD);
}

bool Parser::isObject(int nextToken){
	if (nextToken == have || nextToken == is || nextToken == add || nextToken == divide || nextToken == subtract || make || nextToken == bake || nextToken == print || nextToken == fly || nextToken == sleep || nextToken == snooze)
		return true;
	else
		return false;
}

bool Parser::isSubject(int nextToken){
	if (nextToken == negative || nextToken == plus || nextToken == minus || nextToken == and || nextToken == or || nextToken == multiply || nextToken == divided_by)
		return true;
	else
		return false;
}

// ************************************************************************
//  <comment> -> “(“ {a...z | 0...9} “)”
// ************************************************************************
// basically skips whatever is in the parenthesis.

void Parser::comment(void){
	cout << "comment" << endl;
	if (lexer.lex() == LEFTPAREN){
		do{
			nextToken = lexer.lex();
		} while (lexer.lex() != RIGHTPAREN);
	}
	nextToken = lexer.lex();
}

// ************************************************************************
//  <noun> -> (A...Z) {a...z}
// ************************************************************************
void Parser::noun(void){
	cout << "noun" << endl;
	//if nexttoken is noun else retun error
	nextToken = lexer.lex();
}

// ************************************************************************
//  <verb> -> have | is | add | divide | subtract | make | bake | print | fly | sleep | snooze
// ************************************************************************
void Parser::verb(void){
	cout << "verb" << endl;
	if (nextToken == have || nextToken == is || nextToken == add || nextToken == divide || nextToken == subtract || make || nextToken == bake || nextToken == print || nextToken == fly || nextToken == sleep || nextToken == snooze)
		nextToken = lexer.lex();
	else
		cout << "Error reading verb" << endl;
}

// ************************************************************************
//  <past_tense> -> did <verb>
// ************************************************************************
void Parser::past_tense(void){
	cout << "past_tense" << endl;
	if (nextToken == did){
		nextToken = lexer.lex();
		verb();
	}
	else
		cout << "Error in past_tense, expecting did" << endl;
}

// ************************************************************************
//  <future_tense> -> will <verb>
// ************************************************************************
void Parser::future_tense(void){
	cout << "future_tense" << endl;
	if (nextToken == will){
		nextToken = lexer.lex();
		verb();
	}
	else
		cout << "Error in future tense, expecting will" << endl;
}

// ************************************************************************
//  <subject> -> coffee | bed | ramen | pasta | cake | alarm | homework | program
// ************************************************************************
void Parser::subject(void){
	cout << "subject" << endl;
	if (nextToken == coffee || nextToken == bed || nextToken == ramen || nextToken == pasta || nextToken == cake || nextToken == alarm || nextToken == homework || nextToken == program)
		nextToken = lexer.lex();
	else
		cout << "Error in subject" << endl;
}

// ************************************************************************
//  <object> -> negative | plus | minus | and | or | multiply | divided_by
// ************************************************************************
void Parser::object(void){
	cout << "object" << endl;
	if (nextToken == negative || nextToken == plus || nextToken == minus || nextToken == and || nextToken == or || nextToken == multiply || nextToken == divided_by)
		nextToken = lexer.lex();
	else
		cout << "Error in object" << endl;
}

// ************************************************************************
// <numeric> -> 0...9, { 0...9 }
// ************************************************************************
void Parser::numeric(void){
	cout << "numeric" << endl;
	if (nextToken == DIGIT){
		nextToken = lexer.lex();
	}
	else
		cout << "Error in number" << endl;
}
