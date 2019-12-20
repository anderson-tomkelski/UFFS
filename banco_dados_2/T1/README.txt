Para criar tabelas escrever, max 64 atributos:

create table NOMETABELA(char[N] ATTRIBUTO1, varchar[N] attributo2, int ATTRIBUTO3)

Para inserir dados:

insert into NOMETABELA(ATTRIBUTO1, ATTRIBUTO2, ATTRIBUTO3)

Para deletar dados

delete from NOMETABELA where ATTRIBUTO = VALUE

Para selecionar dados

select * from NOMETABELA

O SQL deve sempre ser mantido sobre essa estrutura, na criacao da tabela é necessário que o campo [N] esteja logo apos o tipo de variável sem espaco

Apenas a primeira operação e os nomes variáveis sao levados em consideração, o restante é para manter as aparências, porém, as palavras devem ser indicadas para que os campos corretos sejam selecionados

Alguns erros de entrada de usuário não são tratados, como por exemplo, a tentativa de acessar uma tabela inexistente irá retornar um sinal do tipo SIGSEGV
