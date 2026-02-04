#include "pync.h"

static int counter = 0;

void
increment (void)
{
   counter++;
}

void
decrement (void)
{
   counter--;
}

void
reset (void)
{
   counter = 0;
}

int
get_number (void)
{
   return counter;
}
