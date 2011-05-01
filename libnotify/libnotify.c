/*
 * Notification library
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
#include <file_stream.h>
#include <memory.h>

#include <liberror.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#include "libnotify.h"

/* The notification stream
 */
FILE *libnotify_stream = NULL;

/* Value to indicate if the notification stream
 * was opened by the library
 */
int libnotify_stream_opened_in_library = 0;

/* Value to indicate if the verbose notification
 * is active
 */
int libnotify_verbose = 0;

/* Set the verbose
 */
void libnotify_set_verbose(
      int verbose )
{
	libnotify_verbose = verbose;
}

/* Set the stream
 * Returns 1 if successful or -1 on error
 */
int libnotify_set_stream(
     FILE *stream,
     liberror_error_t **error )
{
	static char *function = "libnotify_set_stream";

	if( ( libnotify_stream_opened_in_library != 0 )
	 && ( libnotify_stream_close(
	       error ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to close notify stream.",
		 function );

		return( -1 );
	}
	libnotify_stream = stream;

	return( 1 );
}

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
int libnotify_stream_open(
     const char *filename,
     liberror_error_t **error )
{
	static char *function = "libnotify_stream_open";

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( libnotify_stream_opened_in_library != 0 )
	 && ( libnotify_stream_close(
	       error ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to close notify stream.",
		 function );

		return( -1 );
	}
	libnotify_stream = file_stream_open(
	                    filename,
	                    FILE_STREAM_OPEN_APPEND );
	
	if( libnotify_stream == NULL )
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %s.",
				 function,
				 filename );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %s.",
				 function,
				 filename );

				break;

			default:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_OPEN_FAILED,
				 "%s: unable to open file: %s.",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	libnotify_stream_opened_in_library = 1;

	return( 1 );
}

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
int libnotify_stream_close(
     liberror_error_t **error )
{
	static char *function = "libnotify_stream_close";

	if( libnotify_stream_opened_in_library != 0 )
	{
		if( file_stream_close(
		     libnotify_stream ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close stream.",
			 function );

			return( -1 );
		}
		libnotify_stream                   = NULL;
		libnotify_stream_opened_in_library = 0;
	}
	return( 0 );
}

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#define VARARGS( function, stream, type, argument ) \
	function( stream, type argument, ... )
#define VASTART( argument_list, type, name ) \
	va_start( argument_list, name )
#define VAEND( argument_list ) \
	va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARARGS( function, stream, type, argument ) \
	function( stream, va_alist ) va_dcl
#define VASTART( argument_list, type, name ) \
	{ type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VAEND( argument_list ) \
	va_end( argument_list ); }

#endif

/* Print a formatted string on the notify stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int VARARGS(
     libnotify_fprintf,
     FILE *stream,
     const char *,
     format )
{
	va_list argument_list;

	int print_count = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	VASTART(
	 argument_list,
	 char *,
	 format );

#if defined( HAVE_GLIB_H )
	g_logv(
	 G_LOG_DOMAIN,
	 G_LOG_LEVEL_MESSAGE,
	 format,
	 argument_list );

#else
	/* TODO handle narrow and wide streams
	 * for multi platform support
	 */
	print_count = file_stream_vfprintf(
		       stream,
		       format,
		       argument_list );

	/* TODO check return value */
#endif

	VAEND(
	 argument_list );

	return( print_count );
}

#undef VARARGS
#undef VASTART
#undef VAEND

/* Prints the data
 * Returns the amount of printed characters if successful or -1 on error
 */
int libnotify_fprint_data(
     FILE *stream,
     const uint8_t *data,
     size_t data_size )
{
	size_t byte_iterator  = 0;
	size_t data_iterator  = 0;
	int print_count       = 0;
	int total_print_count = 0;

	if( stream == NULL )
	{
		return( -1 );
	}
	if( data == NULL )
	{
		return( -1 );
	}
	if( libnotify_stream != NULL )
	{
		while( data_iterator < data_size )
		{
			while( byte_iterator < data_size )
			{
				if( byte_iterator % 16 == 0 )
				{
					print_count = libnotify_fprintf(
					               stream,
					               "%.8" PRIzx ": ",
					               byte_iterator );

					/* TODO check return value */

					total_print_count += print_count;
				}
				print_count = libnotify_fprintf(
				               stream,
				               "%.2" PRIx8 " ",
				               data[ byte_iterator++ ] );

				/* TODO check return value */

				total_print_count += print_count;

				if( byte_iterator % 16 == 0 )
				{
					break;
				}
				else if( byte_iterator % 8 == 0 )
				{
					print_count = libnotify_fprintf(
					               stream,
					               " " );

					/* TODO check return value */

					total_print_count += print_count;
				}
			}
			while( byte_iterator % 16 != 0 )
			{
				byte_iterator++;

				print_count = libnotify_fprintf(
				               stream,
				               "   " );

				/* TODO check return value */

				total_print_count += print_count;

				if( ( byte_iterator % 8 == 0 )
				 && ( byte_iterator % 16 != 0 ) )
				{
					print_count = libnotify_fprintf(
					               stream,
					               " " );

					/* TODO check return value */

					total_print_count += print_count;
				}
			}
			print_count = libnotify_fprintf(
			               stream,
			               "  " );

			/* TODO check return value */

			total_print_count += print_count;

			byte_iterator = data_iterator;

			while( byte_iterator < data_size )
			{
				if( ( data[ byte_iterator ] >= 0x20 )
				 && ( data[ byte_iterator ] <= 0x7e ) )
				{
					print_count = libnotify_fprintf(
					               stream,
					               "%c",
					               (char) data[ byte_iterator ] );
				}
				else
				{
					print_count = libnotify_fprintf(
					               stream,
					               "." );
				}
				/* TODO check return value */

				total_print_count += print_count;

				byte_iterator++;

				if( byte_iterator % 16 == 0 )
				{
					break;
				}
				else if( byte_iterator % 8 == 0 )
				{
					print_count = libnotify_fprintf(
					               stream,
					               " " );

					/* TODO check return value */

					total_print_count += print_count;
				}
			}
			print_count = libnotify_fprintf(
			               stream,
			               "\n" );

			/* TODO check return value */

			total_print_count += print_count;

			data_iterator = byte_iterator;
		}
		print_count = libnotify_fprintf(
		               stream,
		               "\n" );

		/* TODO check return value */

		total_print_count += print_count;
	}
	return( total_print_count );
}

/* Prints the backtrace of the error
 * Returns the amount of printed characters if successful or -1 on error
 */
int libnotify_fprint_error_backtrace(
     FILE *stream,
     liberror_error_t *error )
{
	if( stream == NULL )
	{
		return( -1 );
	}
	return( liberror_error_backtrace_fprint(
	         error,
	         stream ) );
}

