void load_GL_textures(){
	
	if (DIR *dir = opendir("img")) {
		while (dirent *f = readdir(dir)) {
			if (!f || f->d_name[0] == '.')
				continue; // skip hidden files
			
			//load SDL surface
			char str[64] = "img/";
			strcat(str, f->d_name);
			SDL_Surface* surface 	= IMG_Load(str);
			
			//glut image
			glGenTextures(1, &textures[str]);
			glBindTexture(GL_TEXTURE_2D, textures[str]);
			
			//texture settings: cord up to 0 and 1
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			//texture settings: scale filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			
			//generate image
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,surface->w,surface->h,0,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);
			
			//clear surface
			SDL_FreeSurface(surface);
		}
		closedir(dir);
	}else{//error if directory doens't exist
		printf("error: couldn't find diretory `img`");
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
