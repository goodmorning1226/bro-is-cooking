#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;


bool isMouseOn(sf :: Vector2f mousePos, sf :: Vector2f startPos, sf :: Vector2f endPos);  //判斷滑鼠是否在給予範圍之上 


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
		bool accountUsing(){return this->highestScore == -1 ? false : true;}  //判斷目前是否正在使用帳號 
		bool playerExist(string name);  //確認輸入名稱是否存在 
		void changeAccount(string name);  //更換目前使用帳號 
		void addAccount(string name);  //新增玩家帳號 
		void updateHighestScore(int newScore);  //更新目前使用玩家最高分 
		string getName(){return this->name;} 
		int getHiScore(){return this->highestScore;}
		
}; 

class Ingredient{
	protected:
		int id;
		sf :: Texture texture;  //食材圖片 
		sf :: Vector2f size;  //食材大小 
		sf :: Sprite image;  //食材sprite 
		sf :: Vector2f position;  //食材位置 
		sf :: Vector2f scale;  //食材大小縮放比例 
	
	public:
		Ingredient(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale);  //constructor 
		void setPos(sf :: Vector2f newPos);  //設定食材新位置 
		virtual bool isMouseOn(sf :: Vector2f mousePos);  //判斷滑鼠是否在食材上 
		bool overlap(const sf :: Vector2f startPos, const sf :: Vector2f endPos);  //判斷食材是否和傳入範圍重疊 
		sf :: Vector2f getSize(){return this->size;} 
		sf :: Vector2f getScale(){return this->scale;}
		sf :: Vector2f getPosition(){return this->position;}
		sf :: Sprite& getSprite(){return this->image;} 
		int getId(){return this->id;}
	
};

Ingredient* createIngredient(int ingreType);  //創建該編號食材並回傳新創食材指標 

class Oven{
	private:
		Ingredient* meat[4];  //紀錄烤爐上的肉物件 
		sf :: Clock* cookingTime[4];  //紀錄每個位置的烤肉放上烤爐後過的時間 
		sf :: Time* accumulatedTime[4];  //紀錄烤爐上的肉拿起前所累積的烤肉時間 
		bool isTimeStop[4];  //判斷是否暫停時間(烤爐上的肉被拿起) 
		bool firstStageCooking[4];  //判斷烤肉階段(第一階烤熟，第二階烤焦) 
		bool secondStageCooking[4];
		sf :: Vector2f meatPosition[4];  //紀錄烤爐上的肉的位置 
		
	public:
		Oven();  //constructor 
		~Oven();  //destructor
		int getMeatCnt();  //回傳烤爐上的肉的數量 
		int mouseOnMeat(sf :: Vector2f mousePos);  //判斷滑鼠在哪個烤爐上的肉上，若無則回傳-1 
		void checkCookingTime();  //檢查肉放上烤爐經過時間 
		void timeStop(int index);  //暫停其中一烤爐上的肉的烤肉時間 
		void timeRestart(int index);  //回復其中一烤爐上的肉的烤肉時間 
		void addMeat();  //增加烤爐肉 
		void removeMeat(int index);  //刪除某一烤爐肉 
		void setBackPosition(int index);  //將烤爐上的肉的位置設回初始位置 
		void drawMeat(sf :: RenderWindow& window);  //畫出烤爐肉 
		
		Ingredient* operator[](int index);  //回傳某一烤爐肉物件 
};

class Hamburger : public Ingredient{
	private:
		vector<Ingredient*> ingreStack;  //紀錄漢堡內的Ingredient物件 
		
		static const int maxIngredientCnt;  //最大漢堡內食材數量 
		static const int ingredientOffsetY;  //漢堡食材間隔 
		
	public:
		Hamburger(sf :: Vector2f pos, sf :: Vector2f scale);  //constructor 
		~Hamburger();  //destructor
		void addIngredient(int ingreType);  //增加漢堡食材（最多8個） 
		void setBackPosition();  //將漢堡位置移回漢堡盤 
		void update();  //更新漢堡食材位置至漢堡位置（因漢堡是虛物件） 
		int getSize(){return ingreStack.size();}  //回傳漢堡食材數量 
		void setIngreScale(sf :: Vector2f newScale);  //將漢堡內所有材料等比例縮放
		bool isMouseOn(sf :: Vector2f mousePos);  //判斷滑鼠是否在漢堡上 
		void drawHamburger(sf :: RenderWindow& window);  //畫出漢堡的所有食材 
		vector<int> get_ingre_stack();  //回傳漢堡內食材編號vector 
		
};

class Customer : public Ingredient{
	private:
		vector<vector<int>>orderlist;  //客人漢堡訂單 
		vector<Hamburger*> orderHamburger;  //客人訂單的漢堡的物件（顯示用） 
		int beer_order;  //客人酒訂單 
		sf::Time waitTime;  //客人等待時間 
		sf::Clock arriveTime;  //客人計時器（自抵達時間開始計） 
		int beerServedCnt;  //客人獲得的酒的數量 
		sf :: Text beerText;  //酒需要數量的文字顯示 
		Ingredient* beerImage;  //酒物件（顯示用） 
		Ingredient* orderBox;  //客人訂單對話框（顯示用）
		sf :: Texture timerTexture; //客人計時器圖片 
		sf :: Sprite timer;  //客人計時器（顯示用） 
		static int level;  //整體客人等級（難度） 
		
	public:
		Customer(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale, sf :: Font& font, sf :: Image& initialTimer);
		~Customer();
		static void set_level(int change_level);  //設定客人難度 
		bool check_order(Hamburger* target);  //檢查給予漢堡是否和客人訂單相同 
		bool angry_leave();  //客人等待時間抵達且訂單未滿足則離開 
		void beerServed();  //判斷客人酒訂單是否滿足 
		bool is_served();  //客人訂單被滿足則離開 
		void drawCustomer(sf :: RenderWindow& window);  //畫出客人及其相關物件 
		void timerUpdate(sf :: Image timerImg[], int timerImgCnt);  //更新客人計時器 
		
};

class HeartAndScore{
	private:
		sf :: Texture heartImg;
		sf :: Sprite heart;
		sf :: Text score;
		
	public:
		HeartAndScore(sf :: Font& font, sf :: Image& initialHeart);  //constructor（傳入玩家初始血量圖） 
		~HeartAndScore(); 
		void update(int heart, int score, sf :: Image heartImg[]);  //更新目前血量和分數顯示 
		void drawHeartAndScore(sf :: RenderWindow& window);  //畫出血量和分數 
		
};
