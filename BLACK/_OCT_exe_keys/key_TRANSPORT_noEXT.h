
//		// PLAY activation
//		//
//		if ( 	( keyNdx == KEY_PLAY1 ) 
//			||	( keyNdx == KEY_PLAY2 ) 
//			||	( keyNdx == KEY_PLAY4 )
//			){
//	
//			// React only if the sequencer is stopped
//			if ( (RUNBIT == OFF) ){
//				
//				switch (PAUSEBIT) {
//					// Play from PAUSE state
//					
//					case ON:
//						sequencer_STOP();
//
//						// NO BREAK Fallthrough intended - no break here, 
//						// as we are recovering from pause state
//	
//					case OFF:
//						// Start the sequencer
//						sequencer_START();
//						break;
//				} // pausebit switch
//			}// runbit is OFF
//
//
//			// PLAY ACTIVATION - some PLAYx key was pressed
//			else if (RUNBIT == ON) {
//
//				if (	
//						(	( zoom_level == zoomPAGE )
//						&&	( VIEWER_page->keyMode != KMOD_THIS_TRACK ) )
//					|| 	
//						( zoom_level == zoomTRACK )
//					){
//
//					// Check trackSelection status
//					switch( VIEWER_page->trackSelection ){
//
//						case 0:
//							// Clear the recording track on PLAY1
//							if ( keyNdx == KEY_PLAY1 ){
//
//								// Find and clear the recording track in VIEWER_page
//								if ( VIEWER_page->track_REC_pattern != 0 ){
//
//									// Place recording track into artificial selection
//									VIEWER_page->trackSelection = VIEWER_page->track_REC_pattern;
//									// Clear the track
//									Page_CLEAR_selected_tracks( VIEWER_page );
//									// Forget the artificial selection
//									VIEWER_page->trackSelection = 0;									
//								}
//							}
//							break;
//							
//						default:
//
//							// DOUBLE CLICK was started in the ON toggle state section
//							if (	( DOUBLE_CLICK_TARGET == keyNdx )
//								&& 	( DOUBLE_CLICK_TIMER > DOUBLE_CLICK_ALARM_SENSITIVITY )
//								){
//								
//								// DOUBLE CLICK CODE
//								// Determine the wanted multiplicator / skip value..
//								// ..and store it into the track attribute
//								switch( keyNdx ){
//
//									case KEY_PLAY2:
//										// Divisor 2
//										j = 1;
//
//										if ( is_pressed_key( KEY_PLAY1 )){
//											// Divisor 3
//											j = 2;
//										}
//										break;
//
//									case KEY_PLAY4:
//										// Divisor 4
//										j = 3;
//
//										if ( is_pressed_key( KEY_PLAY1 )){
//											// Divisor 5
//											j = 4;
//											if ( is_pressed_key( KEY_PLAY2 )){
//												// Divisor 7
//												j = 6;
//											}
//										}
//										else if ( is_pressed_key( KEY_PLAY2 )){
//											j = 5;
//										}
//										break;
//								}
//
//								// Set the tempo multiplier of the selected tracks
//								for ( i=0; i < MATRIX_NROF_ROWS; i++ ){
//			
//									// If Track[i] is selected
//									if ( VIEWER_page->trackSelection & (1<<i) ){								
//			
//										// Set the tempo multiplier of selected tracks
//										VIEWER_page->Track[i]->attribute[ATTR_TEMPOMUL_SKIP] = j;							
//
//										// Set the tempo multiplier of selected tracks
//										VIEWER_page->Track[i]->attribute[ATTR_TEMPOMUL] = 1;							
//									}
//								} // row iterator
//							}
//							
//							// Start thinking about double clicking 
//							else if ( DOUBLE_CLICK_TARGET == 0 ) {
//					
//								// Prepare double click timer for zooming into the step
//								DOUBLE_CLICK_TARGET = keyNdx;
//								DOUBLE_CLICK_TIMER = ON;
//					
//								// Start the Double click Alarm
//								cyg_alarm_initialize(
//									doubleClickAlarm_hdl, 
//									cyg_current_time() + DOUBLE_CLICK_ALARM_TIME,
//									DOUBLE_CLICK_ALARM_TIME );
//		
//								// SINGLE CLICK CODE:	
//								// Determine the wanted multiplicator value..
//								// ..and store it into the track attribute
//								switch( keyNdx ){
//			
//									case KEY_PLAY1:
//										j = 1;
//										break;
//			
//									case KEY_PLAY2:
//										j = 2;
//
//										// Add one to the keypress
//										if ( is_pressed_key( KEY_PLAY1 ) ){
//											j = 3;
//										}
//										break;
//			
//									case KEY_PLAY4:
//										j = 4;
//										
//										// Add one to the keypress
//										if ( is_pressed_key( KEY_PLAY1 )){											
//											j = 5;
//											// Add two additional to the keypress
//											if ( is_pressed_key( KEY_PLAY2 )){
//												j = 7;
//											}	
//										}
//										else if ( is_pressed_key( KEY_PLAY2 )){
//												j = 6;
//										}
//										break;
//								}	
//
//								// Set the tempo multiplier of the selected tracks
//								for ( i=0; i < MATRIX_NROF_ROWS; i++ ){
//			
//									// If Track[i] is selected
//									if ( VIEWER_page->trackSelection & (1<<i) ){								
//			
//										// Set the tempo multiplier of selected tracks
//										VIEWER_page->Track[i]->attribute[ATTR_TEMPOMUL] = j;							
//
//										// Make sure to get rid of any skip values
//										VIEWER_page->Track[i]->attribute[ATTR_TEMPOMUL_SKIP] = 0;							
//									}
//								} // row iterator
//							} // single click scenario
//							break;
//
//					} // switch VIEWER_page->trackSelection
//
//				} // zoom_level == zoomPAGE
//
//			} // runbit is ON
//
//		} // keyNdx is one of the play keys

