/*
 * Definitions
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
// for string displaying
#define MAX_LINE_LENGTH 1024
#define FPS 60
#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 16
#define ALIEN_BULLET_SPEED 4
#define MAX_KEYBOARD_KEYS 350
#define SIDE_PLAYER 0
#define SIDE_ALIEN 1
#define MAX_STARS 500
#define MAX_SND_CHANNELS 8

/*
 * Sound channels
 */
enum {
    CH_ANY = -1,
    CH_PLAYER,
    CH_ALIEN_FIRE,
    CH_POINTS
};

/*
 * Sound effects
 */
enum {
    SND_PLAYER_FIRE,
    SND_ALIEN_FIRE,
    SND_PLAYER_DIE,
    SND_ALIEN_DIE,
    SND_POINTS,
    SND_MAX
};
