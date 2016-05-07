#include "markdownparser.h"
#include "buffered.h"

#include <iostream>
#include <assert.h>

#define TRACE 1


typedef Buffered < TokenSP, Scanner > BufferedScanner;

int p_count = 0;

class MarkdownParser : public Parser
{
public:
	BufferedScanner scanner;
	size_t at;

	MarkdownParser(Scanner &_scanner) : scanner(_scanner), at(0) { }

	class Cursor {
	public:
		MarkdownParser *parent;
		size_t at;
		bool reset() {
#if TRACE == 1
			std::cout << "reset token stream to " << at << std::endl;
#endif
			parent->at = at;
			return true;
		}

		Cursor(MarkdownParser *_parent)
			: parent(_parent), at(parent->at)
		{
#if TRACE == 1
			std::cout << "added cursor at " << at << std::endl;
#endif
		}
	};

	// making more readable
	std::string get_type(int x){
		if(x == 0) return "markup";
		else if(x == 1) return "open bold";
	    else if(x == 2) return "close mark";
		else if(x == 3) return "italic open";
		else if(x == 4) return "underline open";
		else if(x == 5) return "bold close";		
		else if(x == 6) return "italic close";
		else if(x == 7) return "underline close";
		else if(x == 8) return "text";
		else if(x == 9) return "end of line";
		else return "end of file";
	}
	
	TokenSP token(int type) {
		std::string my_type;
		TokenSP ans = scanner.peek(at);
	    my_type = get_type(ans->type);
		std::cout << "<br/>" << *ans << "@" << ans->at << std::endl;
		if (ans->type == type) {
			++at;
#if TRACE == 1
			std::cout << "token(" << my_type << ") found (" << ans << ")" << std::endl;
#endif
			return ans;
		}
		else {
#if TRACE == 1
			std::cout << "token(" << my_type << ") not found" << std::endl;
#endif
			return TokenSP(0);
		}
	}

	bool eof() {
#if TRACE == 1
		std::cout << "eof()" << std::endl;
#endif

		bool ans = !!token(Token::END_OF_FILE);
#if TRACE == 1
		std::cout << "eof() = " << ans << std::endl;
#endif
		return ans;
	}

	bool eol() {
#if TRACE == 1
		std::cout << "eol()" << std::endl;
#endif
		bool ans = !!token(Token::END_OF_LINE);
#if TRACE == 1
		std::cout << "eol() = " << ans << std::endl;
#endif
		return ans;
	}

	bool markup(){
#if TRACE == 1
		std::cout << "markup()" << std::endl;
#endif
	bool ans = !!token(Token::MARKUP);
#if TRACE == 1
		std::cout << "markup() = " << ans << std::endl;
#endif
	return ans;
	
	}
	
	bool text(NodeSP &dom) {
#if TRACE == 1
		std::cout << "text()" << std::endl;
#endif
		TokenSP t = token(Token::TEXT);
		bool ans = !!t;
		if (ans) {
			ParagraphNode *node = new ParagraphNode();
			node->content = t->value;
			dom = NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "text() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool open_bold(){
		
#if TRACE == 1
		std::cout << "open_bold()" << std::endl;
#endif
		bool ans = !!token(Token::BOLD_OPEN_MARK);
#if TRACE == 1
		std::cout << "open_bold() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool close_bold(){
		
#if TRACE == 1
		std::cout << "close_bold()" << std::endl;
#endif
		bool ans = !!token(Token::BOLD_CLOSE_MARK);
#if TRACE == 1
		std::cout << "close_bold() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool open_italic(){
		
#if TRACE == 1
		std::cout << "open_italic()" << std::endl;
#endif
		bool ans = !!token(Token::ITALIC_OPEN_MARK);
#if TRACE == 1
		std::cout << "open_italic() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool close_italic(){
		
#if TRACE == 1
		std::cout << "close_italic()" << std::endl;
#endif
		bool ans = !!token(Token::ITALIC_CLOSE_MARK);
#if TRACE == 1
		std::cout << "close_italic() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool open_underline(){
		
#if TRACE == 1
		std::cout << "open_underline()" << std::endl;
#endif
		bool ans = !!token(Token::UNDERLINE_OPEN_MARK);
#if TRACE == 1
		std::cout << "open_underline() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool close_underline(){
		
#if TRACE == 1
		std::cout << "close_underline()" << std::endl;
#endif
		bool ans = !!token(Token::UNDERLINE_CLOSE_MARK);
#if TRACE == 1
		std::cout << "close_underline() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool bold(NodeSP &dom){
#if TRACE == 1
		std::cout<<"bold()"<<std::endl;
#endif
		Cursor at(this);
		NodeSP domText;
		bool ans = (at.reset() && open_bold() && statements(domText) && close_bold());
		if (ans) {
			MarkupNode *node = new MarkupNode();
			node->markup = L"''";
			node->children.push_back(domText);
			dom=NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "bold() = " << ans << std::endl;
#endif
		return ans;
		
	}
	
	bool italic(NodeSP &dom){
#if TRACE == 1
		std::cout<<"italic()"<<std::endl;
#endif
		Cursor at(this);
		NodeSP domText;
		bool ans = (at.reset() && open_italic() && statements(domText) && close_italic());
		if (ans) {
			MarkupNode *node = new MarkupNode();
			node->markup = L"[/";
			node->children.push_back(domText);
			dom=NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "italic() = " << ans << std::endl;
#endif
		return ans;
		
	}
	
	bool underline(NodeSP &dom){
#if TRACE == 1
		std::cout<<"underline()"<<std::endl;
#endif
		Cursor at(this);
		NodeSP domText;
		bool ans = (at.reset() && open_underline() && statements(domText) && close_underline());
		if (ans) {
			MarkupNode *node = new MarkupNode();
			node->markup = L"[_";
			node->children.push_back(domText);
			dom=NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "underline() = " << ans << std::endl;
#endif
		return ans;
		
	}
	
	bool sentence(NodeSP &dom) {
#if TRACE == 1
		std::cout << "sentence()" << std::endl;
#endif
		Cursor at(this);
		bool ans = (at.reset() && bold(dom))
			|| (at.reset() && italic(dom))
			|| (at.reset() && underline(dom))
			|| (at.reset() && text(dom));
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "sentence() = " << ans << std::endl;
#endif
		return ans;
	}
	
	bool header(NodeSP &dom) {
#if TRACE == 1
		std::cout << "header()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1, dom2;
		TokenSP t = token(Token::MARKUP);
		bool ans = (at.reset() && markup() && text(dom) && eol())
			|| (at.reset() && false);
		if (ans) {
			MarkupNode *node = new MarkupNode();
			node->markup = t->value;
			dom = NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "header() = " << ans << std::endl;
#endif
		return ans;
	}

	bool optional_header(NodeSP &dom) {
#if TRACE == 1
		std::cout << "optional_header()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1;
		TokenSP t = token(Token::MARKUP);
		int rule = 0;
		bool ans = (rule=1,header(dom1))
			|| (rule=2,at.reset() && true);
		if (ans) {
			StatementsNode *node = new StatementsNode();
			switch(rule) {
				case 1: node->children.push_back(dom1); break;
				case 2: /* null */; break;
				default: assert(false);
			}
			dom = NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "optional_header() = " << ans << std::endl;
#endif
		return ans;
	}

	bool paragraph(NodeSP &dom) {
#if TRACE == 1
		std::cout << "paragraph()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1, dom2;
		bool ans = (at.reset() && sentence(dom1) && rest_of_paragraph(dom2)) ||
			(at.reset() && false);
		if (ans) {
			dom = dom1;
			((ParagraphNode&)(*dom1)).content
				.append(((ParagraphNode&)(*dom2)).content);
			p_count++;
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "paragraph() = " << ans << std::endl;

#endif
		return ans;
	}

	bool rest_of_paragraph(NodeSP &dom) {
#if TRACE == 1
		std::cout << "rest_of_paragraph()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1;
		int rule = 0;
		bool ans = ((rule = 1), (at.reset() && eol() && paragraph(dom1)))
			|| ((rule = 2), (at.reset() && eol() && rest_of_paragraph(dom1)))
			|| ((rule = 3), (at.reset() && true));

		if (ans) {
			ParagraphNode *node = new ParagraphNode();
			switch (rule) {
			case 1: case 2:
				node->content = L" ";
				node->content.append(((ParagraphNode&)(*dom1)).content);
				break;
			case 3:
				node->content = L"";
				break;
			}
			dom = NodeSP(node);
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "rest_of_paragraph() = " << ans << std::endl;
#endif
		return ans;
	}

	bool statements(NodeSP &dom) {
#if TRACE == 1
		std::cout << "statements()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1, dom2;
		int rule = 0;
		bool ans = ((rule = 1), (at.reset() && paragraph(dom1) && statements(dom2)))
			|| ((rule = 2), at.reset() && true);
		if (ans) {
			switch (rule) {
			case 1:
			{
				StatementsNode &me = (StatementsNode&)(*dom2);
				me.children.insert(me.children.begin(), dom1);
				dom = dom2;
				break;
			}
			case 2:
			{
				dom = NodeSP(new StatementsNode());
				break;
			}
			}
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "statements() = " << ans << std::endl;
#endif
		return ans;
	}

	bool start(NodeSP &dom) {
#if TRACE == 1
		std::cout << "start()" << std::endl;
#endif
		Cursor at(this);
		NodeSP dom1, dom2;
		bool ans = (at.reset() && optional_header(dom1) && statements(dom2) && eof())
			|| (at.reset() && false);
		if (ans) {
			NodeSP dom3 = NodeSP(new StatementsNode());
			for (auto child : dom1->children) { dom3->children.push_back(child); }
			dom3 -> children.push_back(dom2);
			dom = dom3;
		}
#if TRACE == 1
		if (ans) { std::cout << __LINE__ << "dom: "; dom->print(std::cout); std::cout << std::endl; }
		std::cout << "start() = " << ans << std::endl;
#endif
		return ans;
	}

	NodeSP parse() {


		NodeSP dom;
		bool ans = start(dom);
		scanner.shift(at);
		p_count /= 2;
		std::cout<<"the number of paragraphs is "<<p_count<<std::endl;
		std::cin.get();
		return (ans) ? dom : NodeSP(0);

	}
};

ParserSP CreateMarkdownParser(Scanner &scanner) {
	return ParserSP(new MarkdownParser(scanner));
}

