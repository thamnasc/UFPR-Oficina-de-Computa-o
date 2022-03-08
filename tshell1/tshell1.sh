#!/bin/bash

#Feito por Thalita Maria do Nascimento (tmn21)

#requisitos obrigatórios
        chmod 700 ~/bin/tshell1.sh

pushd()
{
	builtin pushd $1 > /dev/null
}

popd()
{
	builtin popd $1 > /dev/null
}

function verifica_memoria 
{
	#conta quantas linhas tem no arquivo '--', que são 15

        #para poder ler o conteúdo do arquivo '--', é preciso
        #tratá-lo como um path ./--

	# $1 corresponde a $vr3
        local BYTES=$(cat ./$1 | wc -l)


	#procura um arquivo com 15 bytes
	#verifica a coluna 5 de cada arquivo e devolve a coluna 9 (nome do arquivo)
	local SEARCH=$(ls -la | awk -v B=$BYTES -F " " '
	{
		for (i=1; i<=NF; i++) 
		{
			if ($5==B) 
			{
				print $9; 
				break;
			}
	 	}
	}')

	echo $SEARCH
}

function procura_arquivo
{
	for ARCHIVE in $(ls -la)
        do
        	if [ $1 $ARCHIVE ] && [ $2 $ARCHIVE ]
                then
                        ARCHIVE=$(echo $ARCHIVE | cut -d\  -f9)
                        break
                fi
        done

	echo $ARCHIVE
}

#a tarefa	
#etapa2
	PATHS=("/home/" "html/" "inf/" "cursos/" "ci1001/" "tshell1/")
	for DIR in ${PATHS[@]}
	do
		pushd $DIR 
	done	
		
	#PATH1="/home/html/inf/cursos/ci1001/tshell1"
	#cd $PATH1

	#pista2.txt é o arquivo encontrado na terceira linha, segunda coluna
	var1=$(cat PISTA1 | awk -F "|" 'FNR==3 {print $2}')

#etapa3
	#'.outra pista' é a mensagem decodificada de pista2.txt
	var2=$(cat $var1 | base64 --decode)
	
#etapa4
	#'--' é o conteúdo encontrado em '.outra pista'
	var3=$(cat "$var2")

#etapa5
	#'?' é o nome do arquivo encontrado
	var4=$(verifica_memoria $var3)
	
#etapa6
	#alias rot13='tr '[a-z]' '[n-za-m]''
	#znvf_hzn_cvfgn é a mensagem decodificada
	var5=$(cat $var4 | rot13)

#etapa7 
	#entra no diretório .znvf_hzn_cvfgn
	pushd .$var5

	#d23 é o diretório encontrado
	ARCHIVE=$(procura_arquivo -w -d)

	pushd $ARCHIVE

	#a21 é o arquivo encontrado
	ARCHIVE=$(procura_arquivo -s -f)

	#is.9ioseo^,78.ss9927< é o conteúdo de a21
	var6=$(cat $ARCHIVE)

#etapa7
	STACK=$(dirs -v | tail -n 1 | cut -d\  -f2)
	for ((i=1; i<=$STACK; i++))
	do
		popd
	done

	#15.910530N,78.559927W são as coordenadas
	SAIDA=$(echo $var6 | sed 'y/isoe^_></1503NSEW/')
	echo Coordenadas do tesouro\: $SAIDA
