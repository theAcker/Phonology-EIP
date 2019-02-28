#include "pch.h"
#include "PortAudiopp.h"
#include <iostream>
#include <conio.h>

int main()
{
	PortAudio pa;

	char c = 0;
	while (true)
	{
		if (c == 0)
			std::cout << "Press [space] to start recording" << std::endl;

		c = _getch();
		if (c == 0x20)
		{
			pa.Record(5);
			pa.Playback();
			c = 0;
		}
	}
}