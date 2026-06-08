##Sobre o Projeto

Implementação do clássico jogo Space Invaders em hardware reconfigurável (FPGA), desenvolvida como projeto final da disciplina de Construção de sistemas digitais. O projeto integra lógica de hardware descrita em VHDL com lógica de aplicação em linguagem C, utilizando um processador embarcado.


## Funcionalidades

- Movimentação da nave e disparo controlados pelos botões onboard da FPGA
- Inimigos com movimento automático progressivo
- Sistema de pontuação
- Múltiplas vidas com controle de estado
- Tela de Game Over com opção de reinício


## Arquitetura Técnica

O projeto é estruturado em dois níveis:

- Hardware (VHDL): Controle da saída VGA, temporização de vídeo (sincronismo horizontal/vertical), leitura dos botões onboard e integração com o processador.
- Software (C): Lógica do jogo — movimentação de sprites, detecção de colisão, controle de pontuação, vidas e telas de estado.


## Principais Funções

draw_sprite -> Renderização de sprites na tela via VGA
init_object -> Inicialização dos objetos do jogo
draw_object -> Atualização visual dos objetos
move_object -> Lógica de movimentação
detect_colision -> Detecção de colisão entre objetos
verifica_col -> Verificação de estado de colisão
object_s -> Estrutura de dados central dos objetos


## Ferramentas Utilizadas

- Vivado
- Linguagem
- VHDL

Projeto desenvolvido em dupla como trabalho acadêmico da PUCRS — Curso de Engenharia de Computação.
