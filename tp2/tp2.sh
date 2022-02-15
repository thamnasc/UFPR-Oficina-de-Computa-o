#!/bin/bash
#o comando acima serve para que, mesmo em outras shell, seja rodado o script em bash

#tp2 - Oficina de Computação - Informática Biomédica
#Criado em 13/02/2022
#por Thalita Maria do Nascimento (tmn21)


# 1. Quantas turmas diferentes estão sendo ofertadas para o seu curso (computação, código 21A; informática biomédica, código 96A)?
# imprime na saída padrão o conteúdo do arquivo | filtra pelas ocorrências de informática biomédica | conta as ocorrências
cat ensalamento.csv | grep 96A | wc -l


# 2. Quantas destas turmas são teóricas?
# imprime na saída padrão o conteúdo do arquivo | filtra por aulas de informática biomédica | que são teóricas | e conta as ocorrências
cat ensalamento.csv | grep 96A | grep Teórica | wc -l


# 3. Quantas destas turmas ocorrem nas sextas-feiras?
# imprime na saída padrão o conteúdo do arquivo | filtra por todas as aulas de informática biomédica | recorta a coluna DIA_SEMANA | filtra as aulas de sextas-feiras | e conta as ocorrências
cat ensalamento.csv | grep 96A | cut -d\; -f5 | grep 6 | wc -l 


# 4. Quais são todos os cursos que constam nesta planilha? Liste-os em ordem alfabética sem repetição
# imprime na saída padrão o conteúdo do arquivo | filtra pela coluna de COD_CURSO | retirando COD_CURSO ou linhas em branco | e ordena sem repetições
cat ensalamento.csv | cut -d\; -f9 | egrep -v 'COD_CURSO|^[[:space:]]*$' | sort -u 


# 5. Quantos são os cursos?
# imprime na saída padrão o conteúdo do arquivo | filtra pela coluna de COD_CURSO | retirando COD_CURSO ou linhas em branco | ordena sem repetições | e conta as ocorrências
cat ensalamento.csv | cut -d\; -f9 | egrep -v 'COD_CURSO|^[[:space:]]*$' | sort -u | wc -l


# 6. Sem contar os cursos de Computação (21A) e de Informática Biomédica (96A), para quais cursos diferentes (em ordem alfabética e sem repetição) o Departamento de Informática oferta alguma turma neste semestre?
# imprime na saída padrão o conteúdo do arquivo | filtra os dados retirando BCC e IBM | seleciona os cursos do Departamento de Informática | recorta a coluna COD_CURSO | e a ordena sem repetição
cat ensalamento.csv | egrep -v "96A|21A" | grep Departamento\ de\ Informática | cut -d\; -f9 | sort -u

# 7. Produza uma planilha nova a partir da planilha fornecida na qual você está interessado em apenas 3 colunas: as colunas COD_DISCIPLINA; COD_CURSO; NOME_DEPTO. A saída deve ser ordenada por NOME_DEPTO e não pode ter repetições.
# recorta as colunas 1, 9 e 10 do arquivo | seleciona as ocorrências únicas (que já estão ordenadas no arquivo original) | envia para um novo arquivo planilha_nova.csv
cut -d\; -f1,9,10 ensalamento.csv | uniq -u | cat > planilha_nova.csv
