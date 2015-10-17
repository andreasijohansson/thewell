#ifndef FORMAT_SUPPORT_H
#define	FORMAT_SUPPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

uint8_t  format_support_uint16ToString( const uint16_t cu16_number, const uint8_t cu8_base, const bool cb_upperCase, char* pc_buf );
uint8_t  format_support_int16ToString( const int16_t cs16_number, const uint8_t cu8_base, const bool cb_upperCase, char* pc_buf );

#ifdef	__cplusplus
}
#endif

#endif	/* FORMAT_SUPPORT_H */
