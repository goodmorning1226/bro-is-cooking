#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;


bool isMouseOn(sf :: Vector2f mousePos, sf :: Vector2f startPos, sf :: Vector2f endPos);  //�P�_�ƹ��O�_�b�����d�򤧤W 


struct PlayerInfo{
    string name;
    int score;
};

bool compareByScore(const PlayerInfo& a, const PlayerInfo& b);

class Player{
	private:
		string name;
		int highestScore;
	
	public:
		Player();
		bool accountUsing(){return this->highestScore == -1 ? false : true;}  //�P�_�ثe�O�_���b�ϥαb�� 
		bool playerExist(string name);  //�T�{��J�W�٬O�_�s�b 
		void changeAccount(string name);  //�󴫥ثe�ϥαb�� 
		void addAccount(string name);  //�s�W���a�b�� 
		void updateHighestScore(int newScore);  //��s�ثe�ϥΪ��a�̰��� 
		string getName(){return this->name;} 
		int getHiScore(){return this->highestScore;}
		
}; 

class Ingredient{
	protected:
		int id;
		sf :: Texture texture;  //�����Ϥ� 
		sf :: Vector2f size;  //�����j�p 
		sf :: Sprite image;  //����sprite 
		sf :: Vector2f position;  //������m 
		sf :: Vector2f scale;  //�����j�p�Y���� 
	
	public:
		Ingredient(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale);  //constructor 
		void setPos(sf :: Vector2f newPos);  //�]�w�����s��m 
		virtual bool isMouseOn(sf :: Vector2f mousePos);  //�P�_�ƹ��O�_�b�����W 
		bool overlap(const sf :: Vector2f startPos, const sf :: Vector2f endPos);  //�P�_�����O�_�M�ǤJ�d���| 
		sf :: Vector2f getSize(){return this->size;} 
		sf :: Vector2f getScale(){return this->scale;}
		sf :: Vector2f getPosition(){return this->position;}
		sf :: Sprite& getSprite(){return this->image;} 
		int getId(){return this->id;}
	
};

Ingredient* createIngredient(int ingreType);  //�Ыظӽs�������æ^�Ƿs�Э������� 

class Oven{
	private:
		Ingredient* meat[4];  //�����N�l�W���ת��� 
		sf :: Clock* cookingTime[4];  //�����C�Ӧ�m���N�ש�W�N�l��L���ɶ� 
		sf :: Time* accumulatedTime[4];  //�����N�l�W���׮��_�e�Ҳֿn���N�׮ɶ� 
		bool isTimeStop[4];  //�P�_�O�_�Ȱ��ɶ�(�N�l�W���׳Q���_) 
		bool firstStageCooking[4];  //�P�_�N�׶��q(�Ĥ@���N���A�ĤG���N�J) 
		bool secondStageCooking[4];
		sf :: Vector2f meatPosition[4];  //�����N�l�W���ת���m 
		
	public:
		Oven();  //constructor 
		~Oven();  //destructor
		int getMeatCnt();  //�^�ǯN�l�W���ת��ƶq 
		int mouseOnMeat(sf :: Vector2f mousePos);  //�P�_�ƹ��b���ӯN�l�W���פW�A�Y�L�h�^��-1 
		void checkCookingTime();  //�ˬd�ש�W�N�l�g�L�ɶ� 
		void timeStop(int index);  //�Ȱ��䤤�@�N�l�W���ת��N�׮ɶ� 
		void timeRestart(int index);  //�^�_�䤤�@�N�l�W���ת��N�׮ɶ� 
		void addMeat();  //�W�[�N�l�� 
		void removeMeat(int index);  //�R���Y�@�N�l�� 
		void setBackPosition(int index);  //�N�N�l�W���ת���m�]�^��l��m 
		void drawMeat(sf :: RenderWindow& window);  //�e�X�N�l�� 
		
		Ingredient* operator[](int index);  //�^�ǬY�@�N�l�ת��� 
};

class Hamburger : public Ingredient{
	private:
		vector<Ingredient*> ingreStack;  //�����~������Ingredient���� 
		
		static const int maxIngredientCnt;  //�̤j�~���������ƶq 
		static const int ingredientOffsetY;  //�~���������j 
		
	public:
		Hamburger(sf :: Vector2f pos, sf :: Vector2f scale);  //constructor 
		~Hamburger();  //destructor
		void addIngredient(int ingreType);  //�W�[�~�������]�̦h8�ӡ^ 
		void setBackPosition();  //�N�~����m���^�~���L 
		void update();  //��s�~��������m�ܺ~����m�]�]�~���O�ꪫ��^ 
		int getSize(){return ingreStack.size();}  //�^�Ǻ~�������ƶq 
		void setIngreScale(sf :: Vector2f newScale);  //�N�~�����Ҧ����Ƶ�����Y��
		bool isMouseOn(sf :: Vector2f mousePos);  //�P�_�ƹ��O�_�b�~���W 
		void drawHamburger(sf :: RenderWindow& window);  //�e�X�~�����Ҧ����� 
		vector<int> get_ingre_stack();  //�^�Ǻ~���������s��vector 
		
};

class Customer : public Ingredient{
	private:
		vector<vector<int>>orderlist;  //�ȤH�~���q�� 
		vector<Hamburger*> orderHamburger;  //�ȤH�q�檺�~��������]��ܥΡ^ 
		int beer_order;  //�ȤH�s�q�� 
		sf::Time waitTime;  //�ȤH���ݮɶ� 
		sf::Clock arriveTime;  //�ȤH�p�ɾ��]�۩�F�ɶ��}�l�p�^ 
		int beerServedCnt;  //�ȤH��o���s���ƶq 
		sf :: Text beerText;  //�s�ݭn�ƶq����r��� 
		Ingredient* beerImage;  //�s����]��ܥΡ^ 
		Ingredient* orderBox;  //�ȤH�q���ܮء]��ܥΡ^
		sf :: Texture timerTexture; //�ȤH�p�ɾ��Ϥ� 
		sf :: Sprite timer;  //�ȤH�p�ɾ��]��ܥΡ^ 
		static int level;  //����ȤH���š]���ס^ 
		
	public:
		Customer(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale, sf :: Font& font, sf :: Image& initialTimer);
		~Customer();
		static void set_level(int change_level);  //�]�w�ȤH���� 
		bool check_order(Hamburger* target);  //�ˬd�����~���O�_�M�ȤH�q��ۦP 
		bool angry_leave();  //�ȤH���ݮɶ���F�B�q�楼�����h���} 
		void beerServed();  //�P�_�ȤH�s�q��O�_���� 
		bool is_served();  //�ȤH�q��Q�����h���} 
		void drawCustomer(sf :: RenderWindow& window);  //�e�X�ȤH�Ψ�������� 
		void timerUpdate(sf :: Image timerImg[], int timerImgCnt);  //��s�ȤH�p�ɾ� 
		
};

class HeartAndScore{
	private:
		sf :: Texture heartImg;
		sf :: Sprite heart;
		sf :: Text score;
		
	public:
		HeartAndScore(sf :: Font& font, sf :: Image& initialHeart);  //constructor�]�ǤJ���a��l��q�ϡ^ 
		~HeartAndScore(); 
		void update(int heart, int score, sf :: Image heartImg[]);  //��s�ثe��q�M������� 
		void drawHeartAndScore(sf :: RenderWindow& window);  //�e�X��q�M���� 
		
};
