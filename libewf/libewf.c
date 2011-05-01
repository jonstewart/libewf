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

#include <common.h>

#if defined( WINAPI )
#include <windows.h>
#endif

/* Define HAVE_LOCAL_LIBEWF for local use of libewf
 */
#if !defined( HAVE_LOCAL_LIBEWF )

#if defined( WINAPI )

#if defined( _MANAGED )
#pragma managed( push, off )
#endif

/* Defines the entry point for the DLL
 */
BOOL WINAPI DllMain(
             HINSTANCE hinstDLL,
             DWORD fdwReason,
             LPVOID lpvReserved )
{
	switch( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(
			 hinstDLL );
		break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			break;
	}
	return( TRUE );
}

#endif

#if defined( LIBEWF_DLL_EXPORT )

/* Function that indicates the library is a DLL
 * Returns 1
 */
char libewf_is_dll(
      void )
{
	return( 1 );
}
#endif

#endif

