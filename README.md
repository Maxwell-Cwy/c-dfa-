dfa识别，递归下降分析四则运算，c语言实现

有左递归的文法：
<expression> ::= <term> | <expression> + <term> | <expression> - <term>
<term> ::= <factor> | <term> * <factor> | <term> / <factor>
<factor> ::= <number> | ( <expression> )

消除左递归的文法
<expression> ::= <term> <expression'>
<expression'> ::= + <term> <expression'> | - <term> <expression'> | ε
<term> ::= <factor> <term'>
<term'> ::= * <factor> <term'> | / <factor> <term'> | ε
<factor> ::= <number> | ( <expression> )

使用vs2022编写，直接打开sln文件
