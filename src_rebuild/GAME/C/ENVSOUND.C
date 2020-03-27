#include "THISDUST.H"
#include "ENVSOUND.H"


// decompiled code
// original method signature: 
// void /*$ra*/ AddEnvSounds(int level /*$a0*/, int time /*$a1*/)
 // line 41, offset 0x00044f60
	/* begin block 1 */
		// Start line: 82
	/* end block 1 */
	// End Line: 83

void AddEnvSounds(int level,int time)

{
  char flags;
  int sample;
  int local_30;
  undefined *local_2c;
  long local_28;
  
  if (time == 3) {
    level = level + 4;
  }
  switch(level) {
  case 0:
    AddEnvSnd(1,'\0',4,2,0,-0x36ffb,0xa4bf0);
    AddEnvSnd(1,'\0',4,2,0,0x12002,-0x57c06);
    AddEnvSnd(1,'\x10',4,3,0,0x2b624,(long)&LAB_00012ebc);
  case 4:
    AddEnvSnd(1,'\x10',4,0,-5000,(long)&DAT_00008d9a,-0x28c8a);
    AddEnvSnd(1,'\x10',4,0,-5000,(long)&DAT_00008d9a,-0x2673c);
    flags = '\x10';
    sample = 0;
    local_30 = -5000;
    local_2c = &DAT_00008d9a;
    local_28 = -0x1368c;
    goto LAB_00045498;
  case 1:
    AddEnvSnd(3,'\0',4,2,2000,-0x38ba8,-0x41096);
    AddEnvSnd(3,'\0',4,2,2000,0x3d928,-0x1d2cc);
    break;
  case 2:
  case 6:
    AddEnvSnd(1,'\x10',4,1,-6000,0x2b3cc,(long)PTR_ARRAY_000e0254);
    AddEnvSnd(1,'\x10',4,1,-6000,(long)&DAT_00004268,0xbfc5c);
    return;
  case 3:
  case 7:
    AddEnvSnd(1,'\x10',4,3,-5000,-0x50b68,0x2641c);
    AddEnvSnd(1,'\x10',4,3,-5000,-0x14a14,0x634ac);
    AddEnvSnd(1,'\x10',4,3,-5000,-0x37398,-0x7f198);
    AddEnvSnd(1,'\x10',4,3,-5000,(long)&DAT_00009182,-0x62444);
    AddEnvSnd(4,'\x18',4,3,-5000,(long)&DAT_00009470,-0x610bc);
    AddEnvSnd(1,'\x10',4,3,-5000,0x279fc,-130000);
    AddEnvSnd(3,'\0',4,0,-1000,0x2b110,-0x2fda0);
    AddEnvSnd(3,'\0',4,0,-1000,0x27ac4,-0x2fb48);
    AddEnvSnd(3,'\0',4,0,-1000,-75000,-0x5a5b4);
    AddEnvSnd(3,'\0',4,0,-1000,-93000,-0x5a80c);
    AddEnvSnd(3,'\0',4,0,-1000,-0x1b0d0,-0x5abf4);
    AddEnvSnd(3,'\0',4,0,-1000,-0x1e58c,-0x5dfe8);
    AddEnvSnd(3,'\0',4,0,-1000,-0x2321c,-0x5dfe8);
    AddEnvSnd(3,'\0',4,0,-1000,-0x27f10,-0x5dad4);
    AddEnvSnd(3,'\0',4,0,-1000,-0x2dadc,-0x5dc64);
    AddEnvSnd(3,'\0',4,0,-1000,-0x2f058,-0x5d174);
    AddEnvSnd(3,'\0',4,0,-1000,-0x30958,-0x5909c);
    AddEnvSnd(3,'\0',4,0,-1000,-0x3370c,-0x58bec);
    AddEnvSnd(3,'\0',4,0,-1000,-0x33edc,-0x4c9c8);
    AddEnvSnd(3,'\0',4,0,-1000,-0x33b58,-0x41104);
    AddEnvSnd(3,'\0',4,0,-1000,-0x1caca,-0x44430);
    AddEnvSnd(3,'\0',4,0,-1000,-0x1fc34,-0x494a8);
    AddEnvSnd(3,'\0',4,0,-1000,-0x227f4,-0x5071c);
    AddEnvSnd(3,'\0',4,0,-1000,-0x1ad1a,-0x51018);
    AddEnvSnd(3,'\0',4,0,-1000,-0x15536,-0x512a2);
    AddEnvSnd(3,'\0',4,0,-1000,-0x12976,-0x52116);
    return;
  case 5:
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x1bcec,-0x2c308);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x1895c,-0x3f0ca);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x2d6f4,-0x4e908);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x44df4,-0x49da4);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x42a68,-0x499bc);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-300000,-0x32ed8);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x22ca4,-0x1f464);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x4293c,-0x1bf44);
    AddEnvSnd(1,'\x10',4,3,-0x1194,-0x25a58,-0x1ed5c);
    break;
  default:
    return;
  }
  AddEnvSnd(1,'\0',4,4,-0xdac,0x4f236,-0x58dae);
  flags = '\0';
  sample = 4;
  local_30 = -0xdac;
  local_2c = (undefined *)0x52e2c;
  local_28 = -0x4fbc8;
LAB_00045498:
  AddEnvSnd(1,flags,4,sample,local_30,(long)local_2c,local_28);
  return;
}





