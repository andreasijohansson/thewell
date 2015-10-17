
#include "../util_string/format_support.h"

//------------------------------------------------------------------------------
uint8_t format_support_convertUnsignedInteger( const uint16_t cu16_number, const uint8_t cu8_base, const bool cb_upperCase, char* pc_buf )
{
  uint8_t u8_nofDigits = 0;
  uint16_t u16_divider = 1;
  uint16_t u16_number = cu16_number;

  // first, calculate the minimum divider necessary in order to get hold of the first digit
  while( cu16_number / u16_divider >= cu8_base )
  {
    u16_divider *= cu8_base;
  }

  while( u16_divider > 0 )
  {
    uint8_t u8_digit = u16_number / u16_divider;
    *pc_buf++ = u8_digit < 10 ? '0' + u8_digit : ( cb_upperCase ? 'A' : 'a' ) + u8_digit - 10;
    u8_nofDigits++;
    u16_number %= u16_divider;
    u16_divider /= cu8_base;
  }

  *pc_buf = 0; // End of string

  return u8_nofDigits;
}

//------------------------------------------------------------------------------
uint8_t format_support_convertSignedInteger( const int16_t cs16_number, const uint8_t cu8_base, const bool cb_upperCase, char* pc_buf )
{
  uint16_t u16_number;
  uint8_t u8_extraChar = 0;
  if( cs16_number < 0 )
  {
    u16_number = (uint16_t)-cs16_number;
    *pc_buf++ = '-';
    u8_extraChar = 1;
  }
  else
  {
    u16_number = (uint16_t)cs16_number;
  }
  return format_support_convertUnsignedInteger( u16_number, cu8_base, cb_upperCase, pc_buf ) + u8_extraChar;
}
