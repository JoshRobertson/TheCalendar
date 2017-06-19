/**********************************************************************
Begin #include statements
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include "Table.h"
#include "HolidayInfo.h"

/**********************************************************************
Begin #define statements
**********************************************************************/
#define FEB 2

typedef char* string;
int month, year = 0, numRows = 0, numCols = 7, totDays = 0, daysInYear = 365, 
daysinMonth = 0, dayCounter = 0, testDays = 0, offset = 0, numVisibleBoxes = 0, dayOfWeek = 0, thisHoliday = 0;
extern int cellNum;
int monthSz[] = {31,28,31,30,31,30,31,31,30,31,30,31};
int MonthFactor[] = {1,4,4,0,2,5,0,3,6,1,4,6};
const string monthNames[] = {"January", "February", "March", "April", "May", "June", 
					"July", "August", "September", "October", "November", "December"};


/**********************************************************************
PURPOSE: Get month and year for calendar generation. Ensure year > 2000.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: None, except user input from scanf().
OUTPUTS: None. Stores input values from user.
ALGORITHM(S): N/A
NOTES: None
**********************************************************************/
int getDate() {
	setlocale(LC_ALL, "");
	wprintf(L"Choose a month. Enter the number value (1-12): ");
	scanf("%d", &month);
	assert(month <=12 && month >0);
	wprintf(L"Choose a year after 2000: ");
	scanf("%d", &year);
	assert(year >=2000 && year<= 9999);
}


/**********************************************************************
PURPOSE: Determine number of rows needed for a given month.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: N/A
OUTPUTS: sets int numRows
ALGORITHM(S): calculates rows needed based on month size and offset
NOTES: numRows value reassed in drawTable() 
**********************************************************************/
void setRows() {
	numRows = ((monthSz[month-1] - numVisibleBoxes)/7 +1);
}

/**********************************************************************
PURPOSE: Calculate how many cells should be offset in the first row of a calendar
for a given month.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: None.
OUTPUTS: Offset calculation is passed as int to offset.
ALGORITHM(S): Implements Zellers algorithm to calculate which day of the week the
month starts on.
NOTES: None
**********************************************************************/
int calcTableOffset() {
	int yrEnding = year%100;
	offset = ((yrEnding + (int)yrEnding/4 + MonthFactor[month-1] +6) % 7);
	numVisibleBoxes = numCols-offset;
}


/**********************************************************************
PURPOSE: Print the contents of a single cell within a given row/column
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: int line is internal line count of cell (0-3).
OUTPUTS: prints appropriate string of values with padding to fit width
ALGORITHM(S): Based on the line count that is incremented in Table.c, prints
appropriate contents of cell. Day of the month is printed on the first line,
Holiday information (if day is a holiday) is printed on line 2 and 3.
NOTES: called holiday functions from HolidayInfo.h
**********************************************************************/
void getBoxString(int line){ 
	//print day on 1st line
	if(line == 0){
		++dayCounter;
		wprintf(L"%13d", dayCounter);
	    cellNum++;
    }
    //if not holiday, blank 2nd line
    else if(line == 1 && (getHolidayStringLength(totDays) == 0)){
        if(dayCounter<7)
            dayOfWeek = totDays - numVisibleBoxes;
        else
            dayOfWeek = totDays - numCols;
        totDays++;
        wprintf(L"%13s", " ");
    }
    //if holiday, print holiday on 2nd line
    else if(line == 1 && (getHolidayStringLength(totDays) != 0)){
        wprintf(L"%13s", getHolidayString(totDays));
        testDays = 1; //Boolean "flag" to enable "Day" printing
        thisHoliday = totDays;
        if(dayCounter<7)
            dayOfWeek = totDays - numVisibleBoxes;
        else
            dayOfWeek = totDays - numCols;
        totDays++; 
    }
    //if holiday print matching "Day" on line 3
    else if(line == 2 && (testDays == 1)){
		if(thisHoliday == 1){
	    	wprintf(L"%13s", "Day");
	        testDays = 0;
	    }
	    else if(dayOfWeek != thisHoliday-1){
	        wprintf(L"%13s", " ");
	        dayOfWeek++;
	    }
	    else {
	    	wprintf(L"%13s", "Day");
	        testDays = 0;
	    }
    } 
    //if not holiday, blank 3rd line
    else if(line == 2 && (getHolidayStringLength(totDays) == 0)){
     	wprintf(L"%13s", " ");
	}
	//blank 4th line
	else wprintf(L"%13s", " ");
}


/**********************************************************************
PURPOSE: To determine if the year entered in console is a leap year or not. Adjusts all associated values if true.
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: Int year
OUTPUTS: Returns a boolean 1 or 0 depending on whether the year is a leap year or not
ALGORITHM(S): Employs standard leap year calculation
NOTES:
**********************************************************************/
int isLeapYear(unsigned int year) {
	if ((year%4==0) && !((year%100==0) && !(year%400==0))) {
	   	monthSz[1] = 29;
	   	daysInYear++;
	   	MonthFactor[0] = 0;
	   	MonthFactor[1] = 3;
	   	return 1;
	}
	else return 0;
}


/**********************************************************************
PURPOSE: Get a running count of the number of days in the year cumulative prior to the month selected
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: Int month, int year
OUTPUTS: increments int totDays as running total of days in the year.
ALGORITHM(S): N/A.
NOTES: Calls isLeapYear() to adjust values as appropriate.
**********************************************************************/
void getDayCount(unsigned int month, unsigned int year) {
	for (int mthCtr = 0; mthCtr < month-1; mthCtr++)
    	totDays += monthSz[mthCtr];
	if (isLeapYear(year) && (month > FEB))
	  	totDays--;
  	totDays++;
}


/**********************************************************************
PURPOSE: Calls and compiles all relevant calendar information and passes it to Table.c (via a call).
HISTORY: Created by Joshua Robertson October 24, 2014.
INPUTS: Int month, int year.
OUTPUTS: N/A
ALGORITHM(S): N/A
NOTES: N/A
**********************************************************************/
int drawCalendar(unsigned int month, unsigned int year){
	isLeapYear(year);
	getDayCount(month, year);
	daysinMonth = monthSz[month-1];
	calcTableOffset();
	setRows();
	//adjust rows based on offset value
	if (offset != 0){
		setTableOffset(offset, numVisibleBoxes);
	}
	else if (offset == 0){
		numRows = 5;
	}
}
