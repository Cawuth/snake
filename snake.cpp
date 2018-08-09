/*
Testo

Data

*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;
/*
FUNZIONI SNAKE
- input dei comandi da utente X
- struttura della cella di una matrice (bool serpentePresente, bool primo, bool ultimo, bool muro)
- spostamento
- morte
	- serpente contro se stesso
	- serpente contro muro
- comparsa mela
- mangiare mela
	- scomparsa mela
	- allungamento
*/

const int W=20;
const int H=20;

struct Cord{
	int riga;
	int colonna;
};

class Cell{
	public:
		Cord cord;
		bool snake_here;
		bool food_here;
		bool wall;
		int ger;
		Cell();
		void visualizzaCella();
		void riepiCellaSerpente();
};
Cell::Cell(){
	this->snake_here=false;
	this->food_here=false;
	this->wall=false;
	this->ger=0;
}
void Cell::visualizzaCella(){
	if(snake_here){
		cout<<"X";
	}else if(wall){
		cout<<"|";
	}else if(food_here){
		cout<<"A";
	}else{
		cout<<" ";
	}
}
void Cell::riepiCellaSerpente(){
	this->snake_here=true;
}
class Map{
	public:
		int w;
		int h;
		Cell** matrix;
		Map(int w, int h);
		void visualizzaMappa();
		void setMuri();
};
Map::Map(int w, int h){
	int r,c;
	this->w=w;
	this->h=h;
	this->matrix=new Cell*[w];
	for (int i = 0; i < w; i++) {
		this->matrix[i]=new Cell[h];
	}
	for(r=0;r<h;r++){
		for(c=0;c<w;c++){
			this->matrix[r][c].cord.riga=r;
			this->matrix[r][c].cord.colonna=c;
		}
	}
	
	this->setMuri();
}

void Map::visualizzaMappa(){
	int r,c;
	for(r=0;r<this->h;r++){
		for(c=0;c<this->w;c++){
			matrix[r][c].visualizzaCella();
		}
		cout<<endl;
	}
}

void Map::setMuri(){
	int r,c;
	for(r=0,c=0;c<w;c++){
		this->matrix[r][c].wall=true;
	}
	for(r=0,c=0;r<h;r++){
		this->matrix[r][c].wall=true;
	}
	for(r=h-1,c=0;c<w;c++){
		this->matrix[r][c].wall=true;
	}
	for(r=0,c=w-1;r<h;r++){
		this->matrix[r][c].wall=true;
	}
}

class Snake{
	public:
		Map* map;
		int length;
		Snake(Map* newMap);
		Cell* trovaUltimo();
		Cell* trovaPrimo();
		bool isDeadMuro();
		bool isDeadCorpo;
		bool isDead();
		bool testaSuMela();
		void move(char tasto, bool melaMangiata);
		void mangiaMela();
};
Snake::Snake(Map* newMap){
	this->map=newMap;
	this->length=6;
	map->matrix[1][1].riepiCellaSerpente();
	map->matrix[1][1].ger=6;
	map->matrix[1][2].riepiCellaSerpente();
	map->matrix[1][2].ger=5;
	map->matrix[1][3].riepiCellaSerpente();
	map->matrix[1][3].ger=4;
	
	map->matrix[1][4].riepiCellaSerpente();
	map->matrix[1][4].ger=3;
	map->matrix[1][5].riepiCellaSerpente();
	map->matrix[1][5].ger=2;
	map->matrix[1][6].riepiCellaSerpente();
	map->matrix[1][6].ger=1;
}

Cell* Snake::trovaUltimo(){
	int r,c;
	for(r=0;r<this->map->h;r++){
		for(c=0;c<this->map->w;c++){
			if(this->map->matrix[r][c].ger==this->length){
				return &this->map->matrix[r][c];
			}
		}
	} 
}

Cell* Snake::trovaPrimo(){
	int r,c;
	for(r=0;r<this->map->h;r++){
		for(c=0;c<this->map->w;c++){
			if(this->map->matrix[r][c].ger==1){
				return &this->map->matrix[r][c];
			}
		}
	} 
}

void Snake::move(char tasto, bool melaMangiata){
	int r,c;
	Cell* ultimo=trovaUltimo();
	Cell* primo=trovaPrimo();
	
	bool movimentoEseguito=false;
	if(tasto=='w'&&this->map->matrix[primo->cord.riga-1][primo->cord.colonna].ger!=2){
		movimentoEseguito=true;
		if(this->map->matrix[primo->cord.riga-1][primo->cord.colonna].ger>2){
			isDeadCorpo=true;
		} else {
			this->map->matrix[primo->cord.riga-1][primo->cord.colonna].snake_here=true;
		}
	}else if(tasto=='a'&&this->map->matrix[primo->cord.riga][primo->cord.colonna-1].ger!=2){
		movimentoEseguito=true;
		if(this->map->matrix[primo->cord.riga][primo->cord.colonna-1].ger>2){
			isDeadCorpo=true;
		} else {
			this->map->matrix[primo->cord.riga][primo->cord.colonna-1].snake_here=true;
		}
	}else if(tasto=='s'&&this->map->matrix[primo->cord.riga+1][primo->cord.colonna].ger!=2){
		movimentoEseguito=true;
		if(this->map->matrix[primo->cord.riga+1][primo->cord.colonna].ger>2){
			isDeadCorpo=true;
		} else {
			this->map->matrix[primo->cord.riga+1][primo->cord.colonna].snake_here=true;
		}
	}else if(tasto=='d'&&this->map->matrix[primo->cord.riga][primo->cord.colonna+1].ger!=2){
		movimentoEseguito=true;
		if(this->map->matrix[primo->cord.riga][primo->cord.colonna+1].ger>2){
			isDeadCorpo=true;
		}else {
			this->map->matrix[primo->cord.riga][primo->cord.colonna+1].snake_here=true;
		}
	}
	
	if(!melaMangiata&&movimentoEseguito){
		ultimo->ger=0;
		ultimo->snake_here=false;
	}
	
	if(movimentoEseguito){
		for(r=0;r<this->map->h;r++){
			for(c=0;c<this->map->w;c++){
				if(this->map->matrix[r][c].snake_here){
					this->map->matrix[r][c].ger++;
				}
			}
	}
	}
	
}

bool Snake::isDeadMuro(){
	int r,c;
	for(r=0;r<this->map->h;r++) {
		for(c=0;c<this->map->w;c++){
			if(this->map->matrix[r][c].snake_here&&this->map->matrix[r][c].wall){
				return true;
			}
		}
	}
	return false;
}

bool Snake::isDead(){
	return isDeadMuro()||isDeadCorpo;
}

bool Snake::testaSuMela(){
	return this->trovaPrimo()->food_here;
}

void Snake::mangiaMela(){
	this->trovaPrimo()->food_here=false;
	this->length++;
}

class FoodManager{
	public:
		Map* map;
		Snake* snake;
		FoodManager(Map* newMap, Snake* newSnake);
		void spawnMela();
};

FoodManager::FoodManager(Map* newMap, Snake* newSnake){
	this->map=newMap;
	this->snake=newSnake;
}

void FoodManager::spawnMela(){
	int random=rand()%((this->map->h * this->map->w)-(this->map->w+this->map->w+(this->map->h-2)+(this->map->h-2)) - this->snake->length)+1;
	int i;
	Cord cordMela;
	for(i=0,cordMela.riga=1,cordMela.colonna=1;i<random;i++){
		if(this->map->matrix[cordMela.riga][cordMela.colonna].snake_here){
			i--;
		}
		if(cordMela.colonna==this->map->w-2){
			cordMela.colonna=0;
			cordMela.riga++;
		}else{
			cordMela.colonna++;
		}
	}
	this->map->matrix[cordMela.riga][cordMela.colonna].food_here=true;
}

class Game{
	public:
		Map* map;
		Snake* player;
		FoodManager* foodManager;
		Game();
		void inizioGioco();
};
Game::Game(){
	map=new Map(20,20);
	player=new Snake(map);
	foodManager=new FoodManager(map,player);
}
void Game::inizioGioco(){
	char tasto;
	bool melaMangiata;
	this->foodManager->spawnMela();
	while(!this->player->isDead()){
		melaMangiata=false;
		system("cls");
		
		if(this->player->testaSuMela()){
			this->player->mangiaMela();
			melaMangiata=true;
			this->foodManager->spawnMela();
		}
		
		this->map->visualizzaMappa();
		tasto=_getch();
		this->player->move(tasto,melaMangiata);
	}
}


int main(){
	srand(time(NULL));
	Game game;
	game.inizioGioco();
	return 0;
}

