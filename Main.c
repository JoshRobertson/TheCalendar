/**********************************************************************
PURPOSE: Draws a Unicode table in the terminal window to the specifications called in Table.c
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: Void.
OUTPUTS: Prints visual output to terminal window.
ALGORITHM(S): N/A. All content is called through drawTable().
NOTES: Main() is the entry point of the program, but all logic is purposely separated from it.
**********************************************************************/

/**********************************************************************
Begin #include statements
**********************************************************************/
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Table.h"
#include "Calendar.h"
#include "ConsoleData.h"


/**********************************************************************
Begin main()
**********************************************************************/
int main(void) {
	//checks to see if console is wide enough for set table output
	if (getConsoleWidthChars() < 100) {
		wprintf(L"Console width is: %d. That is not wide enough to display the Calendar.\
				 Please expand your console and try again.\n", getConsoleWidthChars());
		exit(0);
	}
	drawTable();
	wprintf(L"Calendar for %s %d has %d days\n", monthNames[month-1], year, daysinMonth);
}