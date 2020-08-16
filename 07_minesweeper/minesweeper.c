#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};
typedef struct _board_t board_t;

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines taht we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while (b->board[y][x] == HAS_MINE);
  b->board[y][x] = HAS_MINE;
}

board_t * makeBoard(int w, int h, int numMines) {
  //WRITE ME!
  /*  - makeBoard: this function should malloc and initialize a board_t
    representing the board. The parameters specify the width and
    height of the board, as well as the number of mines. You will also
    need to call malloc (multiple times) to allocate space for the 2D
    array "board". This function should fill in all squares on the
    board with UNKNOWN, then call addRandomMine an appropriate number
    of times (i.e., numMines) to "randomly" place mines on the
    board.
      Note that the fields of your board_t must be initailzed
    before you call addRandomMine. Also note that the mine generation
    is pseudo random and will not change if you re-run the program
    multiple times with the same parameters.
      Note that the layout of b->board should be such that it is indexed
    b->board[y][x] where y is between 0 and the height and x is
    between 0 and the width.*/
  //board_t * b = makeBoard(width, height, numMines);
  board_t *b = malloc(sizeof(*b));//remember
  b->width = w;
  b->height = h;
  b->totalMines = numMines;
  //b->board = malloc(h*w*sizeof(**b->board));//wrong?
  b->board = malloc(h*sizeof(*(b->board)));
  int *line = NULL;
  for(int i=0;i<h;i++)//do it again, hardest part
  {
    line = malloc(w*sizeof(*line));
    for(int j=0;j<h;j++)//j<w is wrong
      line[j] = UNKNOWN;
    b->board[i] = line;
    line = NULL;
  }
  for(int i=0;i<numMines;i++)
  {
    addRandomMine(b);
  }  
  return b;//remember to return b
}

void printBoard(board_t * b) {
  int found = 0;
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y % 100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == KNOWN_MINE) {
        printf("*");
        found++;
      }
      else if (b->board[y][x] < 0) {
        printf("?");
      }
      else if (b->board[y][x] == 0) {
        printf(" ");
      }
      else {
        printf("%d", b->board[y][x]);
      }
    }
    printf("\n");
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x / 10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d", x % 10);
  }
  printf("\nFound %d of %d mines\n", found, b->totalMines);
}
int checkvalid(int x ,int y ,int w,int h){
  if (((x>=0)&&(x < w))&&((y >= 0)&&(y<h))) return 1;
  else return 0;
}
int countMines(board_t * b, int x, int y) {
  //WRITE ME!
  /*- countMines: this funciton takes a board_t, and an (x,y)
    coordinate. It should count the mines in the 8 squares around that
    (x,y) coordinate, and return that count. Note that a mine may be
    indicated by a square on the board either being HAS_MINE or
    KNOWN_MINE. You can use the IS_MINE macro to test both cases: 
      IS_MINE(b->board[ny][nx]) 
    (where b is the board_t, and (nx,ny) are the coordinates you want
    to check). Be careful not to go out of bounds of the array. */
  int w=b->width;
  int h=b->height;
  int c=0;
  
  int x1;
  int y1;
  x1=x-1;
  y1=y-1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  y1=y;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  y1=y+1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }

  x1=x+1;
  y1=y-1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  y1=y;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  y1=y+1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }

  x1=x;
  y1=y-1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  y1=y+1;
  if(checkvalid(x1,y1,w,h)){
    if (IS_MINE(b->board[y1][x1])) c++;
  }
  return c;
}
int click(board_t * b, int x, int y) {
  if (x < 0 || x >= b->width || y < 0 || y >= b->height) {
    return CLICK_INVALID;
  }
  if (b->board[y][x] == KNOWN_MINE) {
    return CLICK_KNOWN_MINE;
  }
  if (b->board[y][x] == HAS_MINE) {
    return CLICK_LOSE;
  }
  if (b->board[y][x] != UNKNOWN) {
    return CLICK_CONTINUE;
  }

  b->board[y][x] = countMines(b, x, y);
  return CLICK_CONTINUE;
}

int checkWin(board_t * b) {
  //WRITE ME!
  /*- checkWin: this funciton takes a board_t and see if the game has
    been won. The game is won when no squares are UNKNOWN. */
  //else if (checkWin(b))
  for(int i=0;i<b->height;i++){
    for(int j=0;j<b->width;j++){
      if(b->board[i][j] == UNKNOWN){
        return 0;
      }
    }
  }
  return 1;
}

void freeBoard(board_t * b) {
  //WRITE ME!
  /*- freeBoard: This function takes a board_t and frees all memory
    associated with it (including the array inside of it). That is,
    freeBoard should undo all the allocations made by a call to
    makeBoard. */
  //int w = b->width;
  int h = b->height;
  for(int i=0;i<h;i++)
  {
    free(b->board[i]);
  }
  free(b->board);
  free(b);
}

int readInt(char ** linep, size_t * lineszp) {
  if (getline(linep, lineszp, stdin) == -1) {
    fprintf(stderr, "End of file from keyboard reading a number.  Quitting\n");
    exit(EXIT_FAILURE);
  }
  char * endptr = NULL;
  long int x = strtol(*linep, &endptr, 10);
  if (endptr == *linep) {
    fprintf(stderr, "You did not enter any valid number\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (*endptr != '\n') {
    fprintf(stderr, "Input was not entirely a number (junk at end)\n");
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  if (x > INT_MAX) {
    fprintf(stderr, "%ld is too big for an int!\n", x);
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  return x;
}

void doReveal(board_t * b, int x, int y, int revealMines) {
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (revealMines) {
          assert(b->board[ny][nx] != UNKNOWN);
          if (b->board[ny][nx] == HAS_MINE) {
            b->board[ny][nx] = KNOWN_MINE;
          }
        }
        else {
          assert(b->board[ny][nx] != HAS_MINE);
          if (b->board[ny][nx] == UNKNOWN) {
            b->board[ny][nx] = countMines(b, nx, ny);
          }
        }
      }
    }
  }
}

int maybeReveal(board_t * b, int x, int y) {
  int unknownSquares = 0;
  int knownMines = 0;
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
        if (b->board[ny][nx] == UNKNOWN || b->board[ny][nx] == HAS_MINE) {
          unknownSquares++;
        }
        else if (b->board[ny][nx] == KNOWN_MINE) {
          knownMines++;
        }
      }
    }
  }
  assert(knownMines + unknownSquares >= b->board[y][x]);
  assert(knownMines <= b->board[y][x]);
  if (unknownSquares > 0) {
    int revealMines = (knownMines + unknownSquares == b->board[y][x]);
    int allKnown = knownMines == b->board[y][x];
    if (revealMines || allKnown) {
      assert(!revealMines || !allKnown);
      doReveal(b, x, y, revealMines);
      return 1;
    }
  }
  return 0;
}

void determineKnownMines(board_t * b) {
  int foundMore = 0;
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] >= 0) {
        foundMore = maybeReveal(b, x, y) || foundMore;
      }
    }
  }
  if (foundMore) {
    determineKnownMines(b);
  }
}

void revealMines(board_t * b) {
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == HAS_MINE) {
        b->board[y][x] = KNOWN_MINE;
      }
    }
  }
}

int playTurn(board_t * b, char ** linep, size_t * lineszp) {
  printf("Current board:\n");
  printBoard(b);
  printf("x coordinate:\n");
  int x = readInt(linep, lineszp);
  printf("y coordinate:\n");
  int y = readInt(linep, lineszp);
  int result = click(b, x, y);
  determineKnownMines(b);
  if (result == CLICK_LOSE) {
    printf("Oh no! That square had a mine. You lose!\n");
    revealMines(b);
    printBoard(b);
    return 1;
  }
  else if (result == CLICK_INVALID) {
    printf("That is not a valid square, please try again\n");
  }
  else if (result == CLICK_KNOWN_MINE) {
    printf("You already know there is a mine there!\n");
  }
  else if (checkWin(b)) {
    printBoard(b);
    printf("You win!\n");
    return 1;
  }
  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: minesweeper width height numMines\n");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int numMines = atoi(argv[3]);
  if (width <= 0 || height <= 0 || numMines <= 0) {
    fprintf(stderr, "Width, height, and numMines must all be positive ints\n");
    return EXIT_FAILURE;
  }
  char * line = NULL;
  size_t linesz = 0;
  do {
    board_t * b = makeBoard(width, height, numMines);
    int gameOver = 0;
    while (!gameOver) {
      gameOver = playTurn(b, &line, &linesz);
    }
    freeBoard(b);
    do {
      printf("Do you want to play again?\n");
    } while (getline(&line, &linesz, stdin) == -1);
  } while (line[0] == 'Y' || line[0] == 'y');
  free(line);
  return EXIT_SUCCESS;
}
