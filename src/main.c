#include "header.h"

int main()
{
    struct User u = {0, "", ""};

    initMenu(&u);
    
    mainMenu(u);

    return 0;
}
