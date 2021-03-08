# TP1-cg
Jogo criado baseado no Galaxian de ATARI.

Desenvolvido por: Alex Meireles Santos Almeida e Darmes Araujo Dias.

1) Para realizar a instalação das bibliotecas necessárias, devemos acessar o Terminal do Linux. Para isso, pressione ctrl + alt + t ou procure por Terminal no Menu Linux.
2) Após abrir o Terminal, precisamos verificar se todas as informações dos pacotes de fontes já instaladas estão configuradas na versão mais recente, caso não esteja, será feita a atualização. Para isso, execute o comando no terminal:
sudo apt-get update

Coloque sua senha para fazer a verificação e aguarde a finalização.

3) Após seu sistema concluir as atualizações, iremos instalar alguns mecanismos necessários para desenvolvermos alguns processos, pelo comando via terminal:
sudo apt-get install build-essential 

No meu caso, todas ferramentas já estão instaladas. Entretanto, caso apareça uma mensagem perguntando se deseja continuar, pressione s e logo em seguida enter.

4) A partir de agora iremos instalar todas as bibliotecas, você deve criar um diretório, e nesse diretório criar um arquivo de texto, nele você
deve inserir isso:
#!/bin/bash 
#avisando o terminal que o nosso script está escrito em bash

FILE="/tmp/out.$$"

#Utilizar o modo administrador para rodar o script
if [[ "$EUID" -ne "0" ]]; then
    echo "Esse script deve ser executado em modo administrador, portanto, "#sudo su" em seu terminal linux, e depois deve digitar sua senha" !>&2
    exit 1
fi
#comandos para instalar as bibliotecas que serão utilizadas
apt-get update -y
apt-get install freeglut3 -y
apt-get install freeglut3-dev -y
apt-get install g++ cmake -y
apt-get install g++ -y
apt-get install binutils-gold -y
apt-get install libglew-dev -y
apt-get install libglew1.5-dev libglm-dev -y
apt-get install libsoil-dev -y
apt-get install mesa-common-dev -y
glxinfo | grep OpenGl

Após copiar e colar, você deve salvar com extensão .sh.

5) Após salvar, você deve entrar no terminal e entrar no diretório que foi salvo, e depois deve escreve sudo su(entrando no modo administrador) e
colocar sua senha, depois escreva chmod +x nomedoarquivo.sh(tornando o arquivo executável).

6) Depois disso é só rodar com ./nomedoarquivo.sh 

7) Todas bibliotecas instaladas! Para jogar baixe o zip do repositório ou faça um git-clone para seu desktop. Se tiver baixado o zip primeiramente descomprima os arquivos, depois acesse a pasta da última versão com o comando:
cd 'pasta-onde-foi-clonado-ou-baixado'/TP1-cg

e depois dê o comando:

make run

Instruções de jogo:
Setas para cima e para baixo para se locomover no menu inicial.
Espaço para acessar algum item do menu.
Esc para voltar se tiver acessado um item do menu, para voltar ao menu caso tiver apertado pause(P), e para sair do jogo caso estiver em jogo ou no menu.
Setas para direita e esquerda para se mover no jogo.
Espaço para atirar.
R reinicia o jogo.
Se caso houver ganhado ou perdido, aperte B para ir para o menu principal.
P para pausar o jogo.

Itens adicionais implementados:

⭐ Texturas animadas: 
    	Jogador parado ou andando.
    	Inimigos andando. 
    	Outros objetos ou cenário animados.
    	Fundo lindão e com movimento/animação 
⭐ Relativos ao jogo:
	    Rasante(ultima fase).
	    Inimigos diferentes 
	    Fases "curadas" 
	    Sistema Pontuação máxima
	    Vidas
	    Telas(menu inicial, créditos, highscore, gameover,win).
	    Implementação criativa: Tela de highscore, tela de menu principal.


