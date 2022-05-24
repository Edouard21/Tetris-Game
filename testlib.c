#include "primlib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 30 
#define BOARD_POSITION 320 
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20 
#define PIECE_BLOCKS 5 
#define PIECE_NUMBER 3
#define NUMBER_ROTATION 4


char pieces [7 /*kind */ ][4 /* rotation */ ][PIECE_BLOCKS][PIECE_BLOCKS] =
{
	
	
// Square
{
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
}
},

// I
{
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 1, 2, 1, 1},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{1, 1, 2, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 1, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
}
}
,
// L
{
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 1, 2, 1, 0},
{0, 1, 0, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 1, 1, 0, 0},
{0, 0, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 1, 0},
{0, 1, 2, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
}
},
// L mirrored
{
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 0, 0},
{0, 1, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 1, 0, 0, 0},
{0, 1, 2, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 1, 2, 1, 0},
{0, 0, 0, 1, 0},
{0, 0, 0, 0, 0}
}
},
// N
{
{
{0, 0, 0, 0, 0},
{0, 0, 0, 1, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 1, 2, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 1, 2, 0, 0},
{0, 1, 0, 0, 0},
{0, 0, 0, 0, 0}
},

{
{0, 0, 0, 0, 0},
{0, 1, 1, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
}
},
// N mirrored
{
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 0, 1, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 2, 1, 0},
{0, 1, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 1, 0, 0, 0},
{0, 1, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 1, 0},
{0, 1, 2, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
}
},
// T
{
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 2, 1, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 1, 2, 1, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 1, 2, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0}
},
{
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 1, 2, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
}
}
};

int piecesInitialPosition [7 /*kind */ ][4 /* rotation */ ][1] =
{
/* Square */
{
{-3},
{-3},
{-3},
{-3}
},
/* I */
{
{-3},
{-2},
{-3},
{-1}
},
/* L */
{
{-2},
{-2},
{-2},
{-2}
},
/* L mirrored */
{
{-2},
{-3},
{-2},
{-3}
},
/* N */
{
{-2},
{-3},
{-3},
{-2}
},
/* N mirrored */
{
{-3},
{-3},
{-3},
{-2}
},
/* T */
{
{-3},
{-3},
{-3},
{-2}
},
};

typedef enum { false, true } bool;

int board[BOARD_WIDTH][BOARD_HEIGHT];

void initBoard();

void drawScene(int posX, int posY, int piece, int rotation, int nextPosX, int nextPosY, int nextPiece, int nextRotation);

void drawPiece(int pX, int pY, int piece, int rotation);

void drawBoard();

void createNewPiece(int* nextPiece, int* nextRotation, int* posX, int* posY, int* piece, int* rotation);

bool isPossibleMovement(int pX, int pY, int piece, int rotation);

enum { POS_FREE, POS_FILLED };

int getYInitialPosition(int piece, int rotation);

int getXPosInPixels (int pos);

int getYPosInPixels (int pos);

void storePiece(int pX, int pY, int piece, int rotation);

void deletePossibleLines();

bool isGameOver();

int getBlockType(int piece, int rotation, int pX, int pY);

bool isFreeBlock(int pX, int pY);

void movingPieces(int nextPiece, int nextRotation, int posX, int posY, int piece, int rotation, int nextPosX, int nextPosY);

int main(int argc, char* argv[]) {

	if (gfx_init()) {
		exit(3);
	}
	
	srand(time(0));

	int piece = rand() % PIECE_NUMBER;
	int rotation = rand() % NUMBER_ROTATION;
	int posX = BOARD_WIDTH/2 - 2;
	int posY = getYInitialPosition(piece,rotation);

	
	int nextPiece = rand() % PIECE_NUMBER;
	int nextRotation = rand() % NUMBER_ROTATION;
	int nextPosX = BOARD_WIDTH + 5;
	int nextPosY = 5;
	
	initBoard();
	
	createNewPiece(&nextPiece, &nextRotation, &posX, &posY, &piece, &rotation);
	
	
	movingPieces(nextPiece, nextRotation, posX,posY, piece, rotation, nextPosX, nextPosY);

	return 0;
}


void movingPieces(int nextPiece, int nextRotation, int posX, int posY, int piece, int rotation, int nextPosX, int nextPosY){
						
		while (gfx_pollkey() != SDLK_ESCAPE) {	

		drawScene(posX, posY, piece, rotation, nextPosX, nextPosY, nextPiece,
				  nextRotation);
		gfx_updateScreen();
		
		for(int k=0;k< 20;k++){
			gfx_pollkey();
		}

		for (int i = 0; i < 20; i++) {
			int key = gfx_pollkey();

	
			if (key == SDLK_RIGHT && 
				isPossibleMovement(posX +1, posY, piece, rotation)) {
				posX++;
			}

			else if (key == SDLK_LEFT &&
					 isPossibleMovement(posX - 1, posY, piece, rotation)) {
				posX = posX - 1;
			}

			else if (key == SDLK_DOWN) {

				
				while (isPossibleMovement(posX, posY, piece, rotation)) {
					posY++;
				}

				storePiece(posX, posY - 1, piece, rotation);
				
				deletePossibleLines();

				if (isGameOver()) {
					gfx_getkey();
					exit(0);
				}

				createNewPiece(&nextPiece, &nextRotation, &posX, &posY, &piece,
							   &rotation);
			}

			else if (key == SDLK_SPACE && isPossibleMovement(posX, posY, piece,
														 (rotation + 1) % 4)) {

				rotation = (rotation + 1) % 4;
			}

			SDL_Delay(10);
		}

		// Vertical movement

		if (isPossibleMovement(posX,posY+1,piece,rotation) == true) {
			posY++;
		} else {
			storePiece(posX, posY, piece, rotation);
			
			deletePossibleLines();
			
			
			if (isGameOver()) {
				SDL_Delay(1000);
				exit(0);
			}

			createNewPiece(&nextPiece, &nextRotation, &posX, &posY, &piece,
						   &rotation);
		}
		
		SDL_Delay(10);

		
	}
	
}



void initBoard() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			board[i][j] = POS_FREE;
		}
	}
}



void storePiece(int pX, int pY, int piece, int rotation) {
		
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++){
		
		
		
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++){
			
			
			// Store only the blocks of the piece that are not holes
			
			if (getBlockType (piece, rotation, j2, i2) != 0 && i1>= 0 && j1>=0){
			
				board[i1][j1] = POS_FILLED;
			
			}
		}
	}

}

bool isGameOver() {
	
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (board[i][0] == POS_FILLED) {
			
			gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
			gfx_textout(500, 100,"YOU LOST THE GAME !", RED);
			gfx_updateScreen();
			return true;
		}
	}
	return false;
}

void deleteLine(int pY) {
	
	// Moves all the upper lines one row down
	for (int j = pY; j > 0; j--) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			board[i][j] = board[i][j - 1];
		}
	}
	
	
}

void deletePossibleLines() {
	
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		int count =0;
		for(int i=0;i < BOARD_WIDTH;i++) {
			if (board[i][j] == POS_FILLED) {
				count++;
			} 
		}
		 
		if (count == BOARD_WIDTH) {
			deleteLine(j);
		}
	}
}

bool isFreeBlock(int pX, int pY) {

	if (board[pX][pY] == POS_FREE) {
		return true;
	} else {
		return false;
	}
}


int getXPosInPixels(int pos) {
	return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) +
			(pos * BLOCK_SIZE));
}

int getYPosInPixels(int pos) {
	return ((gfx_screenHeight() - (BLOCK_SIZE * BOARD_HEIGHT)) +
			(pos * BLOCK_SIZE));
}

int getYInitialPosition (int piece, int rotation){
	
	return piecesInitialPosition [piece][rotation][0];
}

bool isPossibleMovement(int pX, int pY, int piece, int rotation) {
	
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++){
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++){
			// Check if the piece is outside 
			if ( i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1){
				if (getBlockType (piece, rotation, j2, i2) != 0){
					
					return false;
				}
			}

				// Check collision with other blocks
					if ((getBlockType (piece, rotation, j2, i2) != 0 && i1>= 0 && j1 >= 0) && (!isFreeBlock (i1, j1)) ){
							return false;
					}
				}
		}
	

	// No collision
	return true;

}

	

int getBlockType(int piece, int rotation, int pX, int pY) {

	return pieces[piece][rotation][pX][pY];
}



void createNewPiece(int* nextPiece, int* nextRotation, int* posX, int* posY, int* piece, int* rotation) {

	
	*piece = *nextPiece;
	*rotation = *nextRotation;
	*posX = BOARD_WIDTH/2 - 2;
	*posY = getYInitialPosition(*piece,*rotation);
	 printf("%d",*posY);
	
	*nextPiece = rand() % PIECE_NUMBER;
	*nextRotation = rand() % NUMBER_ROTATION;
}

void drawPiece(int pX, int pY, int piece, int rotation) {

	enum color blockClor;

	// Position in pixel to draw
	
	int pixelsX = getXPosInPixels(pX);
	int pixelsY = getYPosInPixels(pY);

	// draw the filled blocks
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			
			// Get the type of the block and draw it with the correct color
			switch (getBlockType(piece, rotation, j, i)) {
			case 1:
				blockClor = MAGENTA;
				break;

			case 2:
				blockClor = YELLOW;
				break; 
			}

			if (getBlockType(piece, rotation, j, i) != 0) {

				gfx_filledRect(
					pixelsX + i * BLOCK_SIZE, pixelsY + j * BLOCK_SIZE,
					(pixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(pixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, blockClor);
			}
		}
	}
}

void drawBoard() {

	// limits of the board in pixels
	int X1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) -1;
	int X2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2)) ;

	int Y = gfx_screenHeight() - (BLOCK_SIZE * BOARD_HEIGHT);

	// Rectangles that delimits the board
	gfx_filledRect(X1 - BOARD_LINE_WIDTH, Y, X1, gfx_screenHeight() - 1, BLUE);

	gfx_filledRect(X2, Y, X2 + BOARD_LINE_WIDTH, gfx_screenHeight() - 1, BLUE);

	// Drawing the blocks that are already stored in the board
	X1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			// Check if the block is filled, if so, draw it
			if (board[i][j] != POS_FREE) {
				
						 gfx_filledRect(X1 + i * BLOCK_SIZE, Y + j * BLOCK_SIZE,
						 (X1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
						 (Y + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
			} else {
				gfx_rect(X1 + i * BLOCK_SIZE, Y + j * BLOCK_SIZE,
						 (X1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
						 (Y + j * BLOCK_SIZE) + BLOCK_SIZE - 1, BLUE);
			}
		}
	}
	gfx_textout(500, 150, "Score : %d" , BLUE);
}

void drawScene(int posX, int posY, int piece, int rotation, int nextPosX,
			   int nextPosY, int nextPiece, int nextRotation) {
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	drawBoard(); 
	drawPiece(posX, posY, piece, rotation); 
	drawPiece(nextPosX, nextPosY, nextPiece,
			  nextRotation); 
}
