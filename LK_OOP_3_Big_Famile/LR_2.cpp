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
#include "CarExhaustPipe.h"

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
			
			/************  Б А З О В Ы Й   К Л А С С  ***********/
			//Base ABase(990, 200, 300, 40, "black");
			//ABase.Show();
			/************	 М А Ш И Н А	 ***********/
			//Car  ACar(950, 400, 300, 50, "red");  // инициализация машины
			//ACar.Show();			// показать машину
			
			//ACarWithHood.Show();

			/************	 М А Ш И Н А  С   Б А Г А Ж Н И К О М	 ***********/
			//CarWithLuggade ACarWithLuggade(950, 590, 300, 50, "black");
			//ACarWithLuggade.Show();
			/************	 М А Ш И Н А  С  К А П О Т О М   И   Б А Г А Ж Н И К О М	 ***********/
			//CarWithHoodAndLuggade ACarWithHoodAndLuggade(650, 250, 300, 50, "gren");
			//ACarWithHoodAndLuggade.Show();
			/************	 К И Р П И Ч	 ***********/
			//Brick ABrick(625, 550, 80, 30);
			//ABrick.Show();
			/************	 М А Ш И Н А  С   К А П О Т О М	  И  В Ы Х Л О П Н О Й   Т Р У Б О Й	***********/
			//CarExhaustPipe ACarExhaustPipe(550, 550, 500, 50, "red");
			//ACarExhaustPipe.Show();
			//ACarExhaustPipe.Drag();
			const int Max_CarsNumber = 5;
			const int Max_CollisionNumber = 3;
			Barriers* matrixBarriers[3] = {
				// матрица переходов для смены 
							  { new Canister(435, 550, 50, 50, RGB(0, 227, 0)) },
							  { new Brick(435, 350, 80, 40, RGB(255, 227, 135)) } ,
							  { new Lightning(500, 600, 90, 90, RGB(255, 227, 0)) }
			};
			//массив координат объектов для коллизии
			int CollisionX[Max_CollisionNumber] = { matrixBarriers[0]->GetX(), matrixBarriers[1]->GetX(),
				matrixBarriers[2]->GetX()};
			int CollisionY[Max_CollisionNumber] = { matrixBarriers[0]->GetY(), matrixBarriers[1]->GetY(),
				matrixBarriers[2]->GetY()};

			int CollisionX_Board[Max_CollisionNumber] = { CollisionX[0] + matrixBarriers[0]->GetLength(),
														  CollisionX[1] + matrixBarriers[1]->GetLength() * 2,
														  CollisionX[2] + matrixBarriers[2]->GetLength()};
			int CollisionY_Board[Max_CollisionNumber] = { CollisionY[0] + matrixBarriers[0]->GetLength(),
														  CollisionY[1] + matrixBarriers[1]->GetLength() * 2,
														  CollisionY[2] + matrixBarriers[2]->GetLength()};


			//массив переходов 
			int CollisionStates[Max_CollisionNumber][Max_CarsNumber] = { {-1, 5, 5, 5, 2, },
																		 {-1, 3, 3, 3, 3, },
																		 {-1, -1, -1, -1, -1} };

			Car* BufCars[Max_CarsNumber];
			Barriers* BufCollision[Max_CollisionNumber];

			



			int Choose = 0;			// вариант 
			int DragChoose = 0;
			int CollisionChoose = 0;
			int i = 0;
			int CollisionCode = 0;
			int NewCollisionState = 0;

			int x0 = 350;
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
			/*indBarriers = matrixBarriers[0];
			indBarriers->Show();
			indBarriers = matrixBarriers[1];
			indBarriers->Show();
			indBarriers = matrixBarriers[2];
			indBarriers->Show();*/

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // цвет тела - кирпичный; //создаём объект-кисть
			/*SelectObject(hdc, hBrush);		//делаем кисть активной

			hBrush = CreateSolidBrush(RGB(255, 255, 255)); // цвет тела - кирпичный; //создаём объект-кисть
			SelectObject(hdc, hBrush);		//делаем кисть активной

			*/
			

			//indCar = matrixCar[2];
			//indCar->Show();
			int step = 20;
			while (1)
			{
				if (KEY_DOWN(49)) {      // нажимаем 1
					
					indCar->Hide();
					indCar = new Car(add_x0, add_y0, 300, 50, RGB(255, 0, 0));
					indCar->Show();
				}
				if (KEY_DOWN(50)) {     // нажимаем 2
					
					indCar->Hide();
					indCar = new CarExhaustPipe(add_x0, add_y0, 300, 50, RGB(255, 0, 0));
					indCar->Show();
				}

				if (KEY_DOWN(37)) {   // нажимаем стрелку влево
					add_x0 -= step;
					indCar->MoveTo(add_x0, add_y0);

				}

				if (KEY_DOWN(38)) {   // нажимаем стрелку вверх
					add_y0 -= step;
					indCar->MoveTo(add_x0, add_y0);
				}

				if (KEY_DOWN(39)) {   // нажимаем стрелку вправо
					add_x0 += step;
					indCar->MoveTo(add_x0, add_y0);
				}
				if (KEY_DOWN(40)) {   // нажимаем стрелку вниз
					add_y0 += step;
					indCar->MoveTo(add_x0, add_y0);

				}

				if (KEY_DOWN(82)) {     // нажимаем клавишу R для возвращения в исходную точку
					indCar->Hide();
					indCar = new Car(x0, y0, 300, 50, RGB(255, 0, 0));
					indCar->Show();
				}
				if (KEY_DOWN(83)) { // клавиша s
					cout << " к. х car = " << indCar->GetX() << " к. у car = " << indCar->GetY() << " car len = " << indCar->GetBaseLenght() << endl;
					cout << " id barriers = " << indBarriers->GetTypeId() << " к. x кирпич = " << indBarriers->GetX() << " к. у кирпич = " << indBarriers->GetY() << endl;

				}
				
				if (indCar->Touch(indCar->GetX(), indCar->GetY(), indCar->GetBaseLenght(), 150, indBarriers->GetX(), indBarriers->GetY(), indBarriers->GetLength())) { // при прикосновении кирпича к машине
					cout << "Врезался" << endl;
					indCar->Hide(); // указатель на текущую машину вызывает метод скрыть текущую машину
					indBarriers->Hide(); // указатель на текущее препятствие вызывает метод скрыть текущую помеху

					hBrush = CreateSolidBrush(RGB(255, 255, 255)); // цвет тела - кирпичный; //создаём объект-кисть
					SelectObject(hdc, hBrush);		//делаем кисть активной
					if (indBarriers->GetTypeId() == 0) { // кирпич
						// меняется указатель через повышение индекса в массиве машины и помехи
						indCar = matrixCar[0];
						indBarriers = matrixBarriers[0]; // меняем на взаимодействие с канистрой
						
					}
					else if (indBarriers->GetTypeId() == 1) { // канистра
						indCar = matrixCar[1];
						indBarriers = matrixBarriers[1]; // меняем на взаимодействие с кирпичом
					}
					indCar->Show();
					indBarriers->Show();

					hBrush = CreateSolidBrush(RGB(255, 255, 255)); // цвет тела - кирпичный; //создаём объект-кисть
					SelectObject(hdc, hBrush);		//делаем кисть активной

					add_x0 = x0;
					add_y0 = y0;
					
				}
				if (KEY_DOWN(VK_ESCAPE))//Конец работы "Esc"
					break;

				Sleep(100);
			}
			

			delete indBarriers;
			delete indCar;
			
			
		}
	}
}