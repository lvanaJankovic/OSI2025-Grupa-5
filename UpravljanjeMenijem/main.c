#include <stdio.h>
#include "meni.h"

int main() {
    if (!ucitajMeni("meni.csv")) {
        printf("Prazan ili nepostojeci meni.\n");
    }

    administratorMeni();

    return 0;
}
