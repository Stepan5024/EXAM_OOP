#pragma once
#include <string>

using namespace std;
/*************************************************************************\
* Comment(s)    : ОБЪЯВЛЕНИЕ ТРЕХ КЛАССОВ. НАСЛЕДОВАНИЕ                   *
*                 СТАТИЧЕСКИЕ ПРАВИЛА						              *
*                 РАННЕЕ СВЯЗЫВАНИЕ						                  *
*                 ПОЗДНЕЕ СВЯЗЫВАНИЕ						              *
\*************************************************************************/

/*-----------------------     Класс Location    -------------------------*/
class Location
{
protected:							   
	int X;
	int Y;

public:
	Location(int InitX, int InitY); 
	int GetX();						// получить X координату точки
	int GetY();						// получить Y координату точки
	void SetX(int NewX);			// установить новое значение Х
	void SetY(int NewY);			// установить новое значение Y
	
};
class Point : public Location
{
protected:
	COLORREF color; //Цвет

public:
	Point(int InitX, int InitY);	//конструктор класса
	~Point();						//деструктор
	COLORREF get_color(COLORREF color);  //Получить цвет
	void set_color(COLORREF new_color);  //Установить новый цвет
};
/************** Интерфейс РИСУНОК *******************/
class IDraw : public Point
{
public:
	IDraw(int InitX, int InitY);
	~IDraw();
	virtual void DrawBaseBody(HPEN Pen) = 0;		// отрисует заданным цветом основу на которую садятся колеса
	virtual void DrawBaseWheels(HPEN Pen) = 0;		// отрисует заданным колеса
	virtual void Show() = 0;              //показать фигуру 
	virtual void Hide() = 0;              //спрятать фигуру
	virtual void MoveTo(int NewX, int NewY) = 0;//переместить точку
};

class Barriers : public Location {
private:
	int Width = 50;			// ширина
	int Length = 50;			// длина
	int id = 0;							// id класса
public:
	Barriers(int InitX, int InitY);
	virtual void Show() = 0;
	virtual void Hide() = 0;
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	virtual int GetLength() {
		return Length;
	};
	virtual int GetTypeId() {
		return id;
	}
};

  /*-----------------------  Класс Canister ----------------------------------*/
class Canister : public Barriers {
private:
	int Width;			// ширина
	int Length;			// длина
	int FuelCapacity; // емкость канистры
	int id = 1;							// id класса
public:
	Canister(int InitX, int InitY, int InitFuelCapacity, int InitWidth, int InitLength);
	void DrawCanister(HPEN Pen); // отрисовкка канистры
	virtual void Show();
	virtual void Hide();
	int GetFuelCapacity();						// получить емкость
	void SetFuelCapacity(int NewFuelCapacity);	// установить емкость
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	int GetCanisterWidth();						// получить ширину
	void SetCanisterWidth(int NewWidth);			// установить ширину
	int GetCanisterLength();						// получить длину
	void SetCanisterLength(int NewLength);			// установить длину
	virtual int GetTypeId() {
		return id;
	}
}; 
/*-----------------------  Класс Brick ----------------------------------*/
class Brick : public Barriers {
private:
	int Width;			// ширина
	int Length;			// длина
	int id = 0;							// id класса
public:
	Brick(int InitX, int InitY, int InitWidth, int InitLength);
	void DrawBrick(HBRUSH Pen); // отрисовкка канистры
	virtual void Show();
	virtual void Hide();
	int GetBrickWidth();						// получить ширину
	void SetBrickWidth(int NewWidth);			// установить ширину
	int GetBrickLength();						// получить длину
	void SetBrickLength(int NewLength);			// установить длину
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord);		// проверить наложение координат кирпича с машиной
	virtual int GetTypeId() {
		return id;
	}
};

/*-----------------------  Класс Base ----------------------------------*/
class ABase : public IDraw { // абстрактный класс
private:

	int BodyCarLenght;				// длина корпуса
	int Speed;						// скорость
	string BaseColor;				// цвет корпуса
	int id = -1;
public:

	ABase(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, string InitBaseColor = "red");
	virtual void DrawBaseBody(HPEN Pen);		// отрисует заданным цветом основу на которую садятся колеса
	virtual void DrawBaseWheels(HPEN Pen);		// отрисует заданным колеса
	void Show();				// отрисует базовый автомобиль
	void Hide();				// спрячет базовый автомобиль
	int GetMaxSpeed() { return Speed; };				// получить текущую скорость
	void SetSpeed(int NewSpeed) { Speed = NewSpeed; };	// установить новую скорость
	int GetBaseLenght() { return BodyCarLenght; };		// получить длину корпуса
	void SetBaseLenght(int NewBaseLenght) { BodyCarLenght = NewBaseLenght; };
	void Drag();						// передвижение фигуры по стрелкам
	void MoveTo(int NewX, int NewY);	// переместить объект по новым координатам
	string GetBaseColor();	// получить цвет машины
	string SetBaseColor(string NewBaseColor) { BaseColor = NewBaseColor; }	// получить цвет машины
	virtual int GetTypeId();
	virtual bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength) = 0;

};

/*-----------------------  Класс Car  -------------------------------*/
class Car : public ABase {
private:	
	int id = 0;							// id класса
	string ManufacturerName;			// название автопроизводителя

public:
	Car(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, string InitBaseColor = "red", string ManufactureName = "VAZ");
	virtual void Show();				// показать фигуру машины
	virtual void Hide();				// скрыть фигуру машины
	void DrawCarCabin(HPEN Pen);		// нарисовать кабину с окном заданного цвета
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength);		// проверить наложение координат кирпича с машиной
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithHood : public Car {		// машина с капотом
private:
	int id = 1;							// id класса
	int Price;			// цена машины, пока не описал сет и гет
public:
	CarWithHood(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, std::string InitBaseColor = "red"); // по умолчанию параметры конструктора
	virtual void Show();				// показать фигуру машины с капотом
	virtual void Hide();				// скрыть фигуру машины с капотом
	void DrawCarHood(HPEN Pen);			// нарисовать капот заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithLuggade : public Car { // машина с багажником
private:
	int id = 2;							// id класса
	int Price;			// цена машины, пока не описал сет и гет
public: 
	CarWithLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, std::string InitBaseColor = "red");
	virtual void Show();				// показать фигуру машины с капотом
	virtual void Hide();				// скрыть фигуру машины с капотом
	void DrawCarLuggade(HPEN Pen);		// нарисовать багажник заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithHoodAndLuggade : public Car {		// машина с капотом
private:
	int id = 3;							// id класса
	int Price;			// цена машины, пока не описал сет и гет
public:
	CarWithHoodAndLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, std::string InitBaseColor = "red"); // по умолчанию параметры конструктора
	virtual void Show();				// показать фигуру машины с капотом
	virtual void Hide();				// скрыть фигуру машины с капотом
	void DrawCarHood(HPEN Pen);			// нарисовать капот заданного цвета
	void DrawCarLuggade(HPEN Pen);		// нарисовать багажник заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};
