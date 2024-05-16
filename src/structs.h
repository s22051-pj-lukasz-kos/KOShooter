typedef struct Entity Entity;

/*
 * Delegate for handling the logic and draw functions in the game's main loop
 */
typedef struct {
    void (*logic)(void);

    void (*draw)(void);
} Delegate;

/*
 * App will hold reference to all related logic, window, keyboard events, etc.
 */
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

/*
 * Represents the entity (player, bullets, enemies, etc.)
 * Entities could structure linked list, using next pointer
 */
struct Entity {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int reload;
    int side;       ///< side defined in defs (player or alien)
    SDL_Texture *texture;
    Entity *next;   ///< Pointer to next Entity (for linked list)
};

/*
 * To hold information about all fighters and bullets
 */
typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
} Stage;
