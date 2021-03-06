#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//===========================================================================

void xpl::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  close_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}
void xpl::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}
void xpl::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  const std::string &value = node->value();

  os() << std::string(lvl, ' ') << "<" << node->label() << ">";
  for (auto it = value.begin(); it != value.end(); ++it) {
    switch (*it) {
      case '\t':
      case '\n':
      case '\r':
        break;
      default:
        os() << *it;
    }
  }

  os() << "</" << node->label() << ">" << std::endl;
}
void xpl::xml_writer::do_null_node(xpl::null_node * const node, int lvl) {
  single_tag(node, lvl);
}

//===========================================================================

inline void xpl::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  open_tag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  close_tag(node, lvl);
}

void xpl::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
void xpl::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
void xpl::xml_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
  open_tag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  close_tag(node, lvl);
}

//===========================================================================

inline void xpl::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  open_tag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  close_tag(node, lvl);
}

void xpl::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_address_of_node(xpl::address_of_node * const node, int lvl) {
  open_tag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  close_tag(node, lvl);
}
void xpl::xml_writer::do_malloc_node(xpl::malloc_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("size", lvl + 2);
  node->expression()->accept(this, lvl + 4);
  close_tag("size", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_index_node(xpl::index_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("expression", lvl + 2);
  node->expression()->accept(this, lvl + 4);
  close_tag("expression", lvl + 2);

  open_tag("offset", lvl + 2);
  node->offset()->accept(this, lvl + 4);
  close_tag("offset", lvl + 2);

  close_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "name='" << node->name() << "'"
      << "/>" << std::endl;
}
void xpl::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  open_tag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  close_tag(node, lvl);
}
void xpl::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  open_tag(node, lvl);

  node->lvalue()->accept(this, lvl);
  reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  close_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  open_tag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  close_tag(node, lvl);
}
void xpl::xml_writer::do_print_node(xpl::print_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "newline='" << node->newline() << "'"
      << ">" << std::endl;
  node->argument()->accept(this, lvl + 2);
  close_tag(node, lvl);
}
void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl) {
  single_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_if_node(xpl::if_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  close_tag("condition", lvl + 2);

  open_tag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  close_tag("then", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  close_tag("condition", lvl + 2);

  open_tag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  close_tag("then", lvl + 2);

  open_tag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  close_tag("else", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_while_node(xpl::while_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  close_tag("condition", lvl + 2);

  open_tag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  close_tag("block", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("lvalue", lvl + 2);
  node->lvalue()->accept(this, lvl + 4);
  close_tag("lvalue", lvl + 2);

  open_tag("initial", lvl + 2);
  node->initial()->accept(this, lvl + 4);
  close_tag("initial", lvl + 2);

  open_tag("upper", lvl + 2);
  node->upper()->accept(this, lvl + 4);
  close_tag("upper", lvl + 2);

  open_tag("step", lvl + 2);
  node->step()->accept(this, lvl + 4);
  close_tag("step", lvl + 2);

  open_tag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  close_tag("block", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("lvalue", lvl + 2);
  node->lvalue()->accept(this, lvl + 4);
  close_tag("lvalue", lvl + 2);

  open_tag("initial", lvl + 2);
  node->initial()->accept(this, lvl + 4);
  close_tag("initial", lvl + 2);

  open_tag("lower", lvl + 2);
  node->lower()->accept(this, lvl + 4);
  close_tag("lower", lvl + 2);

  open_tag("step", lvl + 2);
  node->step()->accept(this, lvl + 4);
  close_tag("step", lvl + 2);

  open_tag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  close_tag("block", lvl + 2);

  close_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_block_node(xpl::block_node * const node, int lvl) {
  open_tag(node, lvl);

  open_tag("declarations", lvl + 2);
  node->declarations()->accept(this, lvl + 4);
  close_tag("declarations", lvl + 2);

  open_tag("statements", lvl + 2);
  node->statements()->accept(this, lvl + 4);
  close_tag("statements", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_next_node(xpl::next_node * const node, int lvl) {
  single_tag(node, lvl);
}
void xpl::xml_writer::do_stop_node(xpl::stop_node * const node, int lvl) {
  single_tag(node, lvl);
}
void xpl::xml_writer::do_return_node(xpl::return_node * const node, int lvl) {
  single_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_funcall_node(xpl::funcall_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "name='" << node->name() << "'"
      << ">" << std::endl;
  node->arguments()->accept(this, lvl + 2);
  close_tag(node, lvl);
}

//===========================================================================

void xpl::xml_writer::do_vardecl_node(xpl::vardecl_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "scope='" << node->scope() << "' "
      <<  "type='" << node->type()->name() << "' "
      <<  "name='" << node->name() << "'"
      << ">" << std::endl;
  close_tag(node, lvl);
}
void xpl::xml_writer::do_var_node(xpl::var_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "scope='" << node->scope() << "' "
      <<  "type='" << node->type()->name() << "' "
      <<  "name='" << node->name() << "'"
      << ">" << std::endl;

  open_tag("value", lvl + 2);
  node->value()->accept(this, lvl + 4);
  close_tag("value", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_fundecl_node(xpl::fundecl_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "scope='" << node->scope() << "' "
      <<  "type='" << node->type()->name() << "' "
      <<  "name='" << node->name() << "'"
      << ">" << std::endl;

  open_tag("arguments", lvl + 2);
  node->arguments()->accept(this, lvl + 4);
  close_tag("arguments", lvl + 2);

  close_tag(node, lvl);
}
void xpl::xml_writer::do_function_node(xpl::function_node * const node, int lvl) {
  os() << std::string(lvl, ' ')
      << "<" << node->label() << " "
      << "scope='" << node->scope() << "' "
      <<  "type='" << node->type()->name() << "' "
      <<  "name='" << node->name()  << "'"
      << ">" << std::endl;

  open_tag("arguments", lvl + 2);
  node->arguments()->accept(this, lvl + 4);
  close_tag("arguments", lvl + 2);

  open_tag("body", lvl + 2);
  node->body()->accept(this, lvl + 4);
  close_tag("body", lvl + 2);

  if (node->retval()) {
    open_tag("return", lvl + 2);
    node->retval()->accept(this, lvl + 4);
    close_tag("return", lvl + 2);
  }

  close_tag(node, lvl);
}
