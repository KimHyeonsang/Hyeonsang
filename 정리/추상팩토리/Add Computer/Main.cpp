#include"Computer.h"

void main()
{
	Computer* apple = new appleComputer();
	Computer* samsang = new SamsangComputer();
	Computer* LG = new LGComputer();

	apple->Setting(new appleKeybord(), new appleMouse());
	samsang->Setting(new samsangKeybord(), new samsangMouse());
	LG->Setting(new LGKeybord(), new LGMouse());
}