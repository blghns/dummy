#include "Lexer.h"


/*
int main(void) 
{
	Lexer lexer; // create a lexer object
	int token;
	if (lexer.openFile()) 
	{
		lexer.getChar();
		do
		{
			token = lexer.lex();
		} while (token != EOF);
	}
}
*/

Lexer::Lexer(void)
{
	fillSpecialWords();
}

Lexer::~Lexer(void)
{
	closeFile();
}

bool Lexer::openFile()
{
	file.open("input.txt");
	if (!file.is_open())
	{
		printf("ERROR - cannot open input.txt \n");
		return false;
	}
	return true;
}

void Lexer::closeFile()
{
	file.close();
	system("pause");
}

void Lexer::fillSpecialWords()
{
	cout << "About to fill special words map\n";

	specialWord[string("have")] = 7;
	specialWord[string("is")] = 8;
	specialWord[string("add")] = 9;
	specialWord[string("divide")] = 10;
	specialWord[string("subtract")] = 11;
	specialWord[string("make")] = 12;
	specialWord[string("bake")] = 13;
	specialWord[string("print")] = 14;
	specialWord[string("fly")] = 15;
	specialWord[string("sleep")] = 16;
	specialWord[string("snooze")] = 17;

	specialWord[string("did")] = 18;
	specialWord[string("will")] = 19;

	specialWord[string("coffee")] = 20;
	specialWord[string("bed")] = 21;
	specialWord[string("ramen")] = 22;
	specialWord[string("pasta")] = 23;
	specialWord[string("cake")] = 24;
	specialWord[string("alarm")] = 25;
	specialWord[string("homework")] = 26;
	specialWord[string("program")] = 27;
	specialWord[string("the_end")] = 29;
	specialWord[string("For_starters")] = 30;
	specialWord[string("concluded")] = 31;

	specialWord[string("negative")] = 32;
	specialWord[string("plus")] = 33;
	specialWord[string("minus")] = 34;
	specialWord[string("and")] = 35;
	specialWord[string("or")] = 36;
	specialWord[string("multiply")] = 37;
	specialWord[string("divided_by")] = 38;

}

int Lexer::lookup(char ch)
{
	switch (ch)
	{
		case '.':
			addChar();
			nextToken = PERIOD;
			break;
		case '(':
			addChar();
			nextToken = LEFTPAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHTPAREN;
			break;
		case '_':
			addChar();
			nextToken = UNDERSCORE;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

void Lexer::addChar()
{
	if (lexLen <= 98)
	{
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

void Lexer::getChar()
{
	if (file.good())
	{
		nextChar = file.get();

		if ('A' <= nextChar && 'Z' >= nextChar)
			charClass = nouns;
		else if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else if (nextChar == '_')
			charClass = UNDERSCORE;
		else
			charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

void Lexer::getNonBlank()
{
	while (isspace(nextChar))
		getChar();
}

int Lexer::lex()
{
	cout << "LEX\n";

	lexLen = 0;
	getNonBlank(); //removes white space

	switch (charClass)
	{
		case nouns:
		case PERIOD:
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE)
			{
				addChar();
				getChar();
			}
			nextToken = specialWord[string(lexeme)];
			break;

		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT)
			{
				addChar();
				getChar();
			}
			nextToken = DIGIT;
			break;

		// Single characters
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	}

	printf("lexeme: %s \n", lexeme);
	return nextToken;
}

