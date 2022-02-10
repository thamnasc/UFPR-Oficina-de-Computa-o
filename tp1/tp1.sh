# tmn21

# ls -la /usr/bin   lista todos os arquivos, mesmo ocultos no diretório bin
# grep "\->"        filtra as ocorrências de links simbólicos
# wc -l             conta as ocorrências
ls -la /usr/bin | grep "\->" | wc -l

# -m1 ^cpu\ cores /proc/cpuinfo
# filtra a primeira ocorrência de "cpu cores" no arquivo cpuinfo
# cut -d: -f2   
# recorta a partir do delimitador : a segunda coluna, que contém o número desejado 
grep -m1 ^cpu\ cores /proc/cpuinfo | cut -d: -f2

# free -h           imprime em formato humano os espaços de memória da máquina
# grep Mem.:        filtra a linha que contém a informação desejada
# awk '{print $2}'  processa o texto buscando a segunda coluna e imprime o valor total de memória
free -h | grep Mem.: | awk '{print $2}'
