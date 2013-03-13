#include "cTimer.h"

void cTimer::Inizio()
{
	QueryPerformanceFrequency(&CPUFreq);
	QueryPerformanceCounter(&t1);

}

void cTimer::Resetta()
{
	QueryPerformanceCounter(&t1);
}

double cTimer::SecondiPassati()
{
	QueryPerformanceCounter(&t2);
	return double(t2.QuadPart-t1.QuadPart)/CPUFreq.QuadPart;
}
