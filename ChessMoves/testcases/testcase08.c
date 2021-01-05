#include <stdlib.h>
#include <string.h>
#include "ChessMoves.h"


// This is a hacky-horrible way of hard-coding a test case.
Game *testcase08(void)
{
	int i;
	char *moves[10];
	Game *g = NULL;

	i = 0;
	moves[i++] = "1. h3 a6";
	moves[i++] = "2. h4 b6";
	moves[i++] = "3. a3 c6";
	moves[i++] = "4. a4 d6";
	moves[i++] = "5. b3 e6";
	moves[i++] = "6. Rh3 f6";
	moves[i++] = "7. Ra3 g6";
	moves[i++] = "8. Rc3 h6";

	g = malloc(sizeof(Game));
	g->numMoves = i;

	g->moves = malloc(sizeof(char *) * g->numMoves);

	for (i = 0; i < g->numMoves; i++)
	{
		g->moves[i] = malloc(sizeof(char) * (strlen(moves[i]) + 1));
		strcpy(g->moves[i], moves[i]);
	}

	return g;
}

Game *destroyGame(Game *g)
{
	int i;

	if (g == NULL)
		return NULL;

	for (i = 0; i < g->numMoves; i++)
		free(g->moves[i]);

	free(g->moves);
	free(g);

	return NULL;
}

int main(void)
{
	// Create a Game struct for this test case.
	Game *g = testcase08();

	// Play the game.
	char **finalBoardState = playTheGame(g);

	// Destroy the chess board returned by playTheGame().
	finalBoardState = destroyChessBoard(finalBoardState);

	// Destroy the Game struct with all the chess moves.
	g = destroyGame(g);

	return 0;
}
