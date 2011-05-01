/*
 * Character string functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <narrow_string.h>
#include <memory.h>
#include <wide_string.h>
#include <types.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_LOCALE_H ) || defined( WINAPI )
#include <locale.h>
#endif

#if defined( HAVE_LANGINFO_H )
#include <langinfo.h>
#endif

#include "libsystem_libuna.h"
#include "libsystem_string.h"

#if !defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

int libsystem_string_is_unicode           = 0;
int libsystem_string_byte_stream_codepage = 0;

#endif

#if defined( libsystem_string_to_signed_long_long )

/* Determines the value represented by a string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_to_int64(
     const libsystem_character_t *string,
     size_t string_size,
     int64_t *value,
     liberror_error_t **error )
{
	libsystem_character_t *end_of_string = NULL;
	static char *function                = "libsystem_string_to_int64";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid string size is zero.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	end_of_string = (libsystem_character_t *) &( string[ string_size - 1 ] );

	errno = 0;

	*value = libsystem_string_to_signed_long_long(
	          string,
	          &end_of_string,
	          0 );

	if( errno != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine value.",
		 function );

		return( -1 );
	}
	return( 1 );
}
#endif

#if defined( libsystem_string_to_unsigned_long_long )

/* Determines the value represented by a string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_to_uint64(
     const libsystem_character_t *string,
     size_t string_size,
     uint64_t *value,
     liberror_error_t **error )
{
	libsystem_character_t *end_of_string = NULL;
	static char *function                = "libsystem_string_to_uint64";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid string size s zero.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	end_of_string = (libsystem_character_t *) &( string[ string_size - 1 ] );

	errno = 0;

	*value = libsystem_string_to_unsigned_long_long(
	          string,
	          &end_of_string,
	          0 );

	if( errno != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine value.",
		 function );

		return( -1 );
	}
	return( 1 );
}
#endif

/* Determines the system string size from the UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_size_from_utf8_string(
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_size_from_utf8_string";

	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_size_from_utf8(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_size_from_utf8(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine string size.",
		 function );

		return( -1 );
	}
#else
	if( libsystem_string_is_unicode != 0 )
	{
		*string_size = 1 + narrow_string_length(
		                    (char *) utf8_string );
	}
	else if( libuna_byte_stream_size_from_utf8(
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          libsystem_string_byte_stream_codepage,
	          string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine string size.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Copies the system string size from the UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_copy_from_utf8_string(
     libsystem_character_t *string,
     size_t string_size,
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_copy_from_utf8_string";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_copy_from_utf8(
	     (libuna_utf32_character_t *) string,
	     string_size,
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_copy_from_utf8(
	     (libuna_utf16_character_t *) string,
	     string_size,
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
#else
	if( libsystem_string_is_unicode != 0 )
	{
		if( string_size < utf8_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string too small.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     string,
		     utf8_string,
		     utf8_string_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
	}
	else if( libuna_byte_stream_copy_from_utf8(
	          (uint8_t *) string,
	          string_size,
	          libsystem_string_byte_stream_codepage,
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Determines the UTF-8 string size from the system string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_size_to_utf8_string(
     const libsystem_character_t *string,
     size_t string_size,
     size_t *utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_size_to_utf8_string";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_size_from_utf32(
	     (libuna_utf32_character_t *) string,
	     string_size,
	     utf8_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_size_from_utf16(
	     (libuna_utf16_character_t *) string,
	     string_size,
	     utf8_string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 string size.",
		 function );

		return( -1 );
	}
#else
	if( libsystem_string_is_unicode != 0 )
	{
		*utf8_string_size = 1 + libsystem_string_length(
		                         string );
	}
	else if( libuna_utf8_string_size_from_byte_stream(
	          (uint8_t *) string,
	          string_size,
	          libsystem_string_byte_stream_codepage,
	          utf8_string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 string size.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Copies the UTF-8 string size from the system string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_copy_to_utf8_string(
     const libsystem_character_t *string,
     size_t string_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_copy_to_utf8_string";

	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_copy_from_utf32(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     (libuna_utf32_character_t *) string,
	     string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_copy_from_utf16(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     (libuna_utf16_character_t *) string,
	     string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
#else
	if( libsystem_string_is_unicode != 0 )
	{
		if( utf8_string_size < string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string too small.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     utf8_string,
		     string,
		     string_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
	}
	else if( libuna_utf8_string_copy_from_byte_stream(
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          (uint8_t *) string,
	          string_size,
	          libsystem_string_byte_stream_codepage,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Split a string into elements using a delimiter character
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_split(
     libsystem_character_t *string,
     size_t string_size,
     libsystem_character_t delimiter,
     libsystem_character_t ***split_values,
     size_t *amount_of_split_values,
     liberror_error_t **error )
{
	libsystem_character_t *split_value_start = NULL;
	libsystem_character_t *split_value_end   = NULL;
	libsystem_character_t *string_end        = NULL;
	static char *function                    = "libsystem_string_split";
	size_t remaining_string_size             = 0;
	size_t split_value_iterator              = 0;
	ssize_t split_value_size                 = 0;

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( split_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split values.",
		 function );

		return( -1 );
	}
	if( *split_values != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: split values already set.",
		 function );

		return( -1 );
	}
	if( amount_of_split_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of split values.",
		 function );

		return( -1 );
	}
	/* Include the last character if not the end of string character
	 */
	if( string[ string_size - 1 ] != 0 )
	{
		string_size += 1;
	}
	/* Do not bother with empty strings
	 */
	if( ( string_size == 0 )
	 || ( string[ 0 ] == 0 ) )
	{
		*split_values           = NULL;
		*amount_of_split_values = 0;

		return( 1 );
	}
	/* Determine the amount of split values
	 */
	remaining_string_size = string_size;
	split_value_start     = string;
	split_value_end       = string;
	string_end            = &string[ string_size - 1 ];

	do
	{
		split_value_end = libsystem_string_search(
		                   split_value_start,
		                   delimiter,
		                   remaining_string_size );

		if( split_value_end > string_end )
		{
			break;
		}
		split_value_iterator++;

		if( split_value_end == NULL )
		{
			break;
		}
		/* Include delimiter character
		 */
		remaining_string_size -= (size_t) ( split_value_end - split_value_start ) + 1;

		if( split_value_end == split_value_start )
		{
			split_value_start += 1;
		}
		else if( split_value_end != string )
		{
			split_value_start = split_value_end + 1;
		}
	}
	while( split_value_end != NULL );

	*amount_of_split_values = split_value_iterator;

	if( *amount_of_split_values == 0 )
	{
		*split_values = NULL;

		return( 1 );
	}
	*split_values = (libsystem_character_t **) memory_allocate(
	                                           sizeof( libsystem_character_t * ) * *amount_of_split_values );

	if( *split_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: unable to create split values.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     *split_values,
	     0,
	     sizeof( libsystem_character_t * ) * *amount_of_split_values ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: unable to clear split values.",
		 function );

		memory_free(
		 *split_values );

		*split_values = NULL;

		return( -1 );
	}
	/* Determine the split values
	 */
	remaining_string_size = string_size;
	split_value_start     = string;
	split_value_end       = string;

	/* Empty values are stored as strings only containing the end of character
	 */
	for( split_value_iterator = 0; split_value_iterator < *amount_of_split_values; split_value_iterator++ )
	{
		if( split_value_end != string )
		{
			split_value_start = split_value_end + 1;
		}
		split_value_end = libsystem_string_search(
		                   split_value_start,
		                   delimiter,
		                   remaining_string_size );

		/* Check for last value
		 */
		if( split_value_end == NULL )
		{
			split_value_size = (ssize_t) ( string_end - split_value_start );
		}
		else
		{
			split_value_size = (ssize_t) ( split_value_end - split_value_start );
		}
		if( split_value_size >= 0 )
		{
			/* Add 1 additional byte required for the end of string character
			 */
			split_value_size += 1;

			( *split_values )[ split_value_iterator ] = (libsystem_character_t *) memory_allocate(
			                                                                       sizeof( libsystem_character_t ) * split_value_size );

			if( ( *split_values )[ split_value_iterator ] == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: unable to create split value: %" PRIzd ".",
				 function,
				 split_value_iterator );

				libsystem_string_split_values_free(
				 *split_values,
				 ( split_value_iterator - 1 ),
				 NULL );

				*split_values = NULL;

				return( -1 );
			}
			if( libsystem_string_copy(
			     ( *split_values )[ split_value_iterator ],
			     split_value_start,
			     split_value_size ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: unable to set split value: %" PRIzd ".",
				 function,
				 split_value_iterator );

				libsystem_string_split_values_free(
				 *split_values,
				 split_value_iterator,
				 NULL );

				*split_values = NULL;

				return( -1 );
			}
			( *split_values )[ split_value_iterator ][ split_value_size - 1 ] = 0;
		}
		/* Include delimiter character
		 */
		remaining_string_size -= (size_t) ( split_value_end - split_value_start ) + 1;

		/* Correct if first value is empty
		 */
		if( split_value_end == string )
		{
			split_value_start += 1;
		}
	}
	return( 1 );
}

/* Clears split values
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_split_values_free(
     libsystem_character_t **split_values,
     size_t amount_of_split_values,
     liberror_error_t **error )
{
	static char *function       = "libsystem_string_split_values_free";
	size_t split_value_iterator = 0;

	if( split_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split values.",
		 function );

		return( -1 );
	}
	for( split_value_iterator = 0; split_value_iterator < amount_of_split_values; split_value_iterator++ )
	{
		if( split_values[ split_value_iterator ] != NULL )
		{
			memory_free(
			 split_values[ split_value_iterator ] );
		}
	}
	memory_free(
	 split_values );

	return( 1 );
}

