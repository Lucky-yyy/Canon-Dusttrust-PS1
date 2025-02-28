#include "main.h"

#include "psx/io.h"
#include "psx/gfx.h"
#include "psx/audio.h"
#include "psx/pad.h"
#include "psx/timer.h"

#include "menu/menu.h"
#include "battle/battle.h"

//Game loop
GameLoop gameloop;

//Error handler
char error_msg[0x200];

void ErrorLock(void)
{
	while (1)
	{
		FntPrint("A fatal error has occured\n~c700%s\n", error_msg);
		Gfx_Flip();
	}
}

//Memory heap
#define MEM_STAT //This will enable the Mem_GetStat function which returns information about available memory in the heap

#define MEM_IMPLEMENTATION
#include "psx/mem.h"
#undef MEM_IMPLEMENTATION

#ifndef PSXF_STDMEM
static u8 malloc_heap[0x1B0000];
#endif

//Entry point
int main()
{	
	//Initialize system
	PSX_Init();
	
	Mem_Init((void*)malloc_heap, sizeof(malloc_heap));
	
	IO_Init();
	Audio_Init();
	Gfx_Init();
	Pad_Init(); 
	Timer_Init();
	
	//Loads game
	gameloop = GameLoop_Menu;
	Menu_Load();

	//Game loop
	while (PSX_Running())
	{
		//Prepare frame
		Timer_Tick();
		Pad_Update();

		#ifdef MEM_STAT
			//Memory stats
			size_t mem_used, mem_size, mem_max;
			Mem_GetStat(&mem_used, &mem_size, &mem_max);
			#ifndef MEM_BAR
				FntPrint("mem: %08X/%08X (max %08X)\n", mem_used, mem_size, mem_max);
			#endif
		#endif
		//Tick and draw game
		switch (gameloop)
		{
			case GameLoop_Menu:
				Menu_Tick();
				break;
			case GameLoop_Battle:
				Battle_Tick();
				break;
		}

		//Flip gfx buffers
		Gfx_Flip();
	}

	//Deinitialize system
	Pad_Quit();
	Gfx_Quit();
	Audio_Quit();
	IO_Quit();
	
	PSX_Quit();
	return 0;
}
