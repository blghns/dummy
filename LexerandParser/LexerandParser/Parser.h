#pragma once
#include "Lexer.h"

class Parser
{
	Lexer lexer;
	int nextToken;

public:
	Parser(void);
	~Parser(void);

	void essay(void);
	void paragraph(void);
	void sentence(void);
	void comment(void);
	void noun(void);

	void verb(void);
	void past_tense(void);
	void future_tense(void);

	void subject(void);
	void object(void);
	void numeric(void);

	bool isObject(int);
	bool isSubject(int);

};


