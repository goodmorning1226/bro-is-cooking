#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "game object.h"
#include "position.h"
using namespace std;

//cheese: 1, cucumber: 2, lettuce: 3, tomato: 4, meat: 5, breadtop: 6, breadbottom: 7, cooked meat: 8, dead meat: 9, hamburger: 10, beer: 11, customer: 12, orderBox: 13
const int timerImgCnt = 24;

int main(){
	sf :: RenderWindow window(sf::VideoMode(1800, 1200), "BRO IS COOKING", sf :: Style :: Titlebar | sf :: Style :: Close);
	
	window.setFramerateLimit(60);
	
	Player player;  //初始化玩家物件 

	sf :: Font font;
	font.loadFromFile("font.ttf");  //字體載入 
	
	//背景圖片載入 
	sf :: Image timerImg[timerImgCnt];  //載入客人計時器圖片 
	for(int i = 0; i < timerImgCnt; i++){
		timerImg[i].loadFromFile("image/timer animation/" + to_string(i + 1) + ".png");
	}
	
	sf :: Image heartImg[3];
	for(int i = 0; i < 3; i++){
		heartImg[i].loadFromFile("image/heart/" + to_string(i + 1) + ".png");
	}
	
	sf :: Texture backgroundImg;  //遊戲背景圖片 
	backgroundImg.loadFromFile("image/background.png");
	
	sf :: Sprite background;
	background.setTexture(backgroundImg);
	background.setPosition(0, 0);
	
	
	sf :: Texture homePageBackgroundImg;  //初始介面背景圖片 
	homePageBackgroundImg.loadFromFile("image/home page background.png");
	
	sf :: Sprite homePageBackground;
	homePageBackground.setTexture(homePageBackgroundImg);
	homePageBackground.setPosition(0, 0);
	
	
	sf :: Texture intro1BackgroundImg;  //遊戲介紹背景圖片1
	intro1BackgroundImg.loadFromFile("image/intro page/intro1.jpg");
	
	sf :: Sprite intro1Background;
	intro1Background.setTexture(intro1BackgroundImg);
	intro1Background.setPosition(0, 0);
	
	sf :: Texture intro2BackgroundImg;  //遊戲介紹背景圖片2
	intro2BackgroundImg.loadFromFile("image/intro page/intro2.png");
	
	sf :: Sprite intro2Background;
	intro2Background.setTexture(intro2BackgroundImg);
	intro2Background.setPosition(0, 0);
	
	sf :: Texture intro3BackgroundImg;  //遊戲介紹背景圖片3
	intro3BackgroundImg.loadFromFile("image/intro page/intro3.jpg");
	
	sf :: Sprite intro3Background;
	intro3Background.setTexture(intro3BackgroundImg);
	intro3Background.setPosition(0, 0);
	
	
	sf :: Texture rankBackgroundImg;  //排名頁面背景圖片 
	rankBackgroundImg.loadFromFile("image/rank.jpg");
	
	sf :: Sprite rankBackground;
	rankBackground.setTexture(rankBackgroundImg);
	rankBackground.setPosition(0, 0);
	
	
	sf :: Texture loginBackgroundImg;  //登入頁面背景圖片 
	loginBackgroundImg.loadFromFile("image/login.jpg");
	
	sf :: Sprite loginBackground;
	loginBackground.setTexture(loginBackgroundImg);
	loginBackground.setPosition(0, 0);
	
	
	sf :: Texture registerBackgroundImg;  //註冊頁面背景圖片 
	registerBackgroundImg.loadFromFile("image/register.jpg");
	
	sf :: Sprite registerBackground;
	registerBackground.setTexture(registerBackgroundImg);
	registerBackground.setPosition(0, 0);
	
	
	sf :: Texture errorBackgroundImg;  //登入失敗頁面背景圖片 
	errorBackgroundImg.loadFromFile("image/error.jpg");
	
	sf :: Sprite errorBackground;
	errorBackground.setTexture(errorBackgroundImg);
	errorBackground.setPosition(0, 0);
	
	
	sf :: Texture gameOverBackgroundImg;  //遊戲結束頁面背景圖片 
	gameOverBackgroundImg.loadFromFile("image/game over.jpg");
	
	sf :: Sprite gameOverBackground;
	gameOverBackground.setTexture(gameOverBackgroundImg);
	gameOverBackground.setPosition(0, 0);
	
	
	bool ingreUsing = false;  //判斷滑鼠是否拿著東西 
	Ingredient* holdingIngredient = nullptr;  //用來儲存目前拿著的東西的指標 
	
	Oven oven;
	bool ovenMeatUsing = false;  //判斷是否拿著烤盤肉 
	int meatHolding = 0;  //判斷要拿的烤盤肉在烤盤上的編號 
	
	Hamburger* hamburger = nullptr;  //儲存漢堡的指標 
	bool hamburgerExist = false;  //判斷現在是否存在漢堡物件 
	bool hamburgerUsing = false;  //判斷是否拿著漢堡 
	
	Customer* customer_list[2] = {nullptr, nullptr};  //客人陣列 
	int order_complete = 0;  //完成訂單數 
	srand(std::time(0)); 
	sf :: Clock customer_Clock;
	sf :: Time customer_spawn_interval;  //客人出現間距 
	
	bool mouseOff = true;
	
	int playerHeart = 3;  //玩家生命 
	
	HeartAndScore* heartAndScore = nullptr;
	
	//判斷目前頁面 
	bool homePage = true;
	
	bool introPage = false;
	bool intro1 = true;
	bool intro2 = false;
	bool intro3 = false;
	
	bool rankPage = false;
	bool rankInitialize = false;
	
	bool loginPage = false;
	bool registerPage = false;
	bool gameStart = false;
	bool gameOver = false;
	bool errorPage = false;
	
	bool gameInitialize = false;
	
	
	while(window.isOpen()){
		sf :: Event event;
		while(homePage){  //初始介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){  //關閉遊戲 
		    		homePage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){  //判斷滑鼠點擊 
					if(isMouseOn(mousePosition, gameStartButtonStartPos, gameStartButtonEndPos)){
						if(player.accountUsing()){  //若玩家已登入則開始遊戲 
							homePage = false;
							gameStart = true;
							gameInitialize = true;
						}
						else{  //否則前往登入頁面 
							homePage = false;
							loginPage = true;
						}
					}
					else if(isMouseOn(mousePosition, infoButtonStartPos, infoButtonEndPos)){  //前往遊戲介紹頁面 
						homePage = false;
						introPage = true;
					}
					else if(isMouseOn(mousePosition, rankButtonStartPos, rankButtonEndPos)){  //前往排名頁面 
						homePage = false;
						rankPage = true;
						rankInitialize = true;
					}
					else if(isMouseOn(mousePosition, loginButtonStartPos, loginButtonEndPos)){  //前往登入頁面 
						homePage = false;
						loginPage = true;
					}
				}
			}
			
			window.clear();
			window.draw(homePageBackground);
			window.display();
		}
		
		
		while(introPage){  //介紹介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		introPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){  //判斷滑鼠點擊 
					if(intro1){
						if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
							introPage = false;
							homePage = true;
						}
						else if(isMouseOn(mousePosition,	nextStartPos, nextEndPos)){
							intro1 = false;
							intro2 = true;
						}
					}
					else if(intro2){
						if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
							intro1 = true;
							intro2 = false;
							introPage = false;
							homePage = true;
						}
						else if(isMouseOn(mousePosition,	nextStartPos, nextEndPos)){
							intro2 = false;
							intro3 = true;
						}
						else if(isMouseOn(mousePosition,	backStartPos, backEndPos)){
							intro2 = false;
							intro1 = true;
						}
					}
					else if(intro3){
						if(isMouseOn(mousePosition, nextStartPos, nextEndPos)){  //intro3的home和前兩頁next同位置 
							intro1 = true;
							intro3 = false;
							introPage = false;
							homePage = true;
						}
						else if(isMouseOn(mousePosition,	backStartPos, backEndPos)){
							intro3 = false;
							intro2 = true;
						}
					}
				}
			}
			
			window.clear();
			if(intro1){
				window.draw(intro1Background);
			}
			else if(intro2){
				window.draw(intro2Background);
			}
			else if(intro3){
				window.draw(intro3Background);
			}
			window.display();
		}
		
		
		sf :: Text playerRank[5];
		sf :: Text playerScoreRank[5];
		for(int i = 0; i < 5; i++){
			playerRank[i].setFont(font);
			playerRank[i].setCharacterSize(70);
			playerRank[i].setPosition(sf :: Vector2f(489, 468 + i * 87));
			playerRank[i].setFillColor(sf :: Color :: White);
			playerRank[i].setStyle(sf :: Text :: Bold);
			
			playerScoreRank[i].setFont(font);
			playerScoreRank[i].setCharacterSize(70);
			playerScoreRank[i].setPosition(sf :: Vector2f(1159, 468 + i * 87));
			playerScoreRank[i].setFillColor(sf :: Color :: White);
			playerScoreRank[i].setStyle(sf :: Text :: Bold);
		}
		while(rankPage){  //排名介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			if(rankInitialize){
				ifstream file("player account.txt"); 
			    string line;
			    vector<PlayerInfo> player_list;
			
			    while(getline(file, line)){  //讀取檔案 
			        if(line.rfind("n: ", 0) == 0){
			            PlayerInfo player;
			            
						line.erase(0, 3); 
			            int spaceIndex = -1;
			            for(int i = line.length() - 1; i >= 0; i--){  //去除後面空白 
			            	if(line[i] == ' '){
			            		spaceIndex = i;
							}
							else{
								break;
							}
						}
			            if(spaceIndex != -1){
			            	line.erase(spaceIndex);
						}
			        	player.name = line;
			            
			            getline(file, line);
			            player.score = stoi(line.substr(3 , line.find(' ' , 3) - 3));
			            player_list.push_back(player);
			        }
			    }
			    sort(player_list.begin() , player_list.end(), compareByScore);  //藉由sort將玩家排名 
				
			    for(int i = 0 ; i < 5; i++){  //寫入前五名字串 
			    	playerRank[i].setString(player_list[i].name);
			    	playerScoreRank[i].setString(to_string(player_list[i].score));
			    }
			    
				file.close();
				
				rankInitialize = false;
			}
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		rankPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						rankPage = false;
						homePage = true;
					}
				}
			}
			
			window.clear();
			window.draw(rankBackground);
			for(int i = 0; i < 5; i++){
				window.draw(playerRank[i]);
				window.draw(playerScoreRank[i]);
			}
			window.display();
		}
		
		
		sf :: Text inputText;
		inputText.setFont(font);
		inputText.setCharacterSize(64);
		inputText.setPosition(sf :: Vector2f(585, 582));
		inputText.setFillColor(sf :: Color :: Black);
		string userName;
		while(loginPage){  //登入介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){  //關閉遊戲 
		    		loginPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						if(userName.length() > 0){  //刪除目前使用字串和顯示字串內部字元 
							userName.erase(0);
						}
						inputText.setString("");
						
						loginPage = false;
						homePage = true;
					}
					else if(isMouseOn(mousePosition, registerButtonStartPos, registerButtonEndPos)){
						if(userName.length() > 0){
							userName.erase(0);
						}
						inputText.setString("");
						
						loginPage = false;
						registerPage = true;
					}
					else if(isMouseOn(mousePosition, inputUserNameStartPos, inputUserNameEndPos)){
						if(player.playerExist(userName)){  //若帳號存在則更新帳號 
							player.changeAccount(userName);
							loginPage = false;
							homePage = true;
						}
						else{  //若否則進入錯誤介面 
							loginPage = false;
							errorPage = true;
						}
						
						if(userName.length() > 0){
							userName.erase(0);
						}
						inputText.setString("");
					}
				}
				if(event.type == sf :: Event :: TextEntered ){
					if(event.text.unicode < 128 && userName.length() < 12 && (isalnum(static_cast<char>(event.text.unicode)) || static_cast<char>(event.text.unicode) == 32)){  //判斷輸入數字是否為英文/數字/空白 
     				   userName +=  static_cast<char>(event.text.unicode);
     				   inputText.setString(userName);
    				}
    				else if(event.text.unicode < 128 && static_cast<char>(event.text.unicode) == 8 && userName.length() > 0){  //若輸入刪除則將輸入字串最後一字刪除 
    					userName.pop_back();
    					inputText.setString(userName);
					}
				}
			}
			
			window.clear();
			window.draw(loginBackground);
			window.draw(inputText);
			window.display();
		}
		
		
		while(registerPage){  //註冊介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		registerPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						if(userName.length() > 0){
							userName.erase(0);
						}
						inputText.setString("");
						
						registerPage = false;
						homePage = true;
					}
					else if(isMouseOn(mousePosition, inputUserNameStartPos, inputUserNameEndPos)){
						if(!player.playerExist(userName) && userName.length() > 0){  //若名子長度夠且帳號不存在則新增帳號 
							player.addAccount(userName);
							registerPage = false;
							loginPage = true;
						}
						
						//否則繼續停留於同頁面並刷新輸入字串 
						if(userName.length() > 0){ 
							userName.erase(0);
						}
						inputText.setString("");
					}
				}
				if(event.type == sf :: Event :: TextEntered ){
					if(event.text.unicode < 128 && userName.length() < 12 && (isalnum(static_cast<char>(event.text.unicode)) || static_cast<char>(event.text.unicode) == 32)){  //判斷輸入數字是否為英文/數字/空白 
     				   userName +=  static_cast<char>(event.text.unicode);
     				   inputText.setString(userName);
    				}
    				else if(event.text.unicode < 128 && static_cast<char>(event.text.unicode) == 8 && userName.length() > 0){  //若輸入刪除則將輸入字串最後一字刪除 
    					userName.pop_back();
    					inputText.setString(userName);
					}
				}
			}
			
			window.clear();
			window.draw(registerBackground);
			window.draw(inputText);
			window.display();
		}
		
		
		while(errorPage){  //帳號不存在頁面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		errorPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						errorPage = false;
						homePage = true;
					}
					else if(isMouseOn(mousePosition, errorToLoginStartPos, errorToLoginEndPos)){  //前往登入頁 
						errorPage = false;
						loginPage = true;
					}
					else if(isMouseOn(mousePosition, errorToRegisterStartPos, errorToRegisterEndPos)){  //前往註冊頁 
						errorPage = false;
						registerPage = true;
					}
				}
			}
			
			window.clear();
			window.draw(errorBackground);
			window.display();
		}
		
		
		while(gameStart){  //遊戲開始 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			if(gameInitialize){  //初始化遊戲數值 
				ingreUsing = false;
	
				ovenMeatUsing = false;
				meatHolding = 0;
				
				hamburger = nullptr;
				hamburgerExist = false; 
				hamburgerUsing = false;
				
				for(int i = 0; i < 2; i++){
					customer_list[i] = nullptr;
				}
				
				order_complete = 0;  //完成訂單數 
				customer_Clock.restart();
				customer_spawn_interval = sf::seconds(rand() % 3 + 3);  //客人出現間距（3-5秒） 
				
				mouseOff = true;
				holdingIngredient = nullptr;
				
				playerHeart = 3;
				
				heartAndScore = new HeartAndScore(font, heartImg[0]);
				
				gameInitialize = false;
			}
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
					gameStart = false;
		    		window.close();
				}
				
				if(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Left)){
					if(!ingreUsing){  //若滑鼠未拿著東西且點擊螢幕，判斷位置並決定拿起的物件 
						if(isMouseOn(mousePosition, cheeseStartPos, cheeseEndPos)){
							holdingIngredient = createIngredient(1);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, cucumberStartPos, cucumberEndPos)){
							holdingIngredient = createIngredient(2);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, lettuceStartPos, lettuceEndPos)){
							holdingIngredient = createIngredient(3);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, tomatoStartPos, tomatoEndPos)){
							holdingIngredient = createIngredient(4);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, meatStartPos, meatEndPos)){
							holdingIngredient = createIngredient(5);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, breadtopStartPos, breadtopEndPos)){
							holdingIngredient = createIngredient(6);
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, breadbottomStartPos, breadbottomEndPos)){
							holdingIngredient = createIngredient(7);
							ingreUsing = true;
						}
						else if(oven.mouseOnMeat(mousePosition) != -1){  //若點擊烤爐位置 
							meatHolding = oven.mouseOnMeat(mousePosition);  //紀錄為哪一格 
							if(oven[meatHolding] != nullptr){  //判斷烤爐上是否有肉，若有則拿起 
								holdingIngredient = oven[meatHolding]; 
								oven.timeStop(meatHolding);
								ovenMeatUsing = true;
								ingreUsing = true;
							}
						}
						else if(hamburgerExist && hamburger->isMouseOn(mousePosition)){
							holdingIngredient = hamburger;  //利用多型將Ingredient指標指向Hamburger物件 
							hamburgerUsing = true;
							ingreUsing = true;
						}
						else if(isMouseOn(mousePosition, beerStartPos, beerEndPos)){
							holdingIngredient = createIngredient(11);
							ingreUsing = true;
						}
					}
					
					mouseOff = false;
				}
				if(!(sf :: Mouse :: isButtonPressed(sf :: Mouse :: Left))){
					mouseOff = true;
				}
			}
			
			oven.checkCookingTime();
			
			if(ingreUsing){  //判斷是滑鼠是否拿著東西 
				if(!mouseOff){  //若手上有東西且滑鼠未放則物件跟著鼠標移動 
					holdingIngredient->setPos(sf :: Vector2f(mousePosition.x - holdingIngredient->getSize().x / 2, mousePosition.y - holdingIngredient->getSize().y / 2));
				}
				
				if(!ovenMeatUsing && mouseOff && holdingIngredient->getId() == 5 && holdingIngredient->overlap(ovenStartPos, ovenEndPos)){
					oven.addMeat();
				}
				else if(mouseOff && holdingIngredient->overlap(burgerPlateStartPos, burgerPlateEndPos)){  //判斷是否將物件放置於漢堡盤上 
					if(!hamburgerExist){  //判斷漢堡是否存在 
						if(holdingIngredient->getId() == 7){
							hamburger = new Hamburger(sf :: Vector2f(1123, 739), sf :: Vector2f(1, 1));
							hamburgerExist = true;
							hamburger->addIngredient(holdingIngredient->getId());
						}	
					}
					else if(holdingIngredient->getId() != 10 && holdingIngredient->getId() != 11){  //若放上的物件非漢堡或酒則將該物件加入漢堡食材中 
						hamburger->addIngredient(holdingIngredient->getId());
					}
				}
				
				if(mouseOff && holdingIngredient->overlap(garbageCanStartPos, garbageCanEndPos)){  //判斷手上物件是否在垃圾桶上 
					if(ovenMeatUsing){  //若為烤爐上的肉被放上垃圾桶則刪除該物件 
						oven.removeMeat(meatHolding);
						holdingIngredient = nullptr;
						ovenMeatUsing = false; 
						ingreUsing = false;
					}
					else if(hamburgerUsing){  //若為漢堡被放上垃圾桶則刪除該物件 
						delete hamburger;
						hamburger = nullptr; 
						holdingIngredient = nullptr;
						hamburgerUsing = false; 
						hamburgerExist = false;
						ingreUsing = false;
					}
				}
				
				if(mouseOff && ingreUsing){  //判斷手上物件放開 
					if(ovenMeatUsing){  //若為烤爐上的肉 
						if(hamburgerExist && hamburger->getSize() < 7 && holdingIngredient->overlap(burgerPlateStartPos, burgerPlateEndPos)){  //若放到漢堡盤上且漢堡存在則加入食材 
							oven.removeMeat(meatHolding);
							holdingIngredient = nullptr;
							ovenMeatUsing = false; 
							ingreUsing = false;
						}
						else{  //若放開於非特定位置則回歸原位 
							oven.setBackPosition(meatHolding);
							holdingIngredient = nullptr;
							ovenMeatUsing = false;
							oven.timeRestart(meatHolding);
						}
					}
					else if(customer_list[0] != nullptr && holdingIngredient->overlap(cust1StartPos , cust1StartPos + customer_list[0]->getSize())){  //若將漢堡或酒放到客人位置則判定其是否符合該客人訂單 
						if(hamburgerUsing){
							if(customer_list[0]->check_order(hamburger)){  //若符合訂單則刪除滑鼠上漢堡和客人的該漢堡訂單 
								delete hamburger;
								hamburger = nullptr; 
								holdingIngredient = nullptr;
								hamburgerUsing = false; 
								hamburgerExist = false;
							}
							else{  //若否則設漢堡回原位 
								hamburger->setBackPosition();
								holdingIngredient = nullptr;
								hamburgerUsing = false;
							}
						}
						else{
							if(holdingIngredient->getId() == 11){  //若將酒放到客人上則增加客人獲得的酒數 
								customer_list[0]->beerServed();
								holdingIngredient = nullptr;
							}
							else{
								delete holdingIngredient;
								holdingIngredient = nullptr;
							}
						}
					}
					else if(customer_list[1] != nullptr && holdingIngredient->overlap(cust2StartPos , cust2StartPos + customer_list[1]->getSize())){
						if(hamburgerUsing){
							if(customer_list[1]->check_order(hamburger)){
								delete hamburger;
								hamburger = nullptr; 
								holdingIngredient = nullptr;
								hamburgerUsing = false; 
								hamburgerExist = false;
							}
							else{
								hamburger->setBackPosition();
								holdingIngredient = nullptr;
								hamburgerUsing = false;
							}
						}
						else{
							if(holdingIngredient->getId() == 11){
								customer_list[1]->beerServed();
								holdingIngredient = nullptr;
							}
							else{
								delete holdingIngredient;
								holdingIngredient = nullptr;
							}
						}
					}
					else if(hamburgerUsing){  //若放開漢堡在非特定位置放開則設回原位 
						hamburger->setBackPosition();
						holdingIngredient = nullptr;
						hamburgerUsing = false;
					}
					else{  //若放開一般食材於非特定位置則刪除該物件 
						delete holdingIngredient;
						holdingIngredient = nullptr;
					}
					
					ingreUsing = false;
				}
			}
			
			for(int i = 0; i < 2; i++){
				if(customer_list[i] != nullptr){
					if(customer_list[i]->is_served()){
						delete customer_list[i];
						customer_list[i] = nullptr;
						order_complete++;
						customer_Clock.restart();
					}
					else if(customer_list[i]->angry_leave()){
						delete customer_list[i];
						customer_list[i] = nullptr;
						customer_Clock.restart();
						playerHeart--;
					}
				}
				heartAndScore->update(playerHeart, order_complete, heartImg);  //更新顯示生命和分數 
			}
			
			for(int i = 0; i < 2; i++){
				if(customer_list[i] != nullptr){
					customer_list[i]->timerUpdate(timerImg, timerImgCnt);
				}
			}
		
			if(order_complete % 8 == 0 && order_complete <= 16){
				Customer :: set_level((order_complete / 8) + 1);
			}
		
			window.clear();
			window.draw(background);
			oven.drawMeat(window);
		
			while(customer_Clock.getElapsedTime() >= customer_spawn_interval){  //若有空位則重新生成隨機圖片客人 
				string m = to_string(rand() % 13 + 1);
				
				if(customer_list[0] == nullptr){
					customer_list[0] = new Customer(12 , "image/customer/" + m + ".png", cust1StartPos, sf::Vector2f(1.5,1.5), font, timerImg[0]);
				}
				else if(customer_list[1] == nullptr){
					customer_list[1] = new Customer(12 , "image/customer/" + m + ".png", cust2StartPos, sf::Vector2f(1.5,1.5), font, timerImg[0]);
				}
				customer_Clock.restart();
				customer_spawn_interval = sf::seconds(rand() % 3 + 3);
			}
			
			//畫出物件 
			for(int i = 0; i < 2; i++){
				if(customer_list[i] != nullptr){
					customer_list[i]->drawCustomer(window);	
				}
			}
		
			if(hamburgerExist){
				hamburger->update();
				hamburger->drawHamburger(window);
			}
			if(!hamburgerUsing && holdingIngredient != nullptr){
				window.draw(holdingIngredient->getSprite());
			}
			
			heartAndScore->drawHeartAndScore(window);
			
			window.display();
			
			if(playerHeart <= 0){  //玩家生命歸零則結束遊戲 
				
				//將既存物件刪除 
				for(int i = 0; i < 2; i++){
					if(customer_list[i] != nullptr){
						delete customer_list[i];
						customer_list[i] = nullptr;
					}
				}
				Customer :: set_level(1);
				
				if(hamburgerExist){
					delete hamburger;
				}
				for(int i = 0; i < 4; i++){
					oven.removeMeat(i);
				}
				
				if(holdingIngredient != nullptr){
					if(hamburgerUsing || ovenMeatUsing){
						holdingIngredient = nullptr;
					}
					else{
						delete holdingIngredient;
						holdingIngredient = nullptr;
					}
				}
				
				delete heartAndScore;
				heartAndScore = nullptr;
				
				gameStart = false;
				gameOver = true;
				
				//更新玩家最高分 
				player.updateHighestScore(order_complete);
			}
		}
		
		
		sf :: Text scoreDisplay;  //顯示此次遊戲分數 
		scoreDisplay.setFont(font);
		scoreDisplay.setCharacterSize(70);
		scoreDisplay.setPosition(sf :: Vector2f(878, 565));
		scoreDisplay.setFillColor(sf :: Color :: White);
		scoreDisplay.setString(to_string(order_complete));
		
		sf :: Text bestScoreDisplay;  //顯示目前使用的玩家帳號的最高分 
		bestScoreDisplay.setFont(font);
		bestScoreDisplay.setCharacterSize(70);
		bestScoreDisplay.setPosition(sf :: Vector2f(912, 739));
		bestScoreDisplay.setFillColor(sf :: Color :: White);
		bestScoreDisplay.setString(to_string(player.getHiScore()));
		while(gameOver){  //遊戲結束介面 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		gameOver = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						gameOver = false;
						homePage = true;
					}
					else if(isMouseOn(mousePosition, gameRestartButtonStartPos, gameRestartButtonEndPos)){
						gameOver = false;
						gameStart = true;
						gameInitialize = true;
					}
				}
			}
			
			window.clear();
			window.draw(gameOverBackground);
			window.draw(scoreDisplay);
			window.draw(bestScoreDisplay);
			window.display();
		}
	}
	
	
	return 0;
}
