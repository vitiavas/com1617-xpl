// $Id: identity_node.h,v 1.1 2017/03/23 19:55:49 ist181045 Exp $ -*- c++ -*-
#ifndef __XPL_IDENTITYNODE_H__
#define __XPL_IDENTITYNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace xpl {

  class identity_node : public cdk::unary_expression_node {
  protected:
    inline identity_node(int lineno, cdk::expression_node *expression)
        : cdk::unary_expression_node(lineno, expression) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identity_node(this, level);
    }

  };

} // cdk

#endif