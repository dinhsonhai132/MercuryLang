#include "C:\MercuryLang\Mercury\Mercury.cpp"

#define MER_CORE_API __mer_core_api__
#define MER_CORE_DATA __mer_core_data__
#define MER_CORE_LIB_API __mer_core_lib_api__

#define MERCURY_MORDEN_DOCUMENTATION \
"Welcome to MercuryLang! Mercury is a free and open-source lightweight interpreter written in C++.\n" \
"It is designed to provide clean, readable, and expressive syntax, making it ideal for developers of all experience levels.\n" \
"MercuryLang began development in 2023 and is still actively being improved.\n\n" \
"--- Lexer Phase ---\n" \
"Source files with the `.mer` extension are first tokenized by the lexer located in `Parser/Lexer/lexer.cpp`.\n" \
"Tokens are defined in the `Parser/Lexer/token.h` file using the `mToken_T` struct.\n" \
"The tokenizer can be accessed using an `mLexer_T` instance and calling `_MerLexer_get_next_tok(...)` to retrieve tokens.\n\n" \
"--- Error Generation ---\n" \
"After initial tokenization, error handling is performed using `Parser/errgen.cpp`.\n" \
"Warnings and errors are printed using `Parser/war.cpp`.\n\n" \
"--- Parsing Phase ---\n" \
"Once tokenized, the input is parsed into an AST using `Parser/parser.cpp` with support from `Parser/ast.cpp`.\n" \
"Parsing is done via the `MerParser_parse_program(...)` function, using the `mParser_T` struct.\n\n" \
"--- Bytecode Compilation ---\n" \
"The generated AST is compiled into bytecode by `Mercury/compile.cpp`.\n" \
"Bytecode is stored in an `mCode_T` structure, which contains two key fields: `prog_code` and `out_code`.\n" \
"Once compiled, Mercury creates two output files: `.merc-250.merc` and `.merc-250.out.merc`.\n\n" \
"--- Virtual Machine & Evaluation ---\n" \
"Bytecode is executed by the Mercury VM, implemented in `Mercury/eval.cpp`.\n" \
"Execution begins via the `MVM_program(...)` function using a stack-based architecture.\n" \
"During execution, runtime objects are created using the `mObject_T` struct.\n" \
"For example, a function object of type `_func` contains the function's name, memory address, and body.\n" \
"These objects are stored on the stack and maintained via a global symbol table (`s_symtable`)."