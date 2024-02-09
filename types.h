#include<raylib.h>
struct window { int height; int width; char *name; };
struct player { int size; Color color; float x; float y; float deltaV; };
struct enemy { int size; Color color; float x; float y; float speed; }; 

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
