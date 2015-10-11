#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define IDENT 0
#define LETTER 1
#define CAPITAL 2
#define DIGIT 3
#define LEFTPAREN 4
#define RIGHTPAREN 5
#define UNDERSCORE 6

#define have 7
#define is 8
#define add 9
#define divide 10
#define subtract 11
#define make 12
#define bake 13
#define print 14
#define fly 15
#define sleep 16
#define snooze 17

#define did 18
#define will 19

#define coffee 20
#define bed 21
#define ramen 22
#define pasta 23
#define cake 24
#define alarm 25
#define homework 26
#define program 27

#define nouns 28

#define UNKNOWN 99

using namespace std;

class Lexer
{
	int charClass;
	int lexeme[100];
	int nextChar;
	int lexLen;
	int token;
	int nextToken:
	ifstream file;
	map<string, int> specialWord;

public:
	Lexer(void);
	~Lexer(void);

	// method declarations
	void addChar();
	void getChar();
	void getNonBlank();
	bool openFile();
	void closeFile();
	void fillSpecialWords();
	int lex();
	int lookup(char ch);
};

