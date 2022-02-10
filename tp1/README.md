# O Exercício tp1
:pushpin: Uma vez logado na máquina cpu1, descubra quantos são os links simbólicos presentes no diretório /usr/bin desta máquina. 

:pushpin: Descubra também quantos núcleos o processador desta máquina tem (olhe o arquivo /proc/cpuinfo);

:pushpin: Quanto tem de espaço de memória nesta máquina, em formato humano (use o comando free, por exemplo).

:pushpin: Sua resposta deve ser um arquivo cujo nome é obrigatoriamente “tp1.sh”.

Este arquivo deverá conter comandos da shell que descobrem a resposta para você. Este arquivo deve ser entregue como resposta deste exercício. A correção será feita usando-se o comando “source” sobre o seu arquivo tp1.sh.

$ source tp1.sh

“source”, na shell, significa executar os comandos que estão escritos no arquivo. O que se espera como saída para o comando source executado acima são as informações pedidas acima, isto é, um número inteiro que é exatamente o número de links simbólicos no diretório /usr/bin da máquina cpu1, outro número inteiro com o número de núcleos e outro número inteiro com o espaço de memória. 



Descrições feitas pelo professor Castilho.