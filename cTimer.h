#ifndef CTIMER_H
#define CTIMER_H

#include <Windows.h>
#include <stdio.h>

class cTimer
{
	public:
	LARGE_INTEGER		CPUFreq;
	LARGE_INTEGER		t1, t2;
	
	void Inizio();
	void Resetta();
	double SecondiPassati();
	

};

#endif