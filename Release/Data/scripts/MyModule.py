import bpMath
import bpTime
import bpUtil
from bpInput import *

bShowFps = False;

def Speak():
	global bShowFps;
	bpUtil.ConsoleClear();
	if(bpTime.DeltaTime() != 0):
		if(KeyPress(KEY.KEY_0) or KeyPress(KEY.NUMPAD0)):
			bShowFps = not bShowFps;
		if(bShowFps == True):
			print(( 1 / bpTime.DeltaTime()));
	
	f2MousePos = CursorPos();
	print(f2MousePos.X);
	print(f2MousePos.Y);
	CursorShow(bShowFps);
	print(bShowFps);
	return;