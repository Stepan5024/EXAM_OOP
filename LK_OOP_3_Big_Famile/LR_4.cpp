/*******************************************************************\
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. НАСЛЕДОВАНИЕ        *
 *				   РИСОВАНИЕ МАШИНЫ							    	*
 *                 ПЕРЕМЕЩЕНИЕ  МАШИНЫ                              *
 *                                                                  *
 \******************************************************************/

#pragma once                  
#include <windows.h>
#include <conio.h>
#include <iostream>    
using namespace std;

#include "ModelingCar.h" 	// объявление классов
#include "GetConWin.h"		// указатель на консольное окно


//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

using namespace std;        // Пространство имен std

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

HDC hdc;	// Объявим контекст устройства
			// Контекст устройства по сути это структура,
			// содержащая описание видеокарты на вашем компьютере
			// и всех необходимых графических элементов

/*---------------------------------------------------------------------*/
/*               П Р О Т О Т И П Ы    Ф У Н К Ц И Й                    */
/*---------------------------------------------------------------------*/

/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/

bool KEY[256];
void GetKEY()
{
	int i = 0;
	while (i < 256)
	{
		if (GetAsyncKeyState(i)) KEY[i] = 1; else KEY[i] = 0;
		i++;
	}
}
//для удобства ввода
void PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			break;
}//PressKey()

bool ErrorCode = false;


int main()
{
	// когда целесообразно использовать веерную иерархию
	// существенные изменения в структуре объекта, простое вертикальное наследование не позволит ...
	// целесообразно когда оптимально мы экономим код и память, Оптимально ли мы выполнили это 
	// одновременно меняется несколько вариантов эволюции объектов. На базе одного идет эволюция нескольких объектов
	// берем свойства предка и изменения разные. Не одно изменение а несколько разных изменений от одного объекта.
	// Наследник имеет некоторое изменение и требуется несколько наследников и несколько способов их 
	//system("color F0");
	setlocale(LC_ALL, "Russian");

	HWND hwnd = GetConcolWindow();//получим дескриптор консольного окна

	if (hwnd != NULL) //если дескриптор существует
	{
		//получим контекст устройства для консольного окна
		hdc = GetWindowDC(hwnd);
		//если контекст существует - можем работать
		if (hdc != 0)
		{
			
			
			const int Max_CarsNumber = 5;
			const int Max_CollisionNumber = 3;

			int X0_Barrier = 960;
			int Y0_Barrier = 550;

			Barriers* matrixBarriers[3] = {
				// матрица переходов для смены 
							  { new Canister(X0_Barrier, Y0_Barrier, 50, 50, RGB(0, 227, 0)) },
							  { new Brick(050, 350, 80, 40, RGB(255, 227, 135)) } ,
							  { new Lightning(800, 600, 90, 90, RGB(255, 227, 0)) }
			};
			//массив координат объектов для коллизии
			int CollisionX[Max_CollisionNumber] = { matrixBarriers[0]->GetX(), matrixBarriers[1]->GetX(),
				matrixBarriers[2]->GetX()}; // правая нижняя координата препятствия
			int CollisionY[Max_CollisionNumber] = { matrixBarriers[0]->GetY(), matrixBarriers[1]->GetY(),
				matrixBarriers[2]->GetY()}; // левая нижняя координата препятствия

			// левая верхняя координата препятствия
			int CollisionX_Board[Max_CollisionNumber] = { CollisionX[0] - matrixBarriers[0]->GetLength(),
														  CollisionX[1] - matrixBarriers[1]->GetLength() * 2,
														  CollisionX[2] - matrixBarriers[2]->GetLength()};
			// правая верхняя координата препятствия
			int CollisionY_Board[Max_CollisionNumber] = { CollisionY[0] - matrixBarriers[0]->GetLength(),
														  CollisionY[1] - matrixBarriers[1]->GetLength() * 2,
														  CollisionY[2] - matrixBarriers[2]->GetLength()};


			//массив переходов 
			int CollisionStates[Max_CollisionNumber][Max_CarsNumber] = { {5, 5, 5, 5, 2, },
																		 {3, 3, 3, 3, 3, },
																		 {-1, -1, -1, -1, -1} };

			Car* BufCars[Max_CarsNumber];
			Barriers* BufCollision[Max_CollisionNumber];

			
			int Choose = 0;			// вариант 
			int DragChoose = 0;
			int CollisionChoose = 0;
			int i = 0;
			int CollisionCode = 0;
			int NewCollisionState = 0;

			int x0 = 950;
			int y0 = 250;
			int add_x0 = x0;
			int add_y0 = y0;

			Car* matrixCar[5] = {
				// матрица переходов для смены 
							  { new Car(x0, y0, 300, 50, RGB(255, 0, 0)) },
							  { new CarWithHood(x0, y0, 300, 50, RGB(255, 0, 0)) },
							  { new CarWithLuggade(650, 250, 300, 50, RGB(0, 0, 0))},
							  { new CarWithHoodAndLuggade(650, 250, 300, 50, RGB(0, 0, 0))},
							{ new CarExhaustPipe(add_x0, add_y0, 300, 50, RGB(255, 0, 0)) } 
			};

			//задаём массив состояний фигуры равной кол-ву Max_CarsNumber
			/************	 М А Ш И Н А	 ***********/
			Car ACar(x0, y0, 300, 50, RGB(255, 0, 0));
			/************	 М А Ш И Н А  С  К А П О Т О М ************/
			CarWithHood ACarWithHood(x0, y0, 300, 50, RGB(255, 0, 0));
			/************	 М А Ш И Н А  С   Б А Г А Ж Н И К О М	 ***********/
			CarWithLuggade ACarWithLuggade(x0, y0, 300, 50, RGB(255, 0, 0));
			/************	 М А Ш И Н А  С  К А П О Т О М   И   Б А Г А Ж Н И К О М	 ***********/
			CarWithHoodAndLuggade ACarWithHoodAndLuggade(650, 250, 300, 50, RGB(0, 0, 0));
			/************	 М А Ш И Н А  С   К А П О Т О М	  И  В Ы Х Л О П Н О Й   Т Р У Б О Й	***********/
			CarExhaustPipe ACarExhaustPipe(add_x0, add_y0, 300, 50, RGB(255, 0, 0));

			BufCars[ACar.GetTypeId() - 1] = &ACar;
			BufCars[ACarWithHood.GetTypeId() - 1] = &ACarWithHood;
			BufCars[ACarWithLuggade.GetTypeId() - 1] = &ACarWithLuggade;
			BufCars[ACarWithHoodAndLuggade.GetTypeId() - 1] = &ACarWithHoodAndLuggade;
			BufCars[ACarExhaustPipe.GetTypeId() - 1] = &ACarExhaustPipe;
			
			Car* indCar;
			Barriers* indBarriers;

			indCar = BufCars[0];


			//задаём массив объектов коллизии
			Canister ACanister(CollisionX[0], CollisionY[0], 50, 50, RGB(0, 227, 0));
			Brick ABrick(CollisionX[1], CollisionY[1], 80, 40, RGB(255, 227, 135));
			Lightning ALightning(CollisionX[2], CollisionY[2], 90, 90, RGB(255, 227, 0));

			BufCollision[ACanister.GetTypeId() - 1] = &ACanister;
			BufCollision[ABrick.GetTypeId() - 1] = &ABrick;
			BufCollision[ALightning.GetTypeId() - 1] = &ALightning;
			
			indBarriers = BufCollision[0];


			/*
			IDraw* pIDraw;
			/************	 М А Ш И Н А  С   К А П О Т О М	 ***********/
			//CarWithHood ACarWithHood(950, 350, 300, 50, "red");
			//cout << "ID Car With Hood = " << ACarWithHood.GetTypeId() << endl;
			/*pIDraw = &ACarWithHood;
			pIDraw->Show();
			*/
			
			int step = 50;
			GetKEY();
			cout << "\nНажмите Enter, чтобы начать";
			while (!KEY_DOWN(VK_ESCAPE)) //Конец работы "Esc"
			{

				PressKey(0x0D); // enter

				ErrorCode = false;

				//очистка буфера
				cin.clear();
				while (cin.get() != '\n')
				{
					continue;
				}
				while (1) {
					cout << "Введите номер класса (состояния) автомобиля (от 1 до 5): ";
					cin >> Choose;
					cout << endl;

					if (Choose > 5 or Choose < 1) {
						cout << "Неправильный номер класса автомобиля!" << endl;
						ErrorCode = true;
						
					} else break;
				}
				indCar = BufCars[Choose - 1];

				cout << "Нажмите S, чтобы отобразить элементы";
				PressKey(0x53); // клавиша S
				indCar->Show();
				for (i = 0; i < Max_CollisionNumber; i++) {

					indBarriers = BufCollision[i];
					indBarriers->Show();

				}//for()

				while (1) {
					if (KEY_DOWN(VK_ESCAPE)) break; // escape

					
					cin.clear(); //очистка буфера
					

					//cout << "\nВыберите, какой объект вы собираетесь перетащить:" << endl;
					//cout << "1. Машину";
					//cout << "\n2. Объект коллизии" << endl;
					//cout << "Введите вариант 1 или 2: ";
					//cin >> DragChoose;
					DragChoose = 1;

					if (DragChoose == 1) {


					/***************************************************/
					/*				  РАБОТА С КОЛЛИЗИЯМИ			   */
					/**************************************************/

						cout << "\nНажмите D, чтобы двигать объект";
						PressKey(68);
						indCar->Drag(step, CollisionX, CollisionY, CollisionX_Board, CollisionY_Board, CollisionCode, Max_CollisionNumber);
						Sleep(500);

						cout << "Номер класса для взаимодействия " << Choose << " - " << " Код коллизии " << CollisionCode << endl;

						if (CollisionCode > 0) {
							NewCollisionState = CollisionStates[CollisionCode - 1][Choose - 1];
						}

						cout << "Новое коллизионное состояние " << NewCollisionState << endl;

						if (NewCollisionState > 0) {

							add_x0 = indCar->GetX();
							add_y0 = indCar->GetY();

							indBarriers = BufCollision[CollisionCode - 1];
							indBarriers->Hide();
							indCar = BufCars[NewCollisionState - 1];

							CollisionX[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionY[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionX_Board[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionY_Board[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран

							indCar->SetX(add_x0);
							indCar->SetY(add_y0);
							indCar->Show();
						}

					}
					

					/*if (DragChoose == 2) {
						//очистка буфера
						cin.clear();
						while (cin.get() != '\n')
						{
							continue;
						}

						cout << "\nВыберите, какой объект столкновения вы собираетесь перетащить (от 1 до 2): ";

						cin >> CollisionChoose;
						if (CollisionChoose > 0 and CollisionChoose < 7) {
							indBarriers = BufCollision[CollisionChoose - 1];
						}
						else break;

						cout << "\nНажмите D, чтобы двигать объект";
						PressKey(68); // D

						HBRUSH hBrush = CreateSolidBrush(RGB(255, 53, 255));
						SelectObject(hdc, hBrush);		//делаем кисть активной

						indBarriers->Drag(step);
						Sleep(500);

						cout << "Номер класса для взаимодействия " << Choose << " - " << " Код коллизии " << CollisionCode << endl;

						if (CollisionCode > 0) {
							NewCollisionState = CollisionStates[CollisionCode - 1][Choose - 1];
						}

						cout << "Новое коллизионное состояние " << NewCollisionState << endl;

						if (NewCollisionState > 0) {

							add_x0 = indCar->GetX();
							add_y0 = indCar->GetY();

							indBarriers = BufCollision[CollisionCode - 1];
							indBarriers->Hide();
							indCar->Hide();

							indCar = BufCars[NewCollisionState - 1];

							CollisionX[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionY[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionX_Board[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран
							CollisionY_Board[CollisionCode - 1] = -100; // убираем взаимодействующие объекты за экран

							indCar->SetX(add_x0);
							indCar->SetY(add_y0);
							indCar->Show();
						}
					}*/
				}
			}
			delete indBarriers;
			delete indCar;
			
		}
	}
}