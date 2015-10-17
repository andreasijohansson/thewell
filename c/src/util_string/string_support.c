#include <stdarg.h>

#include "../util_string/format_support.h"
#include "../util_string/string_support.h"

//------------------------------------------------------------------------------
void string_support_putChar( char** ppc_buffer, uint16_t* pu16_length, const char cc_char )
{
  *(*ppc_buffer)++ = cc_char;
  (*pu16_length)++;
}

//------------------------------------------------------------------------------
void string_support_putString( char** ppc_buffer, uint16_t* pu16_length, const uint16_t cu16_maxLength, char* pc_buf )
{
  char ch;
  while( ( ch = *(pc_buf++) ) && *pu16_length < cu16_maxLength )
  {
    string_support_putChar( ppc_buffer, pu16_length, ch );
  }
}

//------------------------------------------------------------------------------
int16_t string_support_formatString( char* pc_buf, const uint16_t cu16_bufLength, const char *fmt, va_list va )
{
  bool b_error = false;
  uint16_t u16_length = 0;
  uint16_t u16_maxLength = cu16_bufLength;

  char bf[12]; // temporary buffer when converting numbers
  char ch;

  if( u16_maxLength == 0 )
  {
    return -1;
  }

  u16_maxLength--; // make room for final null character, end of string

  while( ( ch = *(fmt++) ) && u16_length < u16_maxLength )
  {
    if( ch != '%' )
    {
      // a character, simply put it in the array, and move on to the next
      string_support_putChar( &pc_buf, &u16_length, ch );
      continue;
    }

    if( !(ch = *(fmt++)) )
    {
      // we reached the end of string, break out of loop...
      break;
    }

    switch( ch )
    {
      case 'u' :
        format_support_convertUnsignedInteger( va_arg(va, unsigned int), 10, false, bf );
        string_support_putString( &pc_buf, &u16_length, u16_maxLength, bf );
        break;

      case 'd':
        format_support_convertSignedInteger( va_arg(va, int), 10, false, bf );
        string_support_putString( &pc_buf, &u16_length, u16_maxLength, bf );
        break;

      case 'x':
      case 'X':
        format_support_convertUnsignedInteger( va_arg(va, unsigned int), 16, (ch == 'X'), bf );
        string_support_putString( &pc_buf, &u16_length, u16_maxLength, bf );
        break;

      case 'c':
        string_support_putChar( &pc_buf, &u16_length, (char)(va_arg(va, int)) );
        break;

      case 's':
        string_support_putString( &pc_buf, &u16_length, u16_maxLength, va_arg( va, char* ) );
        break;

      case '%':
        string_support_putChar( &pc_buf, &u16_length, ch );
        break;

      default:
        // unknown (read: unimplemented) specifier/flag/width
        b_error = true;
        break;
    }
  }

  string_support_putChar(&pc_buf, &u16_length, 0); // END_OF_STRING

  return ( b_error ? -1 : (int16_t)(u16_length-1) );
}

//------------------------------------------------------------------------------
int16_t string_support_snprintf( char* buf, uint16_t size, const char *formatString, ...)
{
  int16_t retVal;
  va_list variableArgumentList;
  va_start(variableArgumentList, formatString);
  retVal = string_support_formatString(buf, size, formatString, variableArgumentList);
  va_end(variableArgumentList);
  return retVal;
}
