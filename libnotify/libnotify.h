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

#if !defined( _LIBNOTIFY_H )
#define _LIBNOTIFY_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern int libnotify_verbose;

extern FILE *libnotify_stream;

void libnotify_set_verbose(
      int verbose );

int libnotify_set_stream(
     FILE *stream,
     liberror_error_t **error );

int libnotify_stream_open(
     const char *filename,
     liberror_error_t **error );

int libnotify_stream_close(
     liberror_error_t **error );

int libnotify_fprintf(
     FILE *stream,
     const char *format,
     ... );

#define libnotify_verbose_fprintf( ... ) \
	if( libnotify_verbose != 0 ) \
		libnotify_fprintf( __VA_ARGS__ )

#define libnotify_printf( ... ) \
	libnotify_fprintf( libnotify_stream, __VA_ARGS__ )

#define libnotify_verbose_printf( ... ) \
	if( libnotify_verbose != 0 ) \
		libnotify_fprintf( libnotify_stream, __VA_ARGS__ )

int libnotify_fprint_data(
     FILE *stream,
     const uint8_t *data,
     size_t data_size );

#define libnotify_verbose_fprint_data( stream, data, data_size ) \
	if( libnotify_verbose != 0 ) \
		libnotify_fprint_data( stream, data, data_size )

#define libnotify_verbose_print_data( data, data_size ) \
	if( libnotify_verbose != 0 ) \
		libnotify_fprint_data( libnotify_stream, data, data_size )

int libnotify_fprint_error_backtrace(
     FILE *stream,
     liberror_error_t *error );

#define libnotify_print_error_backtrace( error ) \
	libnotify_fprint_error_backtrace( libnotify_stream, error )

#if defined( __cplusplus )
}
#endif

#endif

