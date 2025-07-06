#include "..\Mercury\Mercury.cpp"
#define S std::
#define R return
#define A int
#define B char
#define Z if
#define Q ==
#define Y std::string
#define U auto
#define L MerCore_initialize
#define M MerCore_Finalize
#define LLLL {
#define RRRR }
A main(A O,B**P) LLLL Z(O<2){prompt();R 0;}Y X=P[1],T;Z(X Q "-v"){S cout<<LANGUAGE<<" "<<CUSTOM_VERSION<<" 2025 "<<AUTHOR<<'\n';R 0;}Z(X Q "-h"){print_help();R 0;}Z(X Q "-p"){prompt();R 0;}Z(X Q "-ast"||X Q "-c"||X Q "-m"){T=X;X=P[2];}Z(X Q "-info"||X Q "-i"){S cout<<"More info at http://dinhsonhai132.github.io/main.html\n";R 0;}Z(X.substr(X.find_last_of(".")+1)!= "mer"){S cerr<<"Error: file must have .mer extension\n";R 1;}Y I=MerBuffer_read_file(X);L();mLexer_T*J=_MerLexer_init(I.c_str());J->file=X.c_str();mParser_T*K=_MerParser_init(J);mAST_T*N=MerParser_parse_program(K);__compiler_u V=compiler_init();V.file=X.c_str();mCode_T W=MerCompiler_compile_ast_program(N,V);Z(T Q "-m"){print_bytecode(W.prg_code.buff);R 0;}Z(T Q "-ast"){MerAST_print_ast(N,0);}Z(T Q "-c"){Y F=X.substr(0,X.find_last_of("."))+".o";MerBuffer_make_and_write_file_bytecode(F,W.prg_code.buff);}stack*G=MerVM_evaluate_program(W);M();R 0;RRRR
