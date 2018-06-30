
	// TRANSPORT CONTROLS
	if ( G_solo_rec_page != NULL ){
		MIR_write_dot( LED_RECORD, MIR_RED );
		if ( G_run_bit == ON && G_track_rec_bit == ON ){
			MIR_write_dot( LED_RECORD, MIR_GREEN );
			MIR_write_dot( LED_RECORD, MIR_BLINK );
		}

		// Show the end of recording chord flash
		if ( G_solo_rec_ending_flash == OFF ){
			MIR_write_dot( LED_PLAY4, MIR_RED );
		}
		else if ( G_solo_rec_ending_flash == ON ){
			MIR_write_dot( LED_PLAY4, MIR_GREEN );
			MIR_write_dot( LED_PLAY4, MIR_RED );
		}
		else {
			MIR_write_dot( LED_PLAY4, MIR_GREEN );
		}
	}

	if ( G_run_bit == ON ){
		MIR_write_dot( LED_STOP, MIR_RED );
	}

	if ( G_solo_has_rec == ON ){
		if ( G_track_rec_bit == OFF ){
			if ( G_run_bit == ON ){
				MIR_write_dot( LED_PLAY1, MIR_GREEN );
			}
			else {
				MIR_write_dot( LED_PLAY1, MIR_RED );
			}
		}
		if ( G_solo_overdub == OFF ){
			MIR_write_dot( LED_FOLLOW, MIR_RED );
		}
		else {
			MIR_write_dot( LED_FOLLOW, MIR_GREEN );
		}

		// Clear recording
		if ( G_run_bit == OFF ){
			MIR_write_dot( LED_CHAINER, MIR_RED );
		}
	}

	// Free Flow recording
	if ( G_solo_rec_freeflow == ON ){
		MIR_write_dot( LED_CHAINMODE_4, MIR_RED   );
		MIR_write_dot( LED_CHAINMODE_4, MIR_GREEN );
	}

	// Undo Edit buffer
	if ( G_solo_edit_buffer_volatile == ON ){
		MIR_write_dot( LED_EDIT_MASTER, MIR_RED );
		MIR_write_dot( LED_EDIT_MASTER, MIR_GREEN );
		if ( MIX_TIMER == ON ){
			MIR_write_dot( LED_EDIT_MASTER, MIR_BLINK );
		}
	}

	// ESC
	if ( G_run_bit == OFF ){
		MIR_write_dot( LED_RETURN, MIR_GREEN );
	}

	// Slow tempo toggle
	if ( G_slow_tempo != OFF ){
		MIR_write_dot( LED_TEMPO, MIR_GREEN );
		MIR_write_dot( LED_TEMPO, MIR_BLINK );
	}
	else
	{
		MIR_write_dot( LED_TEMPO, MIR_RED );
	}

	if (G_solo_rec_page != NULL && G_run_bit == OFF){

		MIR_write_dot( LED_CLEAR, MIR_RED ); // LEN / clr
		MIR_write_dot( LED_CLEAR, MIR_GREEN );

		if ( G_solo_has_rec == ON ){

			// Grid controls
			MIR_write_dot( LED_TGGL, MIR_RED ); // VEL
			MIR_write_dot( LED_TGGL, MIR_GREEN );

			MIR_write_dot( LED_ZOOM_STEP, MIR_RED ); // STEP ZOOM for Legato note length toggle
			if ( G_solo_rec_legato == ON ){
				MIR_write_dot( LED_ZOOM_STEP, MIR_GREEN );
			}
		}
	}

	// POS recording split button
	if (G_solo_rec_page != NULL && G_solo_has_rec == ON ){
		MIR_write_dot( LED_FLT, MIR_RED ); // POS
		// The recording is playing and not recording so enable split markers using POS
		if ( G_run_bit == ON && G_track_rec_bit == OFF ){
			MIR_write_dot( LED_FLT, MIR_GREEN ); // POS
			if ( ROT_INDEX == REC_MEASURES_SPLIT ){
				MIR_write_dot( LED_FLT, MIR_BLINK ); // POS
			}
		}
	}

	// Show the MODE - (Special) Grid Solo Zoom
	MIR_write_dot( LED_ZOOM_GRID, MIR_RED );
	MIR_write_dot( LED_ZOOM_GRID, MIR_GREEN );
	MIR_write_dot( LED_ZOOM_GRID, MIR_BLINK );

	MIR_write_dot( LED_PASTE, MIR_RED ); // MCH
	MIR_write_dot( LED_PASTE, MIR_GREEN );

	// Quantize value
	// CHORD SECTION
	if ( G_quantize_note > OFF && G_solo_has_rec == ON && G_run_bit == OFF ){
		MIR_write_dot( (LED_QUANTIZE_LOW + G_quantize_note -1), MIR_RED );
	}


	// Strum
	// NUMERIC QUADRANT
	if ( G_strum != 9 ){ // 9 is the OFF value
		MIR_write_dot( LED_ALIGN, MIR_GREEN );
		MIR_write_dot( LED_ALIGN, MIR_RED );
	}
	if ( PHRASE_TIMER == ON || is_pressed_key( KEY_ALIGN )){
		MIR_write_dot( LED_ALIGN, MIR_GREEN );
		MIR_write_dot( LED_ALIGN, MIR_RED );
		show_strum_in_circle( G_strum );
	}
	else if ( G_solo_has_rec == ON && G_run_bit == OFF) {
		// Quantize fine tune value
		// NUMERIC QUADRANT
		switch (G_quantize_fine_tune) {
		case 1:
			MIR_write_dot( 201, MIR_RED );
			break;
		case 2:
			MIR_write_dot( 200, MIR_GREEN );
			break;
		case 3:
			MIR_write_dot( 199, MIR_RED );
			break;
		case 4:
			MIR_write_dot( 198, MIR_GREEN );
			break;
		case 5:
			MIR_write_dot( 197, MIR_RED );
			break;
		case 6:
			MIR_write_dot( 207, MIR_GREEN );
			break;
		case 7:
			MIR_write_dot( 206, MIR_RED );
			break;
		case 8:
			MIR_write_dot( 216, MIR_GREEN );
			break;
		case 9:
			MIR_write_dot( 215, MIR_RED );
			break;
		}
	}

	// MATRIX
	// show( ELE_MATRIX, GRID );
	for (i=0; i < MAX_NROF_PAGES; i++) {
		// Page has contents and is not one of the row zero
		if (	(Page_repository[i].page_clear != ON)  &&	( (i % 10) != 9 )){
			// This is our Solo Recording cluster
			if ( G_solo_rec_page != NULL && selected_page_cluster( i, G_solo_rec_page->pageNdx ) != OFF ){
				GRID_write_dot( i, MIR_GREEN );
			}
			else {

				if ( G_solo_page_play_along[i % 10] == i ){
					GRID_write_dot( i, MIR_GREEN );
					GRID_write_dot( i, MIR_BLINK );
				}
				else {
					// This is a muted page in the grid
					GRID_write_dot( i, MIR_RED );
				}
			}
		} // page_clear != ON
	} // page iterator


	// Write Grid to MIR
	MIR_write_GRID ();


	// Show the GRID cursor
	unsigned char temp = cursor_to_dot( GRID_CURSOR );
	unsigned int selRec = selected_solo_rec_page( GRID_CURSOR, temp );
	if ( selRec == ON ||
	   ( G_solo_rec_page != NULL &&
	     selected_page_cluster( GRID_CURSOR, G_solo_rec_page->pageNdx ) != OFF &&
	     is_pressed_key( temp )
	)){

		if ( selRec == OFF && G_solo_rec_page != NULL ){
			MIR_write_dot( LED_CLEAR, MIR_BLINK );
		}
		if ( G_solo_rec_page == NULL && G_solo_rec_freeflow == OFF ){
			// No recording page has been chosen yet so show the Free Flow button flashing
			// when an eligible grid page is pressed
			MIR_write_dot( LED_CHAINMODE_4, MIR_RED   );
			MIR_write_dot( LED_CHAINMODE_4, MIR_GREEN );
			MIR_write_dot( LED_CHAINMODE_4, MIR_BLINK );
		}

		// Show the pressed recording page or the page to the right that may become a recording page
		if ( G_solo_rec_freeflow == OFF || selected_page_cluster( GRID_CURSOR, G_solo_rec_page->pageNdx ) != OFF ){

			MIR_write_dot( temp, MIR_RED   );
			MIR_write_dot( temp, MIR_GREEN );
			MIR_write_dot( temp, MIR_BLINK );

			unsigned int min = 20;
			unsigned int max = 119;
			unsigned int result = 0;

			// Show the row zero measure count for the pressed page
			for( i=min; i <= max; i+=11 ){
				result = (i - 9) / 11;

				if ( G_solo_rec_page != NULL && Rec_repository[column_of(temp)].measure_count == result ){

					MIR_write_dot( i, MIR_RED );
				}
				else {
					MIR_write_dot( i, MIR_GREEN );
				}
			}
		}
	}
	// Continue flashing the measure selection for a moment
	else if ( ROT_INDEX == REC_MEASURES_IDX ){

		unsigned int min = 20;
		unsigned int max = 119;
		unsigned int result = 0;

		// Show the row zero measure count for the pressed page
		for( i=min; i <= max; i+=11 ){
			result = (i - 9) / 11;

			if ( G_solo_rec_page != NULL && Rec_repository[G_solo_rec_pressed_col].measure_count == result ){

				MIR_write_dot( i, MIR_RED );
				MIR_write_dot( i, MIR_BLINK );
			}
			else {
				MIR_write_dot( i, MIR_GREEN );
			}
		}
	}

	// Show the packman at playtime - unless there is a scale selected
	show ( ELE_OCTAVE_CIRCLE, G_global_locator_PICTURE );


	if ( is_pressed_key(KEY_PASTE) || ( EDIT_TIMER == ON && ROT_INDEX == 10 ) )
	{
		if ( G_solo_midi_ch <= 16 ){

			MIR_point_numeric(
				G_solo_midi_ch,
				9,	MIR_GREEN);
		}
		else if ( GRID_p_set_midi_ch <= 32 ){

			MIR_point_numeric(
				G_solo_midi_ch - 16,
				9,	MIR_RED);
		}
	}
	else if ( ( G_solo_rec_page != NULL ) &&
			( is_pressed_key(KEY_TGGL) || ( EDIT_TIMER == ON && ROT_INDEX == 1 ) ))
	{
		MIR_point_numeric(
			G_solo_normalize_pitch,
			0,	MIR_GREEN);
	}
	else if ( ( G_solo_rec_page != NULL ) &&
			( is_pressed_key(KEY_CLEAR) || ( EDIT_TIMER == ON && ROT_INDEX == 3 ) ))
	{
		MIR_point_numeric(
			G_solo_normalize_len,
			2,	MIR_GREEN);
	}


