/***************************************************
*                                                  *
*  The menu of the main window.                    *
*                                                  *
***************************************************/
#include "def_menu_main.h"

void setup_main_menu(HWND hwnd,MenuHelper_Interface *m)
{
    int t0=m->createNewMenuTitle("&File");
    m->createNewMenuPoint(t0,DEF_MENU_MAIN_FILE_NEW,"&New");
    m->createNewMenuPoint(t0,DEF_MENU_MAIN_FILE_OPEN,"&Open...");
    m->createNewMenuPoint(t0,DEF_MENU_MAIN_FILE_SAVE,"&Save...");
    m->createNewMenuPoint(t0,DEF_MENU_MAIN_FILE_SAVEAS,"&Save as...");
    m->createNewMenuPoint(t0,DEF_MENU_MAIN_FILE_EXIT,"&Exit");
    int t1=m->createNewMenuTitle("&Edit");
    m->createNewMenuPoint(t1,DEF_MENU_MAIN_EDIT_CONF,"&Config");
    m->createNewMenuPoint(t1,DEF_MENU_MAIN_EDIT_MODE,"&Grid edit-mode (on/off)");
    int t2=m->createNewMenuTitle("&Run");
    m->createNewMenuPoint(t2,DEF_MENU_MAIN_RUN_ALL,"&Run all");
    int t9=m->createNewMenuTitle("&Help");
    m->createNewMenuPoint(t9,DEF_MENU_MAIN_HELP_ABOUT,"&About");
    m->select(hwnd);
    delete m;
}
