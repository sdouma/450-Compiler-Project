#include "nodes.h"
#include "htmlencode.h"
#include <iostream>

Node::~Node() {}

void Node::print(std::ostream &out) const {
	out << "(";
	for (size_t i = 0; i<children.size(); i++){
		out << "[" << i << "]=";
		children[i]->print(out);
		out << std::endl;
	}
	out << ")";
}

int StatementsNode::type() const { return STATEMENTS; }

void StatementsNode::print(std::ostream &out) const {
	out << "Statements";
	Node::print(out);
}

int StatementNode::type() const { return STATEMENT; }

void StatementNode::print(std::ostream &out) const{
	out << "Statement";
	Node::print(out);
}


int HeaderNode::type() const{ return HEADER; }

void HeaderNode::print(std::ostream &out) const{
	out << "Header";
	Node::print(out);
}

int ParagraphNode::type() const { return PARAGRAPH; }

void ParagraphNode::print(std::ostream &out) const {
	out << "Paragraph[content=<p>";
    htmlencode(out,content);
	out << "</p>]";
	Node::print(out);
}

int SentenceNode::type() const{ return SENTENCE; }

void SentenceNode::print(std::ostream &out) const{
	Node::print(out);
}

int MarkupNode::type() const { return MARKUP; }

void MarkupNode::print(std::ostream &out) const {
	htmlencode(out,markup);
	Node::print(out);
	out << std::endl;
}

int Rest_of_ParagraphNode::type() const{ return REST_OF_PARAGRAPH; }

void Rest_of_ParagraphNode::print(std::ostream &out) const{
	out << "<block>";
	for (size_t i = 0; i<content.length(); ++i) {
		out << "&#" << (int)content[i] << ";";
	}
	out << "</block>";
}

int EndingNode::type() const{ return ENDING; }

void EndingNode::print(std::ostream &out) const{
	//if (children[0]->type() == END_OF_FILE) break;

}

int StartNode::type() const { return START_MARK; }

void StartNode::print(std::ostream &out) const {
	out << "<b>" << std::endl;
}

int EndNode::type() const { return END_MARK; }

void EndNode::print(std::ostream &out) const {
	out << "</b>" << std::endl;
}
