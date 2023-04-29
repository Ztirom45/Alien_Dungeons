void load_GL_textures(){
	
	if (auto dir = opendir("img")) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.')
				continue; // skip hidden files
			
			//load SDL surface
			std::string str(f->d_name);
			str = "img/"+str;
			SDL_Surface* surface 	= IMG_Load(str.c_str());
			
			//glut image
			GLuint texTure = 0;
			glGenTextures(1, &texTure);
			glBindTexture(GL_TEXTURE_2D, texTure);
			
			//texture settings: cord up to 0 and 1
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			//texture settings: scale filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			
			//generate image
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,surface->w,surface->h,0,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);
			
			//add texture to map
			textures[str] = texTure;
			std::cout<<"Includet image: " << str << ":\t" << &textures[str] <<"\n";
			
			//clear surface
			SDL_FreeSurface(surface);
		}
		closedir(dir);
	}
	
}

//tiles
/*
texture:
+---+---+---+---+
|	|	|	|	|
| 0 | 1 | 2 | 3 |
|	|	|	|	|
+---+---+---+---+
index 0 -return> {
0
0
1
0.25
}
*/

RectF get_texture_quad(int index){
	RectF return_rect;
	return_rect.x = ((float)1/ImgTileW)*index;
	return_rect.y = 0;
	return_rect.w = (float)1/ImgTileW;
	return_rect.h = 1;
	return return_rect;
}
