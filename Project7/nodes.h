#pragma once

#include <memory>
#include <vector>
#include <string>

class Node;
typedef std::shared_ptr < Node > NodeSP;
typedef std::vector < NodeSP > Nodes;

class Node
{
public:
	enum { PARAGRAPH = 1, MARKUP = 2, STATEMENTS = 3, STATEMENT = 4, SENTENCE = 5, ENDING = 6, HEADER = 7, REST_OF_PARAGRAPH = 8, START_MARK = 9, END_MARK = 10 };
	Nodes children;
	virtual int type() const = 0;
	virtual void print(std::ostream &out) const = 0;
	virtual ~Node();
};

class StatementsNode : public Node
{
public:
	virtual int type() const;
	virtual void print(std::ostream &out) const;
};

class StatementNode : public Node
{
public:
	virtual int type() const;
	virtual void print(std::ostream &out) const;
};

class ParagraphNode : public Node
{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class EndingNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class SentenceNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class Rest_of_ParagraphNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class HeaderNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class MarkupNode : public Node
{
public:
	std::wstring markup;
	int type() const;
	void print(std::ostream &out) const;
};

class StartNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};

class EndNode : public Node{
public:
	std::wstring content;
	int type() const;
	void print(std::ostream &out) const;
};