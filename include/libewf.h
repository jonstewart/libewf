/*
 * Library for the Expert Witness Compression Format Support (EWF)
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

#if !defined( _LIBEWF_H )
#define _LIBEWF_H

#include <libewf/codepage.h>
#include <libewf/definitions.h>
#include <libewf/error.h>
#include <libewf/extern.h>
#include <libewf/features.h>
#include <libewf/types.h>

#if 1 || defined( HAVE_V1_API )
#include <libewf/handle.h>
#endif

#include <stdio.h>

#if defined( LIBEWF_HAVE_BFIO )
#include <libbfio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBEWF_EXTERN const char *libewf_get_version(
                           void );

/* Returns the flags for reading
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_read(
                       void );

/* Returns the flags for reading and writing
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_read_write(
                       void );

/* Returns the flags for writing
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_write(
                       void );

/* Returns the flags for resume writing
 */
LIBEWF_EXTERN uint8_t libewf_get_flags_write_resume(
                       void );

/* Determines if a file is an EWF file (check for the EWF file signature)
 * Returns 1 if true, 0 if not or -1 on error
 */
#if 0 || defined( HAVE_V2_API )
LIBEWF_EXTERN int libewf_check_file_signature(
                   const char *filename,
                   libewf_error_t **error );
#else
LIBEWF_EXTERN int libewf_check_file_signature(
                   const char *filename );
#endif

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Determines if a file is an EWF file (check for the EWF file signature)
 * Returns 1 if true, 0 if not or -1 on error
 */
#if 0 || defined( HAVE_V2_API )
LIBEWF_EXTERN int libewf_check_file_signature_wide(
                   const wchar_t *filename,
                   libewf_error_t **error );
#else
LIBEWF_EXTERN int libewf_check_file_signature_wide(
                   const wchar_t *filename );
#endif
#endif

#if 0 || defined( HAVE_V2_API )
#if defined( LIBEWF_HAVE_BFIO )
/* Determines if a file is an EWF file (check for the EWF file signature) using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBEWF_EXTERN int libewf_check_file_signature_file_io_handle(
                   libbfio_handle_t *file_io_handle,
                   libewf_error_t **error );
#endif
#endif

/* Globs the segment files according to the EWF naming schema
 * if the format is known the filename should contain the base of the filename
 * otherwise the function will try to determine the format based on the extension
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_V2_API )
LIBEWF_EXTERN int libewf_glob(
                   const char *filename,
                   size_t filename_length,
                   uint8_t format,
                   char **filenames[],
                   int *amount_of_filenames,
                   libewf_error_t **error );
#else
/* Globs the segment files according to the EWF naming schema
 * if the format is known the filename should contain the base of the filename
 * otherwise the function will try to determine the format based on the extension
 * Returns the amount of filenames if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_glob(
                   const char *filename,
                   size_t filename_length,
                   uint8_t format,
                   char **filenames[] );
#endif

#if 0 || defined( HAVE_V2_API )
/* Frees the globbed filenames
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_glob_free(
                   char *filenames[],
                   int amount_of_filenames,
                   libewf_error_t **error );
#endif

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Globs the segment files according to the EWF naming schema
 * if the format is known the filename should contain the base of the filename
 * otherwise the function will try to determine the format based on the extension
 * Returns 1 if successful or -1 on error
 */
#if 0 || defined( HAVE_V2_API )
LIBEWF_EXTERN int libewf_glob_wide(
                   const wchar_t *filename,
                   size_t filename_length,
                   uint8_t format,
                   wchar_t **filenames[],
                   int *amount_of_filenames,
                   libewf_error_t **error );
#else
/* Globs the segment files according to the EWF naming schema
 * if the format is known the filename should contain the base of the filename
 * otherwise the function will try to determine the format based on the extension
 * Returns the amount of filenames if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_glob_wide(
                   const wchar_t *filename,
                   size_t filename_length,
                   uint8_t format,
                   wchar_t **filenames[] );
#endif

#if 0 || defined( HAVE_V2_API )
/* Frees the globbed filenames
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_glob_free(
                   char *filenames[],
                   int amount_of_filenames,
                   libewf_error_t **error );
#endif
#endif

/* -------------------------------------------------------------------------
 * Notify functions (APIv1)
 * ------------------------------------------------------------------------- */

#if 1 || defined( HAVE_V1_API )

/* Set the notify values
 */
LIBEWF_EXTERN void libewf_set_notify_values(
                    FILE *stream,
                    uint8_t verbose );

#endif

/* -------------------------------------------------------------------------
 * Notify functions (APIv2)
 * ------------------------------------------------------------------------- */

#if 0 || defined( HAVE_V2_API )

/* Set the verbose notification
 */
LIBEWF_EXTERN void libewf_notify_set_verbose(
                    int verbose );

/* Set the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_notify_set_stream(
                   FILE *stream,
                   libewf_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_notify_stream_open(
                   const char *filename,
                   libewf_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_notify_stream_close(
                   libewf_error_t **error );

#endif

/* -------------------------------------------------------------------------
 * Error functions (APIv2)
 * ------------------------------------------------------------------------- */

#if 0 || defined( HAVE_V2_API )

/* Frees the error including elements
 */
LIBEWF_EXTERN void libewf_error_free(
                    libewf_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_error_fprint(
                   libewf_error_t *error,
                   FILE *stream );

/* Prints a descriptive string of the error to the string
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_error_sprint(
                   libewf_error_t *error,
                   char *string,
                   size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_error_backtrace_fprint(
                   libewf_error_t *error,
                   FILE *stream );

/* Prints a backtrace of the error to the string
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_error_backtrace_sprint(
                   libewf_error_t *error,
                   char *string,
                   size_t size );

#endif

/* -------------------------------------------------------------------------
 * File/Handle functions (APIv1)
 * ------------------------------------------------------------------------- */

#if 1 || defined( HAVE_V1_API )

/* Signals the libewf handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_signal_abort(
                   libewf_handle_t *handle );

/* Opens a set of EWF file(s)
 * For reading files should contain all filenames that make up an EWF image
 * For writing files should contain the base of the filename, extentions like .e01 will be automatically added
 * Returns a pointer to the new instance of handle, NULL on error
 */
LIBEWF_EXTERN libewf_handle_t *libewf_open(
                                char * const filenames[],
                                int amount_of_filenames,
                                uint8_t flags );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Opens a set of EWF file(s)
 * For reading files should contain all filenames that make up an EWF image
 * For writing files should contain the base of the filename, extentions like .e01 will be automatically added
 * Returns a pointer to the new instance of handle, NULL on error
 */
LIBEWF_EXTERN libewf_handle_t *libewf_open_wide(
                                wchar_t * const filenames[],
                                int amount_of_filenames,
                                uint8_t flags );
#endif

/* Closes the EWF handle and frees memory used within the handle
 * Returns 0 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_close(
                   libewf_handle_t *handle );

/* Seeks a certain offset of the media data within the EWF file(s)
 * It will set the related file offset to the specific chunk offset
 * Returns the offset if seek is successful or -1 on error
 */
LIBEWF_EXTERN off64_t libewf_seek_offset(
                       libewf_handle_t *handle,
                       off64_t offset );

/* Retrieves the current offset of the media data within the EWF file(s)
 * Returns the offset if successful or -1 on error
 */
LIBEWF_EXTERN off64_t libewf_get_offset(
                       libewf_handle_t *handle );

/* Prepares a buffer with chunk data after reading it according to the handle settings
 * intended for raw read
 * The buffer size cannot be larger than the chunk size
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_read_prepare_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       void *uncompressed_buffer,
                       size_t *uncompressed_buffer_size,
                       int8_t is_compressed,
                       uint32_t chunk_crc,
                       int8_t read_crc );

/* Reads 'raw' data from the curent offset into a buffer
 * size contains the size of the buffer
 * The function sets the chunk crc, is compressed and read crc values
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_read_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       int8_t *is_compressed,
                       uint32_t *chunk_crc,
                       int8_t *read_crc );

/* Reads data from the curent offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_read_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size );

/* Reads media data from an offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_read_random(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       off64_t offset );

/* Prepares a buffer with chunk data before writing according to the handle settings
 * intended for raw write
 * The buffer size cannot be larger than the chunk size
 * The function sets the chunk crc, is compressed and write crc values
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_write_prepare_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       void *compressed_buffer,
                       size_t *compressed_buffer_size,
                       int8_t *is_compressed,
                       uint32_t *chunk_crc,
                       int8_t *write_crc );

/* Writes 'raw' data in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * size contains the size of the data within the buffer while
 * data size contains the size of the actual input data
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_raw_write_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       size_t data_size,
                       int8_t is_compressed,
                       uint32_t chunk_crc,
                       int8_t write_crc );

/* Writes data in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size );

/* Writes data in EWF format from a buffer at an specific offset,
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_random(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       off64_t offset );

/* Finalizes the write by correcting the EWF the meta data in the segment files
 * This function is required after writing from stream
 * Returns the amount of input bytes written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_write_finalize(
                       libewf_handle_t *handle );

/* Retrieves the segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_segment_filename(
                   libewf_handle_t *handle,
                   char *filename,
                   size_t filename_size );

/* Sets the segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_segment_filename(
                   libewf_handle_t *handle,
                   const char *filename,
                   size_t filename_length );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Retrieves the segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_segment_filename_wide(
                   libewf_handle_t *handle,
                   wchar_t *filename,
                   size_t filename_size );

/* Sets the segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_segment_filename_wide(
                   libewf_handle_t *handle,
                   const wchar_t *filename,
                   size_t filename_length );
#endif

/* Retrieves the segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t *segment_file_size );

/* Sets the segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t segment_file_size );

/* Retrieves the delta segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_delta_segment_filename(
                   libewf_handle_t *handle,
                   char *filename,
                   size_t filename_size );

/* Sets the delta segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_delta_segment_filename(
                   libewf_handle_t *handle,
                   const char *filename,
                   size_t filename_length );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Retrieves the delta segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_delta_segment_filename_wide(
                   libewf_handle_t *handle,
                   wchar_t *filename,
                   size_t filename_size );

/* Sets the delta segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_delta_segment_filename_wide(
                   libewf_handle_t *handle,
                   const wchar_t *filename,
                   size_t filename_length );
#endif

/* Retrieves the delta segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_delta_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t *delta_segment_file_size );

/* Sets the delta segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_delta_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t delta_segment_file_size );

#endif

/* -------------------------------------------------------------------------
 * File/Handle functions (APIv2)
 * ------------------------------------------------------------------------- */

#if 0 || defined( HAVE_V2_API )

/* Initialize the handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_initialize(
                   libewf_handle_t **handle,
                   libewf_error_t **error );

/* Frees the handle including elements
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_free(
                   libewf_handle_t **handle,
                   libewf_error_t **error );

/* Signals the libewf handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_signal_abort(
                   libewf_handle_t *handle,
                   libewf_error_t **error );

/* Opens a set of EWF file(s)
 * For reading files should contain all filenames that make up an EWF image
 * For writing files should contain the base of the filename, extentions like .e01 will be automatically added
 * Returns a pointer to the new instance of handle, NULL on error
 */
LIBEWF_EXTERN int libewf_handle_open(
                   libewf_handle_t *handle,
                   char * const filenames[],
                   int amount_of_filenames,
                   uint8_t flags,
                   libewf_error_t **error );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Opens a set of EWF file(s)
 * For reading files should contain all filenames that make up an EWF image
 * For writing files should contain the base of the filename, extentions like .e01 will be automatically added
 * Returns a pointer to the new instance of handle, NULL on error
 */
LIBEWF_EXTERN int libewf_handle_open_wide(
                   libewf_handle_t *handle,
                   wchar_t * const filenames[],
                   int amount_of_filenames,
                   uint8_t flags,
                   libewf_error_t **error );
#endif

#if defined( LIBEWF_HAVE_BFIO )
/* Opens a set of EWF file(s) using a Basic File IO (bfio) pool
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_open_file_io_pool(
                   libewf_handle_t *handle,
                   libbfio_pool_t *file_io_pool,
                   uint8_t flags,
                   libewf_error_t **error );
#endif

/* Closes the EWF handle and frees memory used within the handle
 * Returns 0 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_close(
                   libewf_handle_t *handle,
                   libewf_error_t **error );

/* Seeks a certain offset of the media data within the EWF file(s)
 * It will set the related file offset to the specific chunk offset
 * Returns the offset if seek is successful or -1 on error
 */
LIBEWF_EXTERN off64_t libewf_handle_seek_offset(
                       libewf_handle_t *handle,
                       off64_t offset,
                       int whence,
                       libewf_error_t **error );

/* Retrieves the current offset of the media data within the EWF file(s)
 * Returns the offset if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_offset(
                   libewf_handle_t *handle,
                   off64_t *offset,
                   libewf_error_t **error );

/* Prepares chunk data after reading it according to the handle settings
 * This function should be used after libewf_handle_read_chunk
 * The chunk buffer size should contain the actual chunk size
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_prepare_read_chunk(
                       libewf_handle_t *handle,
                       void *chunk_buffer,
                       size_t chunk_buffer_size,
                       void *uncompressed_buffer,
                       size_t *uncompressed_buffer_size,
                       int8_t is_compressed,
                       uint32_t chunk_crc,
                       int8_t read_crc,
                       libewf_error_t **error );

/* Reads a chunk from the curent offset into a buffer
 * size contains the size of the chunk buffer
 * The function sets the chunk crc, is compressed and read crc values
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_read_chunk(
                       libewf_handle_t *handle,
                       void *chunk_buffer,
                       size_t chunk_buffer_size,
                       int8_t *is_compressed,
                       void *crc_buffer,
                       uint32_t *chunk_crc,
                       int8_t *read_crc,
                       libewf_error_t **error );

/* Reads data from the curent offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_read_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       libewf_error_t **error );

/* Reads media data from an offset into a buffer
 * Returns the amount of bytes read or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_read_random(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       off64_t offset,
                       libewf_error_t **error );

/* Prepares a buffer with chunk data before writing according to the handle settings
 * This function should be used before libewf_handle_write_chunk
 * The chunk buffer size should contain the actual chunk size
 * The function sets the chunk crc, is compressed and write crc values
 * Returns the resulting chunk size or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_prepare_write_chunk(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       void *compressed_buffer,
                       size_t *compressed_buffer_size,
                       int8_t *is_compressed,
                       uint32_t *chunk_crc,
                       int8_t *write_crc,
                       libewf_error_t **error );

/* Writes a chunk in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * size contains the size of the data within the buffer while
 * data size contains the size of the actual input data
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_write_chunk(
                       libewf_handle_t *handle,
                       void *chunk_buffer,
                       size_t chunk_buffer_size,
                       size_t data_size,
                       int8_t is_compressed,
                       void *crc_buffer,
                       uint32_t chunk_crc,
                       int8_t write_crc,
                       libewf_error_t **error );

/* Writes data in EWF format from a buffer at the current offset
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_write_buffer(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       libewf_error_t **error );

/* Writes data in EWF format from a buffer at an specific offset,
 * the necessary settings of the write values must have been made
 * Will initialize write if necessary
 * Returns the amount of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_write_random(
                       libewf_handle_t *handle,
                       void *buffer,
                       size_t buffer_size,
                       off64_t offset,
                       libewf_error_t **error );

/* Finalizes the write by correcting the EWF the meta data in the segment files
 * This function is required after writing from stream
 * Returns the amount of input bytes written or -1 on error
 */
LIBEWF_EXTERN ssize_t libewf_handle_write_finalize(
                       libewf_handle_t *handle,
                       libewf_error_t **error );

/* Retrieves the segment filename size
 * The filename size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_segment_filename_size(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_segment_filename(
                   libewf_handle_t *handle,
                   char *filename,
                   size_t filename_size,
                   libewf_error_t **error );

/* Sets the segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_segment_filename(
                   libewf_handle_t *handle,
                   const char *filename,
                   size_t filename_length,
                   libewf_error_t **error );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Retrieves the segment filename size
 * The filename size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_segment_filename_size_wide(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_segment_filename_wide(
                   libewf_handle_t *handle,
                   wchar_t *filename,
                   size_t filename_size,
                   libewf_error_t **error );

/* Sets the segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_segment_filename_wide(
                   libewf_handle_t *handle,
                   const wchar_t *filename,
                   size_t filename_length,
                   libewf_error_t **error );
#endif

/* Retrieves the segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t *segment_file_size,
                   libewf_error_t **error );

/* Sets the segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t segment_file_size,
                   libewf_error_t **error );

/* Retrieves the delta segment filename size
 * The filename size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_delta_segment_filename_size(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the delta segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_delta_segment_filename(
                   libewf_handle_t *handle,
                   char *filename,
                   size_t filename_size,
                   libewf_error_t **error );

/* Sets the delta segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_delta_segment_filename(
                   libewf_handle_t *handle,
                   const char *filename,
                   size_t filename_length,
                   libewf_error_t **error );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Retrieves the delta segment filename size
 * The filename size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_delta_segment_filename_size_wide(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the delta segment filename
 * The filename size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_delta_segment_filename_wide(
                   libewf_handle_t *handle,
                   wchar_t *filename,
                   size_t filename_size,
                   libewf_error_t **error );

/* Sets the delta segment filename
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_delta_segment_filename_wide(
                   libewf_handle_t *handle,
                   const wchar_t *filename,
                   size_t filename_length,
                   libewf_error_t **error );
#endif

/* Retrieves the delta segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_delta_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t *delta_segment_file_size,
                   libewf_error_t **error );

/* Sets the delta segment file size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_delta_segment_file_size(
                   libewf_handle_t *handle,
                   size64_t delta_segment_file_size,
                   libewf_error_t **error );

/* Retrieves the filename size of the (delta) segment file of the current chunk
 * The filename size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_filename_size(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the filename of the (delta) segment file of the current chunk
 * The filename size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_filename(
                   libewf_handle_t *handle,
                   char *filename,
                   size_t filename_size,
                   libewf_error_t **error );

#if defined( LIBEWF_HAVE_WIDE_CHARACTER_TYPE )
/* Retrieves the filename size of the (delta) segment file of the current chunk
 * The filename size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_filename_size_wide(
                   libewf_handle_t *handle,
                   size_t *filename_size,
                   libewf_error_t **error );

/* Retrieves the filename of the (delta) segment file of the current chunk
 * The filename size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_filename_wide(
                   libewf_handle_t *handle,
                   wchar_t *filename,
                   size_t filename_size,
                   libewf_error_t **error );
#endif

#if defined( LIBEWF_HAVE_BFIO )
/* Retrieves the file io handle of the (delta) segment file of the current chunk
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_file_io_handle(
                   libewf_handle_t *handle,
                   libbfio_handle_t **file_io_handle,
                   libewf_error_t **error );
#endif

#endif

/* -------------------------------------------------------------------------
 * Meta data functions (APIv1)
 * ------------------------------------------------------------------------- */

#if 1 || defined( HAVE_V1_API )

/* Retrieves the amount of sectors per chunk from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t *sectors_per_chunk );

/* Sets the amount of sectors per chunk in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t sectors_per_chunk );

/* Retrieves the amount of bytes per sector from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t *bytes_per_sector );

/* Sets the amount of bytes per sector in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t bytes_per_sector );

/* Retrieves the amount of sectors from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_sectors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_sectors );

/* Retrieves the chunk size from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_chunk_size(
                   libewf_handle_t *handle,
                   size32_t *chunk_size );

/* Retrieves the error granularity from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t *error_granularity );

/* Sets the error granularity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t error_granularity );

/* Retrieves the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_compression_values(
                   libewf_handle_t *handle,
                   int8_t *compression_level,
                   uint8_t *compress_empty_block );

/* Sets the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_compression_values(
                   libewf_handle_t *handle,
                   int8_t compression_level,
                   uint8_t compress_empty_block );

/* Retrieves the size of the contained media data
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_size(
                   libewf_handle_t *handle,
                   size64_t *media_size );

/* Sets the media size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_media_size(
                   libewf_handle_t *handle,
                   size64_t media_size );

/* Retrieves the media type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_type(
                   libewf_handle_t *handle,
                   uint8_t *media_type );

/* Sets the media type
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_media_type(
                   libewf_handle_t *handle,
                   uint8_t media_type );

/* Retrieves the media flags
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_media_flags(
                   libewf_handle_t *handle,
                   uint8_t *media_flags );

/* Sets the media flags
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_media_flags(
                   libewf_handle_t *handle,
                   uint8_t media_flags );

/* Retrieves the volume type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_volume_type(
                   libewf_handle_t *handle,
                   uint8_t *volume_type );

/* Sets the volume type
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_volume_type(
                   libewf_handle_t *handle,
                   uint8_t volume_type );

/* Retrieves the format type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_format(
                   libewf_handle_t *handle,
                   uint8_t *format );

/* Sets the output format
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_format(
                   libewf_handle_t *handle,
                   uint8_t format );

/* Retrieves the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size );

/* Sets the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size );

/* Retrieves the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size );

/* Sets the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_set_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size );

/* Retrieves the SHA1 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_sha1_hash(
                   libewf_handle_t *handle,
                   uint8_t *sha1_hash,
                   size_t size );

/* Sets the SHA1 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_set_sha1_hash(
                   libewf_handle_t *handle,
                   uint8_t *sha1_hash,
                   size_t size );

/* Retrieves the amount of chunks written
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_write_amount_of_chunks(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_chunks );

/* Sets the read wipe chunk on error
 * The chunk is not wiped if read raw is used
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_read_wipe_chunk_on_error(
                   libewf_handle_t *handle,
                   uint8_t wipe_on_error );

/* Copies the media values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_copy_media_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle );

/* Retrieves the amount of acquiry errors
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_acquiry_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors );

/* Retrieves the information of an acquiry error
 * Returns 1 if successful, 0 if no acquiry error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_acquiry_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Add an acquiry error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_acquiry_error(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Retrieves the amount of CRC errors
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_crc_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors );

/* Retrieves the information of a CRC error
 * Returns 1 if successful, 0 if no CRC error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_crc_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Add a CRC error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_crc_error(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Retrieves the amount of sessions
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_sessions(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_sessions );

/* Retrieves the information of a session
 * Returns 1 if successful, 0 if no sessions could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_get_session(
                   libewf_handle_t *handle,
                   uint32_t index,
                   off64_t *first_sector,
                   uint32_t *amount_of_sectors );

/* Add a session
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_add_session(
                   libewf_handle_t *handle,
                   off64_t first_sector,
                   uint32_t amount_of_sectors );

/* Retrieves the header codepage
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_get_header_codepage(
                   libewf_handle_t *handle,
                   int *header_codepage );

/* Sets the header codepage
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_header_codepage(
                   libewf_handle_t *handle,
                   int header_codepage );

/* Retrieves the amount of header values
 * Returns 1 if successful, 0 if no header values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_header_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values );

/* Retrieves the header value identifier size specified by its index
 * The identifier size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_header_value_identifier_size(
                   libewf_handle_t *handle,
                   uint32_t index,
                   size_t *identifier_size );

/* Retrieves the header value identifier specified by its index
 * The strings are encoded in UTF-8
 * The identifier size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_header_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   char *identifier,
                   size_t identifier_size );

/* Retrieves the header value size specified by the identifier
 * The value size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_header_value_size(
                   libewf_handle_t *handle,
                   const char *identifier,
                   size_t *value_size );

/* Retrieves the header value specified by the identifier
 * The strings are encoded in UTF-8
 * The value size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_header_value(
                   libewf_handle_t *handle,
                   const char *identifier,
                   char *value,
                   size_t value_size );

/* Retrieves the header value case number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_case_number( handle, value, value_size ) \
        libewf_get_header_value( handle, "case_number", value, value_size )

/* Retrieves the header value description
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_description( handle, value, value_size ) \
        libewf_get_header_value( handle, "description", value, value_size )

/* Retrieves the header value examiner name
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_examiner_name( handle, value, value_size ) \
        libewf_get_header_value( handle, "examiner_name", value, value_size )

/* Retrieves the header value evidence number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_evidence_number( handle, value, value_size ) \
        libewf_get_header_value( handle, "evidence_number", value, value_size )

/* Retrieves the header value notes
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_notes( handle, value, value_size ) \
        libewf_get_header_value( handle, "notes", value, value_size )

/* Retrieves the header value acquiry date
 * The string is formatted according to the date format
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_acquiry_date( handle, value, value_size ) \
        libewf_get_header_value( handle, "acquiry_date", value, value_size )

/* Retrieves the header value system date
 * The string is formatted according to the date format
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_system_date( handle, value, value_size ) \
        libewf_get_header_value( handle, "system_date", value, value_size )

/* Retrieves the header value acquiry operating system
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_acquiry_operating_system( handle, value, value_size ) \
        libewf_get_header_value( handle, "acquiry_operating_system", value, value_size )

/* Retrieves the header value acquiry software version
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_acquiry_software_version( handle, value, value_size ) \
        libewf_get_header_value( handle, "acquiry_software_version", value, value_size )

/* Retrieves the header value password
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_password( handle, value, value_size ) \
        libewf_get_header_value( handle, "password", value, value_size )

/* Retrieves the header value compression type
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_compression_type( handle, value, value_size ) \
        libewf_get_header_value( handle, "compression_type", value, value_size )

/* Retrieves the header value model
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_model( handle, value, value_size ) \
        libewf_get_header_value( handle, "model", value, value_size )

/* Retrieves the header value serial number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_header_value_serial_number( handle, value, value_size ) \
        libewf_get_header_value( handle, "serial_number", value, value_size )

/* Sets the header value specified by the identifier
 * The strings are encoded in UTF-8
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_header_value(
                   libewf_handle_t *handle,
                   const char *identifier,
                   const char *value,
                   size_t value_length );

/* Sets the header value case number
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_case_number( handle, value, value_length ) \
        libewf_set_header_value( handle, "case_number", value, value_length )

/* Sets the header value description
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_description( handle, value, value_length ) \
        libewf_set_header_value( handle, "description", value, value_length )

/* Sets the header value examiner name
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_examiner_name( handle, value, value_length ) \
        libewf_set_header_value( handle, "examiner_name", value, value_length )

/* Sets the header value evidence number
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_evidence_number( handle, value, value_length ) \
        libewf_set_header_value( handle, "evidence_number", value, value_length )

/* Sets the header value notes
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_notes( handle, value, value_length ) \
        libewf_set_header_value( handle, "notes", value, value_length )

/* Sets the header value acquiry date
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_acquiry_date( handle, value, value_length ) \
        libewf_set_header_value( handle, "acquiry_date", value, value_length )

/* Sets the header value system date
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_system_date( handle, value, value_length ) \
        libewf_set_header_value( handle, "system_date", value, value_length )

/* Sets the header value acquiry operating system
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_acquiry_operating_system( handle, value, value_length ) \
        libewf_set_header_value( handle, "acquiry_operating_system", value, value_length )

/* Sets the header value acquiry software version
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_acquiry_software_version( handle, value, value_length ) \
        libewf_set_header_value( handle, "acquiry_software_version", value, value_length )

/* Sets the header value password
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_password( handle, value, value_length ) \
        libewf_set_header_value( handle, "password", value, value_length )

/* Sets the header value compression type
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_compression_type( handle, value, value_length ) \
        libewf_set_header_value( handle, "compression_type", value, value_length )

/* Sets the header value model
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_model( handle, value, value_length ) \
        libewf_set_header_value( handle, "model", value, value_length )

/* Sets the header value serial number
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_header_value_serial_number( handle, value, value_length ) \
        libewf_set_header_value( handle, "serial_number", value, value_length )

/* Parses the header values from the xheader, header2 or header section
 * Will parse the first available header in order mentioned above
 * Returns 1 if successful, 0 if already parsed or -1 on error
 */
LIBEWF_EXTERN int libewf_parse_header_values(
                   libewf_handle_t *handle,
                   uint8_t date_format );

/* Copies the header values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_copy_header_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle );

/* Retrieves the amount of hash values
 * Returns 1 if successful, 0 if no hash values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_amount_of_hash_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values );

/* Retrieves the hash value identifier size specified by its index
 * The identifier size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_hash_value_identifier_size(
                   libewf_handle_t *handle,
                   uint32_t index,
                   size_t *identifier_size );

/* Retrieves the hash value identifier specified by its index
 * The strings are encoded in UTF-8
 * The identifier size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_hash_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   char *identifier,
                   size_t identifier_size );

/* Retrieves the hash value size specified by the identifier
 * The value size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_hash_value_size(
                   libewf_handle_t *handle,
                   const char *identifier,
                   size_t *value_size );

/* Retrieves the hash value specified by the identifier
 * The strings are encoded in UTF-8
 * The value size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_get_hash_value(
                   libewf_handle_t *handle,
                   const char *identifier,
                   char *value,
                   size_t value_size );

/* Retrieves the hash value MD5
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_hash_value_md5( handle, value, value_size ) \
        libewf_get_hash_value( handle, "MD5", value, value_size )

/* Retrieves the hash value SHA1
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_get_hash_value_sha1( handle, value, value_size ) \
        libewf_get_hash_value( handle, "SHA1", value, value_size )

/* Sets the hash value specified by the identifier
 * The strings are encoded in UTF-8
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_set_hash_value(
                   libewf_handle_t *handle,
                   const char *identifier,
                   const char *value,
                   size_t value_length );

/* Sets the hash value MD5
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_hash_value_md5( handle, value, value_length ) \
        libewf_set_hash_value( handle, "MD5", value, value_length )

/* Sets the hash value SHA1
 * Returns 1 if successful or -1 on error
 */
#define libewf_set_hash_value_sha1( handle, value, value_length ) \
        libewf_set_hash_value( handle, "SHA1", value, value_length )

/* Parses the hash values from the xhash section
 * Returns 1 if successful, 0 if already parsed or -1 on error
 */
LIBEWF_EXTERN int libewf_parse_hash_values(
                   libewf_handle_t *handle );

#endif

/* -------------------------------------------------------------------------
 * Meta data functions (APIv2)
 * ------------------------------------------------------------------------- */

#if 0 || defined( HAVE_V2_API )

/* Retrieves the amount of sectors per chunk from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t *sectors_per_chunk,
                   libewf_error_t **error );

/* Sets the amount of sectors per chunk in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_sectors_per_chunk(
                   libewf_handle_t *handle,
                   uint32_t sectors_per_chunk,
                   libewf_error_t **error );

/* Retrieves the amount of bytes per sector from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t *bytes_per_sector,
                   libewf_error_t **error );

/* Sets the amount of bytes per sector in the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_bytes_per_sector(
                   libewf_handle_t *handle,
                   uint32_t bytes_per_sector,
                   libewf_error_t **error );

/* Retrieves the amount of sectors from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_sectors(
                   libewf_handle_t *handle,
                   uint64_t *amount_of_sectors,
                   libewf_error_t **error );

/* Retrieves the chunk size from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_chunk_size(
                   libewf_handle_t *handle,
                   size32_t *chunk_size,
                   libewf_error_t **error );

/* Retrieves the error granularity from the media information
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t *error_granularity,
                   libewf_error_t **error );

/* Sets the error granularity
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_error_granularity(
                   libewf_handle_t *handle,
                   uint32_t error_granularity,
                   libewf_error_t **error );

/* Retrieves the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_compression_values(
                   libewf_handle_t *handle,
                   int8_t *compression_level,
                   uint8_t *compression_flags,
                   libewf_error_t **error );

/* Sets the compression values
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_compression_values(
                   libewf_handle_t *handle,
                   int8_t compression_level,
                   uint8_t compression_flags,
                   libewf_error_t **error );

/* Retrieves the size of the contained media data
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_media_size(
                   libewf_handle_t *handle,
                   size64_t *media_size,
                   libewf_error_t **error );

/* Sets the media size
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_media_size(
                   libewf_handle_t *handle,
                   size64_t media_size,
                   libewf_error_t **error );

/* Retrieves the media type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_media_type(
                   libewf_handle_t *handle,
                   uint8_t *media_type,
                   libewf_error_t **error );

/* Sets the media type
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_media_type(
                   libewf_handle_t *handle,
                   uint8_t media_type,
                   libewf_error_t **error );

/* Retrieves the media flags
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_media_flags(
                   libewf_handle_t *handle,
                   uint8_t *media_flags,
                   libewf_error_t **error );

/* Sets the media flags
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_media_flags(
                   libewf_handle_t *handle,
                   uint8_t media_flags,
                   libewf_error_t **error );

/* Retrieves the format type value
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_format(
                   libewf_handle_t *handle,
                   uint8_t *format,
                   libewf_error_t **error );

/* Sets the output format
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_format(
                   libewf_handle_t *handle,
                   uint8_t format,
                   libewf_error_t **error );

/* Retrieves the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size,
                   libewf_error_t **error );

/* Sets the GUID
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_guid(
                   libewf_handle_t *handle,
                   uint8_t *guid,
                   size_t size,
                   libewf_error_t **error );

/* Retrieves the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size,
                   libewf_error_t **error );

/* Sets the MD5 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_md5_hash(
                   libewf_handle_t *handle,
                   uint8_t *md5_hash,
                   size_t size,
                   libewf_error_t **error );

/* Retrieves the SHA1 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_sha1_hash(
                   libewf_handle_t *handle,
                   uint8_t *sha1_hash,
                   size_t size,
                   libewf_error_t **error );

/* Sets the SHA1 hash
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_sha1_hash(
                   libewf_handle_t *handle,
                   uint8_t *sha1_hash,
                   size_t size,
                   libewf_error_t **error );

/* Retrieves the amount of chunks written
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_write_amount_of_chunks(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_chunks,
                   libewf_error_t **error );

/* Sets the read wipe chunk on error
 * The chunk is not wiped if read raw is used
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_read_wipe_chunk_on_error(
                   libewf_handle_t *handle,
                   uint8_t wipe_on_error,
                   libewf_error_t **error );

/* Copies the media values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_copy_media_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle,
                   libewf_error_t **error );

/* Retrieves the amount of acquiry errors
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_acquiry_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors,
                   libewf_error_t **error );

/* Retrieves the information of an acquiry error
 * Returns 1 if successful, 0 if no acquiry error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_acquiry_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   uint64_t *first_sector,
                   uint64_t *amount_of_sectors,
                   libewf_error_t **error );

/* Add an acquiry error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_add_acquiry_error(
                   libewf_handle_t *handle,
                   uint64_t first_sector,
                   uint64_t amount_of_sectors,
                   libewf_error_t **error );

/* Retrieves the amount of CRC errors
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_crc_errors(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_errors,
                   libewf_error_t **error );

/* Retrieves the information of a CRC error
 * Returns 1 if successful, 0 if no CRC error could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_crc_error(
                   libewf_handle_t *handle,
                   uint32_t index,
                   uint64_t *first_sector,
                   uint64_t *amount_of_sectors,
                   libewf_error_t **error );

/* Add a CRC error
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_add_crc_error(
                   libewf_handle_t *handle,
                   uint64_t first_sector,
                   uint64_t amount_of_sectors,
                   libewf_error_t **error );

/* Retrieves the amount of sessions
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_sessions(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_sessions,
                   libewf_error_t **error );

/* Retrieves the information of a session
 * Returns 1 if successful, 0 if no sessions could be found or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_session(
                   libewf_handle_t *handle,
                   uint32_t index,
                   uint64_t *first_sector,
                   uint64_t *amount_of_sectors,
                   libewf_error_t **error );

/* Add a session
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_add_session(
                   libewf_handle_t *handle,
                   uint64_t first_sector,
                   uint64_t amount_of_sectors,
                   libewf_error_t **error );

/* Retrieves the header codepage
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_codepage(
                   libewf_handle_t *handle,
                   int *header_codepage,
                   libewf_error_t **error );

/* Sets the header codepage
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_header_codepage(
                   libewf_handle_t *handle,
                   int header_codepage,
                   libewf_error_t **error );

/* Retrieves the header values date format
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_values_date_format(
                   libewf_handle_t *handle,
                   int *date_format,
                   libewf_error_t **error );

/* Sets the header values date format
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_header_values_date_format(
                   libewf_handle_t *handle,
                   int date_format,
                   libewf_error_t **error );

/* Retrieves the amount of header values
 * Returns 1 if successful, 0 if no header values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_header_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values,
                   libewf_error_t **error );

/* Retrieves the header value identifier size specified by its index
 * The identifier size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_value_identifier_size(
                   libewf_handle_t *handle,
                   uint32_t index,
                   size_t *identifier_size,
                   libewf_error_t **error );

/* Retrieves the header value identifier specified by its index
 * The strings are encoded in UTF-8
 * The identifier size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   uint8_t *identifier,
                   size_t identifier_size,
                   libewf_error_t **error );

/* Retrieves the header value size specified by the identifier
 * The value size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_value_size(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   size_t *value_size,
                   libewf_error_t **error );

/* Retrieves the header value specified by the identifier
 * The strings are encoded in UTF-8
 * The value size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_header_value(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   uint8_t *value,
                   size_t value_size,
                   libewf_error_t **error );

/* Retrieves the header value case number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_case_number( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "case_number", 11, value, value_size, error )

/* Retrieves the header value description
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_description( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "description", 11, value, value_size, error )

/* Retrieves the header value examiner name
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_examiner_name( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "examiner_name", 13, value, value_size, error )

/* Retrieves the header value evidence number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_evidence_number( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "evidence_number", 15, value, value_size, error )

/* Retrieves the header value notes
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_notes( handle, value, lengt, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "notes", 5, value, value_size, error )

/* Retrieves the header value acquiry date
 * The string is formatted according to the date format
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_acquiry_date( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "acquiry_date", 12, value, value_size, error )

/* Retrieves the header value system date
 * The string is formatted according to the date format
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_system_date( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "system_date", 11, value, value_size, error )

/* Retrieves the header value acquiry operating system
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_acquiry_operating_system( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "acquiry_operating_system", 24, value, value_size, error )

/* Retrieves the header value acquiry software version
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_acquiry_software_version( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "acquiry_software_version", 24, value, value_size, error )

/* Retrieves the header value password
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_password( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "password", 8, value, value_size, error )

/* Retrieves the header value compression type
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_compression_type( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "compression_type", 16, value, value_size, error )

/* Retrieves the header value model
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_model( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "model", 5, value, value_size, error )

/* Retrieves the header value serial number
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_header_value_serial_number( handle, value, value_size, error ) \
        libewf_handle_get_header_value( handle, (uint8_t *) "serial_number", 13, value, value_size, error )

/* Sets the header value specified by the identifier
 * The strings are encoded in UTF-8
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_header_value(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   const uint8_t *value,
                   size_t value_length,
                   libewf_error_t **error );

/* Sets the header value case number
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_case_number( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "case_number", 11, value, value_length, error )

/* Sets the header value description
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_description( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "description", 11, value, value_length, error )

/* Sets the header value examiner name
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_examiner_name( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "examiner_name", 13, value, value_length, error )

/* Sets the header value evidence number
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_evidence_number( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "evidence_number", 15, value, value_length, error )

/* Sets the header value notes
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_notes( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "notes", 5, value, value_length, error )

/* Sets the header value acquiry date
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_acquiry_date( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "acquiry_date", 12, value, value_length, error )

/* Sets the header value system date
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_system_date( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "system_date", 11, value, value_length, error )

/* Sets the header value acquiry operating system
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_acquiry_operating_system( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "acquiry_operating_system", 24, value, value_length, error )

/* Sets the header value acquiry software version
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_acquiry_software_version( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "acquiry_software_version", 24, value, value_length, error )

/* Sets the header value password
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_password( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "password", 8, value, value_length, error )

/* Sets the header value compression type
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_compression_type( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "compression_type", 16, value, value_length, error )

/* Sets the header value model
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_model( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "model", 5, value, value_length, error )

/* Sets the header value serial number
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_header_value_serial_number( handle, value, value_length, error ) \
        libewf_handle_set_header_value( handle, (uint8_t *) "serial_number", 13, value, value_length, error )

/* Copies the header values from the source to the destination handle
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_copy_header_values(
                   libewf_handle_t *destination_handle,
                   libewf_handle_t *source_handle,
                   libewf_error_t **error );

/* Retrieves the amount of hash values
 * Returns 1 if successful, 0 if no hash values are present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_amount_of_hash_values(
                   libewf_handle_t *handle,
                   uint32_t *amount_of_values,
                   libewf_error_t **error );

/* Retrieves the hash value identifier size specified by its index
 * The identifier size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_hash_value_identifier_size(
                   libewf_handle_t *handle,
                   uint32_t index,
                   size_t *identifier_size,
                   libewf_error_t **error );

/* Retrieves the hash value identifier specified by its index
 * The strings are encoded in UTF-8
 * The identifier size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_hash_value_identifier(
                   libewf_handle_t *handle,
                   uint32_t index,
                   uint8_t *identifier,
                   size_t identifier_size,
                   libewf_error_t **error );

/* Retrieves the hash value size specified by the identifier
 * The value size includes the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_hash_value_size(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   size_t *value_size,
                   libewf_error_t **error );

/* Retrieves the hash value specified by the identifier
 * The strings are encoded in UTF-8
 * The value size should include the end of string character
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_get_hash_value(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   uint8_t *value,
                   size_t value_size,
                   libewf_error_t **error );

/* Retrieves the hash value MD5
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_hash_value_md5( handle, value, value_size, error ) \
        libewf_handle_get_hash_value( handle, "MD5", 3, value, value_size, error )

/* Retrieves the hash value SHA1
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
#define libewf_handle_get_hash_value_sha1( handle, value, value_size, error ) \
        libewf_handle_get_hash_value( handle, "SHA1", 4, value, value_size, error )

/* Sets the hash value specified by the identifier
 * The strings are encoded in UTF-8
 * Returns 1 if successful or -1 on error
 */
LIBEWF_EXTERN int libewf_handle_set_hash_value(
                   libewf_handle_t *handle,
                   const uint8_t *identifier,
                   size_t identifier_length,
                   const uint8_t *value,
                   size_t value_length,
                   libewf_error_t **error );

/* Sets the hash value MD5
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_hash_value_md5( handle, value, value_length, error ) \
        libewf_handle_set_hash_value( handle, "MD5", 3, value, value_length, error )

/* Sets the hash value SHA1
 * Returns 1 if successful or -1 on error
 */
#define libewf_handle_set_hash_value_sha1( handle, value, value_length, error ) \
        libewf_handle_set_hash_value( handle, "SHA1", 4, value, value_length, error )

#endif

#ifdef __cplusplus
}
#endif

#endif

