/*
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */


#include <stdio.h>

#include "vtimer.h"
#include "board.h"
//#include "udp.h"
//#include "rpl.h"

#define ENABLE_DEBUG (1)
#include "debug.h"

int main(void)
{
    timex_t timer = timex_set(1, 0); /* seconds */

    for (;;) {
      printf("Yow!\n");
#if defined(BOARD_IOT_LAB_M3) || defined (BOARD_FOX)
      LED_RED_OFF;
      LED_GREEN_OFF;
      LED_ORANGE_OFF;
#else
      LED_TOGGLE;
#endif
      vtimer_sleep(timer);

#if defined(BOARD_IOT_LAB_M3) || defined (BOARD_FOX)
      LED_RED_ON;
      LED_GREEN_OFF;
      LED_ORANGE_OFF;
#else
      LED_TOGGLE;
#endif
      vtimer_sleep(timer);

      printf("Yow2!\n");
#if defined(BOARD_IOT_LAB_M3) || defined (BOARD_FOX)
      LED_RED_ON;
      LED_GREEN_ON;
      LED_ORANGE_OFF;
#else
      LED_TOGGLE;
#endif
      vtimer_sleep(timer);

#if defined(BOARD_IOT_LAB_M3) || defined (BOARD_FOX)
      LED_RED_ON;
      LED_GREEN_ON;
      LED_ORANGE_ON;
#else
      LED_TOGGLE;
#endif
      vtimer_sleep(timer);
    }
}
