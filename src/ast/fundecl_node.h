// $Id: fundecl_node.h,v 1.2 2017/04/11 22:36:30 ist181045 Exp $ -*- c++ -*-
#ifndef __XPL_FUNDECLNODE_H__
#define __XPL_FUNDECLNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/basic_type.h>

#include <string>

namespace xpl {

  class fundecl_node: public cdk::basic_node {
    int _scope;
    basic_type *_type;
    std::string *_name;
    cdk::sequence_node *_arguments;

  public:
    inline fundecl_node(int lineno, basic_type *type, std::string *name,
        cdk::sequence_node *arguments)
        : cdk::basic_node(lineno), _type(type), _name(name),
        _arguments(arguments) {
    }

  public:
    inline const int scope() const {
      return _scope;
    }
    inline basic_type *type() {
      return _type;
    }
    inline std::string *name() {
      return _name;
    }
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_fundecl_node(this, level);
    }

  };

} // xpl

#endif