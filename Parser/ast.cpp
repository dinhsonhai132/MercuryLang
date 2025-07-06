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
    for (auto &node : ast->children[0]->children) {
        cout << node->type << endl;
    }
}