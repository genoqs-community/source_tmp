//
// Copyright (C) 2004, 2005, 2006, 2007 genoQs Machines
// This file is part of Octopus_OS - 
// the firmware of the genoQs Machines Octopus, MIDI Control Sequencer
//
// The source code Octopus_OS is available for use in accordance with the 
// GNU General Public License (GPL). For more information about Open Source 
// licensing, please visit http://www.opensource.org/
//
// Octopus_OS is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Octopus_OS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Octopus_OS; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//




//		// Check for pressed track_selectors
//		my_pressed_key = is_pressed_keyrange( 1, 10 );
//		
//
//		switch( my_pressed_key ){
//		
//			case 0:
//				// Nothing relevant is pressed, go back to normal mode
//				if ( !(is_pressed_key( KEY_SELECT_MASTER ))
//					){
//		
//					// Enter interactive mode
//					target_page->OPS_mode = INTERACTIVE;
//				}
//				break;
//				
//			default:
//				// Ckeck whether the SEL button is active as well..
//				// ..or if we are in passive mode already - 
//				if (	( is_pressed_key( KEY_SELECT_MASTER ) ) 
//					|| 	( target_page->OPS_mode == PASSIVE ) 
//					){
//	
//					// Enter PASSIVE mode - basically locking the track selection
//					// but only if the recording bit is set
//					if ( target_page->REC_bit == ON ){
//
//						target_page->OPS_mode = PASSIVE;
//					}
//				}				
//				break;
//		}
		






////____________________________________________________________________________
//
//		// Some chord button is pressed
//		if ( is_pressed_keyrange( 252, 258 ) != FALSE ){
//	
//			// If a page button is pressed as well, switch to step mode			
//			if ( is_pressed_pagerange() != FALSE ){
//
//				// Compute Step coordinates
//				row = row_of( is_pressed_pagerange() );
//				col = column_of( is_pressed_pagerange() );
//				
//				// Select the current step formally 
//				Step_set_status( target_page->Step[row][col], STEPSTAT_SELECT, ON );
//									
//				// Update the step selection counter in page
//				target_page->stepSelection = 1;
//
//				// Remember STEP COORDINATES
//				target_page->stepSelectionSingleRow = row;
//				target_page->stepSelectionSingleCol = col;
//
//				//d_iag_printf( "zooming into step row:%d col:%d ts:%d\n", 
//				//		row, col, target_page->trackSelection );
//
//				// Zoom into the step: Switch the mode
//				G_zoom_level = zoomSTEP;
//			}
//
//			// Do not execute the rest of the clause
//			break;
//		}
//		
//
//		switch( target_page->OPS_mode ){
//			
//			case BIRDSEYE:
//				// If the zoom key is not pressed anymore, return to default
//				if (	!(is_pressed_key( KEY_ZOOM_PAGE ))
//					){
//
//					// Enter interactive mode
//					target_page->OPS_mode = INTERACTIVE;
//// d_iag_printf( "going 0 BV->INTERACTIVE.. cursor:%d ndx:%d\n", GRID_CURSOR, target_page->pageNdx );	
//				}
//				else{
//
//					// Nothing to do as of yet..
//				}
//				break;
//
//
//			case INTERACTIVE:
//
//				// Only act like this in Page mode with no steps selected
//				if (	( G_zoom_level != zoomPAGE )
//					||	( target_page->stepSelection != 0 )
//					){
//					break;
//				}
//					
//				// Selector is pressed 
//				if (	( my_pressed_key != 0 )
//					){
//		
//					// Ckeck whether the SEL button is active as well..
//					// ..or if we are in passive mode already - 
//					if (	( is_pressed_key( KEY_SELECT_MASTER ) ) 
//						|| 	( target_page->OPS_mode == PASSIVE ) 
//						){
//		
//						// Enter PASSIVE mode - basically locking the track selection
//						target_page->OPS_mode = PASSIVE;
//
//// d_iag_printf( "going 1 IV->PASSIVE.. cursor:%d ndx:%d\n", GRID_CURSOR, target_page->pageNdx );	
//					}
//				}
//
//				else if ( (is_pressed_key( KEY_ZOOM_PAGE 		)) ){
//					
//					// Enter the Birds Eye view
//					target_page->OPS_mode = BIRDSEYE;
//	
//// d_iag_printf( "going 2 IV->BIRDSEYE.. cursor:%d ndx:%d\n", GRID_CURSOR, target_page->pageNdx );	
//				}
//
//				else {
//					
//					// No interesting key is pressed, so forget selection.	
//					if ( target_page->SEL_LOCK == OFF ){
//						target_page->trackSelection = 0;					
//					}
//				
//					if (	( is_pressed_key( KEY_SELECT_MASTER ) ) ){
//
//						target_page->OPS_mode = PASSIVE;						
//
//// d_iag_printf( "going 3 IV->PASSIVE.. cursor:%d ndx:%d\n", GRID_CURSOR, target_page->pageNdx );	
//					}
//				}
//				break;
//
//
//			case PASSIVE:
//			
//				// Nothing to do yet
//				if (	( my_pressed_key == 0 )
//					&&	( !(is_pressed_key( KEY_SELECT_MASTER 	)) )
//					){
//
//					// Enter interactive mode
//					target_page->OPS_mode = INTERACTIVE;
//// d_iag_printf( "going 4 PV->INTERACTIVE.. cursor:%d ndx:%d \n", GRID_CURSOR, target_page->pageNdx );	
//				}
//
//				break;
//
//		} // switch target_page->OPS_mode	
//


