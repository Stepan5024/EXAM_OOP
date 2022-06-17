﻿/*******************************************************************\
 * Comment(s)    : ОБЪЯВЛЕНИЕ ТРЕХ КЛАССОВ. НАСЛЕДОВАНИЕ            *
 *                 СТАТИЧЕСКИЕ ПРАВИЛА						        *
 *                 РАННЕЕ СВЯЗЫВАНИЕ						        *
 *                                                                  *
 \******************************************************************/

#include <windows.h>
#include "ModelingCar.h"	//объявление классов
#include <iostream>
#include "CarExhaustPipe.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 //глобальная переменная видна в файлах
 //внешнее обявление глобальной переменной
extern HDC hdc;      // объявим  контекст устройства
using namespace std;

// Макрос для проверки состояния клавиатуры
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

	/*----------------------------------------------------------------*/
	/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В               */
	/*----------------------------------------------------------------*/
			/*----------------------------------------*/
			/*        МЕТОДЫ КЛАССА Location          */
			/*----------------------------------------*/
Location::Location(int InitX, int InitY) //конструктор
{
	X = InitX;
	Y = InitY;
};

int Location::GetX()  // получить X координату точки
{	return X;	};

  
int Location::GetY() // получить Y координату точки
{	return Y;	};

void Location::SetX(int NewX)  // установить новое значение Х
{	X = NewX;	};


void Location::SetY(int NewY) // установить новое значение Y 
{	Y = NewY;	}; 

/******************************************/
/*        МЕТОДЫ КЛАССА Point                           */
/******************************************/
Point::Point(int InitX, int InitY, COLORREF InitColor) : Location(InitX, InitY) //конструктор
{
	color = InitColor;
}

Point::~Point(void) //деструктор
{
}

//Метод - получение цвета
COLORREF Point::get_color()
{
	return color;
}
// COLORREF color = RGB(0, 0, 0);	 //Установить изнач. значение цвета - черный
// 
// Point APoint(color, x0, y0);     //Инициализация точки
//Метод - установить новый цвет
void Point::set_color(COLORREF new_color)
{
	color = new_color;
}


/******************************************/
/*        МЕТОДЫ КЛАССА Draw              */
/******************************************/

IDraw::IDraw(int InitX, int InitY, COLORREF InitColor) : Point(InitX, InitY, InitColor)
{
}

IDraw::~IDraw(void)
{
}




			/*----------------------------------------*/
			/*        МЕТОДЫ КЛАССА Brick             */
			/*----------------------------------------*/
Brick::Brick(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor) : Barriers(InitX, InitY, InitColor) {
	Width = InitWidth;
	Length = InitLength;
}

void Brick::Show() {				// отрисует кирпич
	
	HBRUSH hBrush = CreateSolidBrush(RGB(163, 146, 0)); // цвет тела - кирпичный; //создаём объект-кисть
	SelectObject(hdc, hBrush);		//делаем кисть активной
	DrawBrick(hBrush);
	DeleteObject(hBrush);			// Уничтожим нами созданные объекты
};

void Brick::Hide() { // спрячет кирпич
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // цвет тела - кирпичный; //создаём объект-кисть
	SelectObject(hdc, hBrush);		//делаем кисть активной
	DrawBrick(hBrush);
	DeleteObject(hBrush);			// Уничтожим нами созданные объекты
};

int Brick::GetBrickWidth() {		// получить ширину
	return Width;
};

void Brick::SetBrickWidth(int NewWidth) {		// установить ширину
	Width = NewWidth;
};

int Brick::GetLength() {					// получить длину
	return Length;
};

void Brick::SetBrickLength(int NewLength) {		// установить длину
	Length = NewLength;
};
void Brick::MoveTo(int NewX, int NewY) {
	Hide();			// стирание канистры
	X = NewX;		// поменять координаты
	Y = NewY;
	Show();			// показать канистру на новом месте
};


void Brick::DrawBrick(HBRUSH hBrush) {
	
	int length = GetLength();			// длина кирпича
	int width = GetBrickWidth();			// длина кирпича
	Rectangle(hdc, X - width, Y - length, X, Y); // канистра
	Rectangle(hdc, X - width, Y - length, X, Y); //аргументы - это коордианты левого верхнего и правого нижнего углов
	DeleteObject(hBrush); //Уничтожим нами созданный объект

};

bool Brick::Touch(int XCarCoord, int YCarCoord, int CarLenght, int CarHeight, int XBrickCoord, int YBrickCoord) {

	if (XCarCoord >= (XBrickCoord - Brick::GetLength()) && (XCarCoord - CarLenght - 50)
		<= (XBrickCoord - Brick::GetLength()) 
		&& (YCarCoord >= YBrickCoord) // верхний проезд над кирпичом
		&& ((YCarCoord <= YBrickCoord))) // нижний проезд под кирпичом
		return true;
	return false;

}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Barriers          */
/*----------------------------------------*/

Barriers::Barriers(int InitX, int InitY, COLORREF InitColor) : IDraw(InitX, InitY, InitColor) {

}

void Barriers::Show() { // отрисует канистру
	/*HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0)); // Зададим перо и цвет пера - зеленый;
	int height = 50; // высота канистры
	int lenght = 50; // длина канистры
	Rectangle(hdc, X - lenght, Y - height, X, Y); // канистра
	DeleteObject(Pen);			// Уничтожим нами созданные объекты*/
};

void Barriers::Hide() { // спрячет канистру
	/*HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Зададим перо и цвет пера - зеленый;
	int height = 50; // высота канистры
	int lenght = 50; // длина канистры
	Rectangle(hdc, X - lenght, Y - height, X, Y); // канистра
	DeleteObject(Pen);			// Уничтожим нами созданные объекты*/
};


void Barriers::MoveTo(int NewX, int NewY) {
	Hide();			// стирание канистры
	X = NewX;		// поменять координаты
	Y = NewY;
	Show();			// показать канистру на новом месте
};
void Barriers::Drag(int Step) {
	int NextX, NextY;				//новые координаты фигуры

	NextX = GetX();
	NextY = GetY();
	int i;
	//бесконечный цикл буксировки фигуры
	while (1) {

		if (KEY_DOWN(VK_ESCAPE)) break;		//выход по «escape»
		/*детект столкновения
		if (((NextX > MillX - 1.1 * MillWidth) and (NextX < MillX + 0.1 * MillWidth)) and ((NextY > MillY - MillHight) and (NextY < MillY))) {
			//cout << "\n\t\tIn collision" << endl;
			InCollisionFlag = true;
			break;
		}*/

		//направление движения объекта
		if (KEY_DOWN(VK_LEFT)) {			//стрелка влево

			NextX -= Step;
			MoveTo(NextX, NextY);
			Sleep(500);

		}//if()

		if (KEY_DOWN(VK_RIGHT)) {			//39 стрелка вправо

			NextX += Step;
			MoveTo(NextX, NextY);
			Sleep(500);

		}//if()

		if (KEY_DOWN(VK_DOWN)) {			//40 стрелка вниз

			NextY += Step;
			MoveTo(NextX, NextY);
			Sleep(500);

		}//if()

		if (KEY_DOWN(VK_UP)) {			//38 стрелка вверх

			NextY -= Step;
			MoveTo(NextX, NextY);
			Sleep(500);

		}//if()

	}//while

}//Drag

			/*----------------------------------------*/
			/*        МЕТОДЫ КЛАССА Canister          */
			/*----------------------------------------*/

Canister::Canister(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor) : Barriers(InitX, InitY, InitColor) {

	Width = InitWidth;
	Length = InitLength;
} 
			
void Canister::Show() { // отрисует канистру
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0)); // Зададим перо и цвет пера - зеленый;
	DrawCanister(Pen);
	DeleteObject(Pen);			// Уничтожим нами созданные объекты
};

void Canister::Hide() { // спрячет канистру
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Зададим перо и цвет пера - зеленый;
	DrawCanister(Pen);
	DeleteObject(Pen);			// Уничтожим нами созданные объекты
};


int Canister::GetCanisterWidth() {		// получить ширину
	return Width;
};

void Canister::SetCanisterWidth(int NewWidth) {		// установить ширину
	Width = NewWidth;
};

int Canister::GetLength() {					// получить длину
	return Length;
};

void Canister::SetCanisterLength(int NewLength) {		// установить длину
	Length = NewLength;
};
void Canister::MoveTo(int NewX, int NewY) {
	Hide();			// стирание канистры
	X = NewX;		// поменять координаты
	Y = NewY;
	Show();			// показать канистру на новом месте
};
void Canister::DrawCanister(HPEN Pen) {
	SelectObject(hdc, Pen);		// сделаем перо активным
	int height = 50; // высота канистры
	int lenght = 50; // длина канистры
	Rectangle(hdc, X - lenght, Y - height, X, Y); // канистра
	DeleteObject(Pen);			

}; 
			/*----------------------------------------*/
			/*        МЕТОДЫ КЛАССА Lightning          */
			/*----------------------------------------*/

Lightning::Lightning(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor) : Barriers(InitX, InitY, InitColor) {

	Width = InitWidth;
	Length = InitLength;
}

void Lightning::Show() { // отрисует 
	HBRUSH hBrush = CreateSolidBrush(RGB(240, 214, 0));
	SelectObject(hdc, hBrush);		//делаем кисть активной
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 227, 0)); // Зададим перо и цвет пера - зеленый;
	DrawLightning(Pen);
	DeleteObject(Pen);			// Уничтожим нами созданные объекты
};

void Lightning::Hide() { // спрячет канистру
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Зададим перо и цвет пера - зеленый;
	DrawLightning(Pen);
	DeleteObject(Pen);			// Уничтожим нами созданные объекты
};


int Lightning::GetLightningWidth() {		// получить ширину
	return Width;
};

void Lightning::SetLightningWidth(int NewWidth) {		// установить ширину
	Width = NewWidth;
};

int Lightning::GetLength() {					// получить длину
	return Length;
};

void Lightning::SetLightningLength(int NewLength) {		// установить длину
	Length = NewLength;
};
void Lightning::MoveTo(int NewX, int NewY) {
	Hide();			// стирание канистры
	X = NewX;		// поменять координаты
	Y = NewY;
	Show();			// показать канистру на новом месте
};
void Lightning::DrawLightning(HPEN Pen) {
	SelectObject(hdc, Pen);		// сделаем перо активным
	int height = 50; // высота канистры
	int lenght = 50; // длина канистры
	Rectangle(hdc, X - lenght, Y - height, X, Y); // канистра
	DeleteObject(Pen);

};
			/*----------------------------------------*/
			/*        МЕТОДЫ КЛАССА ABase              */
			/*----------------------------------------*/
ABase::ABase(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor) : IDraw(InitX, InitY, InitColor)  // конструктор
{
	BodyCarLenght = InitBodyCarLenght;
	Speed = InitSpeed;
	
}

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);		// сделать текущими координаты x1, y1
	return LineTo(hdc, x2, y2);
} 

void Car::DrawBaseBody(HPEN Pen) {		// основание на котором сидят колеса

	SelectObject(hdc, Pen);				// сделаем перо активным
	int height = 50;
	Rectangle(hdc, X - GetBaseLenght(), Y, X, Y - height); // корпус
	int a = GetBaseLenght() / 4;
	int radius = 70;
	Arc(hdc, X - a * 3 + radius / 10 + radius / 2, Y + 20, X - 3 * a - radius / 10 - radius / 2, Y - 40, GetBaseLenght() * 20, Y + 50, GetBaseLenght() / 20, Y + 50); // левое подколесо
	Arc(hdc, X - 1 * a + radius / 10 + radius / 2, Y + 20, X - 1 * a - radius / 10 - radius / 2, Y - 40, GetBaseLenght() * 20, Y + 50, GetBaseLenght() / 20, Y + 50); // правое подколесо
	int lenght = GetBaseLenght() / 3;
	Rectangle(hdc, X - GetBaseLenght() / 3 - lenght, Y - 50, X - GetBaseLenght() / 3, Y - 120); // нарисуем кабину без окон

	Pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	SelectObject(hdc, Pen);				// сделаем перо активным
	Line(hdc, X - a * 3 + radius / 10 + radius / 2 - 5, Y - 2, X - 3 * a - radius / 10 - radius / 2 + 5, Y - 2); // за контуром колес
	Line(hdc, X - 1 * a + radius / 10 + radius / 2 - 5, Y - 2, X - 1 * a - radius / 10 - radius / 2 + 5, Y - 2); // за контуром колес	
	DeleteObject(Pen);					// Уничтожим нами созданные объекты

} 

void Car::DrawBaseWheels(HPEN Pen) {	// колеса 
	
	SelectObject(hdc, Pen);				//сделаем перо активным
	int radius = 70;					// радиус колес
	int a = GetBaseLenght() / 4;
	Ellipse(hdc, X  - a + radius / 2, Y + 35 - radius, X  - a - radius / 2, Y - 35 + radius); // правое колесо
	Ellipse(hdc, X  - 3 * a + radius / 2, Y + 35 - radius, X - 3 * a - radius / 2, Y - 35 + radius); // левое колесо
	DeleteObject(Pen); 
} 



void ABase::Show() { // отобразить объект

	/*string CarColor = GetBaseColor(); // получаем цвет из класса ABase
	HPEN Pen;
	if (CarColor == "red") 
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Зададим перо и цвет пера - красный
	else if (CarColor == "black")
		Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Зададим перо и цвет пера - черный
	else Pen = CreatePen(PS_SOLID, 2, RGB(255, 165, 0)); // Зададим перо и цвет пера - оранжевый
	
	DrawBaseBody(Pen);
	DrawBaseWheels(Pen);
	DeleteObject(Pen); // Уничтожим нами созданные объекты  */
}

void ABase::Hide() { // спрятать корпус машины

	/*HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Зададим перо и цвет пера - красный
	DrawBaseBody(Pen);
	DrawBaseWheels(Pen);
	DeleteObject(Pen); */
} 

void ABase::MoveTo(int NewX, int NewY) // поставить в соответствие новые координаты
{
	Hide();			// стирание старого контура машины
	X = NewX;		// поменять координаты
	Y = NewY;
	Show();			// показать контур машины на новом месте
}

void ABase::Drag(int Step) // переместить объект
{
	int FigX, FigY; // новые координаты фигуры

	FigX = GetX();    // получаем начальное положение фигуры
	FigY = GetY();

	while (1)	// цикл буксировки фигуры
	{
		if (KEY_DOWN(VK_ESCAPE))     // конец работы 27 escape
		{	
			//cout << "FigX = " << GetX();
			break;
		}
		// направление движения объекта
		if (KEY_DOWN(VK_LEFT)) // стрелка влево  37
		{
			FigX -= GetMaxSpeed();
			MoveTo(FigX, FigY);
			Sleep(500);
		}

		if (KEY_DOWN(VK_RIGHT)) // стрелка вправо  39
		{
			FigX += GetMaxSpeed();
			MoveTo(FigX, FigY);
			Sleep(500);
		}

		if (KEY_DOWN(VK_DOWN)) // стрелка вниз  40
		{
			FigY += GetMaxSpeed();
			MoveTo(FigX, FigY);
			Sleep(500);
		}

		if (KEY_DOWN(VK_UP)) // стрелка вверх  38
		{
			FigY -= GetMaxSpeed();
			MoveTo(FigX, FigY);
			Sleep(500);
		}
	}

};



		/*----------------------------------------*/
		/*        МЕТОДЫ КЛАССА Car               */
		/*----------------------------------------*/

Car::Car(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor) : ABase(InitX, InitY, InitBodyCarLenght, InitSpeed, InitColor) // конструктор Car
{}

void Car::DrawCarCabin(HPEN Pen) { // кабина 
	
	//cout << "x = " << X << " y = " << Y << endl;
	SelectObject(hdc, Pen);		// сделаем перо активным
	int height = 70;
	int lenght = GetBaseLenght() / 3;
	Rectangle(hdc, X - GetBaseLenght() / 3 - lenght * 0.2, Y - 60, X - GetBaseLenght() / 3 - lenght * 0.8, Y - 110); //окошечко
	DeleteObject(Pen);			// Уничтожим нами созданные объекты
} 

void Car::Show()				// показать машину
{
	
	HPEN Pen = CreatePen(PS_SOLID, 2, get_color()); // Зададим перо и цвет пера - красный
	
	DrawBaseBody(Pen);
	DrawBaseWheels(Pen); // избыточность наследования убираем
	// если что-то опровергающее наше мнение простое веерное наследование vs простая иерархия найти исключения
	// когда нет движения , программа простая , когда все делается на этапе компиляции
	// ответ когда большинство параметров нужно для потомка. Пример точка, все ее поля нужны для следующих объектов
	

	DrawCarCabin(Pen);			// кабина
	DeleteObject(Pen);			// Уничтожим нами созданные объекты  
}

void Car::Hide()				// скрыть машину
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // зададим перо и цвет пера - белый
	DrawBaseBody(Pen);
	DrawBaseWheels(Pen);

	DrawCarCabin(Pen);			// кабина
	DeleteObject(Pen);			// Уничтожим нами созданные объекты  
}
bool Car::Touch(int XCarCoord, int YCarCoord, int CarLenght, int CarHeight, int XBrickCoord, int YBrickCoord, int BrickLength) {

	if (XCarCoord + 10 >= (XBrickCoord - BrickLength)
		&& (XCarCoord - CarLenght) <= (XBrickCoord - BrickLength + 10) 
		&& (YCarCoord + 60 >= YBrickCoord ) // верхний проезд над кирпичом
		&& ((YCarCoord <= YBrickCoord + 30))
		
		) // нижний проезд под кирпичом
		
		return true;

	return false;

}
		/*----------------------------------------*/
		/*        МЕТОДЫ КЛАССА CarWithHood       */
		/*----------------------------------------*/

CarWithHood::CarWithHood(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor) : Car(InitX, InitY, InitBodyCarLenght, InitSpeed, InitColor) // конструктор CarExhaustPipe
{}

void CarWithHood::DrawCarHood(HPEN Pen) { // капот
	SelectObject(hdc, Pen);			// сделаем перо активным
	int heightABase = 50;
	int heightCabin = 70;
	int lenght = GetBaseLenght() / 3;
	int a = GetBaseLenght() / 2;
	int radius = 70;
	POINT poly[6];

	poly[0].x = X;					// первая координата полигона
	poly[0].y = Y - heightABase;

	poly[1].x = X - lenght / 2 + 50;
	poly[1].y = Y - heightABase - heightABase / 2;

	poly[2].x = X - lenght / 2 - 10;
	poly[2].y = Y - heightCabin / 2 - heightABase + heightCabin / 13;

	poly[3].x = X - a + lenght / 2 + lenght / 3;
	poly[3].y = Y - heightCabin / 2 - heightABase + heightCabin / 18;

	poly[4].x = X - a + lenght / 2 + lenght / 4;
	poly[4].y = Y - heightCabin / 2 - heightABase + heightCabin / 25;

	poly[5].x = X - a + lenght / 2;
	poly[5].y = Y - heightCabin / 2 - heightABase;

	Polyline(hdc, poly, 6);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
} 

void CarWithHood::Show() {
	
	HPEN Pen = CreatePen(PS_SOLID, 2, get_color()); // Зададим перо и цвет пера - красный
	Car::Show();
	DrawCarHood(Pen);				// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}

void CarWithHood::Hide() {
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));	// Зададим перо и цвет пера - белый
	Car::Hide();
	DrawCarHood(Pen);				// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА CarExhaustPipe    */
/*----------------------------------------*/


CarExhaustPipe::CarExhaustPipe(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor) : CarWithHood(InitX, InitY, InitBodyCarLenght, InitSpeed, InitColor) // конструктор CarExhaustPipe
{}

void CarExhaustPipe::DrawExhaustPipe(HPEN Pen) {
	SelectObject(hdc, Pen);			// сделаем перо активным
	Rectangle(hdc, X - GetBaseLenght() - 30, Y - 30, X - GetBaseLenght(), Y - 10); // выхлопная труба
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
} 

void CarExhaustPipe::Show()			  // показать машину с выхлопной трубой
{
	
	HPEN Pen = CreatePen(PS_SOLID, 2, get_color()); // Зададим перо и цвет пера - красный
	
	CarWithHood::Show();
	DrawExhaustPipe(Pen);			// выхлопная труба
	DeleteObject(Pen);				// Уничтожим нами созданные объекты
} 

void CarExhaustPipe::Hide()			// спрятать 
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));	// Зададим перо и цвет пера - белый
	CarWithHood::Hide();
	DrawExhaustPipe(Pen);			// выхлопная труба
	DeleteObject(Pen);				// Уничтожим нами созданные объекты
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА CarWithLuggade    */
/*----------------------------------------*/

CarWithLuggade::CarWithLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor) : Car(InitX, InitY, InitBodyCarLenght, InitSpeed, InitColor) // конструктор CarExhaustPipe
{

}

void CarWithLuggade::DrawCarLuggade(HPEN Pen) { // багажник


	SelectObject(hdc, Pen);			// сделаем перо активным
	int heightCabin = 70;
	int heightABase = 50;
	int lenght = GetBaseLenght() / 3;
	int a = GetBaseLenght() / 2;
	int radius = 70;
	POINT poly[4];

	poly[0].x = X - 2 * GetBaseLenght() / 3;					// первая координата полигона
	poly[0].y = Y - heightCabin / 2 - heightABase;

	poly[1].x = X - 2 * GetBaseLenght() / 3 - GetBaseLenght() / 3 + lenght / 5;
	poly[1].y = Y - heightCabin / 2 - heightABase;

	poly[2].x = X - 2 * GetBaseLenght() / 3 - GetBaseLenght() / 3;
	poly[2].y = Y - heightCabin / 2 - heightABase + lenght / 5;

	poly[3].x = X - GetBaseLenght();
	poly[3].y = Y - heightABase;

	Polyline(hdc, poly, 4);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
} 

void CarWithLuggade::Show() {

	HPEN Pen = CreatePen(PS_SOLID, 2, get_color()); // Зададим перо и цвет пера - красный
	
	Car::Show();
	DrawCarLuggade(Pen);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}

void CarWithLuggade::Hide() {
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));	// Зададим перо и цвет пера - белый
	Car::Hide();
	DrawCarLuggade(Pen);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}

/*-----------------------------------------------*/
/*        МЕТОДЫ КЛАССА CarWithHoodAndLuggade    */
/*-----------------------------------------------*/

CarWithHoodAndLuggade::CarWithHoodAndLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor)
	: CarWithHood(InitX, InitY, InitBodyCarLenght, InitSpeed, InitColor) // конструктор CarExhaustPipe
{}

void CarWithHoodAndLuggade::DrawCarLuggade(HPEN Pen) { // багажник
	SelectObject(hdc, Pen);			// сделаем перо активным
	int heightCabin = 70;
	int heightABase = 50;
	int lenght = GetBaseLenght() / 3;
	int a = GetBaseLenght() / 2;
	int radius = 70;
	POINT poly[4];

	poly[0].x = X - 2 * GetBaseLenght() / 3;					// первая координата полигона
	poly[0].y = Y - heightCabin / 2 - heightABase;

	poly[1].x = X - 2 * GetBaseLenght() / 3 - GetBaseLenght() / 3 + lenght / 5;
	poly[1].y = Y - heightCabin / 2 - heightABase;

	poly[2].x = X - 2 * GetBaseLenght() / 3 - GetBaseLenght() / 3;
	poly[2].y = Y - heightCabin / 2 - heightABase + lenght / 5;

	poly[3].x = X - GetBaseLenght();
	poly[3].y = Y - heightABase;

	Polyline(hdc, poly, 4);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
} 
/*
void CarWithHoodAndLuggade::DrawCarHood(HPEN Pen) { // капот
	SelectObject(hdc, Pen);			// сделаем перо активным
	int heightABase = 50;
	int heightCabin = 70;
	int lenght = GetBaseLenght() / 3;
	int a = GetBaseLenght() / 2;
	int radius = 70;
	POINT poly[6];

	poly[0].x = X;					// первая координата полигона
	poly[0].y = Y - heightABase;

	poly[1].x = X - lenght / 2 + 50;
	poly[1].y = Y - heightABase - 30;

	poly[2].x = X - lenght / 2 - 10;
	poly[2].y = Y - heightCabin / 2 - heightABase + heightCabin / 13;

	poly[3].x = X - a + lenght / 2 + lenght / 3;
	poly[3].y = Y - heightCabin / 2 - heightABase + heightCabin / 18;

	poly[4].x = X - a + lenght / 2 + lenght / 4;
	poly[4].y = Y - heightCabin / 2 - heightABase + heightCabin / 25;

	poly[5].x = X - a + lenght / 2;
	poly[5].y = Y - heightCabin / 2 - heightABase;

	Polyline(hdc, poly, 6);			// капот
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}
*/
void CarWithHoodAndLuggade::Show() {
	
	HPEN Pen = CreatePen(PS_SOLID, 2, get_color()); // Зададим перо и цвет пера - красный
	Car::Show();
	DrawCarLuggade(Pen);			// капот
	DrawCarHood(Pen);				// багажник
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}

void CarWithHoodAndLuggade::Hide() {
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));	// Зададим перо и цвет пера - белый
	Car::Hide();
	DrawCarLuggade(Pen);			// капот
	DrawCarHood(Pen);				// багажник
	DeleteObject(Pen);				// Уничтожим нами созданные объекты  
}