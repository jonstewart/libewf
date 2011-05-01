/*
 * Notification functions
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

#if !defined( _LIBSYSTEM_NOTIFY_H )
#define _LIBSYSTEM_NOTIFY_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern int libsystem_notify_verbose;

extern FILE *libsystem_notify_stream;

void libsystem_notify_set_verbose(
      int verbose );

int libsystem_notify_set_stream(
     FILE *stream,
     liberror_error_t **error );

int libsystem_notify_stream_open(
     const char *filename,
     liberror_error_t **error );

int libsystem_notify_stream_close(
     liberror_error_t **error );

int libsystem_notify_fprintf(
     FILE *stream,
     const char *format,
     ... );

#define libsystem_notify_verbose_fprintf( ... ) \
	if( libsystem_notify_verbose != 0 ) \
		libsystem_notify_fprintf( __VA_ARGS__ )

#define libsystem_notify_printf( ... ) \
	libsystem_notify_fprintf( libsystem_notify_stream, __VA_ARGS__ )

#define libsystem_notify_verbose_printf( ... ) \
	if( libsystem_notify_verbose != 0 ) \
		libsystem_notify_fprintf( libsystem_notify_stream, __VA_ARGS__ )

int libsystem_notify_fprint_data(
     FILE *stream,
     const uint8_t *data,
     size_t data_size );

#define libsystem_notify_verbose_fprint_data( stream, data, data_size ) \
	if( libsystem_notify_verbose != 0 ) \
		libsystem_notify_fprint_data( stream, data, data_size )

#define libsystem_notify_verbose_print_data( data, data_size ) \
	if( libsystem_notify_verbose != 0 ) \
		libsystem_notify_fprint_data( libsystem_notify_stream, data, data_size )

int libsystem_notify_fprint_error_backtrace(
     FILE *stream,
     liberror_error_t *error );

#define libsystem_notify_print_error_backtrace( error ) \
	libsystem_notify_fprint_error_backtrace( libsystem_notify_stream, error )

#if defined( __cplusplus )
}
#endif

#endif

