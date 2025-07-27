#include "ast.h"

mAST_T *MerAST_new(void)
{
    mAST_T *node = new mAST_T();

    node->is_alone_val = false;
    node->is_if = false;
    node->is_while = false;
    node->is_for = false;
    node->is_import = false;
    node->is_block = false;
    node->has_else = false;
    node->is_built_in_func = false;
    node->is_inf = false;
    node->is_string = false;
    node->is_print = false;
    node->is_var = false;
    node->is_constant = false;
    node->is_global = false;
    node->is_local = false;
    node->is_mom = false;
    node->is_list = false;
    node->is_None = false;
    node->is_return = false;
    node->is_void = false;
    node->is_having_args = false;
    node->cond = false;
    node->is_extract = false;
    node->is_string_extract = false;
    node->for_is_having_else = false;
    node->is_plus_assign = false;
    node->is_minus_assign = false;
    node->is_mul_assign = false;
    node->is_div_assign = false;
    node->is_mod_assign = false;
    node->is_assign_operator = false;
    node->is_break = false;
    node->is_continue = false;
    node->is_dad = false;
    node->is_inc = false;
    node->is_extract_list = false;
    node->is_dec = false;

    node->inc_dec_value = nullptr;
    node->attr = nullptr;
    node->poutput = nullptr;
    node->comp = nullptr;
    node->assign_value = nullptr;
    node->while_cond = nullptr;
    node->print_v = nullptr;
    node->comp_left = nullptr;
    node->comp_right = nullptr;
    node->var_value = nullptr;
    node->return_v = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->extract_value = nullptr;
    node->str_var_value = nullptr;
    node->extract_assign = nullptr;

    node->true_line = 0;

    return node;
}

mAST_T *MerAST_make_parent(string type)
{
    mAST_T *node = MerAST_new();
    node->type = type;
    return node;
}

mAST_T *MerAST_make(string type, string tok, float value, const char *dt, const char *iden, int row)
{
    mAST_T *node = MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = iden;
    return node;
}

int MerAST_free(mAST_T *ast)
{
    if (ast == nullptr)
        return _SUCCESS;

    if (ast->left)
        MerAST_free(ast->left);
    if (ast->right)
        MerAST_free(ast->right);
    if (ast->comp)
        MerAST_free(ast->comp);
    if (ast->comp_left)
        MerAST_free(ast->comp_left);
    if (ast->comp_right)
        MerAST_free(ast->comp_right);
    if (ast->var_value)
        MerAST_free(ast->var_value);
    if (ast->return_v)
        MerAST_free(ast->return_v);
    if (ast->poutput)
        MerAST_free(ast->poutput);

    for (mAST_T *node : ast->args)
    {
        MerAST_free(node);
    }
    for (mAST_T *node : ast->body)
    {
        MerAST_free(node);
    }
    for (mAST_T *node : ast->then_body)
    {
        MerAST_free(node);
    }
    for (mAST_T *node : ast->else_body)
    {
        MerAST_free(node);
    }
    for (mAST_T *node : ast->list)
    {
        MerAST_free(node);
    }
    for (mAST_T *node : ast->children)
    {
        MerAST_free(node);
    }

    delete ast;

    return _SUCCESS;
}

void MerAST_print_ast(mAST_T *ast, int indent) {
    if (!ast) return;

    auto print_indent = [&](int lv) {
        for (int i = 0; i < lv; i++) cout << "  ";
    };

    print_indent(indent);
    cout << "- Node Type: " << ast->type;

    if (!ast->var_name.empty()) cout << ", var: " << ast->var_name;
    if (!ast->assign_iden.empty()) cout << ", assign: " << ast->assign_iden;
    if (!ast->func_name.empty()) cout << ", func: " << ast->func_name;
    if (!ast->func_call.empty()) cout << ", call: " << ast->func_call;
    if (!ast->string_iden.empty()) cout << ", str_iden: " << ast->string_iden;
    if (!ast->extract_name.empty()) cout << ", extract: " << ast->extract_name;
    if (!ast->op.empty()) cout << ", op: " << ast->op;
    if (!ast->comp_op.empty()) cout << ", cmp: " << ast->comp_op;
    if (!ast->str_v.empty()) cout << ", str: \"" << ast->str_v << "\"";
    if (!ast->tok.empty()) cout << ", tok: " << ast->tok;
    if (ast->value != 0.0) cout << ", val: " << ast->value;
    if (ast->is_string) cout << ", is_string";
    if (ast->is_list) cout << ", is_list";

    cout << " (line " << ast->true_line << ")" << endl;

    if (ast->assign_value) {
        print_indent(indent + 1);
        cout << "assign_value:" << endl;
        MerAST_print_ast(ast->assign_value, indent + 2);
    }

    if (ast->return_v) {
        print_indent(indent + 1);
        cout << "return:" << endl;
        MerAST_print_ast(ast->return_v, indent + 2);
    }

    if (ast->left) {
        print_indent(indent + 1);
        cout << "left:" << endl;
        MerAST_print_ast(ast->left, indent + 2);
    }

    if (ast->right) {
        print_indent(indent + 1);
        cout << "right:" << endl;
        MerAST_print_ast(ast->right, indent + 2);
    }

    if (ast->comp_left) {
        print_indent(indent + 1);
        cout << "comp_left:" << endl;
        MerAST_print_ast(ast->comp_left, indent + 2);
    }

    if (ast->comp_right) {
        print_indent(indent + 1);
        cout << "comp_right:" << endl;
        MerAST_print_ast(ast->comp_right, indent + 2);
    }

    if (ast->array_store) {
        print_indent(indent + 1);
        cout << "array_index:" << endl;
        MerAST_print_ast(ast->array_store, indent + 2);
    }

    if (ast->array_store_value) {
        print_indent(indent + 1);
        cout << "array_value:" << endl;
        MerAST_print_ast(ast->array_store_value, indent + 2);
    }

    if (!ast->args.empty()) {
        print_indent(indent + 1);
        cout << "args:" << endl;
        for (auto &arg : ast->args) {
            MerAST_print_ast(arg, indent + 2);
        }
    }

    if (!ast->body.empty()) {
        print_indent(indent + 1);
        cout << "body:" << endl;
        for (auto &stmt : ast->body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->children.empty()) {
        print_indent(indent + 1);
        cout << "children:" << endl;
        for (auto &child : ast->children) {
            MerAST_print_ast(child, indent + 2);
        }
    }

    if (!ast->then_body.empty()) {
        print_indent(indent + 1);
        cout << "then:" << endl;
        for (auto &stmt : ast->then_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->else_body.empty()) {
        print_indent(indent + 1);
        cout << "else:" << endl;
        for (auto &stmt : ast->else_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->list.empty()) {
        print_indent(indent + 1);
        cout << "list:" << endl;
        for (auto &item : ast->list) {
            MerAST_print_ast(item, indent + 2);
        }
    }

    if (ast->comp) {
        print_indent(indent + 1);
        cout << "condition:" << endl;
        MerAST_print_ast(ast->comp, indent + 2);
    }

    if (!ast->do_body.empty()) {
        print_indent(indent + 1);
        cout << "do_body:" << endl;
        for (auto &stmt : ast->do_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->in_body.empty()) {
        print_indent(indent + 1);
        cout << "for_in_body:" << endl;
        for (auto &stmt : ast->in_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->in_else_body.empty()) {
        print_indent(indent + 1);
        cout << "for_else_body:" << endl;
        for (auto &stmt : ast->in_else_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }
}
