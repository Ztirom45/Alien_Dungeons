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
		
		void add_point(vec3f pos,vec3f col,vec2f tex,int position){//if posion == 0 resize else add to position
			//resize and get loacation
			
			if(position==-1){//save performence if a rect resizes only one time
				int last_size = vertex_pos.size()/3;
				vertex_pos.resize((last_size+1)*3);
				vertex_col.resize((last_size+1)*3);
				vertex_tex.resize((last_size+1)*2);
				position = last_size;
			}
			//add position
			vertex_pos[position*3+0] = pos.x;
			vertex_pos[position*3+1] = pos.y;
			vertex_pos[position*3+2] = pos.z;
			//add color
			vertex_col[position*3+0] = col.x;
			vertex_col[position*3+1] = col.y;
			vertex_col[position*3+2] = col.z;
			//add texture
			vertex_tex[position*2+0] = tex.x;
			vertex_tex[position*2+1] = tex.y;
		};
		
		//directions 1: xy 2: xz 3: yz
		void add_rect(RectF pos,float depth,int direction,RectF tex,int position){
				
			//resize vertex arrays
			int rect_last_size = position;
			if(position == -1){
				rect_last_size = vertex_pos.size()/3;
				vertex_pos.resize((rect_last_size+6)*3);
				vertex_col.resize((rect_last_size+6)*3);
				vertex_tex.resize((rect_last_size+6)*2);
			}
			
			//add vertex
			if(direction == 1){

					
					add_point({pos.x		,pos.y,			depth},{1,1,1},{tex.x,		tex.y		},rect_last_size+0);
					add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+1);
					add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+2);
					
					add_point({pos.x+pos.w	,pos.y+pos.h,	depth},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+3);
					add_point({pos.x		,pos.y+pos.h,	depth},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+4);
					add_point({pos.x+pos.w	,pos.y,			depth},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+5);
					
			}else if(direction==2){//xz
					add_point({pos.x		,depth,	pos.y,			},{1,1,1},{tex.x,		tex.y		},rect_last_size+0);
					add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+1);
					add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+2);
					
					add_point({pos.x		,depth,	pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+3);
					add_point({pos.x+pos.w	,depth,	pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+4);
					add_point({pos.x+pos.w	,depth,	pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+5);
			}else if(direction == 3){//yz
					add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+0);
					add_point({depth,	pos.x		,pos.y,			},{1,1,1},{tex.x,		tex.y		},rect_last_size+1);
					add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+2);
					
					add_point({depth,	pos.x+pos.w	,pos.y+pos.h,	},{1,1,1},{tex.x+tex.w,tex.y+tex.h	},rect_last_size+3);
					add_point({depth,	pos.x		,pos.y+pos.h,	},{1,1,1},{tex.x,		tex.y+tex.h	},rect_last_size+4);
					add_point({depth,	pos.x+pos.w	,pos.y,			},{1,1,1},{tex.x+tex.w,tex.y		},rect_last_size+5);
			}
		};
		
		//pages: Buttom,Down,Left,Front,Top,Right
		void add_cube(vec3f pos,vec6i page_texture,vec6b enabled_pages){
			
			//resize
			int quad_last_size = vertex_pos.size()/3;
			
			//6pages  6points per page 3 codinates per point
			vertex_pos.resize((quad_last_size+6*6)*3);
			vertex_col.resize((quad_last_size+6*6)*3);
			vertex_tex.resize((quad_last_size+6*6)*2);
			
			if(enabled_pages.v1){
				add_rect({pos.x,pos.y,1,1},pos.z,1,get_texture_quad(page_texture.v1),quad_last_size);
			}
			if(enabled_pages.v2){
				add_rect({pos.x,pos.z,1,1},pos.y,2,get_texture_quad(page_texture.v2),quad_last_size+6);
			}
			if(enabled_pages.v3){
				add_rect({pos.y,pos.z,1,1},pos.x,3,get_texture_quad(page_texture.v3),quad_last_size+12);
			}
			
			if(enabled_pages.v4){
				add_rect({pos.x,pos.y,1,1},pos.z+1,1,get_texture_quad(page_texture.v4),quad_last_size+18);
			}
			if(enabled_pages.v5){
				add_rect({pos.x,pos.z,1,1},pos.y+1,2,get_texture_quad(page_texture.v5),quad_last_size+24);
			}
			if(enabled_pages.v6){
				add_rect({pos.y,pos.z,1,1},pos.x+1,3,get_texture_quad(page_texture.v6),quad_last_size+30);
			}
			
		};
		/*
		void add_cube(vec3f pos,vec6i page_texture,vec6b enabled_pages,int cube_size){
			
			if(enabled_pages.v1){
				add_rect({pos.x,pos.y,cube_size,cube_size},pos.z,1,get_texture_quad(page_texture.v1));
			}
			if(enabled_pages.v2){
				add_rect({pos.x,pos.z,cube_size,cube_size},pos.y,2,get_texture_quad(page_texture.v2));
			}
			if(enabled_pages.v3){
				add_rect({pos.y,pos.z,cube_size,cube_size},pos.x,3,get_texture_quad(page_texture.v3));
			}
			
			if(enabled_pages.v4){
				add_rect({pos.x,pos.y,cube_size,cube_size},pos.z+cube_size,1,get_texture_quad(page_texture.v4));
			}
			if(enabled_pages.v5){
				add_rect({pos.x,pos.z,cube_size,cube_size},pos.y+cube_size,2,get_texture_quad(page_texture.v5));
			}
			if(enabled_pages.v6){
				add_rect({pos.y,pos.z,cube_size,cube_size},pos.x+cube_size,3,get_texture_quad(page_texture.v6));
			}
			
		};
		* */
};

static mesh my_mesh;
