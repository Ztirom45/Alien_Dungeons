class player{
	public:
		vec3f pos = {0,0,0};
		mesh player_model;
		std::string costume;//texture array
		int lives = 10;
		int speed = 5;
		
		
		void setup_model(){
			player_model.add_cube({pos.x,pos.y,pos.z},{1,1,1,1,1,1},{1,1,1,1,1,1});
		};
		void init(std::string new_costume){
			costume = new_costume;
		};
		
		void pre_draw_model(){
			VertexUpdate(player_model);
		};
		
		void draw_model(){
			draw(player_model);
		}
		
		void update(){
			//lives
			if(lives<=0){
				loop = false;
			}
		};
};

static player my_player;
