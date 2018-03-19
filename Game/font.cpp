#include "font.h"
#include <map>

std::map<const char*, TTF_Font*> cached_fonts;

TTF_Font* ui::load_font(const char* file_name, int font_size) {
	if (cached_fonts.find(file_name) != cached_fonts.end()) {
		return cached_fonts[file_name];
	}

	TTF_Font* font = TTF_OpenFont(file_name, font_size);
	cached_fonts[file_name] = font;
	return font;
}

void ui::clean_up_fonts() {
	for (auto font_pair : cached_fonts) {
		TTF_CloseFont(font_pair.second);
	}
	cached_fonts.clear();
}