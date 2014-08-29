#include "timer.h"

int timer_ticks = 0;
int timer_seconds = 0;

#define HW_CLOCK_FREQ 1000

void timer_phase(int hz)
{
	int divisor = 1193180/hz;
	outportb(0x43, 0x36); // no BCD, rate generator, LSB, counter 0
	outportb(0x40, divisor & 0xFF);
	outportb(0x40, divisor >> 8);
}

void timer_handler(struct regs* r)
{
	++timer_ticks;
	if (timer_ticks == HW_CLOCK_FREQ)
	{
		++timer_seconds;
		timer_ticks = 0;
	}
}

void timer_install()
{
	timer_phase(HW_CLOCK_FREQ);
	irq_install_handler(0, timer_handler);
}
