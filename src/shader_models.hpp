/*
class to controll model transformation and via a graphic pipeline
*/

class shader_model{
	public:
		//vars

		glm::vec3 position = glm::vec3(-4.0f,-4.0f,-4.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		
		glm::mat4 Transformation_mat4;
		glm::mat4 rotation_mat4;
		
		void update_transformation(){
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
		
		void update(){
			//transformation
			GLint TransformationLocation = glGetUniformLocation(ShaderObject.ShaderProgramm,"model_Transformation");
			
			//Transformation Matrix
			
			update_transformation();
			if(TransformationLocation>=0){
				glUniformMatrix4fv(TransformationLocation,1,GL_FALSE,&Transformation_mat4[0][0]);
			}else{
				std::cout << "error: couldn't find model Transformation\n";
				//exit(EXIT_FAILURE);
			}
			
			//Rotation
			GLint RotationLocation = glGetUniformLocation(ShaderObject.ShaderProgramm,"model_Rotation");
			
			//Rotatation Matrix
			
			update_rotation();
			
			if(RotationLocation>=0){
				glUniformMatrix4fv(RotationLocation,1,GL_FALSE,&rotation_mat4[0][0]);
			}else{
				std::cout << "error: couldn't find model rotation\n";
				//exit(EXIT_FAILURE);
			}
			
			
		};

};

shader_model ShaderModelObject;
