

extern int numCols, numRows, year, month, daysInYear, totDays, 
			offset, numVisibleBoxes, daysinMonth, dayCounter;
			
extern int MonthFactor[], monthSz[];
extern const char* monthNames[];

extern void getBoxString(int line);
extern int drawCalendar(unsigned int month, unsigned int year);
extern int getDate();
