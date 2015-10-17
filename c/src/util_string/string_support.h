#ifndef STRING_SUPPORT_H
#define	STRING_SUPPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void    string_support_putChar( char** ppc_buffer, uint16_t* pu16_length, const char cc_char );
void    string_support_putString( char** ppc_buffer, uint16_t* pu16_length, const uint16_t cu16_maxLength, char* pc_buf );
int16_t string_support_formatString( char* pc_buf, const uint16_t cu16_bufLength, const char *fmt, va_list va );
int16_t string_support_snprintf( char* buf, uint16_t size, const char *formatString, ...);

#ifdef	__cplusplus
}
#endif

#endif	/* STRING_SUPPORT_H */
