#include <sys/ioctl.h>
#include <stdio.h>


int main(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    printf("lines: %d, cols: %d\n", w.ws_row, w.ws_col);
    return 0;
}
