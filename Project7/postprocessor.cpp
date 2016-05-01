#include <iostream>

#include "postprocessor.h"
#include "htmlencode.h"
#include "markdownparser.h"

extern int p_count;
int current = 0;

PostProcessor::PostProcessor(NodeSP &_dom, std::ostream &_out)
  : dom(_dom), out(_out)
{

}

bool in_paragraph = false;

PostProcessor::~PostProcessor()
{
}

class SimplePostProcessor : public PostProcessor
{
public:
  SimplePostProcessor(NodeSP &dom, std::ostream &out)
    : PostProcessor(dom,out)
  {
  }

  void process() { dom->print(std::cout); }
};

PostProcessorSP CreateSimplePostProcessor(NodeSP &dom, std::ostream &out)
{
  return PostProcessorSP(new SimplePostProcessor(dom,out));
}

class HTMLPostProcessor : public PostProcessor
{
public:
  HTMLPostProcessor(NodeSP &dom, std::ostream &out)
    : PostProcessor(dom,out)
  {
  }

  void doctype() {
    out << "<!DOCTYPE html>" << std::endl;
  }

  void html()
  {
    out << "<html>" << std::endl;
    head();
    body();
    out << "</html>" << std::endl;    
  }

  void head()
  {
    out << "<head>" << std::endl;
    title();
    out << "</head>" << std::endl;        
  }

  std::wstring gettext(NodeSP &node)
  {
    if (node->type() == Node::PARAGRAPH) {
      return ((ParagraphNode&)*node).content;
    }
    if (node->type() == Node::MARKUP) {
      if (node->children.size() > 0) {
        return gettext(node->children[0]);
      }
    }
    return L"unknown";
  }

  void title()
  {
    out << "<title>" << std::endl;
    std::wstring text=L"unset";
    if (dom->children.size() > 0) {
      htmlencode(out,gettext(dom->children[0]));
    }
    out << "</title>" << std::endl;        

  }

  void body()
  {
    out << "<body>";
    for (size_t i=0; i<dom->children.size(); ++i) {
      process(dom->children[i]);
    }
    out << "</body>" << std::endl;
  }



  void process(NodeSP child)
  {
    switch(child->type()) {
    case Node::STATEMENTS:
      for (size_t i=0; i<child->children.size(); ++i) {
        process(child->children[i]);
		if(in_paragraph == true && (current > p_count  || p_count == 1)){
			out<<"</p>";
			in_paragraph = false;
		}
      }
      break;
    case Node::PARAGRAPH:
	
	if(in_paragraph == false){
      out << "<p>";
	  in_paragraph = true;
	}
	
	current++;
      htmlencode(out,gettext(child));
	  /*
	  if(in_paragraph == true && current == p_count){
      out << "</p>";
	  in_paragraph = false;
	  }
	  */
      break;
    case Node::MARKUP:      
      out << "<b>";
      for (size_t i=0; i<child->children.size(); ++i) {
        process(child->children[i]);
      }
      out << "</b>";
      break;
    }
  }

 
  void process() {
    doctype();
    html();

  }
};


  //void count_paragraphs(NodeSP child){
	  /*
	  if(child->type() == Node::PARAGRAPH){
		  pcount++;
		  for( size_t i=0; i<child->children.size(); ++i){
		  count_paragrphs(child->children[i]);
		  }
	  }
	  else{
		  for(size_t i=0; i<child->children.size(); ++i){
			  count_paragrphs(child->children[i]);
		  }
	  }
	  */
	  /*
	  for(size_t i=0; i<child->children.size(); ++i){
		 if(child->type() == 2) pcount++;
		 //std::cout<<child->type();
		 //std::cin.get();
		 count_paragraphs(child->children[i], pcount);
	  }
  }
  */
  
PostProcessorSP CreateHTMLPostProcessor(NodeSP &dom,std::ostream &out)
{
  return PostProcessorSP(new HTMLPostProcessor(dom,out));
}

