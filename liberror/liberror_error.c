/*
 * Error functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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
#include <memory.h>
#include <narrow_string.h>

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#include "liberror_definitions.h"
#include "liberror_error.h"
#include "liberror_types.h"

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#define VARARGS( function, error, error_domain, error_code, type, argument ) \
        function( error, error_domain, error_code, type argument, ... )
#define VASTART( argument_list, type, name ) \
        va_start( argument_list, name )
#define VAEND( argument_list ) \
        va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARARGS( function, error, error_domain, error_code, type, argument ) \
        function( error, error_domain, error_code, va_alist ) va_dcl
#define VASTART( argument_list, type, name ) \
        { type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VAEND( argument_list ) \
        va_end( argument_list ); }

#endif

/* Set an error initializes the error
 * The error domain and code are set only the first time and the error message is appended for backtracing
 */
void VARARGS(
      liberror_error_set,
      liberror_error_t **error,
      int error_domain,
      int error_code,
      const char *,
      format )
{
	va_list argument_list;

	liberror_internal_error_t *internal_error = NULL;
	void *reallocation                        = NULL;
	size_t message_size                       = 64;
	int print_count                           = 0;

	if( error == NULL )
	{
		return;
	}
	if( *error == NULL )
	{
		*error = (liberror_error_t *) memory_allocate(
		                               sizeof( liberror_internal_error_t ) );

		if( *error == NULL )
		{
			return;
		}
		( (liberror_internal_error_t *) *error )->amount_of_messages = 0;
		( (liberror_internal_error_t *) *error )->message            = NULL;
		( (liberror_internal_error_t *) *error )->domain             = error_domain;
		( (liberror_internal_error_t *) *error )->code               = error_code;
	}
	internal_error = (liberror_internal_error_t *) *error;

	reallocation = memory_reallocate(
	                internal_error->message,
	                sizeof( char * ) * ( internal_error->amount_of_messages + 1 ) );

	if( reallocation == NULL )
	{
		return;
	}
	internal_error->amount_of_messages                               += 1;
	internal_error->message                                           = (char **) reallocation;
	internal_error->message[ internal_error->amount_of_messages - 1 ] = NULL;

	do
	{
		reallocation = memory_reallocate(
		                internal_error->message[ internal_error->amount_of_messages - 1 ],
		                sizeof( char ) * message_size );

		if( reallocation == NULL )
		{
			memory_free(
			 internal_error->message[ internal_error->amount_of_messages - 1 ] );

			internal_error->message[ internal_error->amount_of_messages - 1 ] = NULL;

			return;
		}
		internal_error->message[ internal_error->amount_of_messages - 1 ] = reallocation;

		VASTART(
		 argument_list,
		 const char *,
		 format );

		print_count = narrow_string_vsnprintf(
		               internal_error->message[ internal_error->amount_of_messages - 1 ],
		               message_size,
		               format,
		               argument_list );

		VAEND(
		 argument_list );

		if( print_count <= -1 )
		{
			message_size += 64;
		}
		else if( ( (size_t) print_count > message_size )
		      || ( internal_error->message[ internal_error->amount_of_messages - 1 ][ print_count ] != 0 ) )
		{
			message_size = (size_t) ( print_count + 1 );
			print_count  = -1;
		}
	}
	while( print_count <= -1 );
}

#undef VARARGS
#undef VASTART
#undef VAEND

/* Free an error and its elements
 */
void liberror_error_free(
      liberror_error_t **error )
{
	liberror_internal_error_t *internal_error = NULL;
	int message_iterator                      = 0;

	if( error == NULL )
	{
		return;
	}
	if( *error != NULL )
	{
		internal_error = (liberror_internal_error_t *) *error;

		if( internal_error->message != NULL )
		{
			for( message_iterator = 0;
			     message_iterator < internal_error->amount_of_messages;
			     message_iterator++ )
			{
				if( internal_error->message[ message_iterator ] != NULL )
				{
					memory_free(
					 internal_error->message[ message_iterator ] );
				}
			}
			memory_free(
			 internal_error->message );
		}
		memory_free(
		 *error );

		*error = NULL;
	}
}

/* Determines if an error equals a certain error code of a domain
 * Returns 1 if error matches or 0 if not
 */
int liberror_error_matches(
     liberror_error_t *error,
     int error_domain,
     int error_code )
{
	if( error == NULL )
	{
		return( 0 );
	}
	if( ( ( (liberror_internal_error_t *) error )->domain == error_domain )
	 && ( ( (liberror_internal_error_t *) error )->code == error_code ) )
	{
		return( 1 );
	}
	return( 0 );
}

/* Prints a descriptive string of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int liberror_error_fprint(
     liberror_error_t *error,
     FILE *stream )
{
	liberror_internal_error_t *internal_error = NULL;
	int message_iterator                      = 0;
	int print_count                           = 0;

	if( error == NULL )
	{
		return( -1 );
	}
	if( stream == NULL )
	{
		return( -1 );
	}
	if( ( (liberror_internal_error_t *) error )->message == NULL )
	{
		return( -1 );
	}
	internal_error = (liberror_internal_error_t *) error;

	message_iterator = internal_error->amount_of_messages - 1;

	if( internal_error->message[ message_iterator ] != NULL )
	{
		print_count = fprintf(
		               stream,
		               "%s\n",
		               internal_error->message[ message_iterator ] );

		/* TODO check return value */
	}
	return( print_count );
}

/* Prints a descriptive string of the error to the string
 * Returns the amount of printed characters if successful or -1 on error
 */
int liberror_error_sprint(
     liberror_error_t *error,
     char *string,
     size_t size )
{
	liberror_internal_error_t *internal_error = NULL;
	int message_iterator                      = 0;
	int print_count                           = 0;

	if( error == NULL )
	{
		return( -1 );
	}
	if( string == NULL )
	{
		return( -1 );
	}
	if( ( (liberror_internal_error_t *) error )->message == NULL )
	{
		return( -1 );
	}
	internal_error = (liberror_internal_error_t *) error;

	message_iterator = internal_error->amount_of_messages - 1;

	if( internal_error->message[ message_iterator ] != NULL )
	{
		print_count = narrow_string_snprintf(
		               string,
		               size,
		               "%s\n",
		               internal_error->message[ message_iterator ] );

		/* TODO check return value */
	}
	return( print_count );
}

/* Prints a backtrace of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int liberror_error_backtrace_fprint(
     liberror_error_t *error,
     FILE *stream )
{
	liberror_internal_error_t *internal_error = NULL;
	int message_iterator                      = 0;
	int print_count                           = 0;
	int total_print_count                     = 0;

	if( error == NULL )
	{
		return( -1 );
	}
	if( stream == NULL )
	{
		return( -1 );
	}
	internal_error = (liberror_internal_error_t *) error;

	if( internal_error->message == NULL )
	{
		return( -1 );
	}
	for( message_iterator = 0;
	     message_iterator < internal_error->amount_of_messages;
	     message_iterator++ )
	{
		if( internal_error->message[ message_iterator ] != NULL )
		{
			print_count = fprintf(
			               stream,
			               "%s\n",
			               internal_error->message[ message_iterator ] );

			/* TODO check return value */

			total_print_count += print_count;
		}
	}
	return( total_print_count );
}

/* Prints a backtrace of the error to the string
 * Returns the amount of printed characters if successful or -1 on error
 */
int liberror_error_backtrace_sprint(
     liberror_error_t *error,
     char *string,
     size_t size )
{
	liberror_internal_error_t *internal_error = NULL;
	int message_iterator                      = 0;
	int print_count                           = 0;
	int total_print_count                     = 0;

	if( error == NULL )
	{
		return( -1 );
	}
	if( string == NULL )
	{
		return( -1 );
	}
	internal_error = (liberror_internal_error_t *) error;

	if( internal_error->message == NULL )
	{
		return( -1 );
	}
	for( message_iterator = 0;
	     message_iterator < internal_error->amount_of_messages;
	     message_iterator++ )
	{
		if( internal_error->message[ message_iterator ] != NULL )
		{
			print_count = narrow_string_snprintf(
			               string,
			               size,
			               "%s\n",
			               internal_error->message[ message_iterator ] );

			/* TODO check return value */

			total_print_count += print_count;
		}
	}
	return( total_print_count );
}

