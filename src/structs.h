/*
 * App will hold reference to window and renderer
 *
 * @param *renderer
 * @param *window
 *
 * @return App reference
 */
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int right;
} App;

/*
 * Represents the player
 *
 * @param x coordinate
 * @param y coordinate
 * @param *texture player texture
 */
typedef struct {
    int x;
    int y;
    SDL_Texture *texture;
} Entity;
