#ifndef PSXF_GUARD_FONT_H
#define PSXF_GUARD_FONT_H

#include "../psx/gfx.h"

//Font types
typedef enum
{
	Font_UT,
} Font;

typedef enum
{
	FontAlign_Left,
	FontAlign_Center,
	FontAlign_Right,
} FontAlign;

typedef struct FontData
{
	//Font functions and data
	s32 (*get_width)(struct FontData *this, const char *text);
	void (*draw_col)(struct FontData *this, const char *text, s32 x, s32 y, FontAlign align, u8 r, u8 g, u8 b);
	void (*draw)(struct FontData *this, const char *text, s32 x, s32 y, FontAlign align);
	
	Gfx_Tex tex;
} FontData;

//Font functions
void FontData_Load(FontData *this, Font font);

#endif
