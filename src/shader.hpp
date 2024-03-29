class shader{
	public:

		//Program Object (for our shader)
		GLuint ShaderProgramm = 0;

		std::string fs_data;
		std::string vs_data;

		
		void load_vs_file(std::string path){
			std::ifstream myfile(path);
			std::string line;
			vs_data = "";
			if (myfile.is_open()){
				while(getline(myfile,line)){
					vs_data.append(line);
					vs_data.append("\n");
				}
			}else{
				std::cout << "couldn't open vertex shader\n";
			}
			myfile.close();
		};
		
		void load_fs_file(std::string path){
			std::ifstream myfile(path);
			std::string line;
			fs_data = "";
			if (myfile.is_open()){
				while(getline(myfile,line)){
					fs_data.append(line);
					fs_data.append("\n");
				}
			}else{
				std::cout << "couldn't open fragment shader\n";
			}
			myfile.close();
		};
		
		GLuint CompileShader(GLuint type, const std::string& code){
			GLuint shaderObject;
			
			shaderObject = glCreateShader(type);
			
			const char* c_code = code.c_str();
			glShaderSource(shaderObject,1,&c_code, nullptr);
			glCompileShader(shaderObject);
			
			//error messages
			GLint success;
			glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
			
			if (success != GL_TRUE) {
				GLint info_log_length;
				glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &info_log_length);
				
				std::cout <<"log len:"<< info_log_length<< "\n";
				
				size_t log_len_size = info_log_length;
				GLchar* info_log;
				info_log = (GLchar*)malloc(log_len_size);
				glGetShaderInfoLog(shaderObject, info_log_length, NULL, info_log);
				
				printf("failed to compile shader:\n%s\n", info_log);
				free(info_log);
			}else{
				printf("compilation success\n");//no error
				//std::cout << "compilation success\n";//error
			}
			
			return shaderObject;
		};

		void CreateShader(){
			ShaderProgramm = glCreateProgram();
			
			GLuint VetexShader = CompileShader(GL_VERTEX_SHADER,vs_data);
			GLuint FragmentShader = CompileShader(GL_FRAGMENT_SHADER,fs_data);
			
			glAttachShader(ShaderProgramm,VetexShader);
			glAttachShader(ShaderProgramm,FragmentShader);
			glLinkProgram(ShaderProgramm);
			
			//validate our program
			glValidateProgram(ShaderProgramm);
			//glDetachShader, glDetachShader
		};
};

static shader ShaderObject;

//send texture via graphics pipeline
void update_textures(std::string texture_name){//name of texture in map
			
			//thanks to https://stackoverflow.com/questions/34432414/how-are-textures-referenced-in-shaders
			GLint TextureLocation = glGetUniformLocation(ShaderObject.ShaderProgramm, "Texture");
			GLuint texture_id = textures[texture_name];
			
			if(TextureLocation>=0){
				glActiveTexture(GL_TEXTURE0+0);//texture at position 0
				glBindTexture(GL_TEXTURE_2D, texture_id);
				
				glUniform1i(TextureLocation,0);//texture from position 0
			}else{
				std::cout << "error: couldn't find Texture\n";
				//exit(EXIT_FAILURE);
			}
}

