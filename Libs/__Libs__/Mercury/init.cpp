#include <Mercury.h>

START_DLL

DLL_EXPORT table* __print_ast(table* args[]) {
    table *code = args[0];
    string str = __convert_to_string(code->f_str_v);

    mLexer_T *lexer = _MerLexer_init(str.c_str());
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);

    MerAST_print_ast(ast);

    return value(0);
}

DLL_EXPORT table* __print_bytecode(table* args[]) {
    table *code = args[0];
    string str = __convert_to_string(code->f_str_v);

    mLexer_T *lexer = _MerLexer_init(str.c_str());
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u glb = compiler_init();
    mCode_T bcode = MerCompiler_compile_ast_program(ast, glb);
    print_bytecode(bcode.prg_code.buff);

    return value(0);
}

DLL_EXPORT table* initialize(table* args[]) {
    MerCore_initialize();
    return value(0);
}

DLL_EXPORT table* finalize(table* args[]) {
    MerCore_Finalize();
    return value(0);
}

DLL_EXPORT table* run_program(table* args[]) {
    table *code = args[0];
    string str = __convert_to_string(code->f_str_v);
    MercuryRunSimpleString(str.c_str());

    return value(0);
}

END_DLL