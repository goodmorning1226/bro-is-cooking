#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "game object.h"
#include "position.h"
#include <SFML/Graphics.hpp>
using namespace std;


bool isMouseOn(sf :: Vector2f mousePos, sf :: Vector2f startPos, sf :: Vector2f endPos){
	if(mousePos.x >= startPos.x && mousePos.x <= endPos.x && mousePos.y >= startPos.y && mousePos.y <= endPos.y){  //判斷屬標位置是否在傳入範圍內 
		return true;
	}
	
	return false;
}


bool compareByScore(const PlayerInfo& a, const PlayerInfo& b){
    return a.score > b.score;  //前面的比較大
}

Player :: Player(){
	this->name = "";
	this->highestScore = -1;
}

bool Player :: playerExist(string name){
	ifstream accountReader;
	accountReader.open("player account.txt");
	
	string accountName;
	while(getline(accountReader, accountName)){
		if(accountName[0] == 'n'){
			accountName.erase(0, 3);
			
			int spaceStart = -1;
			for(int i = accountName.length() - 1; i >= 0; i--){  //檢查名稱後是否有空格 
				if(accountName[i] == ' '){
					spaceStart = i;
				}
				else{
					break;
				}
			}
			if(spaceStart != -1){
				accountName.erase(spaceStart);
			}
			
			if(accountName == name){
				accountReader.close();
				return true;
			}
		}
	}
	
	accountReader.close();
	return false;
}

void Player :: changeAccount(string name){
	ifstream accountReader;
	accountReader.open("player account.txt");
	
	string accountName;
	while(getline(accountReader, accountName)){
		if(accountName[0] == 'n'){
			accountName.erase(0, 3);
			
			int spaceStart = -1;
			for(int i = accountName.length() - 1; i >= 0; i--){  //檢查名稱後是否有空格 
				if(accountName[i] == ' '){
					spaceStart = i;
				}
				else{
					break;
				}
			}
			if(spaceStart != -1){
				accountName.erase(spaceStart);
			}
			
			if(accountName == name){
				this->name = accountName;
				getline(accountReader, accountName);
				accountName.erase(0, 3);
				this->highestScore = stoi(accountName);
				
				accountReader.close();
				return;
			}
		}
	}
}

void Player :: addAccount(string name){
	ofstream accountAdder;
	accountAdder.open("player account.txt", ios :: app);
	
	accountAdder << "n: " << name;
	for(int i = 0; i < 12 - name.length(); i++){
		accountAdder << " ";
	}
	accountAdder << "\n";
	
	accountAdder << "s: 0 \n";
	
	accountAdder.close();
	
	return;
}

void Player :: updateHighestScore(int newScore){
	ifstream accountReader;
	accountReader.open("player account.txt");
	
	
	if(newScore <= this->highestScore){
		return;
	}
	
	this->highestScore = newScore;
	
	string accountList;
	getline(accountReader, accountList, '*');  //檔案無*字元，因此getline會讀到eof 
	int writeIndex = accountList.find(this->name) + 16;  //判斷名稱位置以決定覆寫位置 
	
	
	if(newScore / 10 > 0){ 
		accountList.replace(writeIndex, 2, to_string(newScore));
	}
	else{
		accountList.replace(writeIndex, 1, to_string(newScore));
	}
	
	accountReader.close();
	
	
	ofstream accountWriter;
	accountWriter.open("player account.txt");
	
	accountWriter << accountList;  //將更改後數據覆寫至檔案 
	
	accountWriter.close();
}



Ingredient :: Ingredient(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale){
	this->id = id;
	this->texture.loadFromFile(imgURL);
	this->position = pos;
	this->scale = scale;
	this->size.x = texture.getSize().x * this->scale.x;
	this->size.y = texture.getSize().y * this->scale.y;
	this->image.setTexture(texture);
	this->image.setPosition(position);
	this->image.setScale(scale);
}

void Ingredient :: setPos(sf :: Vector2f newPos){
	this->position = newPos;
	this->image.setPosition(this->position);
}

bool Ingredient :: isMouseOn(sf :: Vector2f mousePos){
	if(mousePos.x >= this->position.x && mousePos.x <= this->position.x + this->size.x && mousePos.y >= this->position.y && mousePos.y <= this->position.y + this->size.y){
		return true;
	}
	
	return false;
}

bool Ingredient :: overlap(const sf :: Vector2f startPos, const sf :: Vector2f endPos){ 
	if(this->position.x + this->size.x >= startPos.x &&  // Ingredient 右邊 >= 垃圾桶左邊
    	this->position.x <= endPos.x &&                  // Ingredient 左邊 <= 垃圾桶右邊
        this->position.y + this->size.y >= startPos.y && // Ingredient 下邊 >= 垃圾桶上邊
        this->position.y <= endPos.y) {                 // Ingredient 上邊 <= 垃圾桶下邊
        
		return true;
    }
    return false;
}

Ingredient* createIngredient(int ingreType){
	Ingredient* newIngredient = nullptr;
	
	switch(ingreType){
		case 1:
			newIngredient = new Ingredient(1, ingreImgURL[ingreType - 1], cheeseStartPos, sf :: Vector2f(1.2, 1.2));
			break;
			
		case 2:
			newIngredient = new Ingredient(2, ingreImgURL[ingreType - 1], cucumberStartPos, sf :: Vector2f(0.4, 0.4));
			break;
			
		case 3:
			newIngredient = new Ingredient(3, ingreImgURL[ingreType - 1], lettuceStartPos, sf :: Vector2f(1.2, 1.2));
			break;
			
		case 4:
			newIngredient = new Ingredient(4, ingreImgURL[ingreType - 1], tomatoStartPos, sf :: Vector2f(0.65, 0.65));
			break;
			
		case 5:
			newIngredient = new Ingredient(5, ingreImgURL[ingreType - 1], meatStartPos, sf :: Vector2f(0.82, 0.82));
			break;
		
		case 6:
			newIngredient = new Ingredient(6, ingreImgURL[ingreType - 1], breadtopStartPos, sf :: Vector2f(1, 1));
			break;
			
		case 7:
			newIngredient = new Ingredient(7, ingreImgURL[ingreType - 1], breadbottomStartPos, sf :: Vector2f(1, 1));
			break;
			
		case 8:
			newIngredient = new Ingredient(8, ingreImgURL[ingreType - 1], meatStartPos, sf :: Vector2f(0.82, 0.82));
			break;
			
		case 9:
			newIngredient = new Ingredient(9, ingreImgURL[ingreType - 1], meatStartPos, sf :: Vector2f(0.82, 0.82));
			break;
			
		case 11:
			newIngredient = new Ingredient(11, ingreImgURL[9], beerStartPos, sf :: Vector2f(0.6, 0.6));
	}

	return newIngredient;
}



Oven :: Oven(){
	for(int i = 0; i < 4; i++){
		this->meat[i] = nullptr;
		this->cookingTime[i] = new sf :: Clock();
		this->accumulatedTime[i] = new sf :: Time;
		*this->accumulatedTime[i] = sf :: seconds(0);
		this->isTimeStop[i] = false;
		this->firstStageCooking[i] = false;
		this->secondStageCooking[i] = false;
		switch(i){  //設定烤爐位置 
			case 0:
				meatPosition[i] = sf :: Vector2f(589, 648);
				break;
				
			case 1:
				meatPosition[i] = sf :: Vector2f(783, 648);
				break;
				
			case 2:
				meatPosition[i] = sf :: Vector2f(589, 776);
				break;
				
			case 3:
				meatPosition[i] = sf :: Vector2f(783, 776);
				break;
		}
	}
}

Oven :: ~Oven(){
	for(int i = 0; i < 4; i++){
		if(this->meat[i] != nullptr){
			delete this->meat[i];
		}
		delete this->cookingTime[i];	
	}
}

int Oven :: getMeatCnt(){
	int meatCnt = 0;
	
	for(int i = 0; i < 4; i++){
		if(meat[i] != nullptr){
			meatCnt++;
		}
	}
	
	return meatCnt;
}

int Oven :: mouseOnMeat(sf :: Vector2f mousePos){
	for(int i = 0; i < 4; i++){
		if(this->meat[i] != nullptr && this->meat[i]->isMouseOn(mousePos)){
			return i;
		}
	}
	
	return -1;
}

void Oven :: addMeat(){
	for(int i = 0; i < 4; i++){
		if(this->meat[i] == nullptr){	
			this->meat[i] = new Ingredient(5, "image/meat.png", meatPosition[i], sf :: Vector2f(1, 1));
			this->firstStageCooking[i] = true;  //開啟該位置第一階段烤肉 
			this->cookingTime[i]->restart();  //將該位置烤肉計時器刷新 
			
			return;
		}
	}
}

void Oven :: removeMeat(int index){
	try{
		if(this->meat[index] != nullptr){
			delete this->meat[index];
			this->meat[index] = nullptr;
			*this->accumulatedTime[index] = sf :: seconds(0);
			this->isTimeStop[index] = false;
			this->firstStageCooking[index] = false;
			this->secondStageCooking[index] = false;
		}
	}
	catch(runtime_error){
		cerr << "remove meat runtime error";
	}
	catch(logic_error){
		cerr << "remove meat logic error";
	}
}

void Oven :: checkCookingTime(){
	for(int i = 0; i < 4; i++){
		if(!this->isTimeStop[i] &&this->firstStageCooking[i] == true && this->accumulatedTime[i]->asSeconds() + this->cookingTime[i]->getElapsedTime().asSeconds() >= 3){  //判斷累積時間和計時器相加是否超過3秒 
			this->firstStageCooking[i] = false;
			this->secondStageCooking[i] = true;  //開啟第二階段烤肉 
			delete this->meat[i];
			this->meat[i] = new Ingredient(8, "image/cooked meat.png", meatPosition[i], sf :: Vector2f(1, 1));
		}
		else if(!this->isTimeStop[i] && this->secondStageCooking[i] == true && this->accumulatedTime[i]->asSeconds() + this->cookingTime[i]->getElapsedTime().asSeconds() >= 11){  //判斷累積時間和計時器相加是否超過11秒（3 + 8） 
			this->secondStageCooking[i] = false;
			delete this->meat[i];
			this->meat[i] = new Ingredient(9, "image/dead meat.png", meatPosition[i], sf :: Vector2f(1, 1));
			*this->accumulatedTime[i] = sf :: seconds(0);
		}
	}
}

void Oven :: timeStop(int index){
	*this->accumulatedTime[index] += this->cookingTime[index]->getElapsedTime();  //將計時器時間存入累積時間內 
	this->isTimeStop[index] = true;
	
}
void Oven :: timeRestart(int index){
	this->cookingTime[index]->restart();  //重啟計時器 
	this->isTimeStop[index] = false;
}

void Oven :: setBackPosition(int index){
	if(this->meat[index] != nullptr){
		this->meat[index]->setPos(meatPosition[index]);
	}
}

void Oven :: drawMeat(sf :: RenderWindow& window){//
	for(int i = 0; i < 4; i++){
		if(meat[i] != nullptr){
			window.draw(meat[i]->getSprite());
		}
	}
}

Ingredient* Oven :: operator[](int index){
	try{
		return meat[index];
	}
	catch(out_of_range){
		cerr << "Oven[] index incorrect." << endl;
	}
	
	return nullptr;
}



const int Hamburger :: maxIngredientCnt = 8;

const int Hamburger :: ingredientOffsetY = 20;

Hamburger :: Hamburger(sf :: Vector2f pos, sf :: Vector2f scale) : Ingredient(10, "image/cheese.png", pos, scale){}

Hamburger :: ~Hamburger(){
	for(int i = 0; i < ingreStack.size(); i++){
		delete ingreStack[i];
	}
}

void Hamburger :: addIngredient(int ingreType){
	if(ingreStack.size() == 0 && ingreType != 7){  //若第一個不為麵包底則不加入食材 
		return;
	}
	if(ingreStack.size() == maxIngredientCnt - 1 && ingreType != 6){  //若漢堡食材數量達最大數量-1則若加入食材不為麵包頂則不加入 
		return;
	}
	if(ingreStack.size() > 0 && ingreStack[ingreStack.size() - 1]->getId() == 6){  //若已存在麵包頂則不加入新食材 
		return;
	}
	if(ingreStack.size() < maxIngredientCnt){  //若漢堡食材數未滿則在漢堡vector中加入新食材 
		Ingredient* newIngre = createIngredient(ingreType);
		newIngre->setPos(sf :: Vector2f(this->position.x, this->position.y - this->ingredientOffsetY * this->ingreStack.size()));
		ingreStack.push_back(newIngre);
	}
}

bool Hamburger :: isMouseOn(sf :: Vector2f mousePos){
	if(mousePos.x >= this->ingreStack.back()->getPosition().x && mousePos.x <= this->ingreStack.front()->getPosition().x + this->ingreStack.front()->getSize().x && mousePos.y >= this->ingreStack.back()->getPosition().y && mousePos.y <= this->ingreStack.front()->getPosition().y + this->ingreStack.front()->getSize().y){
		return true;
	}
	
	return false;
}

void Hamburger :: drawHamburger(sf :: RenderWindow& window){
	for(int i = 0; i < this->ingreStack.size(); i++){
		window.draw(this->ingreStack[i]->getSprite());
	}
}

void Hamburger :: setBackPosition(){
	this->setPos(sf :: Vector2f(1123, 739));
}

void Hamburger :: update(){
	for(int i = 0; i < this->ingreStack.size(); i++){
		ingreStack[i]->setPos(sf :: Vector2f(this->position.x, this->position.y - this->ingredientOffsetY * i));
	}
}

void Hamburger :: setIngreScale(sf :: Vector2f newScale){ 
	for(int i = 0; i < ingreStack.size(); i++){
		ingreStack[i]->getSprite().setScale(sf :: Vector2f(ingreStack[i]->getScale().x * newScale.x, ingreStack[i]->getScale().y * newScale.y));
	}
}

vector<int> Hamburger::get_ingre_stack(){
	vector<int> temp;
	for(int i = 0 ; i < ingreStack.size() ; i++){
		temp.push_back(this->ingreStack[i]->getId());
	}
	return temp;
}



int Customer::level = 1;

Customer::Customer(int id, string imgURL, sf :: Vector2f pos, sf :: Vector2f scale, sf :: Font& font, sf :: Image& initialTimer):Ingredient(id, imgURL, pos, scale){
	this->waitTime = sf::seconds(20);
	srand(time(0));
	int hamburger_cnt = rand() % level + 1;

	for(int i = 0 ; i < hamburger_cnt ; i++){
		orderlist.push_back(vector<int>());
		orderlist[i].push_back(7);
		int ingre_cnt = rand() % (level * 2) + 1;
		for(int j = 0 ; j < ingre_cnt ; j++){
			int ingre_id = rand() % 8 + 1;
			if(ingre_id != 6){
				orderlist[i].push_back(ingre_id);
			}
		}
		orderlist[i].push_back(6);
	}
	beer_order = rand() % 3;  //酒要的數量 0-3 
	beerServedCnt = 0;
	
	waitTime = sf::seconds(rand() % 3 * (5 - level) + 15);  //等待時間依等級隨機指定 
	
	for(int i = 0; i < orderlist.size(); i++){  //依客人訂單創建漢堡物件 
		Hamburger* newBurger = new Hamburger(this->position + sf :: Vector2f(350 + 120 * i, 70), sf :: Vector2f(1, 1));
		orderHamburger.push_back(newBurger);
		for(int j = 0; j < orderlist[i].size(); j++){
			orderHamburger[i]->addIngredient(orderlist[i][j]);
		}
		orderHamburger[i]->setIngreScale(sf :: Vector2f(0.8, 0.8));
	}
	
	this->beerImage = createIngredient(11);
	this->beerImage->setPos(this->position + sf :: Vector2f(375, 170));
	this->beerImage->getSprite().setScale(sf :: Vector2f(0.4, 0.4));
	
	this->beerText.setFont(font);
	this->beerText.setCharacterSize(48);
	this->beerText.setFillColor(sf :: Color :: Black);
	this->beerText.setPosition(this->position + sf :: Vector2f(445, 230));
	this->beerText.setString("X " + to_string(beer_order));
	
	this->orderBox = new Ingredient(13, "image/orderBox.png", this->position + sf :: Vector2f(330, -65), sf :: Vector2f((orderlist.size() == 1 ? 0.12 : 0) + 0.2 * orderlist.size(), 0.45));  //創建客人訂單對話框 
	
	this->timerTexture.loadFromImage(initialTimer);
	this->timer.setTexture(this->timerTexture);
	this->timer.setPosition(this->position + sf :: Vector2f(-50, -65));
	this->timer.setScale(0.4, 0.4);
}

Customer :: ~Customer(){
	for(int i = 0; i < orderlist.size(); i++){
		delete orderHamburger[i];
	}
	delete this->beerImage;
	delete this->orderBox;
}

void Customer::set_level(int change_level){
	level = change_level;
}

bool Customer::check_order(Hamburger* target)
{
	for(int i = 0 ; i < this->orderlist.size() ; i++){  //若漢堡符合訂單則移除客人訂單中該漢堡 
		if(orderlist[i] == target->get_ingre_stack()){
			orderlist.erase(orderlist.begin() + i);
			delete orderHamburger[i];
			orderHamburger.erase(orderHamburger.begin() + i);
			return true;
		}
	}
	return false;
}

bool Customer::angry_leave(){
	if(this->arriveTime.getElapsedTime() > waitTime){
		return true;
	}
	return false;
}

void Customer :: beerServed(){
	this->beerServedCnt++;
	if(beer_order - beerServedCnt >= 0){
		beerText.setString("X " + to_string(beer_order - beerServedCnt));  //若酒訂單 > 0 則顯示剩餘酒需求數 
	}
	else{
		beerText.setString("X 0");  //否則顯示0 
	}
}

bool Customer::is_served(){
	if(this->beerServedCnt >= this->beer_order && this->orderlist.size() == 0){
		return true;
	}
	return false;
}


void Customer :: drawCustomer(sf :: RenderWindow& window){
	window.draw(this->orderBox->getSprite());
	window.draw(this->getSprite());
	for(int i = 0; i < this->orderlist.size(); i++){
		this->orderHamburger[i]->drawHamburger(window);
	}
	window.draw(this->beerImage->getSprite());
	window.draw(this->beerText);
	window.draw(this->timer);
}

void Customer :: timerUpdate(sf :: Image timerImg[], int timerImgCnt){
	float changeInterval = waitTime.asSeconds() / timerImgCnt;  //將客人總等待時間切成imgCnt份間距 
	int currentInterval = static_cast<int>(arriveTime.getElapsedTime().asSeconds() / changeInterval);  //判斷目前經過時間所在間距 
	try{
		this->timerTexture.update(timerImg[currentInterval]);  //更新時間條為目前所在間距 
	}
	catch(out_of_range){
		cerr << "timer image " << currentInterval << " does not exist." << endl;
	}
}


HeartAndScore :: HeartAndScore(sf :: Font& font, sf :: Image& initialHeart){
	this->heartImg.loadFromImage(initialHeart);
	this->heart.setTexture(heartImg);
	this->heart.setPosition(sf :: Vector2f(20, 1100));
	this->heart.setScale(sf :: Vector2f(0.7, 0.7));
	
	this->score.setFont(font);
	this->score.setCharacterSize(48);
	this->score.setStyle(sf :: Text :: Bold);
	this->score.setFillColor(sf :: Color :: White);
	this->score.setPosition(sf :: Vector2f(375, 1090));
	this->score.setString(to_string(0));
}

HeartAndScore :: ~HeartAndScore(){}

void HeartAndScore :: update(int heartLeft, int newScore, sf :: Image heartImg[]){
	if(heartLeft >= 1){
		this->heartImg.update(heartImg[3 - heartLeft]);
	}
	
	this->score.setString(to_string(newScore));
}

void HeartAndScore :: drawHeartAndScore(sf :: RenderWindow& window){
	window.draw(this->heart);
	window.draw(this->score);
}
