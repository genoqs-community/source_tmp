
	if ( keyNdx == KEY_TEMPO ){

		if ( SOLO_slow_tempo != OFF ){ // slow tempo
			G_master_tempo = SOLO_slow_tempo;
			SOLO_slow_tempo = OFF;
		}
		else { // reset to original tempo
			SOLO_slow_tempo = G_master_tempo;
			G_master_tempo = 100;
		}
	}

	if ( keyNdx == KEY_PLAY4 ){ // values = OFF, ON, 1.2.3.
		if ( ++SOLO_rec_ending_flash == QBIT )
		{
			SOLO_rec_ending_flash = OFF;
		}
	}

	if ( SOLO_rec_page != NULL ){ // A record page cluster is selected

		if ( keyNdx == KEY_PLAY1 && SOLO_has_rec == ON){
			G_track_rec_bit = OFF;
			sequencer_command_PLAY();
		}

		else if ( keyNdx == KEY_STOP ){
			stop_solo_rec();
		}

		else if ( keyNdx == KEY_RECORD ){
			G_track_rec_bit = ON;
			if ( SOLO_has_rec == OFF ){
				SOLO_rec_measure_hold = ON;
			}
			sequencer_command_PLAY();
		}

		else if ( keyNdx == KEY_CHAINER && G_run_bit == OFF ){
			if ( SOLO_has_rec == ON ){
				SOLO_edit_buffer_volatile ^= 1; // toggle
				SOLO_has_rec = OFF;
				MIX_TIMER = ON;
				// Setup alarm for the MIX TIMER
				cyg_alarm_initialize(	alarm_hdl,
										cyg_current_time() + TIMEOUT_VALUE,
										0 );
			}
		}

		else if ( keyNdx == KEY_EDIT_MASTER && SOLO_edit_buffer_volatile == ON ){
			SOLO_has_rec = ON; // XXX rm - only for UI testing
			SOLO_edit_buffer_volatile ^= 1; // toggle
		}

		else if ( keyNdx == KEY_FOLLOW ){
			SOLO_overdub ^= 1; // toggle
		}

		// Legato
		if ( keyNdx == KEY_ZOOM_STEP && G_run_bit == OFF &&  SOLO_has_rec == ON ){
			SOLO_rec_legato ^= 1; // toggle
		}
	}

	// Clear the record pages
	if (keyNdx == KEY_CLEAR && G_run_bit == OFF){
		unsigned char temp = cursor_to_dot( GRID_CURSOR );
		if ( SOLO_rec_page != NULL &&
			 selected_page_cluster( GRID_CURSOR, SOLO_rec_page->pageNdx ) != OFF &&
			 is_pressed_key( temp )
		){
			// Clear the page cluster if it is currently selected
			selected_page_cluster_clear(SOLO_rec_page->pageNdx);
			SOLO_normalize_pitch = OFF;
			SOLO_normalize_len = OFF;
			SOLO_rec_page = NULL;
			SOLO_has_rec = OFF;
			SOLO_edit_buffer_volatile = OFF;
			SOLO_rec_freeflow = OFF;
			G_measure_locator = OFF;
			Solorec_init();
		}
	}

	else if (keyNdx == KEY_FLT){

		if ( SOLO_has_rec == ON && G_run_bit == ON && G_track_rec_bit == OFF && SOLO_pos_marker_out == OFF ){

			if ( SOLO_pos_marker_in == OFF ){
				SOLO_pos_marker_in = G_measure_locator;
			}
			else {
				SOLO_pos_marker_out = G_measure_locator;
				// XXX only for UI testing
				// TODO: apply the pos splits
				G_track_rec_bit = OFF;
				G_run_bit = OFF;
				SOLO_pos_marker_in = OFF; // XXX
				SOLO_pos_marker_out = OFF;
			}

			ROT_INDEX = REC_MEASURES_SPLIT;
			// Setup alarm for the EDIT TIMER
			cyg_alarm_initialize(	alarm_hdl,
									cyg_current_time() + (TIMEOUT_VALUE),
									0 );
		}
	}

	// Quantize chord buttons
	else if (SOLO_has_rec == ON && G_run_bit == OFF && keyNdx >= KEY_QUANTIZE_LOW && keyNdx <= KEY_QUANTIZE_HIGH){

		if ((keyNdx - KEY_QUANTIZE_LOW + 1) == SOLO_quantize_note){
			// turn quantize off if the same button is pressed twice
			SOLO_quantize_note = 0;
		}
		else {
			SOLO_quantize_note = keyNdx - KEY_QUANTIZE_LOW + 1;
		}
	}
	else {

		// GRID PAGE CLUSTER SELECTIONS
		if ( ( (keyNdx < 187)
		) ) {

			unsigned char temp = row_of(keyNdx) + (10 * column_of(keyNdx));
			GRID_CURSOR = temp;
		}

		// Grid page toggle
		unsigned char keyRow = row_of(keyNdx);
		unsigned int pressed = is_pressed_pagerange();
		unsigned int rowZeroTrack = is_key_rowzero(keyNdx);
		unsigned int pressedCol = column_of (pressed);
		pressed = row_of(pressed) + (10 * column_of (pressed));
		unsigned char cursor = Page_repository[pressed].pageNdx;

		// Activate a record page - set the measure count
		if ( !SOLO_has_rec && // does not have a recording yet
			 ( selected_solo_rec_page( cursor, cursor_to_dot( cursor ) ) == ON ||
			   selected_page_cluster( cursor, SOLO_rec_page->pageNdx ) != OFF )){
			/*
			 * A page with a measure count has been selected on this press
			 */
			if ( keyNdx == KEY_CHAINMODE_4 && SOLO_rec_page == NULL && Page_repository[pressed].page_clear == ON ){
				SOLO_rec_freeflow = ON;
				Page_repository[pressed].page_clear = OFF;
				SOLO_rec_page = &Page_repository[pressed];
				Rec_repository[pressedCol].measure_count = 1;
			}
			// A page is pressed first then step 1 through 10 of row zero to set the measure count
			else if ( rowZeroTrack != OFF && rowZeroTrack <= 10 && SOLO_rec_freeflow == OFF ){

				if ( Page_repository[pressed].page_clear == ON ){
					/*
					 * ########################################
					 * A record page was created!
					 * ########################################
					 */
					SOLO_rec_page = &Page_repository[pressed];

					if ( SOLO_has_rec == OFF ){
						GRID_CURSOR = SOLO_rec_page->pageNdx; // TODO: <-------- freeflow
					}
				}

				SOLO_rec_pressed_col = pressedCol;
				create_page_record_track_chain(SOLO_rec_page, rowZeroTrack);
				Rec_repository[pressedCol].measure_count = rowZeroTrack;

				// Snow the measure count for a few extra blinks
				ROT_INDEX = REC_MEASURES_IDX;
				// Setup alarm for the EDIT TIMER
				cyg_alarm_initialize(	alarm_hdl,
										cyg_current_time() + (TIMEOUT_VALUE / 3),
										0 );
			}
		}

		// Toggle the play along status of existing pages in the grid
		else if ( SOLO_rec_page != NULL && Page_repository[GRID_CURSOR].page_clear == OFF ){

			// no play along pages set for this row
			// and - this row does not contain the solo recording page
			if ((( SOLO_page_play_along[keyRow] == NOP && ( SOLO_rec_page->pageNdx % 10) != keyRow ))
				|| // or
					((( SOLO_page_play_along[keyRow] % 10) == keyRow ) && // a page in a play along row was pressed
					( SOLO_page_play_along[keyRow] != GRID_CURSOR ) // and - this page was not already the play along page
				)){
				SOLO_page_play_along[keyRow] = GRID_CURSOR;
			}
			else {
				SOLO_page_play_along[keyRow] = NOP;
			}
		}

		if (SOLO_has_rec == ON && G_run_bit == OFF){
			// Fine tune quantize
			unsigned char xdx = BK_KEY_to_xdx( keyNdx );
			SOLO_quantize_fine_tune = SOLO_quantize_fine_tune == xdx ? 0 : xdx;
		}
	}
