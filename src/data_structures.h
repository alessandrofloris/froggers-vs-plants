typedef enum MenuOptions {
    NEW_GAME,
    QUIT
} MenuOptions;

typedef struct MenuState {
    MenuOptions selected_option;
    int options_length;
} MenuState;

typedef struct MainMenu {
    WINDOW* window;
    MenuState state;
} MainMenu;

typedef struct MenuOption {
    char placeholder[64];
    char selected_placeholder[64];
    MenuOptions id;
    int y;
    int x;
    int selected_x;
} MenuOption;