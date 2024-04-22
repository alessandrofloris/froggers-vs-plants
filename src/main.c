/**
 * 
 *  Froggers vs Plants
 * 
 *  @author Floris Alessandro
 * 
*/

#include <curses.h>

#include <stdlib.h>

#include <unistd.h>

#include "data_structures.h"

void curses_end() {

    endwin();

}

/**
 * Inits the curse mode
 */
void curses_init() {

    WINDOW* w = initscr(); /* Start curses mode */

    if( w == NULL ) {
        fprintf(stderr, "[Error] Ncurses init.\n");
        exit(EXIT_FAILURE);
    }

    curs_set(0); /* Hide cursor */
	noecho(); /* Do not show keypresses */
	cbreak(); /* Do not buffer keypresses */

}

/**
 * Draws the option menu and does a refresh of the main menu window 
 */
void draw_menu_options(MainMenu menu) {

    MenuOption options[] = {
        { .id = NEW_GAME, .placeholder = "Nuova Partita", .selected_placeholder = "> Nuova Partita <", .y = LINES/2, .x = (COLS/2)-6, .selected_x = (COLS/2)-8 },
        { .id = QUIT, .placeholder = "Esci", .selected_placeholder = "> Esci <", .y = (LINES/2)+4, .x = (COLS/2)-2, .selected_x = (COLS/2)-4 }
    };
    
    for(int i=0; i < menu.state.options_length; i++) {
        wmove(menu.window, options[i].y, 0);
        wclrtoeol(menu.window);
    }

    for(int i=0; i <= 1; i++) {
        if(options[i].id == menu.state.selected_option) {
            mvwprintw(menu.window, options[i].y, options[i].selected_x, options[i].selected_placeholder);
        } else {
            mvwprintw(menu.window, options[i].y, options[i].x, options[i].placeholder);
        }
    }

    wrefresh(menu.window);
    
}

/**
 * Draws the main menu (title + options) and does a refresh of the main menu window 
 */
void draw_menu(MainMenu menu) {

    mvwprintw(menu.window, LINES/6, (COLS/2)-9, "Froggers Vs Plants");

    draw_menu_options(menu);

}

/**
 * Inits the main menu configuration (graphic + state)
 */
MainMenu menu_init() {

    WINDOW* menu_win;

    menu_win = newwin(LINES, COLS, 0, 0);
    
    if(menu_win == NULL) {
        fprintf(stderr, "[Error] Window init.\n");
        curses_end();
        exit(EXIT_FAILURE);
    }

    nodelay(menu_win, true); /* Input not blocking */
    keypad(menu_win, true); /* Enable special keys */

    box(menu_win, ACS_VLINE, ACS_HLINE); /* Draws a border around the edges of the specified window */

    MenuState menu_state = { .selected_option = NEW_GAME, .options_length = 2 };
    MainMenu menu = { .window = menu_win, .state = menu_state };

    draw_menu(menu);

    return menu;

}

/**
 * Selects the current option in the main menu 
 */
void select_current_menu_option(MainMenu menu) {

    switch(menu.state.selected_option) {

        case NEW_GAME:
            // start_new_game()
            break;
        case QUIT:
            curses_end();
            exit(EXIT_SUCCESS);
            break;
        
    }

}

/**
 * Updates the menu_state data structure with the new selected option 
 */
void change_menu_selected_option(MainMenu* menu, int key) {

    switch(key) {

        case KEY_UP:
            if( menu->state.selected_option > 0 ) {
                menu->state.selected_option -= 1;
                draw_menu_options(*menu);
            } 
            break;
        case KEY_DOWN:
            if( (int)menu->state.selected_option < menu->state.options_length-1 ) {
                menu->state.selected_option += 1;
                draw_menu_options(*menu);
            } 
            break;

    }

}

/**
 * Handles the user inputs in the main menu
 */
void handle_menu_inputs(MainMenu *menu) {

    int c;

   while( (c = wgetch(menu->window)) ) {

        switch(c) {

        case KEY_UP: 
            change_menu_selected_option(menu, KEY_UP);
            break; 
        case KEY_DOWN:
            change_menu_selected_option(menu, KEY_DOWN);
            break;
        case (int)'\n':
            select_current_menu_option(*menu);
            break;

        }

    }

}

int main() {

    curses_init();
    
    MainMenu main_menu = menu_init();

    handle_menu_inputs(&main_menu); 

    curses_end();
    
}