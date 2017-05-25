#include <stdio.h>
#include <stdlib.h>
#include "frame.h"

int main(int argc, char ** argv)
{
    printf("sizeof command frame: %lu\n", sizeof (ucirc_cmd_param));
    printf("sizeof status frame: %lu\n", sizeof(ucirc_status_frame));
}

