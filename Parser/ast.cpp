#include "ast.h"

mAST_T *_MerAST_new(void)
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

    return node;
}


mAST_T *_MerAST_make_parent(string type)
{
    mAST_T *node = _MerAST_new();
    node->type = type;
    return node;
}

mAST_T *_MerAST_make(string type, string tok, float value, const char *dt, const char *iden)
{
    mAST_T *node = _MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = iden;
    return node;
}

int _MerAST_free(mAST_T *ast)
{
    if (ast == nullptr)
        return _SUCCESS;

    if (ast->left)
        _MerAST_free(ast->left);
    if (ast->right)
        _MerAST_free(ast->right);
    if (ast->comp)
        _MerAST_free(ast->comp);
    if (ast->comp_left)
        _MerAST_free(ast->comp_left);
    if (ast->comp_right)
        _MerAST_free(ast->comp_right);
    if (ast->var_value)
        _MerAST_free(ast->var_value);
    if (ast->return_v)
        _MerAST_free(ast->return_v);
    if (ast->poutput)
        _MerAST_free(ast->poutput);

    for (mAST_T *node : ast->args)
    {
        _MerAST_free(node);
    }
    for (mAST_T *node : ast->body)
    {
        _MerAST_free(node);
    }
    for (mAST_T *node : ast->then_body)
    {
        _MerAST_free(node);
    }
    for (mAST_T *node : ast->else_body)
    {
        _MerAST_free(node);
    }
    for (mAST_T *node : ast->list)
    {
        _MerAST_free(node);
    }
    for (mAST_T *node : ast->children)
    {
        _MerAST_free(node);
    }

    delete ast;

    return _SUCCESS;
}

