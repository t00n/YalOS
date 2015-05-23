#ifndef __TIMER_H
#define __TIMER_H
#include "irq.h"

int timer_ticks;
int timer_seconds;

void timer_phase(int hz);

void timer_handler(struct regs* r);

void timer_install();


#endif
