typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris Debris;

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
 * Represent explosions when fighter die
 */
struct Explosion {
    float x;
    float y;
    float dx;
    float dy;
    int r, g, b, a;
    Explosion *next;
};

/*
 * Represents debris that is thrown when a ship is destroyed
 */
struct Debris {
    float x;
    float y;
    float dx;
    float dy;
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;
    Debris *next;
};

/*
 * To hold information about the stage: fighters, bullets, explosions etc.
 *
 * Head represents the beginning of linked list. By defining Head as a value,
 * it ensures that the list always has a node to start from. Head doesn't contain actual data,
 * but provides an anchor to list. When list is empty Head.next is NULL
 * Head.next contains first element in the list with actual value.
 *
 * Tail is a pointer to the last element in the linked list. This allows for adding new elements to list.
 * When list is empty, Tail points to Head. This allows to quickly check if Head.next is NULL.
 *
 */
typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
} Stage;

/*
 * Represents background stars
 */
typedef struct {
    int x;
    int y;
    int speed;
} Star;
