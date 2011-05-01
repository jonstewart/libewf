/*
 * GetOpt functions
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "libsystem_getopt.h"
#include "libsystem_notify.h"
#include "libsystem_string.h"

#if !defined( HAVE_GETOPT )

/* The current option argument
 */
libsystem_character_t *optarg = NULL;

/* The option index
 * Start with argument 1 (argument 0 is the program name)
 */
int optind = 1;

/* Value to indicate the current option
 */
libsystem_integer_t optopt = 0;

/* Get the program options
 * Function for platforms that do not have the getopt function
 * Returns the option character processed, or -1 on error,
 * ? if the option was not in the options string, : if the option argument was missing
 */
libsystem_integer_t libsystem_getopt(
                     int argument_count,
                     libsystem_character_t * const argument_values[],
                     const libsystem_character_t *options_string )
{
	libsystem_character_t *option_value   = NULL;
	libsystem_character_t *argument_value = NULL;
	static char *function                 = "libsystem_getopt";

	if( optind >= argument_count )
	{
		return( (libsystem_integer_t) -1 );
	}
	argument_value = argument_values[ optind ];

	/* Check if the argument value is not an empty string
	 */
	if( *argument_value == (libsystem_character_t) '\0' )
	{
		return( (libsystem_integer_t) -1 );
	}
	/* Check if the first character is a option marker '-'
	 */
	if( *argument_value != (libsystem_character_t) '-' )
	{
		return( (libsystem_integer_t) -1 );
	}
	argument_value++;

	/* Check if long options are provided '--'
	 */
	if( *argument_value == (libsystem_character_t) '-' )
	{
		optind++;

		return( (libsystem_integer_t) -1 );
	}
	optopt       = *argument_value;
	option_value = libsystem_string_search(
	                options_string,
	                optopt,
	                libsystem_string_length(
	                 options_string ) );

	argument_value++;

	/* Check if an argument was specified or that the option was not found
	 * in the option string
	 */
	if( ( optopt == (libsystem_integer_t) ':' )
	 || ( option_value == NULL ) )
	{
		if( *argument_value == (libsystem_character_t) '\0' )
		{
			optind++;
		}
		if( ( *options_string != (libsystem_character_t) ':' )
		 && ( optopt != (libsystem_integer_t) '?' ) )
		{
			libsystem_notify_printf(
			 "%s: no such option: %" PRIc_LIBSYSTEM ".\n",
			 function,
			 optopt );
		}
		return( (libsystem_integer_t) '?' );
	}
	option_value++;

	/* Check if no option argument is required
	 */
	if( *option_value != (libsystem_character_t) ':' )
	{
		optarg = NULL;

		if( *argument_value == (libsystem_character_t) '\0' )
		{
			optind++;
		}
	}
	/* Check if the argument is right after the option flag with no space in between
	 */
	else if( *argument_value != (libsystem_character_t) '\0' )
	{
		optarg = argument_value;

		optind++;
	}
	else
	{
		optind++;

		/* Check if the argument was provided as the next argument value
		 */
		if( argument_count <= optind )
		{
			if( *option_value == ':' )
			{
				return( (libsystem_integer_t) ':' );
			}
			libsystem_notify_printf(
			 "%s: option: %" PRIc_LIBSYSTEM " requires an argument.\n",
			 function,
			 optopt );

			return( (libsystem_integer_t) '?' );
		}
		optarg = argument_values[ optind ];

		optind++;
	}
	return( optopt );
}

#endif

