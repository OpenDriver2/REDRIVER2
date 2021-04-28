__heap_base = memTab_end;

SECTIONS {		
		
	OVERLAY __bss_end : NOCROSSREFS SUBALIGN(4)
	{
		.memTab
        {
            memTab_org = .;
			. = 0x50400;
			memTab_end = .;
        }
		
		.path
        {
			KEEP(GameSRC/Game/C/pathfind.o(.text))
			__path_ctor = .;
			KEEP(GameSRC/Game/C/pathfind.o(.text.startup._GLOBAL__*))
			KEEP(GameSRC/Game/C/pathfind.o(.text.*))
			KEEP(GameSRC/Game/C/pathfind.o(.rodata*))
            KEEP(GameSRC/Game/C/pathfind.o(.sdata*))
			KEEP(GameSRC/Game/C/pathfind.o(.data*))
            KEEP(GameSRC/Game/C/pathfind.o(.sbss*))
			KEEP(GameSRC/Game/C/pathfind.o(.bss*))
			KEEP(GameSRC/Game/C/pathfind.o(.ctors))
			
			. = ALIGN(4);
			__path_end = .;			
		}
		
		.lead
        {
			KEEP(GameSRC/Game/C/leadai.o(.text))
			__lead_ctor = .;
			KEEP(GameSRC/Game/C/leadai.o(.text.startup._GLOBAL__*))
			KEEP(GameSRC/Game/C/leadai.o(.text.*))
			KEEP(GameSRC/Game/C/leadai.o(.rodata*))
            KEEP(GameSRC/Game/C/leadai.o(.sdata*))
			KEEP(GameSRC/Game/C/leadai.o(.data*))
            KEEP(GameSRC/Game/C/leadai.o(.sbss*))
			KEEP(GameSRC/Game/C/leadai.o(.bss*))
			KEEP(GameSRC/Game/C/leadai.o(.ctors))
			
			. = ALIGN(4);
			__lead_end = .;			
		}
	}
		
	OVERLAY LOADADDR(.memTab) + SIZEOF(.memTab) : NOCROSSREFS SUBALIGN(4)
	{		
		.mallocTab
        {
            mallocTab_org = .;
			. = 0xD7C00;
			mallocTab_end = .;
        }
	
		.frnt
        {
			KEEP(GameSRC/Game/*.o(.text))
			__frnt_ctor = .;
			KEEP(GameSRC/Game/Frontend/*.o(.text.startup._GLOBAL__*))
			KEEP(GameSRC/Game/Frontend/*.o(.text.*))
			KEEP(GameSRC/Game/Frontend/*.o(.rodata*))
            KEEP(GameSRC/Game/Frontend/*.o(.sdata*))
			KEEP(GameSRC/Game/Frontend/*.o(.data*))
            KEEP(GameSRC/Game/Frontend/*.o(.sbss*))
			KEEP(GameSRC/Game/Frontend/*.o(.bss*))
			KEEP(GameSRC/Game/Frontend/*.o(.ctors))
			
			. = ALIGN(4);
			__frnt_end = .;			
		}
	}
}


