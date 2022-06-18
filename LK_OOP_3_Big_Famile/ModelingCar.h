#pragma once
#include <string>

using namespace std;
/*************************************************************************\
* Comment(s)    : ���������� ���� �������. ������������                   *
*                 ����������� �������						              *
*                 ������ ����������						                  *
*                 ������� ����������						              *
\*************************************************************************/

/*-----------------------     ����� Location    -------------------------*/
class Location
{
protected:							   
	int X;
	int Y;

public:
	Location(int InitX, int InitY); 
	int GetX();						// �������� X ���������� �����
	int GetY();						// �������� Y ���������� �����
	void SetX(int NewX);			// ���������� ����� �������� �
	void SetY(int NewY);			// ���������� ����� �������� Y
	
};

class Point : public Location
{
protected:
	COLORREF color; //����

public:
	Point(int InitX, int InitY, COLORREF InitColor);			//����������� ������
	~Point();								//����������
	COLORREF get_color();		//�������� ����
	void set_color(COLORREF new_color);		//���������� ����� ����
};
/************** ��������� ������� *******************/
class IDraw : public Point
{
public:
	IDraw(int InitX, int InitY, COLORREF InitColor);
	~IDraw();
	//virtual void DrawBaseBody(HPEN Pen) = 0;		// �������� �������� ������ ������ �� ������� ������� ������
	//virtual void DrawBaseWheels(HPEN Pen) = 0;	// �������� �������� ������
	virtual void Show() = 0;						//�������� ������ 
	virtual void Hide() = 0;						//�������� ������
	virtual void MoveTo(int NewX, int NewY) = 0;	//����������� �����
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) = 0;				//���������� ������
};

class Barriers : public IDraw { // ����������� ������� �����
private:
	int Width = 50;			// ������
	int Length = 50;		// �����

public:
	Barriers(int InitX, int InitY, COLORREF InitColor);
	virtual void Show() override;
	virtual void Hide() override;
	void MoveTo(int NewX, int NewY) override;			// ����������� ������ �� ����� �����������
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) override;
	virtual void Drag(int Step);
	virtual int GetTypeId() = 0;
	virtual int GetLength() = 0;
};

  /*-----------------------  ����� Canister ----------------------------------*/
class Canister : public Barriers {
private:
	int Width;			// ������
	int Length;			// �����
	int id = 1;			// id ������
public:
	Canister(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(0, 255, 0));
	void DrawCanister(HPEN Pen); // ���������� ��������
	virtual void Show();
	virtual void Hide();
	void MoveTo(int NewX, int NewY);			// ����������� ������ �� ����� �����������
	int GetCanisterWidth();						// �������� ������
	void SetCanisterWidth(int NewWidth);		// ���������� ������
								
	void SetCanisterLength(int NewLength);		// ���������� �����
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override; // �������� �����
}; 
/*-----------------------  ����� Canister ----------------------------------*/
class Lightning : public Barriers {
private:
	int Width;			// ������
	int Length;			// �����
	int id = 3;			// id ������
public:
	Lightning(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(0, 255, 0));
	void DrawLightning(HPEN Pen); // ���������� ��������
	virtual void Show();
	virtual void Hide();
	void MoveTo(int NewX, int NewY);			// ����������� ������ �� ����� �����������
	int GetLightningWidth();						// �������� ������
	void SetLightningWidth(int NewWidth);		// ���������� ������
	void SetLightningLength(int NewLength);		// ���������� �����
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override; // �������� �����
};
/*-----------------------  ����� Brick ----------------------------------*/
class Brick : public Barriers {
private:
	int Width;			// ������
	int Length;			// �����
	int id = 2;			// id ������
public:
	Brick(int InitX, int InitY, int InitWidth, int InitLength, COLORREF InitColor = RGB(185, 122, 87));
	void DrawBrick(HBRUSH Pen); // ���������� ��������
	virtual void Show();
	virtual void Hide();
	int GetBrickWidth();						// �������� ������
	void SetBrickWidth(int NewWidth);			// ���������� ������

	void SetBrickLength(int NewLength);			// ���������� �����
	void MoveTo(int NewX, int NewY);			// ����������� ������ �� ����� �����������
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord);		// ��������� ��������� ��������� ������� � �������
	virtual int GetTypeId() override {
		return id;
	}
	int GetLength() override;							// �������� �����
};


/*-----------------------  ����� Base ----------------------------------*/
class Base : public IDraw { // ����������� �����
private:

	int BodyCarLenght;				// ����� �������
	int Speed;						// ��������
	

public:

	Base(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor = RGB(255, 0, 0));
	virtual void DrawBaseBody(HPEN Pen) = 0;		// �������� �������� ������ ������ �� ������� ������� ������
	virtual void DrawBaseWheels(HPEN Pen) = 0;		// �������� �������� ������
	virtual int GetTypeId() = 0; // ID ������
	int GetMaxSpeed() { return Speed; };				// �������� ������� ��������
	void SetSpeed(int NewSpeed) { Speed = NewSpeed; };	// ���������� ����� ��������
	int GetBaseLenght() { return BodyCarLenght; };		// �������� ����� �������
	void SetBaseLenght(int NewBaseLenght) { BodyCarLenght = NewBaseLenght; };
	
	virtual bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength) = 0;
	virtual void Drag(int Step, int CollisionX[], int CollisionY[], int CollisionX_Board[], int CollisionY_Board[],
		int& CollisionCode, const int Max_CollisionNubmer) override;						// ������������ ������ �� ��������
	virtual void MoveTo(int NewX, int NewY) override;	// ����������� ������ �� ����� �����������
	virtual void Show() override;				// �������� ������� ����������
	virtual void Hide() override;				// ������� ������� ����������
};

/*-----------------------  ����� Car  -------------------------------*/
class Car : public Base {
private:	
	int id = 1;							// id ������

public:
	Car(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor);
	virtual void Show() override;				// �������� ������ ������
	virtual void Hide() override;				// ������ ������ ������
	void DrawCarCabin(HPEN Pen);		// ���������� ������ � ����� ��������� �����
	bool Touch(int AnotherXCarCoord, int AnotherYCarCoord, int CarLenght, int CarHeight, int AnotherXBrickCoord, int AnotherYBrickCoord, int BrickLength) override;		// ��������� ��������� ��������� ������� � �������
	void DrawBaseBody(HPEN Pen) override;		// �������� �������� ������ ������ �� ������� ������� ������
	virtual void DrawBaseWheels(HPEN Pen) override;		// �������� �������� ������
	virtual int GetTypeId() override {
		return id;
	}
};

class CarWithHood : public Car {		// ������ � �������
private:
	int id = 2;							// id ������

public:
	CarWithHood(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // �� ��������� ��������� ������������
	virtual void Show() override;				// �������� ������ ������ � �������
	virtual void Hide() override;				// ������ ������ ������ � �������
	void DrawCarHood(HPEN Pen);			// ���������� ����� ��������� �����
	int GetTypeId() {
		return id;
	}
};

class CarWithLuggade : public Car { // ������ � ����������
private:
	int id = 3;							// id ������

public: 
	CarWithLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor);
	virtual void Show() override;				// �������� ������ ������ � �������
	virtual void Hide() override;				// ������ ������ ������ � �������
	void DrawCarLuggade(HPEN Pen);		// ���������� �������� ��������� �����
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithHoodAndLuggade : public CarWithHood {		// ������ � �������
private:
	int id = 4;							// id ������
public:
	CarWithHoodAndLuggade(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // �� ��������� ��������� ������������
	virtual void Show() override;				// �������� ������ ������ � �������
	virtual void Hide() override;				// ������ ������ ������ � �������
	//void DrawCarHood(HPEN Pen);			// ���������� ����� ��������� �����
	void DrawCarLuggade(HPEN Pen);		// ���������� �������� ��������� �����
	virtual int GetTypeId() {
		return id;
	}
};

class CarExhaustPipe : public CarWithHood {
private:
	int id = 5;							// id ������
public:
	CarExhaustPipe(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // �� ��������� ��������� ������������

	virtual void Show();				// �������� ������  
	virtual void Hide();				// ������ ������ 
	void DrawExhaustPipe(HPEN Pen);		// ��������� ����� ��������� �����
	virtual int GetTypeId() {
		return id;
	}
};

class CarWithBattery : public CarWithHood {
private:
	int id = 6;							// id ������
public:
	CarWithBattery(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, COLORREF InitColor); // �� ��������� ��������� ������������

	virtual void Show();				// �������� ������  
	virtual void Hide();				// ������ ������ 
	void DrawBattery(HPEN Pen);		// ��������� ����� ��������� �����
	virtual int GetTypeId() {
		return id;
	}
};

