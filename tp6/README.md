# **Verificador de Expressões**

Escreva um programa em C usando pilha (com uma biblioteca "libpilha" feita por você) para verificar se uma dada expressão é válida.

Considere uma expressão como uma string que contenha os seguintes caracteres: "(", ")", "[", "]", "{", "}"

A expressão é válida se a quantidade de cada caracter de abertura e fechamento estão equilibrados na string e se as aberturas e fechamentos estão em ordem correta. Por exemplo:

A expressão a seguir é válida: "{[[()]]}(){[]}[()]"

A expressão a seguir NÃO é válida: "{\[}]()", pois abre-se a chave, abre-se o colchete e este não é fechado antes do fechamento da chave;

A expressão a seguir também NÃO é válida: "{[]}(", pois abre-se um parênteses que não é fechado.

Logo, seu programa deve receber uma string como expressão de entrada e retornar, como saída, o inteiro 1 para expressão válida e o inteiro 0 para expressão inválida.

O algoritmo para realizar a avaliação de expressões deve ser feito de acordo com a especificação abaixo:

\1. Use uma pilha no main.c, de acordo com sua implementação feita na pilha.h/.c

\2. Percorra a string que representa a expressão. Ao encontrar um caracter de abertura, como "(", "[" ou "{", insira-o na pilha. Ao encontrar um caracter de fechamento, como ")", "]" ou "}", remova o topo da pilha. Caso o caracter removido (de abertura) seja par do caracter lido (de fechamento), continue o processo até terminar a leitura da string.

\3. Se os caracteres removido e lido não fizerem par, a expressão é inválida.

\4. Se ao final da leitura da string da expressão restarem caracteres na pilha, a expressão é inválida.

A implementação da pilha deve usar um vetor alocado dinamicamente e a pilha deve usar uma struct que conhece este vetor, seu tamanho e o topo.