class shader{
	public:

		//Program Object (for our shader)
		GLuint ShaderProgramm = 0;

		std::string fs_data;
		std::string vs_data;

;

		
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
				std::cout << "copilation succes\n";
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
