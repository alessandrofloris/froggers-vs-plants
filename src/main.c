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

void menu_init() {

    WINDOW* menu;

    menu = newwin(LINES, COLS, 0, 0);
    
    if(menu == NULL) {
        fprintf(stderr, "[Error] Window init.\n");
        curses_end();
        exit(EXIT_FAILURE);
    }

    nodelay(menu, true); /* Input not blocking */
    keypad(menu, true); /* Enable special keys */

    box(menu, ACS_VLINE, ACS_HLINE); /* Draws a border around the edges of the specified window */

    mvwprintw(menu, LINES/6, (COLS/2)-9, "Froggers Vs Plants");

    wrefresh(menu);

}


int main() {

    curses_init();
    
    menu_init();

    usleep(5000000);

    curses_end();
    
}