# ATMEGA328P-LIBRARY-Matrix_Keyboard
Use two ports of the atmega328P for a keyboard matrix (designed for atmega328P)

This library requires the Common_Timer library also available on github. It specifically uses the following:

void init1msTimer0(uint64_t speed);

The above is a 1ms timer, the variable is e_milliseconds that the library uses for time.
