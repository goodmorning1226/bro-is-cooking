#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

const string ingreImgURL[10]  //圖片陣列 
= {"image/cheese.png", "image/cucumber.png", "image/lettuce.png",
	"image/tomato.png", "image/meat.png", "image/breadtop.png", 
	"image/breadbottom.png", "image/cooked meat.png", "image/dead meat.png", "image/beer.png"};

const sf :: Vector2f garbageCanStartPos(68, 824);  //垃圾桶位置 
const sf :: Vector2f garbageCanEndPos(279, 894);

//食材位置 
const sf :: Vector2f cheeseStartPos(1595, 739);
const sf :: Vector2f cheeseEndPos(1719, 841);

const sf :: Vector2f cucumberStartPos(1445, 636);
const sf :: Vector2f cucumberEndPos(1559, 707);

const sf :: Vector2f lettuceStartPos(1428, 756);
const sf :: Vector2f lettuceEndPos(1565, 841);

const sf :: Vector2f tomatoStartPos(1590, 619);
const sf :: Vector2f tomatoEndPos(1712, 701);

const sf :: Vector2f meatStartPos(377, 681);
const sf :: Vector2f meatEndPos(524, 873);

const sf :: Vector2f breadtopStartPos(535, 995);
const sf :: Vector2f breadtopEndPos(856, 1136);

const sf :: Vector2f breadbottomStartPos(925, 1004);
const sf :: Vector2f breadbottomEndPos(1248, 1134);

const sf :: Vector2f ovenStartPos(546, 640);
const sf :: Vector2f ovenEndPos(944,890);

const sf :: Vector2f burgerPlateStartPos(994, 651);
const sf :: Vector2f burgerPlateEndPos(1373, 907);

const sf :: Vector2f beerStartPos(74, 504);
const sf :: Vector2f beerEndPos(262, 751);

const sf::Vector2f cust1StartPos(254 , 101);
const sf::Vector2f cust2StartPos(1020 , 101);

//home page
const sf :: Vector2f gameStartButtonStartPos(710, 902);
const sf :: Vector2f gameStartButtonEndPos(1057, 1025);

const sf :: Vector2f rankButtonStartPos(1112, 902);
const sf :: Vector2f rankButtonEndPos(1444, 1025);

const sf :: Vector2f infoButtonStartPos(301, 902);
const sf :: Vector2f infoButtonEndPos(639, 1025);

const sf :: Vector2f loginButtonStartPos(1432, 48);
const sf :: Vector2f loginButtonEndPos(1772, 188);

const sf :: Vector2f registerButtonStartPos(1060, 706);
const sf :: Vector2f registerButtonEndPos(1240, 738);

//game over page
const sf :: Vector2f gameRestartButtonStartPos(1472, 1054);
const sf :: Vector2f gameRestartButtonEndPos(1762, 1169);

//login & register page
const sf :: Vector2f inputUserNameStartPos(748, 784);
const sf :: Vector2f inputUserNameEndPos(1060, 908);

//error page
const sf :: Vector2f errorToLoginStartPos(484, 781);
const sf :: Vector2f errorToLoginEndPos(793, 908);

const sf :: Vector2f errorToRegisterStartPos(1003, 781);
const sf :: Vector2f errorToRegisterEndPos(1315, 908);

//intro頁面
const sf :: Vector2f backStartPos(1458, 917);
const sf :: Vector2f backEndPos(1743, 1027);

const sf :: Vector2f nextStartPos(1458, 1055);
const sf :: Vector2f nextEndPos(1743, 1169);

//所有home鍵通用 
const sf :: Vector2f backToHomeStartPos(57, 1054);
const sf :: Vector2f backToHomeEndPos(340, 1169);
