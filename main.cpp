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
	
	Player player;  //��l�ƪ��a���� 

	sf :: Font font;
	font.loadFromFile("font.ttf");  //�r����J 
	
	//�I���Ϥ����J 
	sf :: Image timerImg[timerImgCnt];  //���J�ȤH�p�ɾ��Ϥ� 
	for(int i = 0; i < timerImgCnt; i++){
		timerImg[i].loadFromFile("image/timer animation/" + to_string(i + 1) + ".png");
	}
	
	sf :: Image heartImg[3];
	for(int i = 0; i < 3; i++){
		heartImg[i].loadFromFile("image/heart/" + to_string(i + 1) + ".png");
	}
	
	sf :: Texture backgroundImg;  //�C���I���Ϥ� 
	backgroundImg.loadFromFile("image/background.png");
	
	sf :: Sprite background;
	background.setTexture(backgroundImg);
	background.setPosition(0, 0);
	
	
	sf :: Texture homePageBackgroundImg;  //��l�����I���Ϥ� 
	homePageBackgroundImg.loadFromFile("image/home page background.png");
	
	sf :: Sprite homePageBackground;
	homePageBackground.setTexture(homePageBackgroundImg);
	homePageBackground.setPosition(0, 0);
	
	
	sf :: Texture intro1BackgroundImg;  //�C�����ЭI���Ϥ�1
	intro1BackgroundImg.loadFromFile("image/intro page/intro1.jpg");
	
	sf :: Sprite intro1Background;
	intro1Background.setTexture(intro1BackgroundImg);
	intro1Background.setPosition(0, 0);
	
	sf :: Texture intro2BackgroundImg;  //�C�����ЭI���Ϥ�2
	intro2BackgroundImg.loadFromFile("image/intro page/intro2.png");
	
	sf :: Sprite intro2Background;
	intro2Background.setTexture(intro2BackgroundImg);
	intro2Background.setPosition(0, 0);
	
	sf :: Texture intro3BackgroundImg;  //�C�����ЭI���Ϥ�3
	intro3BackgroundImg.loadFromFile("image/intro page/intro3.jpg");
	
	sf :: Sprite intro3Background;
	intro3Background.setTexture(intro3BackgroundImg);
	intro3Background.setPosition(0, 0);
	
	
	sf :: Texture rankBackgroundImg;  //�ƦW�����I���Ϥ� 
	rankBackgroundImg.loadFromFile("image/rank.jpg");
	
	sf :: Sprite rankBackground;
	rankBackground.setTexture(rankBackgroundImg);
	rankBackground.setPosition(0, 0);
	
	
	sf :: Texture loginBackgroundImg;  //�n�J�����I���Ϥ� 
	loginBackgroundImg.loadFromFile("image/login.jpg");
	
	sf :: Sprite loginBackground;
	loginBackground.setTexture(loginBackgroundImg);
	loginBackground.setPosition(0, 0);
	
	
	sf :: Texture registerBackgroundImg;  //���U�����I���Ϥ� 
	registerBackgroundImg.loadFromFile("image/register.jpg");
	
	sf :: Sprite registerBackground;
	registerBackground.setTexture(registerBackgroundImg);
	registerBackground.setPosition(0, 0);
	
	
	sf :: Texture errorBackgroundImg;  //�n�J���ѭ����I���Ϥ� 
	errorBackgroundImg.loadFromFile("image/error.jpg");
	
	sf :: Sprite errorBackground;
	errorBackground.setTexture(errorBackgroundImg);
	errorBackground.setPosition(0, 0);
	
	
	sf :: Texture gameOverBackgroundImg;  //�C�����������I���Ϥ� 
	gameOverBackgroundImg.loadFromFile("image/game over.jpg");
	
	sf :: Sprite gameOverBackground;
	gameOverBackground.setTexture(gameOverBackgroundImg);
	gameOverBackground.setPosition(0, 0);
	
	
	bool ingreUsing = false;  //�P�_�ƹ��O�_���۪F�� 
	Ingredient* holdingIngredient = nullptr;  //�Ψ��x�s�ثe���۪��F�誺���� 
	
	Oven oven;
	bool ovenMeatUsing = false;  //�P�_�O�_���ۯN�L�� 
	int meatHolding = 0;  //�P�_�n�����N�L�צb�N�L�W���s�� 
	
	Hamburger* hamburger = nullptr;  //�x�s�~�������� 
	bool hamburgerExist = false;  //�P�_�{�b�O�_�s�b�~������ 
	bool hamburgerUsing = false;  //�P�_�O�_���ۺ~�� 
	
	Customer* customer_list[2] = {nullptr, nullptr};  //�ȤH�}�C 
	int order_complete = 0;  //�����q��� 
	srand(std::time(0)); 
	sf :: Clock customer_Clock;
	sf :: Time customer_spawn_interval;  //�ȤH�X�{���Z 
	
	bool mouseOff = true;
	
	int playerHeart = 3;  //���a�ͩR 
	
	HeartAndScore* heartAndScore = nullptr;
	
	//�P�_�ثe���� 
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
		while(homePage){  //��l���� 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){  //�����C�� 
		    		homePage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){  //�P�_�ƹ��I�� 
					if(isMouseOn(mousePosition, gameStartButtonStartPos, gameStartButtonEndPos)){
						if(player.accountUsing()){  //�Y���a�w�n�J�h�}�l�C�� 
							homePage = false;
							gameStart = true;
							gameInitialize = true;
						}
						else{  //�_�h�e���n�J���� 
							homePage = false;
							loginPage = true;
						}
					}
					else if(isMouseOn(mousePosition, infoButtonStartPos, infoButtonEndPos)){  //�e���C�����Э��� 
						homePage = false;
						introPage = true;
					}
					else if(isMouseOn(mousePosition, rankButtonStartPos, rankButtonEndPos)){  //�e���ƦW���� 
						homePage = false;
						rankPage = true;
						rankInitialize = true;
					}
					else if(isMouseOn(mousePosition, loginButtonStartPos, loginButtonEndPos)){  //�e���n�J���� 
						homePage = false;
						loginPage = true;
					}
				}
			}
			
			window.clear();
			window.draw(homePageBackground);
			window.display();
		}
		
		
		while(introPage){  //���Ф��� 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){
		    		introPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){  //�P�_�ƹ��I�� 
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
						if(isMouseOn(mousePosition, nextStartPos, nextEndPos)){  //intro3��home�M�e�⭶next�P��m 
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
		while(rankPage){  //�ƦW���� 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			if(rankInitialize){
				ifstream file("player account.txt"); 
			    string line;
			    vector<PlayerInfo> player_list;
			
			    while(getline(file, line)){  //Ū���ɮ� 
			        if(line.rfind("n: ", 0) == 0){
			            PlayerInfo player;
			            
						line.erase(0, 3); 
			            int spaceIndex = -1;
			            for(int i = line.length() - 1; i >= 0; i--){  //�h���᭱�ť� 
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
			    sort(player_list.begin() , player_list.end(), compareByScore);  //�ǥ�sort�N���a�ƦW 
				
			    for(int i = 0 ; i < 5; i++){  //�g�J�e���W�r�� 
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
		while(loginPage){  //�n�J���� 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			while(window.pollEvent(event)){
				if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Escape) || event.type == sf :: Event :: Closed){  //�����C�� 
		    		loginPage = false;
					window.close();
				}
				if(event.type == sf :: Event :: MouseButtonReleased && event.mouseButton.button == sf :: Mouse :: Left){
					if(isMouseOn(mousePosition, backToHomeStartPos, backToHomeEndPos)){
						if(userName.length() > 0){  //�R���ثe�ϥΦr��M��ܦr�ꤺ���r�� 
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
						if(player.playerExist(userName)){  //�Y�b���s�b�h��s�b�� 
							player.changeAccount(userName);
							loginPage = false;
							homePage = true;
						}
						else{  //�Y�_�h�i�J���~���� 
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
					if(event.text.unicode < 128 && userName.length() < 12 && (isalnum(static_cast<char>(event.text.unicode)) || static_cast<char>(event.text.unicode) == 32)){  //�P�_��J�Ʀr�O�_���^��/�Ʀr/�ť� 
     				   userName +=  static_cast<char>(event.text.unicode);
     				   inputText.setString(userName);
    				}
    				else if(event.text.unicode < 128 && static_cast<char>(event.text.unicode) == 8 && userName.length() > 0){  //�Y��J�R���h�N��J�r��̫�@�r�R�� 
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
		
		
		while(registerPage){  //���U���� 
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
						if(!player.playerExist(userName) && userName.length() > 0){  //�Y�W�l���װ��B�b�����s�b�h�s�W�b�� 
							player.addAccount(userName);
							registerPage = false;
							loginPage = true;
						}
						
						//�_�h�~�򰱯d��P�����è�s��J�r�� 
						if(userName.length() > 0){ 
							userName.erase(0);
						}
						inputText.setString("");
					}
				}
				if(event.type == sf :: Event :: TextEntered ){
					if(event.text.unicode < 128 && userName.length() < 12 && (isalnum(static_cast<char>(event.text.unicode)) || static_cast<char>(event.text.unicode) == 32)){  //�P�_��J�Ʀr�O�_���^��/�Ʀr/�ť� 
     				   userName +=  static_cast<char>(event.text.unicode);
     				   inputText.setString(userName);
    				}
    				else if(event.text.unicode < 128 && static_cast<char>(event.text.unicode) == 8 && userName.length() > 0){  //�Y��J�R���h�N��J�r��̫�@�r�R�� 
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
		
		
		while(errorPage){  //�b�����s�b���� 
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
					else if(isMouseOn(mousePosition, errorToLoginStartPos, errorToLoginEndPos)){  //�e���n�J�� 
						errorPage = false;
						loginPage = true;
					}
					else if(isMouseOn(mousePosition, errorToRegisterStartPos, errorToRegisterEndPos)){  //�e�����U�� 
						errorPage = false;
						registerPage = true;
					}
				}
			}
			
			window.clear();
			window.draw(errorBackground);
			window.display();
		}
		
		
		while(gameStart){  //�C���}�l 
			sf::Vector2f mousePosition(sf :: Mouse :: getPosition(window).x, sf :: Mouse :: getPosition(window).y);
			
			if(gameInitialize){  //��l�ƹC���ƭ� 
				ingreUsing = false;
	
				ovenMeatUsing = false;
				meatHolding = 0;
				
				hamburger = nullptr;
				hamburgerExist = false; 
				hamburgerUsing = false;
				
				for(int i = 0; i < 2; i++){
					customer_list[i] = nullptr;
				}
				
				order_complete = 0;  //�����q��� 
				customer_Clock.restart();
				customer_spawn_interval = sf::seconds(rand() % 3 + 3);  //�ȤH�X�{���Z�]3-5��^ 
				
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
					if(!ingreUsing){  //�Y�ƹ������۪F��B�I���ù��A�P�_��m�èM�w���_������ 
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
						else if(oven.mouseOnMeat(mousePosition) != -1){  //�Y�I���N�l��m 
							meatHolding = oven.mouseOnMeat(mousePosition);  //���������@�� 
							if(oven[meatHolding] != nullptr){  //�P�_�N�l�W�O�_���סA�Y���h���_ 
								holdingIngredient = oven[meatHolding]; 
								oven.timeStop(meatHolding);
								ovenMeatUsing = true;
								ingreUsing = true;
							}
						}
						else if(hamburgerExist && hamburger->isMouseOn(mousePosition)){
							holdingIngredient = hamburger;  //�Q�Φh���NIngredient���Ы��VHamburger���� 
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
			
			if(ingreUsing){  //�P�_�O�ƹ��O�_���۪F�� 
				if(!mouseOff){  //�Y��W���F��B�ƹ�����h�����۹��в��� 
					holdingIngredient->setPos(sf :: Vector2f(mousePosition.x - holdingIngredient->getSize().x / 2, mousePosition.y - holdingIngredient->getSize().y / 2));
				}
				
				if(!ovenMeatUsing && mouseOff && holdingIngredient->getId() == 5 && holdingIngredient->overlap(ovenStartPos, ovenEndPos)){
					oven.addMeat();
				}
				else if(mouseOff && holdingIngredient->overlap(burgerPlateStartPos, burgerPlateEndPos)){  //�P�_�O�_�N�����m��~���L�W 
					if(!hamburgerExist){  //�P�_�~���O�_�s�b 
						if(holdingIngredient->getId() == 7){
							hamburger = new Hamburger(sf :: Vector2f(1123, 739), sf :: Vector2f(1, 1));
							hamburgerExist = true;
							hamburger->addIngredient(holdingIngredient->getId());
						}	
					}
					else if(holdingIngredient->getId() != 10 && holdingIngredient->getId() != 11){  //�Y��W������D�~���ΰs�h�N�Ӫ���[�J�~�������� 
						hamburger->addIngredient(holdingIngredient->getId());
					}
				}
				
				if(mouseOff && holdingIngredient->overlap(garbageCanStartPos, garbageCanEndPos)){  //�P�_��W����O�_�b�U����W 
					if(ovenMeatUsing){  //�Y���N�l�W���׳Q��W�U����h�R���Ӫ��� 
						oven.removeMeat(meatHolding);
						holdingIngredient = nullptr;
						ovenMeatUsing = false; 
						ingreUsing = false;
					}
					else if(hamburgerUsing){  //�Y���~���Q��W�U����h�R���Ӫ��� 
						delete hamburger;
						hamburger = nullptr; 
						holdingIngredient = nullptr;
						hamburgerUsing = false; 
						hamburgerExist = false;
						ingreUsing = false;
					}
				}
				
				if(mouseOff && ingreUsing){  //�P�_��W�����} 
					if(ovenMeatUsing){  //�Y���N�l�W���� 
						if(hamburgerExist && hamburger->getSize() < 7 && holdingIngredient->overlap(burgerPlateStartPos, burgerPlateEndPos)){  //�Y���~���L�W�B�~���s�b�h�[�J���� 
							oven.removeMeat(meatHolding);
							holdingIngredient = nullptr;
							ovenMeatUsing = false; 
							ingreUsing = false;
						}
						else{  //�Y��}��D�S�w��m�h�^�k��� 
							oven.setBackPosition(meatHolding);
							holdingIngredient = nullptr;
							ovenMeatUsing = false;
							oven.timeRestart(meatHolding);
						}
					}
					else if(customer_list[0] != nullptr && holdingIngredient->overlap(cust1StartPos , cust1StartPos + customer_list[0]->getSize())){  //�Y�N�~���ΰs���ȤH��m�h�P�w��O�_�ŦX�ӫȤH�q�� 
						if(hamburgerUsing){
							if(customer_list[0]->check_order(hamburger)){  //�Y�ŦX�q��h�R���ƹ��W�~���M�ȤH���Ӻ~���q�� 
								delete hamburger;
								hamburger = nullptr; 
								holdingIngredient = nullptr;
								hamburgerUsing = false; 
								hamburgerExist = false;
							}
							else{  //�Y�_�h�]�~���^��� 
								hamburger->setBackPosition();
								holdingIngredient = nullptr;
								hamburgerUsing = false;
							}
						}
						else{
							if(holdingIngredient->getId() == 11){  //�Y�N�s���ȤH�W�h�W�[�ȤH��o���s�� 
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
					else if(hamburgerUsing){  //�Y��}�~���b�D�S�w��m��}�h�]�^��� 
						hamburger->setBackPosition();
						holdingIngredient = nullptr;
						hamburgerUsing = false;
					}
					else{  //�Y��}�@�뭹����D�S�w��m�h�R���Ӫ��� 
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
				heartAndScore->update(playerHeart, order_complete, heartImg);  //��s��ܥͩR�M���� 
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
		
			while(customer_Clock.getElapsedTime() >= customer_spawn_interval){  //�Y���Ŧ�h���s�ͦ��H���Ϥ��ȤH 
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
			
			//�e�X���� 
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
			
			if(playerHeart <= 0){  //���a�ͩR�k�s�h�����C�� 
				
				//�N�J�s����R�� 
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
				
				//��s���a�̰��� 
				player.updateHighestScore(order_complete);
			}
		}
		
		
		sf :: Text scoreDisplay;  //��ܦ����C������ 
		scoreDisplay.setFont(font);
		scoreDisplay.setCharacterSize(70);
		scoreDisplay.setPosition(sf :: Vector2f(878, 565));
		scoreDisplay.setFillColor(sf :: Color :: White);
		scoreDisplay.setString(to_string(order_complete));
		
		sf :: Text bestScoreDisplay;  //��ܥثe�ϥΪ����a�b�����̰��� 
		bestScoreDisplay.setFont(font);
		bestScoreDisplay.setCharacterSize(70);
		bestScoreDisplay.setPosition(sf :: Vector2f(912, 739));
		bestScoreDisplay.setFillColor(sf :: Color :: White);
		bestScoreDisplay.setString(to_string(player.getHiScore()));
		while(gameOver){  //�C���������� 
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
