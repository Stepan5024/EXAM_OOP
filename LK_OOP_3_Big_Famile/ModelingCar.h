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
	Point(int InitX, int InitY, COLORREF InitColor);			//конструктор класса
	~Point();								//деструктор
	COLORREF get_color();		//Получить цвет
	void set_color(COLORREF new_color);		//Установить новый цвет
};
/************** Интерфейс РИСУНОК *******************/
class IDraw : public Point
{
public:
	IDraw(int InitX, int InitY, COLORREF InitColor);
	~IDraw();
	//virtual void DrawBaseBody(HPEN Pen) = 0;		// отрисует заданным цветом основу на которую садятся колеса
	//virtual void DrawBaseWheels(HPEN Pen) = 0;	// отрисует заданным колеса
	virtual void Show() = 0;						//показать фигуру 
	virtual void Hide() = 0;						//спрятать фигуру
	virtual void MoveTo(int NewX, int NewY) = 0;	//переместить точку
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) = 0;				//буксировка фигуры
};

class Barriers : public IDraw { // Абстрактный базовый класс
private:
	int Width = 50;			// ширина
	int Length = 50;		// длина

public:
	Barriers(int InitX, int InitY, COLORREF InitColor);
	virtual void Show() override;
	virtual void Hide() override;
	void MoveTo(int NewX, int NewY) override;			// переместить объект по новым координатам
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) override;
	virtual void Drag(int Step);
	virtual int GetTypeId() = 0;
	virtual int GetLength() = 0;
};

  /*-----------------------  Класс Canister ----------------------------------*/
class Canister : public Barriers {
private:
	int Width;			// ширина
	int Length;			// длина
	int id = 1;			// id класса
public:
	Canister(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(0, 255, 0));
	void DrawCanister(HPEN Pen); // отрисовкка канистры
	virtual void Show();
	virtual void Hide();
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	int GetCanisterWidth();						// получить ширину
	void SetCanisterWidth(int NewWidth);		// установить ширину
								
	void SetCanisterLength(int NewLength);		// установить длину
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override; // получить длину
}; 
/*-----------------------  Класс Canister ----------------------------------*/
class Lightning : public Barriers {
private:
	int Width;			// ширина
	int Length;			// длина
	int id = 3;			// id класса
public:
	Lightning(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(0, 255, 0));
	void DrawLightning(HPEN Pen); // отрисовкка канистры
	virtual void Show();
	virtual void Hide();
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	int GetLightningWidth();						// получить ширину
	void SetLightningWidth(int NewWidth);		// установить ширину
	void SetLightningLength(int NewLength);		// установить длину
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override; // получить длину
};
/*-----------------------  Класс Brick ----------------------------------*/
class Brick : public Barriers {
private:
	int Width;			// ширина
	int Length;			// длина
	int id = 2;			// id класса
public:
	Brick(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(185, 122, 87));
	void DrawBrick(HBRUSH Pen); // отрисовкка канистры
	virtual void Show();
	virtual void Hide();
	int GetBrickWidth();						// получить ширину
	void SetBrickWidth(int NewWidth);			// установить ширину

	void SetBrickLength(int NewLength);			// установить длину
	void MoveTo(int NewX, int NewY);			// переместить объект по новым координатам
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord);		// проверить наложение координат кирпича с машиной
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override;							// получить длину
};


/*-----------------------  Класс Base ----------------------------------*/
class Base : public IDraw { // абстрактный класс
private:

	int BodyCarLenght;				// длина корпуса
	int Speed;						// скорость
	

public:

	Base(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor = RGB(255, 0, 0));
	virtual void DrawBaseBody(HPEN Pen) = 0;		// отрисует заданным цветом основу на которую садятся колеса
	virtual void DrawBaseWheels(HPEN Pen) = 0;		// отрисует заданным колеса
	virtual int GetTypeId() = 0; // ID класса
	int GetMaxSpeed() { return Speed; };				// получить текущую скорость
	void SetSpeed(int NewSpeed) { Speed = NewSpeed; };	// установить новую скорость
	int GetBaseLenght() { return BodyCarLenght; };		// получить длину корпуса
	void SetBaseLenght(int NewBaseLenght) { BodyCarLenght = NewBaseLenght; };
	
	virtual bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength) = 0;
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) override;						// передвижение фигуры по стрелкам
	virtual void MoveTo(int NewX, int NewY) override;	// переместить объект по новым координатам
	virtual void Show() override;				// отрисует базовый автомобиль
	virtual void Hide() override;				// спрячет базовый автомобиль
};

/*-----------------------  Класс Car  -------------------------------*/
class Car : public Base {
private:	
	int id = 1;							// id класса

public:
	Car(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor);
	virtual void Show() override;				// показать фигуру машины
	virtual void Hide() override;				// скрыть фигуру машины
	void DrawCarCabin(HPEN Pen);		// нарисовать кабину с окном заданного цвета
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength) override;		// проверить наложение координат кирпича с машиной
	void DrawBaseBody(HPEN Pen) override;		// отрисует заданным цветом основу на которую садятся колеса
	virtual void DrawBaseWheels(HPEN Pen) override;		// отрисует заданным колеса
	virtual int GetTypeId() override {
		return id;
	}
};

class CarWithHood : public Car {		// машина с капотом
private:
	int id = 2;							// id класса

public:
	CarWithHood(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // по умолчанию параметры конструктора
	virtual void Show() override;				// показать фигуру машины с капотом
	virtual void Hide() override;				// скрыть фигуру машины с капотом
	void DrawCarHood(HPEN Pen);			// нарисовать капот заданного цвета
	int GetTypeId() {
		return id;
	}
};

class CarWithLuggade : public Car { // машина с багажником
private:
	int id = 3;							// id класса

public: 
	CarWithLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor);
	virtual void Show() override;				// показать фигуру машины с капотом
	virtual void Hide() override;				// скрыть фигуру машины с капотом
	void DrawCarLuggade(HPEN Pen);		// нарисовать багажник заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithHoodAndLuggade : public CarWithHood {		// машина с капотом
private:
	int id = 4;							// id класса
public:
	CarWithHoodAndLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // по умолчанию параметры конструктора
	virtual void Show() override;				// показать фигуру машины с капотом
	virtual void Hide() override;				// скрыть фигуру машины с капотом
	//void DrawCarHood(HPEN Pen);			// нарисовать капот заданного цвета
	void DrawCarLuggade(HPEN Pen);		// нарисовать багажник заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

class CarExhaustPipe : public CarWithHood {
private:
	int id = 5;							// id класса
public:
	CarExhaustPipe(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // по умолчанию параметры конструктора

	virtual void Show();				// показать фигуру  
	virtual void Hide();				// скрыть фигуру 
	void DrawExhaustPipe(HPEN Pen);		// выхлопная труба заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithBattery : public CarWithHood {
private:
	int id = 6;							// id класса
public:
	CarWithBattery(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // по умолчанию параметры конструктора

	virtual void Show();				// показать фигуру  
	virtual void Hide();				// скрыть фигуру 
	void DrawBattery(HPEN Pen);		// выхлопная труба заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

