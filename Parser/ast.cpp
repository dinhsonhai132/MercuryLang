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
    node->is_class = false;
    node->is_mod_assign = false;
    node->is_assign_operator = false;
    node->is_break = false;
    node->is_continue = false;
    node->is_dad = false;
    node->is_inc = false;
    node->is_dec = false;

    node->inc_dec_value = nullptr;
    node->attr = nullptr;
    node->attr_value = nullptr;
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
    if (ast == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        cout << "  ";
    }

    cout << ast->type;
    if (!ast->string_iden.empty()) cout << " (id: " << ast->string_iden << ")";
    if (!ast->assign_iden.empty()) cout << " (assign: " << ast->assign_iden << ")";
    if (!ast->var_name.empty()) cout << " (var: " << ast->var_name << ")";
    if (!ast->func_name.empty()) cout << " (func: " << ast->func_name << ")";
    if (!ast->func_call.empty()) cout << " (call: " << ast->func_call << ")";
    if (!ast->list_name.empty()) cout << " (list: " << ast->list_name << ")";
    if (!ast->extract_name.empty()) cout << " (extract: " << ast->extract_name << ")";
    if (!ast->str_var_name.empty()) cout << " (str_var: " << ast->str_var_name << ")";
    if (ast->value != 0.0) cout << " (value: " << ast->value << ")";
    cout << endl;

    // Print children vectors
    for (auto *child : ast->children) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->then_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->else_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->do_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->args) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->list) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->in_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->in_else_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->class_body) MerAST_print_ast(child, indent + 1);
    for (auto *child : ast->str_children) MerAST_print_ast(child, indent + 1);

    // Print single child pointers
    if (ast->left) MerAST_print_ast(ast->left, indent + 1);
    if (ast->right) MerAST_print_ast(ast->right, indent + 1);
    if (ast->comp) MerAST_print_ast(ast->comp, indent + 1);
    if (ast->comp_left) MerAST_print_ast(ast->comp_left, indent + 1);
    if (ast->comp_right) MerAST_print_ast(ast->comp_right, indent + 1);
    if (ast->var_value) MerAST_print_ast(ast->var_value, indent + 1);
    if (ast->assign_value) MerAST_print_ast(ast->assign_value, indent + 1);
    if (ast->return_v) MerAST_print_ast(ast->return_v, indent + 1);
    if (ast->while_cond) MerAST_print_ast(ast->while_cond, indent + 1);
    if (ast->print_v) MerAST_print_ast(ast->print_v, indent + 1);
    if (ast->extract_value) MerAST_print_ast(ast->extract_value, indent + 1);
    if (ast->extract_assign) MerAST_print_ast(ast->extract_assign, indent + 1);
    if (ast->array_store) MerAST_print_ast(ast->array_store, indent + 1);
    if (ast->array_store_value) MerAST_print_ast(ast->array_store_value, indent + 1);
    if (ast->attr) MerAST_print_ast(ast->attr, indent + 1);
    if (ast->attr_value) MerAST_print_ast(ast->attr_value, indent + 1);
    if (ast->poutput) MerAST_print_ast(ast->poutput, indent + 1);
}