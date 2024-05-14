#ifndef _KDEBUG_H
#define _KDEBUG_H

#define MAGICBP     asm("xchgw %bx, %bx")

void panic_spin(char* filename, int line, const char* func, const char* condition);

#define PANIC(...) panic_spin (__FILE__, __LINE__, __func__, __VA_ARGS__)
 /***********************************************************************/

#ifdef NDEBUG
   #define ASSERT(CONDITION) ((void)0)
#else
   #define ASSERT(CONDITION)                                        \
      if ((CONDITION)) {} else {                                      \
	    PANIC(#CONDITION);                                          \
      }
#endif /*__NDEBUG */


#endif