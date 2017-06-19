/**********************************************************************
Begin #include statements
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include "BoxDrawChars.h"
#include "Calendar.h"

 int H = 4, W = 13, l = 1;
 static int line = 0, cellNum = 1;


/**********************************************************************
PURPOSE: Prototype function to print a single line of a table.
HISTORY: Created by Joshua Robertson October 24, 2014
INPUTS: string (wchar_t*) for visual output elements (Unicode), ints for other parameters.
OUTPUTS: A printed Unicode line of characters to serve as a single line of a table.
ALGORITHM(S): See attached document
NOTES: None
**********************************************************************/
int outputTableString(string printline[], int numCols){
	//if not offset, run standard output algorithm
	if (printline[LEFT] != offsetSpaces[LEFT]){
		wprintf(printline[LEFT]);
		for (int i=0; i<numCols; i++) {
			if (printline[BAR] == intern[BAR] && cellNum%8!=0 && l%5!=0 )
				getBoxString(line);
			else{
				for (int j=0; j<W;j++)
					wprintf(printline[BAR]);
			}
			if (i==numCols-1)
				wprintf(printline[RIGHT]);
			else
				wprintf(printline[MIDDLE]);
		}	
		l++;
		wprintf(CR);
	}
	//if printing offset, substitute blanks
	else {
		for (int i=0; i<offset; i++) {
			for (int j=0; j<W;j++)
				wprintf(printline[BAR]);
			wprintf(L"%s", " ");
		}
	}
}


/**********************************************************************
PURPOSE: Prints the offset of the first row of the table as applicable.
HISTORY: Created by Joshua Robertson October 24, 2014
INPUTS: string (wchar_t*) for visual output elements (Unicode), ints for other parameters.
OUTPUTS: A printed line of 'null' characters to serve as offset for table row.
ALGORITHM(S): See attached document
NOTES: None
**********************************************************************/
void setTableOffset(int offset, int numVisibleBoxes) {
	outputTableString(offsetSpaces, offset);
	outputTableString(first, numVisibleBoxes);
	for (line=0; line<H; line++){
		outputTableString(offsetSpaces, offset);
		outputTableString(intern, numVisibleBoxes);
	}
}


/**********************************************************************
PURPOSE: Prints the last row of the table to match applicable offset
HISTORY: Created by Joshua Robertson October 24, 2014
INPUTS: None
OUTPUTS: Printed cells for last week of the year, row truncated accordingly
ALGORITHM(S): See attached document
NOTES: None
**********************************************************************/
void setTableEnd(){
	int endDays = monthSz[month-1]-dayCounter;
	for (line=0; line<H;line++)
		outputTableString(intern, endDays);
	outputTableString(last, endDays);
}

/**********************************************************************
PURPOSE: A 'sub function' designed to print the internal contents of each table cell
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: None.
OUTPUTS: A printed line of 'null' characters to serve as cell spacing/contents, and
a single bar between each cell of the row.
ALGORITHM(S): See attached document
NOTES: Called in tandem with row() to generate proper table.
**********************************************************************/
void height() {
	for (line=0; line<H; line++)
		outputTableString(intern, numCols);
}


/**********************************************************************
PURPOSE: A 'sub function' designed to print the middle bars between rows of the table.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: None.
OUTPUTS: A printed row of Unicode characters to serve as row demarcation.
ALGORITHM(S): See attached document
NOTES: Called in tandem with height() to generate proper table.
**********************************************************************/
void row () {
	for (int i=1; i<numRows-1; i++) {
		height();
		cellNum = 1;
		outputTableString(middle, numCols);
	}
}


/**********************************************************************
PURPOSE: Calls row() and height() to get appropriate number of table lines
needed for the specified table. Also receives all Calendar-specific information
needed to manipulate a table into a calendar.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: None (but drawCalendar is passed ints for month and year).
OUTPUTS: Entire graphical output to console
ALGORITHM(S): N/A
NOTES: Is called by main()
**********************************************************************/
int drawTable() {
	setlocale(LC_ALL, "");
	getDate();
	drawCalendar(month, year);
	outputTableString(first, numCols);
	row();
	height();
	outputTableString(last, numCols);
	//if needed, add extra row
	if (dayCounter != monthSz[month-1])
		setTableEnd();
}