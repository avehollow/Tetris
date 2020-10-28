#include "pch.h"
#include "System.h"

#define ENTRY_POINT System g; \
					g.Run();

int main()
{
	ENTRY_POINT
	return 0;
}


///* Windows sleep in 100ns units */
/// Funkcja dziala na 100ns jednostkach, Czyli je¿eli chcesz przespac 100ns to do funkcji przekazujesz 100ns/100; Ponizej 100ns nie da sie !
//BOOLEAN nanosleep(LONGLONG ns) {
//	/* Declarations */
//	HANDLE timer;	/* Timer handle */
//	LARGE_INTEGER li;	/* Time defintion */
//	/* Create timer */
//	if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
//		return FALSE;
//	/* Set timer properties */
//	li.QuadPart = -ns;
//	if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
//		CloseHandle(timer);
//		return FALSE;
//	}
//	/* Start & wait for timer */
//	WaitForSingleObject(timer, INFINITE);
//	/* Clean resources */
//	CloseHandle(timer);
//	/* Slept without problems */
//	return TRUE;
//}

///* Jezeli funkcja jest wywolywana w petli */
// Umiescic poza petla
/* Declarations */ 
//	HANDLE timer;	/* Timer handle */
//	LARGE_INTEGER li;	/* Time defintion */
//	/* Create timer */
//	if (!timer = CreateWaitableTimer(NULL, TRUE, NULL)))
//		return FALSE;

//void nanosleep(LONGLONG ns) {
//
//	/* Set timer properties */
//	li.QuadPart = -ns;
//	SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE);
//	
//	/* Start & wait for timer */
//	WaitForSingleObject(timer, INFINITE);
//
//}

//http://www.geisswerks.com/ryan/FAQS/timing.html