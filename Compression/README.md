# Trabalho 4
 
## Objetivo

O objetivo principal deste trabalho é dar ao aluno a oportunidade de analisar e comparar o desempenho de diferentes 
estruturas de dados e seus algoritmos aplicados a um conjunto de dados reais. Para tanto, será considerado como exemplo, 
problemas reais de encontrar padrões em sequências de DNA e, de armazenar tais sequências de forma mais eficiente. 
Utilize sequências geradas aleatoriamente disponíveis em: 
https://www.bioinformatics.org/sms2/random_dna.html


## Como fornecer os arquivos da sequência de DNA

A sequência de bases do DNA a ser comprimida pelo Huffman deve ser fornecida em um aquivo de texto, com extensão .txt, e sem quebras de linha. Há, no link abaixo, um exemplo de como deve ser formatado o arquivo.

Os arquivos com a sequência de DNA devem ser nomeados dnaX.txt onde X é um valor entre 1 a S e S é quantidade de sequências que serão processadas. Para os padrões, os arquivos devem ser nomeados como padraoX.txt onde X é um valor entre 1 a N.

Arquivo de exemplo: https://drive.google.com/file/d/1S2B8RT3ckD19dxNZtU9eDOuHivF-SOgv/view?usp=sharing

Você ainda pode baixar 5 (cinco) sequências de bases de DNA geradas aleatoriamente previamente no link a seguir (as pastas com "B" no final são as que foram usadas para as métricas do casamento de strings): https://drive.google.com/drive/folders/1Rcv9QUspnuRIJdYvJhMAatSmQb5OO66o?usp=sharing

## Como compilar e executar

Você pode compilar e executar o programa seguindo o passo a passo abaixo:

1. Abra um terminal de sua escolha

2. Navegue até a pasta onde está o programa

3. Digite o comando "mkdir build && cd build" (sem aspas)

4. Digite o comando "cmake ../" (sem aspas)

5. Digite o comando "make clean all" (sem aspas)

6. Digite o comando "./DNAWork.exe {coloque-aqui-o-caminho-da-pasta-para-a-compressao} {coloque-aqui-o-caminho-da-pasta-para-o-casamento-de-strings}" (sem aspas)

Exemplo: 

mkdir build && cd build

cmake ../

make clean all

./DNAWork.exe /home/joaoliveira/Documents/Repositories/DCC012/Trabalhos/Repositorios_Principais/04_Quarto_Trabalho/trabalho-pratico-4-grupo-2/dta/dtaC3 /home/joaoliveira/Documents/Repositories/DCC012/Trabalhos/Repositorios_Principais/04_Quarto_Trabalho/trabalho-pratico-4-grupo-2/dta/dtaC3B



Após a primeira execução você pode apenas usar os passos 5 e 6 (garantindo que ainda está dentro da pasta build)
