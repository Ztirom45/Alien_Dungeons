/*
mesh stores vertexcdata and have got add functions
*/
/*
textures[] = {
{},
{},
{},
};
*/

class mesh{
	public:
		std::vector<GLfloat> vertex_pos = {};
		std::vector<GLfloat> vertex_col = {};
		std::vector<GLfloat> vertex_tex = {};
		
		void add_point(vec3f pos,vec3f col,vec2f tex,bool resize){
			//resize and get loacation
			int last_size = vertex_pos.size()/3;
			if(resize){//save performence if a rect resizes only one time
				vertex_pos.resize((last_size+1)*3);
				vertex_col.resize((last_size+1)*3);
				vertex_tex.resize((last_size+1)*2);
			}else{
				last_size-=1;
			}
			//add position
			vertex_pos[last_size*3+0] = pos.x;
			vertex_pos[last_size*3+1] = pos.y;
			vertex_pos[last_size*3+2] = pos.z;
			//add color
			vertex_col[last_size*3+0] = col.x;
			vertex_col[last_size*3+1] = col.y;
			vertex_col[last_size*3+2] = col.z;
			//add texture
			vertex_tex[last_size*2+0] = tex.x;
			vertex_tex[last_size*2+1] = tex.y;
			
		};
		
		//directions 1: xy 2: xz 3: yz
		void add_rect(RectF pos,float depth,int direction,RectF tex){
				/*
				//resize vertex arrays
				int last_size = vertex_pos.size()/3;
				vertex_pos.resize((last_size+1)*3)
				vertex_col.resize((last_size+1)*3)
				vertex_texture.resize((last_size+1)*2)
				*/
			//add vertex
			switch(direction){
				case 1://xy
					
					add_point({pos.x		,pos.y,			depth},{1,1,1},{tex.x,		tex.y		},true);
					add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},true);
					
					add_point({pos.x+pos.w	,pos.y+pos.h,	depth},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},true);
					add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},true);
					break;
				case 2://xz
					add_point({pos.x		,depth,	pos.y,			},{1,1,1},{tex.x,		tex.y		},true);
					add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},true);
					
					add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},true);
					add_point({pos.x+pos.w	,depth,	pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},true);
					break;
				case 3://yz
					add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},true);
					add_point({depth,	pos.x		,pos.y,			},{1,1,1},{tex.x,		tex.y		},true);
					add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					
					add_point({depth,	pos.x+pos.w	,pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},true);
					add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},true);
					add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},true);
					break;
			}
		};
		
		//pages: Buttom,Down,Left,Front,Top,Right
		void add_cube(vec3f pos,vec6i page_texture,vec6b enabled_pages){
			
			if(enabled_pages.v1){
				add_rect({pos.x,pos.y,1,1},pos.z,1,get_texture_quad(page_texture.v1));
			}
			if(enabled_pages.v2){
				add_rect({pos.x,pos.z,1,1},pos.y,2,get_texture_quad(page_texture.v2));
			}
			if(enabled_pages.v3){
				add_rect({pos.y,pos.z,1,1},pos.x,3,get_texture_quad(page_texture.v3));
			}
			
			if(enabled_pages.v4){
				add_rect({pos.x,pos.y,1,1},pos.z+1,1,get_texture_quad(page_texture.v4));
			}
			if(enabled_pages.v5){
				add_rect({pos.x,pos.z,1,1},pos.y+1,2,get_texture_quad(page_texture.v5));
			}
			if(enabled_pages.v6){
				add_rect({pos.y,pos.z,1,1},pos.x+1,3,get_texture_quad(page_texture.v6));
			}
			
		}
};

static mesh my_mesh;
