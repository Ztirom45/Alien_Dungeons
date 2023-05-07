class player{
	public:
		glm::vec3 pos = glm::vec3(0.0f,-8.0f,-5.0f);//offset form camera pos
		glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f);//rotation of player model
		mesh player_model;
		int lives = 10;
		int speed = 5;
		
		
		void setup_model(){
			float W = 20;
			float H = 14;
			std::vector<RectF> texRects = {
				(RectF){0.0f,0.0f,0.5f,10.0f/H},
				(RectF){0.5f,0.0f,0.5f,10.0f/H},
				(RectF){0.0f,10.0f/H,8.0f/W,4.0f/H},
				(RectF){8.0f/W,10.0f/H,4.0f/W,4.0f/H},
				(RectF){12.0f/W,10.0f/H,3.0f/W,3.0f/H},
			};
			
			/*                		 A
			   ###            		 |
			   ###      ----0.8		1.8
			#-#####-#   ----0.3/0.4	 |
			   # #      ----0		 |
			*/
			//head
			player_model.add_cube({-0.5,0.8,-0.5},
				{	texRects[0],
					texRects[0],
					texRects[0],
					texRects[1],
					texRects[0],
					texRects[0],

				},{1,1,1,1,1,1},1);
			
			//body
			player_model.add_cube({-0.4,0.4,-0.2},
				{	texRects[2],
					texRects[2],
					texRects[3],
					texRects[2],
					texRects[2],
					texRects[3],

				},{1,1,1,1,1,1},0.4,{2.0f,1.0f,1.0f});
			
			//left hand
			player_model.add_cube({-0.7,0.3,0},
				{	texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],

				},{1,1,1,1,1,1},0.3);
			
			//right Hand
			player_model.add_cube({0.4,0.3,0},
				{	texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],

				},{1,1,1,1,1,1},0.3);
			
			//left foot
			player_model.add_cube({-0.5,0,-0.1},
				{	texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],

				},{1,1,1,1,1,1},0.4);
			//right foot
			player_model.add_cube({0.1,0,-0.1},
				{	texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],

				},{1,1,1,1,1,1},0.4);
		};
		
		void update(){
			//lives
			if(lives<=0){
				loop = false;
			}
		};
};

static player my_player;
