class shader{
	public:

		//Program Object (for our shader)
		GLuint ShaderProgramm = 0;

		std::string vs_data = 
			"#version 330\n"
			"in vec4 position;\n"
			"void main() {\n"
			"    gl_Position = vec4(position.x,position.y,position.z,position.w);\n"
			"}\n";

		std::string fs_data = 
			"#version 330\n"
			"out vec4 color;\n"
			"void main() {\n"
			"    color = vec4(1, 0.15, 0.15, 0);\n"
			"}\n";

		GLuint CompileShader(GLuint type, const std::string& code){
			GLuint shaderObject;
			
			shaderObject = glCreateShader(type);
			
			const char* c_code = code.c_str();
			glShaderSource(shaderObject,1,&c_code, nullptr);
			glCompileShader(shaderObject);
			
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
