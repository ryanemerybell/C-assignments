//Ryan Bell - 9/25/16
//PID: 3605342
//NID: ry049745
//COP3502 Sean Szumlanski
//Chess Moves Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ChessMoves.h"

//Helper Functions!

//Checks if a Rook, Bishop, or Queen can move to a spot that they path to
//AKA checks to see if that piece is not blocked and all squares between
//The from location and to location are ' ', returns 1 if possible, 0 if not
int isAble(char **board, int fromRow, int fromCol, int toRow, int toCol)
{
    int i, a = toRow-fromRow, b = fromCol-toCol, c = toCol-fromCol;

    //How are the spaces lined up with each other?
    //Horizontally:
    if(fromRow == toRow)
    {
        //Going left
        if(fromCol>toCol)
        {
            for(i=(toCol+1);i<fromCol;i++)
            {
                if(board[toRow][i]!=' ')
                    return 0;
            }
        }
        //Going right
        if(fromCol<toCol)
        {
            for(i=(fromCol+1);i<toCol;i++)
            {
                if(board[toRow][i]!=' ')
                    return 0;
            }
        }
    }
    //Vertically:
    if(fromCol == toCol)
    {
        //Going up
        if(fromRow>toRow)
        {
            for(i=(toRow+1);i<fromRow;i++)
            {
                if(board[i][toCol]!=' ')
                    return 0;
            }
        }
        //Going down
        if(fromRow<toRow)
        {
            for(i=(fromRow+1);i<toRow;i++)
            {
                if(board[i][toCol]!=' ')
                    return 0;
            }
        }
    }
    //Diagonally positive slope:
    if(a == b)
    {
        //Going up-right
        if(toCol>fromCol)
        {
            for(i=1;i<c;i++)
            {
                if(board[fromRow-i][fromCol+i]!=' ')
                    return 0;
            }
        }
        //Going down-left
        if(toCol<fromCol)
        {
             for(i=1;i<b;i++)
            {
                if(board[fromRow+1][fromCol-1]!=' ')
                    return 0;
            }
        }
    }
    //Diagonally Negative slope:
    if(a == c)
    {
        //Going down-right
        if(toCol>fromCol)
        {
            for(i=1;i<c;i++)
            {
                if(board[fromRow+i][fromCol+i]!=' ')
                    return 0;
            }
        }
        //Going up-left
        if(toCol<fromCol)
        {
             for(i=1;i<b;i++)
            {
                if(board[fromRow-1][fromCol-1]!=' ')
                    return 0;
            }
        }
    }

    //Assumed possible unless proven otherwise
    return 1;
}

//Returns 1 if argument is a column character or 'x' for taking a piece
//Returns 0 otherwise (meaning an integer or ' ')
int isLetter(char c)
{
    if (c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f'||c=='g'||c=='h'||c=='x')
        return 1;
    return 0;
}

//Turns an column index into a column letter
char colConverter(int index)
{
    if(index==0)
        return 'a';
    if(index==1)
        return 'b';
    if(index==2)
        return 'c';
    if(index==3)
        return 'd';
    if(index==4)
        return 'e';
    if(index==5)
        return 'f';
    if(index==6)
        return 'g';
    if(index==7)
        return 'h';
    //If the index is wrong
    return 'x';
}

//Checks if a variable is between two values
//Returns 1 if so, 0 if not
int isBetween(int i, int lo, int hi)
{
    if(i>=lo&&i<=hi)
        return 1;
    return 0;
}

//----------------------------------------------------------------------------------------------

//CS1 Assignment functions!

char **createChessBoard(void)
{
    //Variable Declaration:
    //i and j are for loop counters, board is
    //the 2D char array initialized to NULL
    int i, j;
    char** board = NULL;

    //malloc call to give board an array of char
    //arrays of length 9-1 = 8 (b/c of '\0')
    board = malloc(sizeof(char *)*9);

    //For loop to malloc space for each char array
    for(i=0;i<=7;i++)
        board[i] = malloc(sizeof(char)*9);

    //NOTE TO SELF: for board[i][j],
    //i is the row number (rank) and
    //j is the column number (file)

    //NOTE TO SELF:
    //i (0-7) corresponds to rank (row) 8-i (8-1)
    //j (0-7) corresponds to file (column) "Lowercase letter of the alphabet + 1" (a-h)

    //These two for loops populate the board's pawns
    //This is Black's pawns, uppercase
    for(i=0;i<=7;i++)
        board[1][i] = 'P';

    //This is White's pawns, lowercase
    for(i=0;i<=7;i++)
        board[6][i] = 'p';

    //Rooks
    board[0][0]=board[0][7]='R';
    board[7][0]=board[7][7]='r';

    //Knights
    board[0][1]=board[0][6]='N';
    board[7][1]=board[7][6]='n';

    //Bishops
    board[0][2]=board[0][5]='B';
    board[7][2]=board[7][5]='b';

    //Queens
    board[0][3]='Q';
    board[7][3]='q';

    //King
    board[0][4]='K';
    board[7][4]='k';

    //Blank spaces
    for(i=2;i<=5;i++){
        for(j=0;j<=7;j++)
            board[i][j]=' ';
    }
    //Returns address of chess board
    //aka 2D array char pointer
    return board;
}

char **destroyChessBoard(char **board)
{
    int i;

    for(i=0;i<8;i++)
        free(board[i]);

    free(board);

    return NULL;
}

void printChessBoard(char **board)
{
    int i, j;

    //= Border
    for(i=0;i<=7;i++)
        printf("=");
    printf("\n");

    //Prints out entire board from left to right (inner for loop)
    //and top to bottom (outer for loop)
    for(i=0;i<=7;i++){
        for(j=0;j<=7;j++)
            printf("%c",board[i][j]);
        printf("\n");
    }

    //= Border
    for(i=0;i<=7;i++)
        printf("=");
    printf("\n");
    printf("\n");
}

char **playTheGame(Game *g)
{
    //Declare the board and the moves, along with a for loop counter
    //Initialize the board
    char **board = createChessBoard();
    Move whiteMove, blackMove;
    int i;

    //Print the original board
    printChessBoard(board);

    for(i=0;i<g->numMoves;i++)
    {
        //Read each move, make each move, print each move.
        parseNotationString(g->moves[i], &whiteMove, &blackMove);
        movePiece(board,&whiteMove);
        printChessBoard(board);
        movePiece(board,&blackMove);
        printChessBoard(board);

    }

    return board;
}

void parseNotationString(char *str, Move *whiteMove, Move *blackMove)
{
    //Throughout this function I will be subtracting 48 a lot
    //This is because a positive integer 'x' has an ascii value of
    //x+48, therefore subtracting 48 from the ascii value of, for example,
    //'4' will give me the number 4

    //Declaring a counter i that keeps track of
    //where I am in the string
    //j and k are used for a neat trick I use in this function
    int i = 0, j = 0, k = 0;

    //Duh?
    whiteMove->color = WHITE;
    blackMove->color = BLACK;

    //Assume a piece isn't captured until proven otherwise
    whiteMove->isCapture = 0;
    blackMove->isCapture = 0;

    //Assume we don't know the from location until proven otherwise
    whiteMove->from_loc.col = 'x';
    whiteMove->from_loc.row = -1;
    blackMove->from_loc.col = 'x';
    blackMove->from_loc.row = -1;

    //Parses through the string until the first space is hit
    //Then, increment i again to move on to the first index of white's move
    while(str[i]!=' ')
        i++;
    i++;

    //FIRST OFF IS WHITE'S MOVE:
    //--------------------------
    //Checks if a Piece or Pawn is being moved
    if(str[i]=='K'||str[i]=='Q'||str[i]=='R'||str[i]=='N'||str[i]=='B')
    {
        whiteMove->piece = str[i];
        //Moves on to the next character
        i++;
    }
    else
        //Don't move on to the next character b/c pawn moves omit 'P'
        whiteMove->piece = 'P';

    if(isLetter(str[i]))
    {
        //j is a dummy used in place of i so i doesn't change
        //k keeps track of how many more characters are left in white's move
        j = i;
        //This condition changes to (..!='\0') for black
        while(str[j]!=' ')
        {
            j++;
            k++;
        }
        //The intuition: if k == 2, then str[i] must be a to column letter
        //if k > 2, then str[i] is either an x or a from column letter

        //Case where a to column letter is given
        if(k==2)
        {
             whiteMove->to_loc.col = str[i];
             i++;
             //The only possible character after a to column letter is a to row number
             whiteMove->to_loc.row = str[i]-48;
             //The only possibility after a to row number is a space (for white; for black it's '\0')
             i++;
             //Last character was a space, next character will be the first character of black's move
             i++;
        }

        //Case where an 'x' or a from column letter is given
        if(k>2)
        {
            //Case where an 'x' is given
            if(str[i]=='x')
            {
               //Proves my earlier assumption wrong
               whiteMove->isCapture = 1;

               i++;
               //The only possible character after an 'x' is a to column letter
               whiteMove->to_loc.col = str[i];
               i++;
               //The only possible character after a to column number is a to row number
               whiteMove->to_loc.row = str[i]-48;
               //The only possibility after a to row number is a space (for white; for black it's '\0')
               i++;
               //Last character was a space, next character will be the first character of black's move
               i++;
            }
            //Case where a from column letter is given
            else
            {

                //Set the from column letter and move on
                whiteMove->from_loc.col = str[i];
                i++;

                //Case where a letter is given
                if(isLetter(str[i]))
                {
                    //Case where an 'x' is given
                    if(str[i]=='x')
                    {
                        //Proves my earlier assumption wrong
                        whiteMove->isCapture = 1;

                        i++;
                        //The only possible character after an 'x' is a to column letter
                        whiteMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column number is a to row number
                        whiteMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is a space (for white; for black it's '\0')
                        i++;
                        //Last character was a space, next character will be the first character of black's move
                        i++;
                    }
                    //Case where a to column letter is given
                    else
                    {
                        whiteMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column letter is a to row number
                        whiteMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is a space (for white; for black it's '\0')
                        i++;
                        //Last character was a space, next character will be the first character of black's move
                        i++;
                    }
                }

                //Case where a from row number is given
                else
                {
                    //Set the from row number and move on
                    whiteMove->from_loc.row = str[i]-48;
                    i++;

                    //Case where an 'x' is given
                    if(str[i]=='x')
                    {
                        //Proves my earlier assumption wrong
                        whiteMove->isCapture = 1;

                        i++;
                        //The only possible character after an 'x' is a to column letter
                        whiteMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column number is a to row number
                        whiteMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is a space (for white; for black it's '\0')
                        i++;
                        //Last character was a space, next character will be the first character of black's move
                        i++;
                    }
                    //Case where a to column letter is given
                    else
                    {
                        whiteMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column letter is a to row number
                        whiteMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is a space (for white; for black it's '\0')
                        i++;
                        //Last character was a space, next character will be the first character of black's move
                        i++;
                    }
                }
            }
        }
    }

    //Only possible scenario here is when the from row number is given
    else
    {
      //Set the from row number and move on
      whiteMove->from_loc.row = str[i]-48;
      i++;

      //Case where an 'x' is given
        if(str[i]=='x')
        {
        //Proves my earlier assumption wrong
            whiteMove->isCapture = 1;

            i++;
            //The only possible character after an 'x' is a to column letter
            whiteMove->to_loc.col = str[i];
            i++;
            //The only possible character after a to column number is a to row number
            whiteMove->to_loc.row = str[i]-48;
            //The only possibility after a to row number is a space (for white; for black it's '\0')
            i++;
            //Last character was a space, next character will be the first character of black's move
            i++;
        }
        //Case where a to column letter is given
        else
        {
            whiteMove->to_loc.col = str[i];
            i++;
            //The only possible character after a to column letter is a to row number
            whiteMove->to_loc.row = str[i]-48;
            //The only possibility after a to row number is a space (for white; for black it's '\0')
            i++;
            //Last character was a space, next character will be the first character of black's move
            i++;
        }

    }
    //END OF WHITE'S MOVE

    //Reset k
    k = 0;

    //NEXT UP IS BLACK'S MOVE
    //------------------------
    //Checks if a Piece or Pawn is being moved
    if(str[i]=='K'||str[i]=='Q'||str[i]=='R'||str[i]=='N'||str[i]=='B')
    {
        blackMove->piece = str[i];
        //Moves on to the next character
        i++;
    }
    else
        //Don't move on to the next character b/c pawn moves omit 'P'
        blackMove->piece = 'P';

    if(isLetter(str[i]))
    {
        //j is a dummy used in place of i so i doesn't change
        //k keeps track of how many more characters are left in black's move
        j = i;
        while(str[j]!='\0')
        {
            j++;
            k++;
        }
        //The intuition: if k == 2, then str[i] must be a to column letter
        //if k > 2, then str[i] is either an x or a from column letter
        //Case where a to column letter is given
        if(k==2)
        {
             blackMove->to_loc.col = str[i];
             i++;
             //The only possible character after a to column letter is a to row number
             blackMove->to_loc.row = str[i]-48;
             //The only possibility after a to row number is '\0'
        }

        //Case where an 'x' or a from column letter is given
        if(k>2)
        {
            //Case where an 'x' is given
            if(str[i]=='x')
            {
               //Proves my earlier assumption wrong
               blackMove->isCapture = 1;

               i++;
               //The only possible character after an 'x' is a to column letter
               blackMove->to_loc.col = str[i];
               i++;
               //The only possible character after a to column number is a to row number
               blackMove->to_loc.row = str[i]-48;
               //The only possibility after a to row number is '\0'
            }
            //Case where a from column letter is given
            else
            {

                //Set the from column letter and move on
                blackMove->from_loc.col = str[i];
                i++;

                //Case where a letter is given
                if(isLetter(str[i]))
                {
                    //Case where an 'x' is given
                    if(str[i]=='x')
                    {
                        //Proves my earlier assumption wrong
                        blackMove->isCapture = 1;

                        i++;
                        //The only possible character after an 'x' is a to column letter
                        blackMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column number is a to row number
                        blackMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is a '\0'
                    }
                    //Case where a to column letter is given
                    else
                    {
                        blackMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column letter is a to row number
                        blackMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is '\0'
                    }
                }

                //Case where a from row number is given
                else
                {
                    //Set the from row number and move on
                    blackMove->from_loc.row = str[i]-48;
                    i++;

                    //Case where an 'x' is given
                    if(str[i]=='x')
                    {
                        //Proves my earlier assumption wrong
                        blackMove->isCapture = 1;

                        i++;
                        //The only possible character after an 'x' is a to column letter
                        blackMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column number is a to row number
                        blackMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is '\0'
                    }
                    //Case where a to column letter is given
                    else
                    {
                        blackMove->to_loc.col = str[i];
                        i++;
                        //The only possible character after a to column letter is a to row number
                        blackMove->to_loc.row = str[i]-48;
                        //The only possibility after a to row number is '\0'
                    }
                }
            }
        }
    }

    //Only possible scenario here is when the from row number is given
    else
    {
      //Set the from row number and move on
      blackMove->from_loc.row = str[i]-48;
      i++;

      //Case where an 'x' is given
        if(str[i]=='x')
        {
        //Proves my earlier assumption wrong
            blackMove->isCapture = 1;

            i++;
            //The only possible character after an 'x' is a to column letter
            blackMove->to_loc.col = str[i];
            i++;
            //The only possible character after a to column number is a to row number
            blackMove->to_loc.row = str[i]-48;
            //The only possibility after a to row number is '\0'
        }
        //Case where a to column letter is given
        else
        {
            blackMove->to_loc.col = str[i];
            i++;
            //The only possible character after a to column letter is a to row number
            blackMove->to_loc.row = str[i]-48;
            //The only possibility after a to row number is '\0'
        }

    }
    //END OF BLACK'S MOVE.
    //FIN.
}

void movePiece(char **board, Move *move)
{
    //These variables track the index of the space the piece is moving to
    //-97: because the ascii value of lowercase letters then becomes their index
    //8-: turns chess notation rows into row indeces
    //Also: now since I have a findFromLoc() function, I run that first to
    //Initialize my from_loc field
    findFromLoc(board, move);
    int toCol = move->to_loc.col - 97, toRow = 8 - move->to_loc.row;
    int fromCol = move->from_loc.col - 97, fromRow = 8 - move->from_loc.row;

    //Set the space at the to location to the piece being moved
    if(move->color == WHITE)
        board[toRow][toCol] = tolower(move->piece);
    if(move->color == BLACK)
        board[toRow][toCol] = move->piece;

    //Set the space at the from location to a space: always.
    board[fromRow][fromCol] = ' ';
}

void findFromLoc(char **board, Move *move)
{
    //These variables track the index of the space the piece is moving to
    //-97: because the ascii value of lowercase letters then becomes their index
    //8-: turns chess notation rows into row indeces
    int toCol = move->to_loc.col - 97, toRow = 8 - move->to_loc.row;
    int i, j, k;

    //Why should I run this function if I already have this information?
    if(move->from_loc.row != -1 && move->from_loc.col != 'x')
       return;

        if(move->piece=='P')
        {
            //Obviously pawns move differently when a piece is taken
            if(move->isCapture == 1)
            {
                for(i=-1;i<=1;i++)
                {
                    //Omit the column the pawn is on
                    if(i!=0)
                    {
                        //Make sure that the column is on the board
                        if(isBetween(toCol+i,0,7))
                        {
                            if(move->color == WHITE && board[toRow+1][toCol+i] == 'p')
                            {
                                //Duh?
                                move->from_loc.row = 8-(toRow+1);
                                if(move->from_loc.col == 'x')
                                    move->from_loc.col = colConverter(toCol+i);
                            }
                            if(move->color == BLACK && board[toRow-1][toCol+i] == 'P')
                            {
                                //Duh?
                                move->from_loc.row = 8-(toRow-1);
                                if(move->from_loc.col == 'x')
                                    move->from_loc.col = colConverter(toCol+i);
                            }
                        }
                    }
                }
            }
            if(move->isCapture == 0)
            {
                //Duh?
                move->from_loc.col = colConverter(toCol);
                if(move->color == WHITE)
                {
                    if(board[toRow+1][toCol] == 'p')
                        move->from_loc.row = 8-(toRow+1);
                    else
                        move->from_loc.row = 8-(toRow+2);
                }

                if(move->color == BLACK)
                {
                    if(board[toRow-1][toCol] == 'P')
                        move->from_loc.row = 8-(toRow-1);
                    else
                        move->from_loc.row = 8-(toRow-2);
                }
            }
        }
        if(move->piece=='R')
        {
            //Checking the column of the to location
            for(i=0;i<=7;i++)
            {
              //Omit the space the rook is on
              if(toRow != i)
              {
                 if((move->color == WHITE && board[i][toCol] == 'r')||(move->color == BLACK && board[i][toCol] == 'R'))
                 {
                   if(isAble(board,i,toCol,toRow,toCol))
                   {
                    if(move->from_loc.row == -1)
                        {
                            if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(toCol))
                                move->from_loc.row = 8-i;
                            if(move->from_loc.col == 'x')
                                move->from_loc.row = 8-i;
                        }
                    if(move->from_loc.col == 'x')
                       {
                        if(move->from_loc.row != -1 && move->from_loc.row == 8-i)
                            move->from_loc.col = colConverter(toCol);
                        if(move->from_loc.row == -1)
                            move->from_loc.col = colConverter(toCol);
                       }
                   }
                  }
              }
            }
            //Checking the row of the to location
            for(j=0;j<=7;j++)
            {
              //Omit the space the rook is on
              if(toCol != j)
              {
                if((move->color == WHITE && board[toRow][j] == 'r')||(move->color == BLACK && board[toRow][j] == 'R'))
                {
                 if(isAble(board,toRow,j,toRow,toCol))
                 {
                   if(move->from_loc.row == -1)
                        {
                            if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j))
                                move->from_loc.row = 8-toRow;
                            if(move->from_loc.col == 'x')
                                move->from_loc.row = 8-toRow;
                        }
                     if(move->from_loc.col == 'x')
                       {
                        if(move->from_loc.row != -1 && move->from_loc.row == 8-toRow)
                            move->from_loc.col = colConverter(j);
                        if(move->from_loc.row == -1)
                            move->from_loc.col = colConverter(j);
                       }
                 }
                }
               }
             }

        }
        if(move->piece=='B')
        {
            i = toRow, j = toCol;
            while(1)
            {
                i++, j++;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'b') || (move->color == BLACK && board[i][j] == 'B'))
                {
                  if(isAble(board,i,j,toRow,toCol))
                  {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                  }
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i++, j--;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'b') || (move->color == BLACK && board[i][j] == 'B'))
                {
                  if(isAble(board,i,j,toRow,toCol))
                  {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                  }
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i--, j++;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'b') || (move->color == BLACK && board[i][j] == 'B'))
                {
                  if(isAble(board,i,j,toRow,toCol))
                  {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                  }
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i--, j--;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'b') || (move->color == BLACK && board[i][j] == 'B'))
                {
                  if(isAble(board,i,j,toRow,toCol))
                  {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                  }
                }
            }
        }
        if(move->piece=='N')
        {
            //Check 4 rows
            for(i=-2;i<=2;i++)
            {
                //Omit the row the knight is on
                if(i!=0)
                {
                    //Make sure the row is on the board
                    if((toRow+i)>=0&&(toRow+i)<=7)
                    {
                        //Check two columns per row
                        for(j=-1;j<=1;j++)
                        {
                            //Omit the column the knight is on
                            if(j!=0)
                            {
                                //For the top and bottom rows
                                if(i==-2||i==2)
                                {
                                    //Make sure the column is on the board
                                    if((toCol+j)>=0&&(toCol+j)<=7)
                                    {
                                        //Is this square the piece that I want?
                                        //The case of the letter depends on what color I'm looking for.
                                         if((move->color == WHITE && board[toRow+i][toCol+j] == 'n')||(move->color == BLACK && board[toRow+i][toCol+j] == 'N'))
                                         {
                                             //Checks if the information must be changed, and also checks if given
                                             //A row or column to choose the piece that corresponds
                                             if(move->from_loc.col == 'x')
                                                if(move->from_loc.row != -1 && move->from_loc.row == 8-(toRow+i))
                                                    move->from_loc.col = colConverter(toCol+j);
                                                if(move->from_loc.row == -1)
                                                    move->from_loc.col = colConverter(toCol+j);

                                             if(move->from_loc.row == -1)
                                                if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(toCol+j))
                                                    move->from_loc.row = 8-(toRow+i);
                                                if(move->from_loc.col == 'x')
                                                    move->from_loc.row = 8-(toRow+i);
                                         }
                                    }
                                }
                                //For the two middle rows
                                if(i==-1||i==1)
                                {
                                    //Because geometry
                                    k = 2*j;

                                    //Make sure the column is on the board
                                    if(toCol+k>=0 && toCol+k<=7)
                                    {
                                        //Is this square the piece that I want?
                                        if((move->color == WHITE && board[toRow+i][toCol+k] == 'n')||(move->color == BLACK && board[toRow+i][toCol+k] == 'N'))
                                        {
                                            //Checks if the information must be changed, and also checks if given
                                            //A row or column to choose the piece that corresponds
                                            if(move->from_loc.col == 'x')
                                                if(move->from_loc.row != -1 && move->from_loc.row == 8-(toRow+i))
                                                    move->from_loc.col = colConverter(toCol+k);
                                                if(move->from_loc.row == -1)
                                                    move->from_loc.col = colConverter(toCol+k);

                                            if(move->from_loc.row == -1)
                                                if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(toCol+k))
                                                    move->from_loc.row = 8-(toRow+i);
                                                if(move->from_loc.col == 'x')
                                                    move->from_loc.row = 8-(toRow+i);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(move->piece=='K')
        {
            //Checks all squares around the king
            for(i=-1;i<=1;i++)
            {
                for(j=-1;j<=1;j++)
                {
                    //Omit the square the king is on
                    if(i!=0||j!=0)
                    {
                        //Make sure the square is on the board
                        if(isBetween(toRow+i,0,7)&&isBetween(toCol+j,0,7))
                        {
                            if((move->color == WHITE && board[toRow+i][toCol+j] == 'k') || (move->color == BLACK && board[toRow+i][toCol+j] == 'K'))
                            {
                                move->from_loc.row = 8 - (toRow+i);
                                move->from_loc.col = colConverter(toCol+j);
                            }
                        }
                    }
                }
            }
        }
        if(move->piece=='Q')
        {
        //All I did for the queen was combine my rook and bishop searches
            //Checking the column of the to location
            for(i=0;i<=7;i++)
            {
              //Omit the space the queen is on
              if(toRow != i)
              {
                 if((move->color == WHITE && board[i][toCol] == 'q')||(move->color == BLACK && board[i][toCol] == 'Q'))
                 {
                    if(move->from_loc.row == -1)
                        {
                            if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(toCol))
                                move->from_loc.row = 8-i;
                            if(move->from_loc.col == 'x')
                                move->from_loc.row = 8-i;
                        }
                    if(move->from_loc.col == 'x')
                       {
                        if(move->from_loc.row != -1 && move->from_loc.row == 8-i)
                            move->from_loc.col = colConverter(toCol);
                        if(move->from_loc.row == -1)
                            move->from_loc.col = colConverter(toCol);
                       }
                  }
              }
            }
            //Checking the row of the to location
            for(j=0;j<=7;j++)
            {
              //Omit the space the queen is on
              if(toCol != j)
              {
                if((move->color == WHITE && board[toRow][j] == 'q')||(move->color == BLACK && board[toRow][j] == 'Q'))
                {
                   if(move->from_loc.row == -1)
                        {
                            if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j))
                                move->from_loc.row = 8-toRow;
                            if(move->from_loc.col == 'x')
                                move->from_loc.row = 8-toRow;
                        }
                     if(move->from_loc.col == 'x')
                       {
                        if(move->from_loc.row != -1 && move->from_loc.row == 8-toRow)
                            move->from_loc.col = colConverter(j);
                        if(move->from_loc.row == -1)
                            move->from_loc.col = colConverter(j);
                       }

                 }
               }
             }

            //Checks Diagonals
            i = toRow, j = toCol;
            while(1)
            {
                i++, j++;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'q') || (move->color == BLACK && board[i][j] == 'Q'))
                {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i++, j--;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'q') || (move->color == BLACK && board[i][j] == 'Q'))
                {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i--, j++;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'q') || (move->color == BLACK && board[i][j] == 'Q'))
                {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                }
            }
            i = toRow, j = toCol;
            while(1)
            {
                i--, j--;
                if((isBetween(i,0,7) + isBetween(j,0,7)) != 2)
                    break;

                if((move->color == WHITE && board[i][j] == 'q') || (move->color == BLACK && board[i][j] == 'Q'))
                {
                    if(move->from_loc.row != -1 && move->from_loc.row == 8 - i && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.row == -1 && move->from_loc.col == 'x')
                        move->from_loc.col = colConverter(j);
                    if(move->from_loc.col != 'x' && move->from_loc.col == colConverter(j) && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                    if(move->from_loc.col == 'x' && move->from_loc.row == -1)
                        move->from_loc.row = 8 - i;
                }
            }
        }

}

double difficultyRating(void)
{
    return 3.0;
}

double hoursSpent(void)
{
    return 30;
}
