#include <SDL_ttf.h>

#ifndef FONT_H
#define FONT_H

namespace ui {

	TTF_Font* load_font(const char* file_name, int font_size);
	void clean_up_fonts();

}

#endif // !FONT_H