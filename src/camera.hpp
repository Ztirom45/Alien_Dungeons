class Camera{
	public:
		//vars

		glm::vec3 position = glm::vec3(0.0f,0.0f,-2.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec4 perspective = glm::vec4(glm::radians(45.0f),(float)Win_W/Win_H,0.1f,10.0f);
		
		glm::mat4 Transformation_mat4;
		glm::mat4 perspective_mat4;
		glm::mat4 rotation_mat4;
		
		void update_translation(){
			//position
			Transformation_mat4 = glm::translate(glm::mat4(1.0f),position);
		};
		
		void update_rotation(){
			//position
			rotation_mat4 = glm::mat4(
			glm::vec4(1.0f,0.0f,0.0f,0.0f),
			glm::vec4(0.0f,1.0f,0.0f,0.0f),
			glm::vec4(0.0f,0.0f,1.0f,0.0f),
			glm::vec4(0.0f,0.0f,0.0f,1.0f));
			
			//rotatation
			rotation_mat4 = glm::rotate(rotation_mat4, glm::radians(rotation.x), glm::vec3(1,0,0));
			rotation_mat4 = glm::rotate(rotation_mat4, glm::radians(rotation.y), glm::vec3(0,1,0));
			rotation_mat4 = glm::rotate(rotation_mat4, glm::radians(rotation.z), glm::vec3(0,0,1));
		};
		
		void update_perspective(){
			perspective_mat4 = glm::perspective(perspective.x,perspective.y,perspective.z,perspective.w);
		};
		
		void update(){
			//transformation
			GLint TransformationLocation = glGetUniformLocation(ShaderObject.ShaderProgramm,"Transformation");
			
			//Transformation Matrix
			
			update_translation();
			if(TransformationLocation>=0){
				glUniformMatrix4fv(TransformationLocation,1,GL_FALSE,&Transformation_mat4[0][0]);
			}else{
				std::cout << "error: couldn't find Transformation\n";
				//exit(EXIT_FAILURE);
			}
			
			//Rotation
			GLint RotationLocation = glGetUniformLocation(ShaderObject.ShaderProgramm,"Rotation");
			
			//Rotatation Matrix
			
			update_rotation();
			
			if(RotationLocation>=0){
				glUniformMatrix4fv(RotationLocation,1,GL_FALSE,&rotation_mat4[0][0]);
			}else{
				std::cout << "error: couldn't find rotation\n";
				//exit(EXIT_FAILURE);
			}
			
			
			//Projektion in perspective
			GLint PerspectiveLocation = glGetUniformLocation(ShaderObject.ShaderProgramm,"Perspective");
			
			//Projetion Matrix
			update_perspective();
			
			if(PerspectiveLocation>=0){
				glUniformMatrix4fv(PerspectiveLocation,1,GL_FALSE,&perspective_mat4[0][0]);
			}else{
				std::cout << "error: couldn't find perspective\n";
				//exit(EXIT_FAILURE);
			}
			
		};
		void move(glm::vec3 speed){
			float cosa = cos(glm::radians(rotation.y));
			float sina = sin(glm::radians(rotation.y));
			
			//calculate new x,z value
			position.x += speed.z * sina + speed.x * cosa;
			position.z += speed.z * cosa - speed.x * sina;

		};

};

Camera CameraObject;
