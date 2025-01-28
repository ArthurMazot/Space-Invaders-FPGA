#include <hf-risc.h>
#include "vga_drv.h"

#define QTDLin 6
#define QTDI 12 
#define LIMITX 300
#define LIMITY 218
/* sprites and sprite drawing */

char colors[1][16] = { //Teste de Cores
	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}
};

char gun_skin[1][4] = { //Tiro do personagem
	{1,1,1,1}
};

char attack_skin[1][4] = { //Tiro do invasor
	{4,4,4,4}
};

char explosao_player[8][15] = { 
	{0,   0,   0,   0,   0,   4,   0,   0,   0,   0,   0,  0,  0,  0,  0},
	{0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,  0,  0,  0,  0},
	{0,   0,   0,   0,   0,   4,   0,   4,   0,  12,   0,  0,  0,  0,  0},
	{0,   0,   4,   0,   0,  12,   0,   0,   0,   0,   0,  0,  0,  0,  0},
	{0,   0,   0,   0,   0,   0,  12,  12,   0,  12,   4,  0,  0,  0,  0},
	{4,   0,   0,   0,  12,   0,  12,  14,   0,  12,   0,  4,  0,  0,  0},
	{0,   0,  12,  12,  14,  12,  14,  14,  14,  12,   0,  0,  4,  0,  0},
	{0,  12,  14,  14,  14,  14,  14,  14,  14,  14,  12,  0,  4,  0,  4},
};

char explosao_nave[9][13] = { 
	{0,  13,  0,  0, 14,  0, 0,  0, 13,  0,  0, 14,  0},
	{0,   0, 13,  0,  0, 14, 0, 13,  0,  0, 14,  0,  0},
	{0,   0,  0, 13,  0,  0, 0,  0,  0, 14,  0,  0,  0},
	{14, 14,  0,  0,  0,  0, 0,  0,  0,  0,  0, 13, 13},
	{0,   0,  0, 13,  0,  0, 0,  0,  0, 14,  0,  0,  0},
	{0,   0, 13,  0,  0, 14, 0, 13,  0,  0, 14,  0,  0},
	{0,  13,  0,  0, 14,  0, 0,  0, 13,  0,  0, 14,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0}
};

char mystery1[7][16] = { 
	{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0, 0, 0, 0},
	{0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0, 0, 0, 0},
	{0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  1,  1,  1, 0, 0, 0},
	{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 0, 0},
	{0,  1,  1,  13,  1,  1,  14,  1,  1,  13,  1,  1,  14, 1, 1, 0},
	{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1, 1},
	{0,  0,  1,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1, 1, 0, 0},
};

char mystery2[7][16] = { 
	{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0, 0, 0, 0},
	{0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0, 0, 0, 0},
	{0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  1,  1,  1, 0, 0, 0},
	{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 0, 0},
	{0,  1,  1,  14,  1,  1,  13,  1,  1,  14,  1,  1,  13, 1, 1, 0},
	{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1, 1},
	{0,  0,  1,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1, 1, 0, 0},
};

char vid1[8][9] = { 
	{0,  0,  2,  2,  0,  2,  2, 0, 0},
	{0,  2,  0,  0,  2,  0,  0, 2, 0},
	{2,  0,  0,  0,  0,  0,  0, 0, 2},
	{2,  0,  0,  0,  0,  0,  0, 0, 2},
	{0,  2,  0,  0,  0,  0,  0, 2, 0},
	{0,  0,  2,  0,  0,  0,  2, 0, 0},
	{0,  0,  0,  2,  0,  2,  0, 0, 0},
	{0,  0,  0,  0,  2,  0,  0, 0, 0},
};

char vid2[8][9] = { 
	{0,  0,  15,  15,  0,  15,  15, 0, 0},
	{0,  15,  4,  4,  15,  4,  4, 15, 0},
	{15,  4,  4,  4,  4,  4,  4, 4, 15},
	{15,  4,  4,  4,  4,  4,  4, 4, 15},
	{0,  15,  4,  4,  4,  4,  4, 15, 0},
	{0,  0,  15,  4,  4,  4,  15, 0, 0},
	{0,  0,  0,  15,  4,  15,  0, 0, 0},
	{0,  0,  0,  0,  15,  0,  0, 0, 0},
};

char escudo[16][22] = { 
	{0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 9, 0, 0, 0, 0, 0},
	{0, 0, 0, 15, 15, 9, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 3, 3, 0, 0, 0},
	{0, 0, 15, 9, 9, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 0, 0},
	{0, 15, 9, 9, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 3, 0},
	{15, 9, 9, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 3},
	{15, 9, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 3},
	{15, 11, 3, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 3},
	{15, 11, 3, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 11, 3},
	{15, 9, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 11, 11, 3},
	{15, 9, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 11, 11, 3, 3},
	{15, 9, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 11, 11, 3, 3, 3},
	{15, 9, 11, 11, 3, 3, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 11, 11, 3, 3, 9, 3},
	{15, 11, 11, 3, 3, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 11, 11, 3, 3, 9, 9, 3},
	{15, 3, 3, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 3, 3, 9, 9, 9, 3},
	{15, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9, 9, 9, 3},
	{9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 3, 3, 3, 3}
	};

char explosao_invasores[9][13] = {  
	{0,  13,  0,  0, 13,  0, 0,  0, 13,  0,  0, 13,  0},
	{0,   0, 13,  0,  0, 13, 0, 13,  0,  0, 13,  0,  0},
	{0,   0,  0, 13,  0,  0, 0,  0,  0, 13,  0,  0,  0},
	{13, 13,  0,  0,  0,  0, 0,  0,  0,  0,  0, 13, 13},
	{0,   0,  0, 13,  0,  0, 0,  0,  0, 13,  0,  0,  0},
	{0,   0, 13,  0,  0, 13, 0, 13,  0,  0, 13,  0,  0},
	{0,  13,  0,  0, 13,  0, 0,  0, 13,  0,  0, 13,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0}
};

char explosao_invasores1[9][13] = {
	{0,  2,  0,  0, 2,  0, 0,  0, 2,  0,  0, 2,  0},
	{0,   0, 2,  0,  0, 2, 0, 2,  0,  0, 2,  0,  0},
	{0,   0,  0, 2,  0,  0, 0,  0,  0, 2,  0,  0,  0},
	{2, 2,  0,  0,  0,  0, 0,  0,  0,  0,  0, 2, 2},
	{0,   0,  0, 2,  0,  0, 0,  0,  0, 2,  0,  0,  0},
	{0,   0, 2,  0,  0, 2, 0, 2,  0,  0, 2,  0,  0},
	{0,  2,  0,  0, 2,  0, 0,  0, 2,  0,  0, 2,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0}
};

char explosao_invasores2[9][13] = { 
	{0,  4,  0,  0, 4,  0, 0,  0, 4,  0,  0, 4,  0},
	{0,   0, 4,  0,  0, 4, 0, 4,  0,  0, 4,  0,  0},
	{0,   0,  0, 4,  0,  0, 0,  0,  0, 4,  0,  0,  0},
	{4, 4,  0,  0,  0,  0, 0,  0,  0,  0,  0, 4, 4},
	{0,   0,  0, 4,  0,  0, 0,  0,  0, 4,  0,  0,  0},
	{0,   0, 4,  0,  0, 4, 0, 4,  0,  0, 4,  0,  0},
	{0,  4,  0,  0, 4,  0, 0,  0, 4,  0,  0, 4,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0},
	{0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0, 0,  0}
};

char nave2[9][15] = {
	{0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 11, 15, 11, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 11, 15, 15, 15, 11, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 11, 15, 15, 1, 15, 15, 11, 0, 0, 0, 0},
	{0, 0, 0, 15, 15, 15, 1, 1, 1, 15, 15, 15, 0, 0, 0},
	{0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0},
	{0, 15, 15, 15, 11, 4, 12, 6, 12, 4, 11, 15, 15, 15, 0},
	{15, 15, 11, 0, 0, 0, 4, 12, 4, 0, 0, 0, 11, 15, 15},
	{0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0}
};

char nave1[9][15] = {
	{0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 11, 15, 11, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 11, 15, 15, 15, 11, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 11, 15, 15, 1, 15, 15, 11, 0, 0, 0, 0},
	{0, 0, 0, 15, 15, 15, 1, 1, 1, 15, 15, 15, 0, 0, 0},
	{0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0},
	{0, 15, 15, 15, 11, 0, 4, 12, 4, 0, 11, 15, 15, 15, 0},
	{15, 15, 11, 0, 0, 0, 0, 4, 0, 0, 0, 0, 11, 15, 15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char monster1a[8][11] = { //Invasor 10 Pontos
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10},
	{0, 2, 0, 2, 10, 10, 10, 10, 0, 10, 0},
	{0, 0, 2, 10, 10, 10, 10, 10, 10, 0, 0},
	{2, 0, 2, 10, 15, 15, 0, 15, 10, 0, 10},
	{0, 2, 2, 10, 15, 15, 0, 15, 10, 10, 0},
	{0, 0, 2, 10, 10, 10, 10, 10, 10, 0, 0},
	{0, 2, 0, 2, 10, 10, 10, 10, 0, 10, 0},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10}
};

char monster1b[8][11] = { //Invasor 10 Pontos
	{0, 2, 0, 2, 10, 10, 10, 10, 0, 10, 0},
	{2, 0, 2, 10, 15, 15, 4, 15, 10, 0, 10},
	{0, 0, 2, 10, 10, 10, 10, 10, 10, 0, 0},
	{0, 2, 2, 10, 15, 0, 0, 15, 10, 10, 0},
	{2, 0, 2, 10, 0, 0, 0, 0, 10, 0, 10},
	{0, 0, 2, 10, 15, 0, 4, 4, 10, 0, 0},
	{0, 2, 0, 2, 10, 10, 10, 4, 0, 10, 0},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 103}
};

char monster2a[9][8] = { //Invasor 20 Pontos
	{0, 4, 0, 0, 0, 0, 12, 0},
	{0, 4, 12, 12, 12, 12, 12, 0},
	{4, 12, 15, 15, 4, 15, 15, 12},
	{4, 12, 12, 15, 4, 15, 12, 12},
	{4, 12, 12, 12, 12, 12, 12, 12},
	{0, 4, 12, 12, 12, 12, 12, 0},
	{0, 0, 12, 0, 0, 12, 0, 0},
	{4, 0, 12, 0, 0, 12, 0, 4},
	{0, 12, 0, 0, 0, 0, 12, 0}
};

char monster2b[9][8] = { //Invasor 20 Pontos
	{0, 4, 0, 0, 0, 0, 12, 0},
	{0, 4, 12, 12, 12, 12, 12, 0},
	{4, 12, 15, 15, 4, 15, 15, 12},
	{4, 12, 12, 15, 15, 15, 12, 12},
	{0, 4, 12, 12, 12, 12, 12, 0},
	{12, 0, 12, 12, 12, 12, 0, 12},
	{12, 0, 0, 0, 0, 0, 0, 12},
	{12, 0, 4, 0, 0, 4, 0, 12},
	{0, 12, 0, 0, 0, 0, 12, 0}
};

char monster3a[8][12] = { //Invasor 30 Pontos
	{0, 0, 0, 0, 13, 13, 5, 0, 0, 0, 0, 0},
	{0, 13, 13, 13, 15, 0, 15, 5, 5, 5, 0, 0},
	{13, 15, 12, 15, 0, 0, 0, 15, 12, 15, 5, 0},
	{0, 13, 13, 13, 15, 0, 15, 13, 13, 5, 0, 0},
	{0, 0, 13, 13, 13, 13, 13, 13, 13, 0, 0, 0},
	{0, 13, 0, 0, 13, 0, 0, 13, 0, 5, 0, 0},
	{0, 0, 13, 0, 13, 0, 13, 0, 0, 0, 5, 0},
	{0, 0, 0, 13, 0, 13, 0, 13, 0, 5, 0, 0}
};

char monster3b[8][12] = { //Invasor 30 Pontos
	{0, 0, 0, 13, 15, 0, 15, 5, 0, 0, 0, 0},
	{0, 13, 13, 15, 0, 0, 0, 15, 5, 5, 0, 0},
	{13, 5, 5, 0, 0, 0, 0, 0, 13, 13, 5, 0},
	{0, 13, 13, 15, 0, 0, 0, 15, 5, 5, 0, 0},
	{0, 0, 13, 13, 15, 0, 15, 5, 5, 0, 0, 0},
	{0, 13, 0, 13, 0, 0, 0, 13, 0, 13, 0, 0},
	{13, 0, 0, 13, 0, 0, 13, 0, 0, 13, 0, 13},
	{13, 0, 13, 0, 13, 0, 0, 13, 0, 0, 13, 0}
};

void draw_sprite(unsigned int x, unsigned int y, char *sprite,
	unsigned int sizex, unsigned int sizey, int color)
{
	unsigned int px, py;
	
	if (color < 0) {
		for (py = 0; py < sizey; py++)
			for (px = 0; px < sizex; px++)
				display_pixel(x + px, y + py, sprite[py * sizex + px]);
	} else {
		for (py = 0; py < sizey; py++)
			for (px = 0; px < sizex; px++)
				display_pixel(x + px, y + py, color & 0xf);
	}
	
}

/* sprite based objects */
struct object_s {
	char alive;
	int count;
	char *sprite_frame[3];
	char spriteszx, spriteszy, sprites;
	int cursprite;
	unsigned int posx, posy;
	int dx, dy;
	int speedx, speedy;
	int speedxcnt, speedycnt;
	int pontos;
};

//Variaveis Globais
struct object_s enemies[QTDLin][QTDI];
struct object_s gun_enemies[3];
struct object_s player, gun, mystery;
char buf[10] = {};
int posicao[3] = {-1, -1, -1};
int pontuacao = 0;
int aux = 0;
int pos[3] = {5, 5, 5};
int vidas = 3;
int qntInimigos = QTDI*(QTDLin-1) + 1;
int win = 0;
int replay = 0; 

void init_object(struct object_s *obj, char *spritea, char *spriteb,
	char *spritec, char spriteszx, char spriteszy, int posx, int posy, 
	int dx, int dy, int spx, int spy, int pon)
{	
	obj->alive = 1;
	obj->count = 2;
	obj->sprite_frame[0] = spritea;
	obj->sprite_frame[1] = spriteb;
	obj->sprite_frame[2] = spritec;
	obj->spriteszx = spriteszx;
	obj->spriteszy = spriteszy;
	obj->cursprite = 0;
	obj->posx = posx;
	obj->posy = posy;
	obj->dx = dx;
	obj->dy = dy;
	obj->speedx = spx;
	obj->speedy = spy;
	obj->speedxcnt = spx;
	obj->speedycnt = spy;
	obj->pontos = pon;
}

void draw_object(struct object_s *obj, char chgsprite, int color)
{
	if (chgsprite) {
		obj->cursprite++;
		if (obj->sprite_frame[obj->cursprite] == 0)
			obj->cursprite = 0;
	}
	if(obj->alive){
		draw_sprite(obj->posx, obj->posy, obj->sprite_frame[obj->cursprite],
			obj->spriteszx, obj->spriteszy, color);
	}
	else if(obj->count){
		if(obj->sprite_frame[0] == monster1a[0]){
		draw_sprite(obj->posx, obj->posy, explosao_invasores1[0], 13, 9, color); }
	
		if(obj->sprite_frame[0] == monster3a[0]){
		draw_sprite(obj->posx, obj->posy, explosao_invasores[0], 13, 9, color); }

		if(obj->sprite_frame[0] == monster2a[0]){
		draw_sprite(obj->posx, obj->posy, explosao_invasores2[0], 13, 9, color); }

		if(obj->sprite_frame[0] == mystery1[0]){
		draw_sprite(obj->posx, obj->posy, 0, 16, 7, 0); 
		draw_sprite(obj->posx, obj->posy, explosao_nave[0], 13, 9, color); }

				obj->count--;}

	else draw_sprite(obj->posx, obj->posy, explosao_invasores[0],
				13, 8, 0);
}

void move_object(struct object_s *obj)
{
	struct object_s oldobj;

	memcpy(&oldobj, obj, sizeof(struct object_s));

	if((obj->posx <= 10) || ((obj->posx+20) > LIMITX))
		for(int i = 0; i < QTDLin; i++){
			for(int j = 0; j < QTDI; j++){
				draw_object(&enemies[i][j], 0, 0);
				enemies[i][j].posx += (enemies[i][j].dx == 1) ? -1 : 1;
				enemies[i][j].dx *= -1;}}

	if (--obj->speedxcnt == 0) {
		obj->speedxcnt = obj->speedx;
		obj->posx = obj->posx + obj->dx;
	}
	if (--obj->speedycnt == 0) {
		obj->speedycnt = obj->speedy;
		obj->posy = obj->posy + obj->dy;
	}

	if ((obj->speedx == obj->speedxcnt) || (obj->speedy == obj->speedycnt)){
		draw_object(&oldobj, 0, 0);
		draw_object(obj, 1, -1);
	}
}

void detect_colision(struct object_s *g){

	if(g->posy < 15){
		draw_object(g, 0, 0);
		g->posx = player.posx + 6;
		g->posy = player.posy - 4;
		aux = 0;
		return;}

	if((display_getpixel(g->posx, g->posy-1) != BLACK)){
		for(int i = 0; i < QTDLin; i++)
			for(int j = 0; j < QTDI; j++){
				if((g->posx >= enemies[i][j].posx) && (g->posx < (enemies[i][j].posx + enemies[i][j].spriteszx)) && (g->posy-1 >= enemies[i][j].posy) && (g->posy-1 < (enemies[i][j].posy + enemies[i][j].spriteszy))){
					if(enemies[i][j].alive){
						pontuacao += enemies[i][j].pontos;
						enemies[i][j].alive = 0;
						qntInimigos--;
						draw_object(g, 0, 0);
						display_print(buf, 60, 0, 1, BLACK);
						sprintf(buf, "%d", pontuacao);
						display_print(buf, 60, 0, 1, GREEN);
						aux = 0;}
					return;}}
		draw_sprite(g->posx, g->posy-1, 0, 1, 1, 0);
		draw_object(g, 0, 0);
		g->posx = player.posx + 6;
		g->posy = player.posy - 4;
		aux = 0;
	}
}

int verfica_col(int rand){
	for(int i = 0; i < 3; i++)
		if(rand == posicao[i])
			return -1;
	for(int i = QTDLin-1; i > 0; i--)
		if(enemies[i][rand].alive)
			return i;
	return -1;}

void define_new_pos(struct object_s *g, int p){
	int rand = random() % QTDI;
	pos[p] = verfica_col(rand);
	posicao[p] = rand;
	if(pos[p] == -1) return;
	g->posx = enemies[pos[p]][rand].posx + enemies[pos[p]][rand].spriteszx/2;
	g->posy = enemies[pos[p]][rand].posy + enemies[pos[p]][rand].spriteszy;
}

void detect_colision_enemy(struct object_s *g, int p){

	if(pos[p] == -1){
		define_new_pos(g, p);
		return;}

	if(g->posy >= (LIMITY-7)){
		draw_object(g, 0, 0);
		define_new_pos(g, p);
		return;}

	if((display_getpixel(g->posx, g->posy+4) != BLACK)){
		if((g->posx >= player.posx) && (g->posx < (player.posx + player.spriteszx)) && ((g->posy+4) >= player.posy) && ((g->posy+4) < (player.posy + player.spriteszy))){
			if(vidas > 0){
				vidas--;
				draw_object(g, 0, 0);
				draw_sprite(266 + vidas*11, 1, vid1[0], 9, 8, 0);
				//display_print("ACERTEI", 220, 1, 1, GREEN + vidas);
				define_new_pos(g, p);}
			else {
				player.alive = 0;
				//display_print("ACERTEI", 220, 1, 1, BLACK);
				//display_print("ACABOU", 220, 1, 1, GREEN);
				} //terminar o jogo
			return;}
	draw_sprite(g->posx-1, g->posy+4, 0, 3, 1, 0);
	draw_object(g, 0, 0);
	define_new_pos(g, p);}
}



/* display and input */
void init_display()
{
	display_background(BLACK);
}

enum {
	KEY_CENTER	= 0x01,
	KEY_UP		= 0x02,
	KEY_LEFT	= 0x04,
	KEY_RIGHT	= 0x08,
	KEY_DOWN	= 0x10
};

void init_input()
{
	GPIOB->DDR &= ~(MASK_P8 | MASK_P9 | MASK_P10 | MASK_P11 | MASK_P12);
}

int get_input()
{
	int keys = 0;
	
	if (GPIOB->IN & MASK_P8)	keys |= KEY_CENTER;
	if (GPIOB->IN & MASK_P9)	keys |= KEY_UP;
	if (GPIOB->IN & MASK_P10)	keys |= KEY_LEFT;
	if (GPIOB->IN & MASK_P11)	keys |= KEY_RIGHT;
	if (GPIOB->IN & MASK_P12)	keys |= KEY_DOWN;
		
	return keys;
}

void move_player(struct object_s *pl){
	int keys = get_input();
	if((keys & KEY_LEFT) == KEY_LEFT) pl->dx = -1; 
	else if ((keys & KEY_RIGHT) == KEY_RIGHT) pl->dx = 1;
	else pl->dx = 0;
	if(((pl->dx == -1) && (pl->posx >= 20)) || ((pl->dx == 1) && pl->posx < (LIMITX-40)))
		move_object(pl);

	draw_object(pl, 1, -1);
}

int dot_demo()
{
	uint16_t k, l;
	int i = 0;
	
	for (;;) {
		k = random() % VGA_WIDTH;
		l = random() % VGA_HEIGHT;

		display_pixel(k, l, 15);
		
		if (i > 450)
			break;
			
		i++;
		
	}
		
	return i;
}

void rank(){
	sprintf(buf, "%05d", pontuacao);
	//display_print("|", 0, 0, 1, WHITE);
	//display_print("|", 280, 0, 1, WHITE);

	display_print("HIGH SCORES", 55, 10, 2, BLUE);
	display_print("RANK", 40, 50, 1, YELLOW);
	display_print("SCORE", 125, 50, 1, YELLOW);
	display_print("NAME", 210, 50, 1, YELLOW);

	delay_ms(300);
	display_print("1ST", 40, 65, 1, CYAN);
	display_print(buf, 125, 65, 1, CYAN);
	display_print("SJF", 210, 65, 1, CYAN);

	sprintf(buf, "%05d", (int)(pontuacao * 0.8));
	delay_ms(300);
	display_print("2ND", 40, 80, 1, LCYAN);
	display_print(buf, 125, 80, 1, LCYAN);
	display_print("CSD", 210, 80, 1, LCYAN);

	sprintf(buf, "%05d", (int)(pontuacao * 0.6));
	delay_ms(300);
	display_print("3RD", 40, 95, 1, LBLUE);
	display_print(buf, 125, 95, 1, LBLUE);
	display_print("GPB", 210, 95, 1, LBLUE);

	sprintf(buf, "%05d", (int)(pontuacao * 0.4));
	delay_ms(300);
	display_print("4TH", 40, 110, 1, MAGENTA);
	display_print(buf, 125, 110, 1, MAGENTA);
	display_print("ALM", 210, 110, 1, MAGENTA);

	sprintf(buf, "%05d", (int)(pontuacao * 0.2));
	delay_ms(300);
	display_print("5TH", 40, 125, 1, LMAGENTA);
	display_print(buf, 125, 125, 1, LMAGENTA);
	display_print("LFM", 210, 125, 1, LMAGENTA);

	delay_ms(300);
	display_print("6TH", 40, 140, 1, LRED);
	display_print("00000", 125, 140, 1, LRED);
	display_print("ABC", 210, 140, 1, LRED);

	delay_ms(300);
	display_print("Play Again?", 110, 180, 1, WHITE);
	delay_ms(150);
	display_print("YES", 120, 195, 1, WHITE);
	delay_ms(150);
	display_print("NO", 160, 195, 1, WHITE);

}
/* main game loop */
int main(void)
{
	win = 0; 
	vidas = 3; 
	pontuacao = 0; 
	qntInimigos = QTDI*(QTDLin-1) + 1;

	srand(100);
	init_display();
	int flag = 0; 
	int stars = 0;
	while(flag == 0){
		//rank();
		display_print("PRESS PLAY", 80, 110, 2, WHITE);
		int keys = get_input();
		if(stars == 0){
			dot_demo();
			stars = 1;
		}
		if((keys & KEY_CENTER) == KEY_CENTER){
			flag = 1;
			display_background(BLACK);
			display_print("PRESS PLAY", 80, 110, 2, BLACK);
		}
	}

	//display_print("|", 0, 0, 1, WHITE); // Limites de tela
	display_print("SCORE:", 10, 1, 1, WHITE);

	display_print("LIVES:", 220, 1, 1, WHITE);

	//display_print("|", 280, 0, 1, WHITE); // Limites de tela
	display_hline(20, 216, 280, WHITE);
	init_input();

	init_object(&gun, gun_skin[0], 0, 0, 1, 4, 156, 204, 0, -1, 0, 1, 0);
	init_object(&player, nave1[0], nave2[0], 0, 15, 9, 150, 206, -1, 0, 10, 0, 0);
	draw_object(&player, 1, -1);

	for(int i = 0; i < 3; i++){ 
		posicao[i] = (random() % QTDI);
		init_object(&gun_enemies[i], attack_skin[0], 0, 0, 1, 4, 36 + 18*posicao[i], 112, 0, 1, 0, 4, 0);}

	for(int i = 0; i < QTDLin; i++){ //inicia os inimigos
		for(int j = 0; j < QTDI; j++){
			if(i < 1){
				init_object(&enemies[i][j], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			  if(j < 1){
				init_object(&enemies[i][j], mystery1[0], mystery2[0], 0, 16, 7, 30, 30, -1, 0, 15, 0, 50);
			  } 
			} else if(i < 2){
				init_object(&enemies[i][j], monster2a[0], monster2b[0], 0, 8, 9, 28 + j*18, 31 + i*15, -1, 0, 90, 0, 30);
			} else if(i < 4){
				init_object(&enemies[i][j], monster1a[0], monster1b[0], 0, 11, 8, 25 + j*18, 30 + i*15, -1, 0, 90, 0, 20);
			} else if(i < 6){
				init_object(&enemies[i][j], monster3a[0], monster3b[0], 0, 12, 8, 25 + j*18, 30 + i*15, -1, 0, 90, 0, 10);
			}
			draw_object(&enemies[i][j], 1, -1);
		}
	}

	for(int i = 0; i < 4; i++) //inicia os escudos
		draw_sprite(50 + i*60, 160, escudo[0], 22, 16, -1);

	for(int i = 0; i < 3; i++) // inicia vidas
		draw_sprite(266 + i*11, 1, vid1[0], 9, 8, -1);

	//draw_sprite(100, 1, colors[0], 16, 1, -1); //Paleta de cores

	while (1) {
		int shoot = get_input();
		int aim; 

		if((shoot & KEY_UP) == KEY_UP){ //Se aperta o botão, atira
			aux = 1;
			aim = 1; 
		}

		detect_colision(&gun);
		if(aux == 1){
			move_object(&gun);
		} else if (aim == 1){
			gun.posx = player.posx + 6;
			gun.posy = player.posy - 4;
		}

	     if(pontuacao > 0){
		for(int i = 0; i < 3; i++){ //Detecta colisão dos ataques dos invasores
			detect_colision_enemy(&gun_enemies[i], i); 
			if(pos[i] == -1){
				draw_object(&gun_enemies[i], 0, 0);
				gun_enemies[i].posx = 0;
				gun_enemies[i].posy = 36;
			}
			else move_object(&gun_enemies[i]);}
		}

		for(int i = 0; i < QTDLin; i++) //Movimento dos invasores
			for(int j = 0; j < QTDI; j++)
				move_object(&enemies[i][j]);	
		move_player(&player);

		if(qntInimigos == 0){ //Se Vitória
			win = 1;
			replay = 0; 
			delay_ms(500); 
			break;
		}

		if(vidas == 0){ //Se Derrota
		win = 0;
		replay = 0; 
		draw_sprite(player.posx, player.posy, 0, 16, 7, 0); 
		draw_sprite(player.posx, player.posy, explosao_player[0], 15, 8, -1); 
		delay_ms(1000);
		break;
		}
		delay_ms(2);
	}

		if(win == 0){
			display_background(BLACK);
			display_print("GAME OVER", 80, 110, 2, RED);
			delay_ms(1500);
			display_background(BLACK);
			rank();
		} else if(win == 1){
			display_background(BLACK);
			display_print("YOU WIN!", 80, 110, 2, WHITE);
			delay_ms(1500);
			display_background(BLACK);
			rank();
		}

		while(replay == 0){
		int keys = get_input();
		if((keys & KEY_CENTER) == KEY_CENTER){
			display_print("YES", 120, 195, 1, GREEN);
			replay = 1;
			delay_ms(500);
			display_background(BLACK);
			main();
		}

		if((keys & KEY_DOWN) == KEY_DOWN){
			display_print("NO", 160, 195, 1, GREEN);
			replay = 1;
			delay_ms(500);
			display_background(BLACK);
			return 0;
		}
	}
	return 0;
}
