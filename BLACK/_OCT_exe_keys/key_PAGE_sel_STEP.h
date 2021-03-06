// 
// The case where the page contains an active step selection
//
	
	// Coordinates of the first selected step in page.

	// COMPUTE STEP COORDINATES: ROW AND COL
	// Compute ROW
	for (row=0; row<MATRIX_NROF_ROWS; row++) {
		j= Page_get_selection_trackpattern( VIEWER_page, row );
		if (j != 0) {
			// row was found
			break;
		}
	}
	// COMPUTE COL
	for (col=0; col<MATRIX_NROF_COLUMNS; col++) {
		if ( ((1<<(15-col)) & j) != 0) {
			// col was found
			break;
		}
	}

	// Remember STEP COORDINATES
	VIEWER_page->stepSelectionSingleRow = row;
	VIEWER_page->stepSelectionSingleCol = col;
	

	// STEP mode switch
	//
	if (keyNdx == KEY_ZOOM_STEP) {
		if (VIEWER_page->stepSelection == 1) {
			VIEWER_page->keyMode = KMOD_THIS_STEP;
			zoom_level = zoomSTEP;
		}
	}
	


	//
	// TRACK_MUTATORS
	//
	if ((keyNdx >= 187) && (keyNdx <= 196)) {

		switch (keyNdx) {
			
			case TGGL_KEY:
				// Only active when there is no stepAttributeSelection
				if ( VIEWER_page->stepAttributeSelection != 0 ){
					break;
				}
		
				// Go through all selected steps and toggle their activity status
				// ..scaning through all steps of the matrix - not very efficient!!			
				// d_iag_printf( "Toggle\n" );
				
				for (row=0; row < MATRIX_NROF_ROWS; row++) {			
					for (col=0; col < MATRIX_NROF_COLUMNS; col++) {
		
						// If the selection flag is set
						if (Step_get_status( VIEWER_page->Step[row][col], STEPSTAT_SELECT ) == ON){
		
							if( Step_get_status( VIEWER_page->Step[row][col], STEPSTAT_TOGGLE ) == ON){
	
								// If the activity flag is set - turn it off
								Step_set_status( VIEWER_page->Step[row][col], STEPSTAT_TOGGLE, OFF );
								// d_iag_printf( "OFF row:%d col:%d\n", row, col );
							}
							else {
								
								// Turn ON step
								Step_set_status( VIEWER_page->Step[row][col], STEPSTAT_TOGGLE, ON );
							}
						}
					}
				}
				break;
			
			
		
			case CLEAR_KEY:
				// Search all steps and act on the ones selected
				for (row=0; row < MATRIX_NROF_ROWS; row++) {
					for (col=0; col < MATRIX_NROF_COLUMNS; col++) {
		
						// If the selection flag is set, act on step
						if ( Step_get_status( VIEWER_page->Step[row][col], STEPSTAT_SELECT ) == ON){
		
							#include "key_STEP_exe_CLR.h"
						} // step is selcted
		
					} // col iterator
				} // row iterator
				break;
		
				
		
			case RANDOMIZE_KEY:

				// Search all steps and act on the ones selected
				for (row=0; row < MATRIX_NROF_ROWS; row++) {
					for (col=0; col < MATRIX_NROF_COLUMNS; col++) {
		
						// If the selection flag is set, act on step
						if (Step_get_status( VIEWER_page->Step[row][col], STEPSTAT_SELECT ) == ON){
		
							#include "key_STEP_exe_RND.h"				
						} // step is selected
						
					} // col iterator
				} // row iterator
				break;
		
		
		
			case ZOOM_KEY:	
				// This works if only one step is selected..
				// ..and no stepAttribute selection is active.
				if (	(VIEWER_page->stepSelection == 1) 
					&&	(VIEWER_page->stepAttributeSelection == 0)	){
				
				
					// COMPUTE STEP COORDINATES: ROW AND COL
					// Compute ROW
					for (row=0; row<MATRIX_NROF_ROWS; row++) {
						j= Page_get_selection_trackpattern( VIEWER_page, row );
						if (j != 0) {
							// row was found
							break;
						}
					}
					// COMPUTE COL
					for (col=0; col<MATRIX_NROF_COLUMNS; col++) {
						if ( ((1<<(15-col)) & j) != 0) {
							// col was found
							break;
						}
					}
		
					// Remember STEP COORDINATES
					VIEWER_page->stepSelectionSingleRow = row;
					VIEWER_page->stepSelectionSingleCol = col;
		
					// Switch the mode
					VIEWER_page->keyMode = KMOD_THIS_STEP;
					zoom_level = zoomSTEP;
//					VIEWER_step = VIEWER_page->Step [VIEWER_page->stepSelectionSingleRow]
//													[VIEWER_page->stepSelectionSingleCol];
				}							
				break;
		
		
		
			case COPY_KEY:	
				if (VIEWER_page->stepSelection != 1){
					break;
				}
		
				// Coordinates of already selected step
				row = VIEWER_page->stepSelectionSingleRow;
				col = VIEWER_page->stepSelectionSingleCol;
		
				// Copy the step pointer to the buffer
				STEP_COPY_BUFFER = VIEWER_page->Step[row][col];
		
				// Unselect the step
				Step_set_status( VIEWER_page->Step[row][col], STEPSTAT_SELECT, OFF );
				VIEWER_page->stepSelection = 0;
		
				break;
		
		
		
			case PASTE_KEY:	
				if (	(VIEWER_page->stepSelection != 1)
					||	(STEP_COPY_BUFFER == NULL) 
					){

					break;
				}
		
				// Coordinates of already selected step
				row = VIEWER_page->stepSelectionSingleRow;
				col = VIEWER_page->stepSelectionSingleCol;
		
				// Copy step data from buffer to pointer
				Step_copy( STEP_COPY_BUFFER, VIEWER_page->Step[row][col]);
		
				// Unselect the step
				Step_set_status( VIEWER_page->Step[row][col], STEPSTAT_SELECT, OFF );
				VIEWER_page->stepSelection = 0;
				STEP_COPY_BUFFER = NULL;	
	
				break;
		}
		
	} // Key is a track mutator	


	//
	// TRANSPORT functions - when nothing is selected in page
	//
	switch( keyNdx ){

		case KEY_STOP:
			sequencer_command_STOP();
			break;


		case KEY_PAUSE:
			sequencer_command_PAUSE();
			break;


		case KEY_PLAY1:
		case KEY_PLAY2:
		case KEY_PLAY4:
			
			// Clear the recording track on PLAY1 while recording..
			if (	( keyNdx == KEY_PLAY1 )
				&&	( RUNBIT == ON )
				){

				// Find and clear the recording track in VIEWER_page
				if ( VIEWER_page->track_REC_pattern != 0 ){

					// Place recording track into artificial selection
					VIEWER_page->trackSelection = VIEWER_page->track_REC_pattern;
					// Clear the track
					Page_CLEAR_selected_tracks( VIEWER_page );
					// Forget the artificial selection
					VIEWER_page->trackSelection = 0;									
				}
			}

			// Make sure the sequencer is running
			sequencer_command_PLAY();

			break;
	}	



