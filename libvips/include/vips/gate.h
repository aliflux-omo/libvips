/* Thread profiling.
 */

/*

    This file is part of VIPS.
    
    VIPS is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

 */

#ifndef VIPS_GATE_H
#define VIPS_GATE_H

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#include <vips/vips.h>

#define VIPS_GATE_SIZE (10000)

/* A set of timing records. i is the index of the next slot we fill. 
 */
typedef struct _VipsThreadGateBlock {
	struct _VipsThreadGateBlock *prev;

	gint64 time[VIPS_GATE_SIZE];
	int i;
} VipsThreadGateBlock; 

/* What we track for each gate-name.
 */
typedef struct _VipsThreadGate {
	const char *name;
	VipsThreadGateBlock *start;
	VipsThreadGateBlock *stop;
} VipsThreadGate; 

/* One of these in per-thread private storage. 
 */

typedef struct _VipsThreadProfile {
	/*< private >*/

	const char *name;
	GThread *thread;
	GHashTable *gates;
} VipsThreadProfile; 

#define VIPS_GATE_START( NAME ) \
G_STMT_START { \
	if( vips__thread_profile ) \
		vips__thread_gate_start( NAME ); \
} G_STMT_END

#define VIPS_GATE_STOP( NAME ) \
G_STMT_START { \
	if( vips__thread_profile ) \
		vips__thread_gate_stop( NAME ); \
} G_STMT_END

extern gboolean vips__thread_profile;

void vips__thread_profile_attach( const char *thread_name );
void vips__thread_profile_stop( void );

void vips__thread_gate_start( const char *gate_name ); 
void vips__thread_gate_stop( const char *gate_name ); 

#endif /*VIPS_GATE_H*/

#ifdef __cplusplus
}
#endif /*__cplusplus*/
