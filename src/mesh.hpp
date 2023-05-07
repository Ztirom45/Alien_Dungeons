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
		
		std::string texture = "img/tiles.png";
		
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
			//number of quads to draw
			int quads_num =	 (int)enabled_pages.v1
							+(int)enabled_pages.v2
							+(int)enabled_pages.v3
							+(int)enabled_pages.v4
							+(int)enabled_pages.v5
							+(int)enabled_pages.v6;
			
			//6pages  6points per page 3 codinates per point
			vertex_pos.resize((quad_last_size+6*quads_num)*3);
			vertex_col.resize((quad_last_size+6*quads_num)*3);
			vertex_tex.resize((quad_last_size+6*quads_num)*2);
			
			//counts every page, so that the gap will be leaved out
			int page_counter = 0;
			
			if(enabled_pages.v1){
				add_rect({pos.x,pos.y,1,1},pos.z,1,get_texture_quad(page_texture.v1),quad_last_size);
				page_counter++;
			}
			if(enabled_pages.v2){
				add_rect({pos.x,pos.z,1,1},pos.y,2,get_texture_quad(page_texture.v2),quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v3){
				add_rect({pos.y,pos.z,1,1},pos.x,3,get_texture_quad(page_texture.v3),quad_last_size+6*page_counter);
				page_counter++;
			}
			
			if(enabled_pages.v4){
				add_rect({pos.x,pos.y,1,1},pos.z+1,1,get_texture_quad(page_texture.v4),quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v5){
				add_rect({pos.x,pos.z,1,1},pos.y+1,2,get_texture_quad(page_texture.v5),quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v6){
				add_rect({pos.y,pos.z,1,1},pos.x+1,3,get_texture_quad(page_texture.v6),quad_last_size+6*page_counter);
				page_counter++;
			}
			
		};
		
		void add_cube(vec3f pos,std::vector<RectF> page_texture,vec6b enabled_pages,float cube_size){
			
			printf("%d: %f\n",page_texture.size(),page_texture[4].w);
			//resize
			int quad_last_size = vertex_pos.size()/3;
			//number of quads to draw
			int quads_num =	 (int)enabled_pages.v1
							+(int)enabled_pages.v2
							+(int)enabled_pages.v3
							+(int)enabled_pages.v4
							+(int)enabled_pages.v5
							+(int)enabled_pages.v6;
			
			//6pages  6points per page 3 codinates per point
			vertex_pos.resize((quad_last_size+6*quads_num)*3);
			vertex_col.resize((quad_last_size+6*quads_num)*3);
			vertex_tex.resize((quad_last_size+6*quads_num)*2);
			
			//counts every page, so that the gap will be leaved out
			int page_counter = 0;
			
			if(enabled_pages.v1){
				add_rect((RectF){pos.x,pos.y,cube_size,cube_size},pos.z,1,page_texture[0],quad_last_size);
				page_counter++;
			}
			if(enabled_pages.v2){
				add_rect((RectF){pos.x,pos.z,cube_size,cube_size},pos.y,2,page_texture[1],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v3){
				add_rect((RectF){pos.y,pos.z,cube_size,cube_size},pos.x,3,page_texture[2],quad_last_size+6*page_counter);
				page_counter++;
			}
			
			if(enabled_pages.v4){
				add_rect((RectF){pos.x,pos.y,cube_size,cube_size},pos.z+cube_size,1,page_texture[3],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v5){
				add_rect((RectF){pos.x,pos.z,cube_size,cube_size},pos.y+cube_size,2,page_texture[4],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v6){
				add_rect((RectF){pos.y,pos.z,cube_size,cube_size},pos.x+cube_size,3,page_texture[5],quad_last_size+6*page_counter);
				page_counter++;
			}
			
		};
		
		void add_cube(vec3f pos,std::vector<RectF> page_texture,vec6b enabled_pages,float cube_size,vec3f scale){
			
			printf("%d: %f\n",page_texture.size(),page_texture[4].w);
			//resize
			int quad_last_size = vertex_pos.size()/3;
			//number of quads to draw
			int quads_num =	 (int)enabled_pages.v1
							+(int)enabled_pages.v2
							+(int)enabled_pages.v3
							+(int)enabled_pages.v4
							+(int)enabled_pages.v5
							+(int)enabled_pages.v6;
			
			//6pages  6points per page 3 codinates per point
			vertex_pos.resize((quad_last_size+6*quads_num)*3);
			vertex_col.resize((quad_last_size+6*quads_num)*3);
			vertex_tex.resize((quad_last_size+6*quads_num)*2);
			
			//counts every page, so that the gap will be leaved out
			int page_counter = 0;
			
			if(enabled_pages.v1){
				add_rect((RectF){pos.x,pos.y,cube_size*scale.x,cube_size*scale.y},pos.z*scale.z,1,page_texture[0],quad_last_size);
				page_counter++;
			}
			if(enabled_pages.v2){
				add_rect((RectF){pos.x,pos.z,cube_size*scale.x,cube_size*scale.z},pos.y*scale.y,2,page_texture[1],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v3){
				add_rect((RectF){pos.y,pos.z,cube_size*scale.y,cube_size*scale.z},pos.x,3,page_texture[2],quad_last_size+6*page_counter);
				page_counter++;
			}
			
			if(enabled_pages.v4){
				add_rect((RectF){pos.x,pos.y,cube_size*scale.x,cube_size*scale.y},pos.z+cube_size*scale.z,1,page_texture[3],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v5){
				add_rect((RectF){pos.x,pos.z,cube_size*scale.x,cube_size*scale.z},pos.y+cube_size*scale.y,2,page_texture[4],quad_last_size+6*page_counter);
				page_counter++;
			}
			if(enabled_pages.v6){
				add_rect((RectF){pos.y,pos.z,cube_size*scale.y,cube_size*scale.z},pos.x+cube_size*scale.x,3,page_texture[5],quad_last_size+6*page_counter);
				page_counter++;
			}
			
		};
		
		void setup_mesh(){
			//genereate VAO
			glGenVertexArrays(1,&VertexArrayObject);
			glBindVertexArray(VertexArrayObject);
			
			//generate position VBO at 0
			glGenBuffers(1,&VertexBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER,
				vertex_pos.size()*sizeof(GLfloat),
				vertex_pos.data(),
				GL_STATIC_DRAW);
			
			//linking up the position array
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(	0,
									3,//x,y,z
									GL_FLOAT,
									GL_FALSE,
									0,
									(void*)0
			);
				
			//generate color VBO
			glGenBuffers(1,&VertexBufferObject2);
			glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject2);
			glBufferData(GL_ARRAY_BUFFER,
				vertex_col.size()*sizeof(GLfloat),
				vertex_col.data(),
				GL_STATIC_DRAW);
			
			//linking up the color array
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(	1,
									3,//r,g,b
									GL_FLOAT,//type
									GL_FALSE,//do something with values
									0,
									(void*)0//offset
			);

			//generate texture VBO
			glGenBuffers(1,&VertexBufferObject3);
			glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject3);
			glBufferData(GL_ARRAY_BUFFER,
				vertex_tex.size()*sizeof(GLfloat),
				vertex_tex.data(),
				GL_STATIC_DRAW);
			
			//linking up the texture array
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(	2,//position
									2,//x,y
									GL_FLOAT,//type
									GL_FALSE,//do something with values
									0,
									(void*)0//offset
			);
			
			//unbind Vertex array
			glBindVertexArray(0);
			glBindVertexArray(1);
			glBindVertexArray(2);
			//disable attrib arrays
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
		
		void draw(){
			//send stuff to GPU:
			glBindVertexArray(VertexArrayObject);
			glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
			glDrawArrays(GL_TRIANGLES,0,vertex_pos.size());
		}
		
};

static mesh my_mesh;
