#pragma once
#include "ModelingCar.h"

class CarExhaustPipe : public CarWithHood {
private:
	int id = 4;							// id класса
	int EmissionsLevel;			// Уровень выбросов
public:
	CarExhaustPipe(int InitX, int InitY, int InitBodyCarLenght, int InitSpeed, std::string InitBaseColor = "red"); // по умолчанию параметры конструктора

	virtual void Show();				// показать фигуру  
	virtual void Hide();				// скрыть фигуру 
    void DrawExhaustPipe(HPEN Pen);		// выхлопная труба заданного цвета
	virtual int GetTypeId() {
		return id;
	}
};

