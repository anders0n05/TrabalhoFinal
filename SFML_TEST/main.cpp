#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "Deque.h"

using namespace std;

//ESTRUTURA PRINCIPAL DA SCHEDULE.

struct Schedule
{

	string name;
	string number;
};

//FUNÇÂO RESPONSAVEL POR DAR O SPLIT DA LINHA QUE SERÁ RECEBIDA NO ARQUIVO, FONTE DE ONDE FOI RETIRDA A FUNÇÃO -->https://social.msdn.microsoft.com/Forums/pt-BR/57ab4ab9-485e-4d6b-90f3-2365b95d2919/existe-alguma-funo-no-c-equivalente-ao-split?forum=vscmaismaispt 
void StringSplit(string str, string delim, vector<string>& results)
{
	int cutAt;
	while ((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if (cutAt > 0) {
			results.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0) {
		results.push_back(str);
	}
}

int main()
{

	TDQueue<Schedule> test;
	inicialize_Dqueue(test);

	Schedule data;

	string name = "", number = "", name_chat = "", number_chat = ""; //Strings responsaveis por receberem as entradas que irão ser adicionadas na schedule.
	int position = 0; //Pega a posição da listbox ja janela 04.
	int index = 0; //Variavel responsavel pelo controle das ações das janelas.
	int index_text = 0; //Variavel responsavel pelo controle das chatbox para coletar o name e number da agenda.
	int fator_pagina = 0; //Variavel responsavel pelo controle da paginação da listbox, e controle do remove.

	//WINDOW --> GERAL
	sf::RenderWindow window(sf::VideoMode(400, 600), "MENU SCHEDULE");
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(400, 600));
	background.setFillColor(sf::Color(211, 211, 211));

	//CHATBOX --> WINDOW 3
	sf::RectangleShape Chatbox;
	Chatbox.setSize(sf::Vector2f(380, 50));
	Chatbox.setFillColor(sf::Color::White);
	Chatbox.setOutlineThickness(1);
	Chatbox.setOutlineColor(sf::Color::Black);

	//LISTBOX --> WINDOW 4
	sf::RectangleShape listbox;
	listbox.setSize(sf::Vector2f(390, 201));
	listbox.setFillColor(sf::Color::White);
	listbox.setOutlineColor(sf::Color::Black);
	listbox.setOutlineThickness(1);
	listbox.setPosition(sf::Vector2f(5, 5));

	//SELECT_LISTBOX --> WINDOW 4
	sf::RectangleShape Select_listbox;
	Select_listbox.setSize(sf::Vector2f(388, 19.8));
	Select_listbox.setFillColor(sf::Color(30, 144, 255));

	//BUTTON --> GERAL
	sf::RectangleShape Button;
	Button.setSize(sf::Vector2f(390, 125));
	Button.setFillColor(sf::Color(192, 192, 192));
	Button.setOutlineColor(sf::Color::Black);
	Button.setOutlineThickness(1);

	//BUTTON (WINDOW 4) --> WINDOW 4
	sf::RectangleShape Buttonwindow4;
	Buttonwindow4.setSize(sf::Vector2f(390, 107));
	Buttonwindow4.setFillColor(sf::Color(192, 192, 192));
	Buttonwindow4.setOutlineColor(sf::Color::Black);
	Buttonwindow4.setOutlineThickness(1);

	//BUTTON PAGE --> WINDOW 4
	sf::RectangleShape Buttonpage;
	Buttonpage.setSize(sf::Vector2f(190, 20));
	Buttonpage.setFillColor(sf::Color(192, 192, 192));
	Buttonpage.setOutlineColor(sf::Color::Black);
	Buttonpage.setOutlineThickness(1);

	//CARRY FONT --> arial.ttf
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {

		cout << "ERRO AO CARREGAR A FONTE" << endl;
	}

	//LABEL --> GERAL
	sf::Text Label;
	Label.setFont(font);
	Label.setFillColor(sf::Color::Black);

	//LABEL LISTBOX --> GERAL
	sf::Text LabelLIST;
	LabelLIST.setFont(font);
	LabelLIST.setFillColor(sf::Color::Black);
	LabelLIST.setCharacterSize(15);

	//LABEL --> CHATBOX
	sf::Text Chat_text;
	Chat_text.setFont(font);
	Chat_text.setFillColor(sf::Color::Black);
	Chat_text.setCharacterSize(20);

	//LABEL_EMPTY --> WINDOW 4
	sf::Text label_empty;
	label_empty.setFont(font);
	label_empty.setString("NÃO POSSUI CONTATOS NA AGENDA");
	label_empty.setFillColor(sf::Color::Black);
	label_empty.setCharacterSize(20);
	label_empty.setPosition(sf::Vector2f(16, 90));

	//Carregar imagem da seta para cima -->
	sf::Texture Seta_cima;
	if (!Seta_cima.loadFromFile("Seta_cima.png")) {

		cout << "ERRO AO CARREGAR IMAGEM DA SETA PARA CIMA" << endl;
	}

	//Carregar imagem do asterik -->
	sf::Texture asterisk;
	if (!asterisk.loadFromFile("icons8-erro-64.png")) {

		cout << "ERRO AO CARREGAR IMAGEM DO ASTERISCO" << endl;
	}

	//Criação do sprite do asterisk -->
	sf::Sprite asterisco;
	asterisco.setTexture(asterisk);
	asterisco.setScale(sf::Vector2f(0.6, 0.6));


	//Criação do sprite da seta para cima -->
	sf::Sprite seta_cima;
	seta_cima.setTexture(Seta_cima);
	seta_cima.setPosition(sf::Vector2f(92, 217));

	//Carregar imagem da seta para baixo -->
	sf::Texture Seta_baixo;
	if (!Seta_baixo.loadFromFile("Seta_baixo.png")) {

		cout << "ERRO AO CARREGAR IMAGEM DA SETA PARA BAIXO" << endl;
	}

	//Criação do sprite da seta para cima -->
	sf::Sprite seta_baixo;
	seta_baixo.setTexture(Seta_baixo);
	seta_baixo.setPosition(sf::Vector2f(292, 217));

	//Carregar imagem de logo --> SCHEDULE
	sf::Texture image;
	if (!image.loadFromFile("test_image.png")) {

		cout << "ERRO AO CARREGAR IMAGEM DA SCHEDULE DE LOGO" << endl;
	}

	//Criação do sprite da logo -->
	sf::Sprite sprite;
	sprite.setTexture(image);
	sprite.setPosition(sf::Vector2f(-50, -80));

	//Carregar arquivo txt da schedule -->
	ifstream file("Schedule.txt");
	if (!file) {

		cout << "ERRO AO CARREGAR O ARQUIVO .txt" << endl;
	}

	string line_all;
	vector<string> line_split;
	int k = 0;
	//Traz o arquivo para a estrutura.
	while (!file.eof())
	{

		getline(file, line_all); //Pega a primeira linha do arquivo e adiciona na string line_all.

		if (line_all == "," || line_all == "") { //Tanto vazio como virgula sozinhos são ignorados.

		}
		else {

			StringSplit(line_all, ",", line_split); //Cada virgula ele splita a string line all em duas ques respectivamente são nome e numero.
			data.name = line_split[k];
			k++;
			data.number = line_split[k];
			k++;
			insert_begin(test, data);
			cout << test.begin->data.name << " e " << test.begin->data.number << endl;
		}
	}

	file.close();

	window.clear();
	window.draw(background);
	window.draw(sprite);
	Button.setPosition(sf::Vector2f(5, 330));
	window.draw(Button);
	Button.setPosition(sf::Vector2f(5, 470));
	window.draw(Button);
	Label.setString("SCHEDULE");
	Label.setPosition(sf::Vector2f(125, 370));
	window.draw(Label);
	Label.setString("EXIT");
	Label.setPosition(sf::Vector2f(170, 515));
	window.draw(Label);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed) {

				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {

				//Ação da janela 01 --> SCHEDULE.
				if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x >= 5 &&
					event.mouseButton.x <= 395 && event.mouseButton.y >= 330 && event.mouseButton.y <= 455 && index == 0) {

					index = 1;
					window.setTitle("SCHEDULE OPTIONS");
					window.clear();
					window.draw(background);
					Button.setPosition(sf::Vector2f(5, 10));
					window.draw(Button);
					Label.setString("ADD CONTACT");
					Label.setPosition(sf::Vector2f(100, 50));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 150));
					window.draw(Button);
					Label.setString("LIST SCHEDULE");
					Label.setPosition(sf::Vector2f(90, 195));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 290));
					window.draw(Button);
					Label.setString("EXIT");
					Label.setPosition(sf::Vector2f(170, 335));
					window.draw(Label);
					window.display();

				}
				//Ação da janela 01 --> EXIT.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 470 &&
					event.mouseButton.y <= 595 && index == 0 && event.mouseButton.button == sf::Mouse::Left) {

					exit(1);
				}
				//Ação da janela 02 --> SAVE/EXIT.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 290 &&
					event.mouseButton.y <= 415 && index == 1 && event.mouseButton.button == sf::Mouse::Left) {

					if (test.begin == NULL && test.last == NULL) {

						remove("schedule.txt"); //Deleta o arquivo schedule.txt da pasta SFML_TEST.
						ofstream file_write;
						file_write.open("schedule.txt", ios::out); //Cria um arquivo .txt vazio com abertura apenas para escrita chamado schedule.txt.
						file_write.close();
						exit(1);
					}
					else
					{

						remove("schedule.txt"); //Deleta o arquivo schedule.txt da pasta SFML_TEST.
						ofstream file_write;
						file_write.open("schedule.txt", ios::out); //Cria um arquivo .txt vazio com abertura apenas para escrita chamado schedule.txt.
						string glory;
						TDQueue<Schedule> aux = test;

						//For responsavel por escrever no formato toda a estrutura para o arquivo.
						for (int t = 0; t < amount(test); t++) {

							glory += aux.begin->data.name + "," + aux.begin->data.number + "\n";
							aux.begin = aux.begin->next;
						}


						file_write << glory;

						file_write.close();

						exit(1);
					}

				}
				//Ação da janela 02 --> LIST.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 150 &&
					event.mouseButton.y <= 275 && index == 1 && event.mouseButton.button == sf::Mouse::Left) {

					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					//PRINT DA ESTRUTURA VAZIA.
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						//PRINT DA ESTRUTURA.
						TDQueue<Schedule> aux = test;
						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;
							}
						}
					}

					window.display();
				}
				//Ação da janela 02 --> ADD CONTACT.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 5 &&
					event.mouseButton.y <= 130 && index == 1 && event.mouseButton.button == sf::Mouse::Left) {

					index = 2;
					window.clear();
					window.setTitle("REGISTER SCHEDULE");
					window.draw(background);
					Label.setString("REGISTER");
					Label.setPosition(sf::Vector2f(120, 10));
					window.draw(Label);
					Label.setString("NAME: ");
					Label.setPosition(sf::Vector2f(10, 100));
					window.draw(Label);
					Chatbox.setPosition(sf::Vector2f(10, 140));
					window.draw(Chatbox);
					Label.setString("NUMBER: ");
					Label.setPosition(sf::Vector2f(10, 220));
					window.draw(Label);
					Chatbox.setPosition(sf::Vector2f(10, 260));
					window.draw(Chatbox);
					Button.setPosition(sf::Vector2f(5, 330));
					window.draw(Button);
					Button.setPosition(sf::Vector2f(5, 470));
					window.draw(Button);
					Label.setString("ADD");
					Label.setPosition(sf::Vector2f(165, 370));
					window.draw(Label);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 515));
					window.draw(Label);
					window.display();

				}
				//Ação da janela 03 --> SETA O TEXTO NA CHATBOX DO NOME. 
				else if (event.mouseButton.x >= 10 && event.mouseButton.x <= 390 && event.mouseButton.y >= 140 &&
					event.mouseButton.y <= 190 && index == 2 && event.mouseButton.button == sf::Mouse::Left) {

					index_text = 0;
					name = "";

				}
				//Ação da janela 03 --> SETA O TEXTO NA CHATBOX DO NUMERO.
				else if (event.mouseButton.x >= 10 && event.mouseButton.x <= 390 && event.mouseButton.y >= 260 &&
					event.mouseButton.y <= 310 && index == 2 && event.mouseButton.button == sf::Mouse::Left) {

					index_text = 1;
					number = "";
				}
				//Ação da janela 03 --> ADD.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 330 &&
					event.mouseButton.y <= 455 && index == 2 && event.mouseButton.button == sf::Mouse::Left) {

					if (name == "" && number == "") { //Se nenhum campo estiver preenchido, retorna para a página de ADD.

						index = 2; //Fator da pagina ADD.
						index_text = 0; //Fator do campo name.
						window.clear();
						window.setTitle("REGISTER SCHEDULE");
						window.draw(background);
						Label.setString("REGISTER");
						Label.setPosition(sf::Vector2f(120, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						asterisco.setPosition(sf::Vector2f(350, 145));
						window.draw(asterisco); //Image do campo não preenchido.
						asterisco.setPosition(sf::Vector2f(350, 265));
						window.draw(asterisco); //Image do campo não preechido.
						window.display();
					}

					else if (name == "") { //Se o campo nome não estiver preencido, retorna a pagina ADD

						index = 2; //Fator da pagina ADD.
						window.clear();
						window.setTitle("REGISTER SCHEDULE");
						window.draw(background);
						Label.setString("REGISTER");
						Label.setPosition(sf::Vector2f(120, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						asterisco.setPosition(sf::Vector2f(350, 145));
						window.draw(asterisco); //Image do campo não preechido.
						window.display();
					}
					else if (number == "") { //Se o campo number não estiver preenchido, retorna a pagina ADD

						index = 2;
						window.clear();
						window.setTitle("REGISTER SCHEDULE");
						window.draw(background);
						Label.setString("REGISTER");
						Label.setPosition(sf::Vector2f(120, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						asterisco.setPosition(sf::Vector2f(350, 265));
						window.draw(asterisco);
						window.display();
					}
					else {

						data.name = name;
						data.number = number;
						insert_begin(test, data);

						name = "";
						number = "";
						index_text = 0;
						index = 1;
						window.setTitle("SCHEDULE OPTIONS");
						window.clear();
						window.draw(background);
						Button.setPosition(sf::Vector2f(5, 10));
						window.draw(Button);
						Label.setString("ADD CONTACT");
						Label.setPosition(sf::Vector2f(100, 50));
						window.draw(Label);
						Button.setPosition(sf::Vector2f(5, 150));
						window.draw(Button);
						Label.setString("LIST SCHEDULE");
						Label.setPosition(sf::Vector2f(90, 195));
						window.draw(Label);
						Button.setPosition(sf::Vector2f(5, 290));
						window.draw(Button);
						Label.setString("EXIT");
						Label.setPosition(sf::Vector2f(170, 335));
						window.draw(Label);
						window.display();
					}
				}
				//Ação da janela 03 --> BACK.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 470 &&
					event.mouseButton.y <= 595 && index == 2 && event.mouseButton.button == sf::Mouse::Left) {

					index = 1;
					name = "";
					number = "";
					window.setTitle("SCHEDULE OPTIONS");
					window.clear();
					window.draw(background);
					Button.setPosition(sf::Vector2f(5, 10));
					window.draw(Button);
					Label.setString("ADD CONTACT");
					Label.setPosition(sf::Vector2f(100, 50));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 150));
					window.draw(Button);
					Label.setString("LIST SCHEDULE");
					Label.setPosition(sf::Vector2f(90, 195));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 290));
					window.draw(Button);
					Label.setString("EXIT");
					Label.setPosition(sf::Vector2f(170, 335));
					window.draw(Label);
					window.display();
				}
				//Ação da janela 04 --> CHANGE.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 195 && event.mouseButton.y >= 365 &&
					event.mouseButton.y <= 472 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					if ((position + fator_pagina) > amount(test) || position == 0) {

						index = 3;
						if (amount(test) == 10) {

							fator_pagina = 0;
						}

						position = 0;
						window.clear();
						window.setTitle("LIST SCHEDULE");
						window.draw(background);
						window.draw(listbox);
						Buttonpage.setPosition(sf::Vector2f(5, 215));
						window.draw(Buttonpage);
						window.draw(seta_cima);
						Buttonpage.setPosition(sf::Vector2f(205, 215));
						window.draw(Buttonpage);
						window.draw(seta_baixo);
						Buttonwindow4.setPosition(sf::Vector2f(5, 245));
						window.draw(Buttonwindow4);
						Label.setString("REMOVE");
						Label.setPosition(sf::Vector2f(135, 280));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 365));
						window.draw(Buttonwindow4);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(135, 400));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 485));
						window.draw(Buttonwindow4);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 518));
						window.draw(Label);

						if (test.begin == NULL && test.last == NULL) {

							window.draw(label_empty);
						}
						else {

							TDQueue<Schedule> aux = test;
							if (amount(test) > 10) {

								if (amount(test) + 1 == fator_pagina + 10) {

									for (int p = 0; p < fator_pagina - 1; p++) {

										aux.begin = aux.begin->next;
									}

									fator_pagina--;

								}
								else
								{

									for (int p = 0; p < fator_pagina; p++) {

										aux.begin = aux.begin->next;

									}
								}
							}

							int j = 5;
							for (int i = 0; i < 10; i++) {

								if (amount(test) < 10) {

									for (int i = 0; i < amount(test); i++) {

										LabelLIST.setString(aux.begin->data.name);
										LabelLIST.setPosition(sf::Vector2f(10, j));
										window.draw(LabelLIST);
										LabelLIST.setString(aux.begin->data.number);
										LabelLIST.setPosition(sf::Vector2f(275, j));
										window.draw(LabelLIST);

										j = j + 20;
										aux.begin = aux.begin->next;
									}
									break;
								}
								else
								{

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;

								}

							}
						}

						window.display();
					}
					else
					{

						TDQueue<Schedule> aux = test;

						for (int i = 0; i < (position + fator_pagina - 1); i++)
						{

							aux.begin = aux.begin->next;
						}

						name_chat = aux.begin->data.name;
						number_chat = aux.begin->data.number;

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						window.display();
					}
				}
				//Ação da janela 04 --> SUBIR PAGINA.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 195 && event.mouseButton.y >= 215 &&
					event.mouseButton.y <= 235 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					index = 3;

					if (amount(test) > 10) {

						if (fator_pagina > 0) {

							TDQueue<Schedule> aux = test;

							fator_pagina--;
							window.clear();
							window.setTitle("LIST SCHEDULE");
							window.draw(background);
							window.draw(listbox);
							Buttonpage.setPosition(sf::Vector2f(5, 215));
							window.draw(Buttonpage);
							window.draw(seta_cima);
							Buttonpage.setPosition(sf::Vector2f(205, 215));
							window.draw(Buttonpage);
							window.draw(seta_baixo);
							Buttonwindow4.setPosition(sf::Vector2f(5, 245));
							window.draw(Buttonwindow4);
							Label.setString("REMOVE");
							Label.setPosition(sf::Vector2f(135, 280));
							window.draw(Label);
							Buttonwindow4.setPosition(sf::Vector2f(5, 365));
							window.draw(Buttonwindow4);
							Label.setString("CHANGE");
							Label.setPosition(sf::Vector2f(135, 400));
							window.draw(Label);
							Buttonwindow4.setPosition(sf::Vector2f(5, 485));
							window.draw(Buttonwindow4);
							Label.setString("BACK");
							Label.setPosition(sf::Vector2f(160, 518));
							window.draw(Label);

							for (int p = 0; p < fator_pagina; p++) {

								aux.begin = aux.begin->next;
							}

							int j = 5;
							for (int i = 0; i < 10; i++) {

								if (amount(test) < 10) {

									for (int i = 0; i < amount(test); i++) {

										LabelLIST.setString(aux.begin->data.name);
										LabelLIST.setPosition(sf::Vector2f(10, j));
										window.draw(LabelLIST);
										LabelLIST.setString(aux.begin->data.number);
										LabelLIST.setPosition(sf::Vector2f(275, j));
										window.draw(LabelLIST);

										j = j + 20;
										aux.begin = aux.begin->next;
									}
									break;
								}
								else
								{

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
							}

							window.display();
						}
						else {

							cout << "A ESTRUTURA ESTA NO COMECO" << endl;
						}
					}
					else {

						cout << "NAO DA PARA SUBIR A ESTRUTURA" << endl;
					}
				}
				//Ação da janela 04 --> DESCER PAGINA.
				else if (event.mouseButton.x >= 205 && event.mouseButton.x <= 395 && event.mouseButton.y >= 215 &&
					event.mouseButton.y <= 235 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					index = 3;
					if (amount(test) > 10) {

						if (10 + fator_pagina < amount(test)) {

							TDQueue<Schedule> aux = test;

							fator_pagina++;
							window.clear();
							window.setTitle("LIST SCHEDULE");
							window.draw(background);
							window.draw(listbox);
							Buttonpage.setPosition(sf::Vector2f(5, 215));
							window.draw(Buttonpage);
							window.draw(seta_cima);
							Buttonpage.setPosition(sf::Vector2f(205, 215));
							window.draw(Buttonpage);
							window.draw(seta_baixo);
							Buttonwindow4.setPosition(sf::Vector2f(5, 245));
							window.draw(Buttonwindow4);
							Label.setString("REMOVE");
							Label.setPosition(sf::Vector2f(135, 280));
							window.draw(Label);
							Buttonwindow4.setPosition(sf::Vector2f(5, 365));
							window.draw(Buttonwindow4);
							Label.setString("CHANGE");
							Label.setPosition(sf::Vector2f(135, 400));
							window.draw(Label);
							Buttonwindow4.setPosition(sf::Vector2f(5, 485));
							window.draw(Buttonwindow4);
							Label.setString("BACK");
							Label.setPosition(sf::Vector2f(160, 518));
							window.draw(Label);

							for (int p = 0; p < fator_pagina; p++) {

								aux.begin = aux.begin->next;
							}

							int j = 5;
							for (int i = 0; i < 10; i++) {

								if (amount(test) < 10) {

									for (int i = 0; i < amount(test); i++) {

										LabelLIST.setString(aux.begin->data.name);
										LabelLIST.setPosition(sf::Vector2f(10, j));
										window.draw(LabelLIST);
										LabelLIST.setString(aux.begin->data.number);
										LabelLIST.setPosition(sf::Vector2f(275, j));
										window.draw(LabelLIST);

										j = j + 20;
										aux.begin = aux.begin->next;
									}
									break;
								}
								else
								{

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}

							}

							window.display();

						}
						else
						{

							cout << "A ESTRUTURA ESTA NO FIM" << endl;

						}
					}
					else {

						cout << "NAO TEM COMO DESCER A PAGINA" << endl;
					}
				}
				//Ação da janela 04 --> REMOVER.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 245 &&
					event.mouseButton.y <= 352 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					if (position == 0) {

						index = 3;
						position == 0;
						window.clear();
						window.setTitle("LIST SCHEDULE");
						window.draw(background);
						window.draw(listbox);
						Buttonpage.setPosition(sf::Vector2f(5, 215));
						window.draw(Buttonpage);
						window.draw(seta_cima);
						Buttonpage.setPosition(sf::Vector2f(205, 215));
						window.draw(Buttonpage);
						window.draw(seta_baixo);
						Buttonwindow4.setPosition(sf::Vector2f(5, 245));
						window.draw(Buttonwindow4);
						Label.setString("REMOVE");
						Label.setPosition(sf::Vector2f(135, 280));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 365));
						window.draw(Buttonwindow4);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(135, 400));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 485));
						window.draw(Buttonwindow4);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 518));
						window.draw(Label);

						if (test.begin == NULL && test.last == NULL) {

							window.draw(label_empty);
						}
					}
					else {

						index = 3;
						if (amount(test) == 10) {

							fator_pagina = 0;
						}

						position = position + fator_pagina;

						remove_position(test, position);
						position = 0;
						window.clear();
						window.setTitle("LIST SCHEDULE");
						window.draw(background);
						window.draw(listbox);
						Buttonpage.setPosition(sf::Vector2f(5, 215));
						window.draw(Buttonpage);
						window.draw(seta_cima);
						Buttonpage.setPosition(sf::Vector2f(205, 215));
						window.draw(Buttonpage);
						window.draw(seta_baixo);
						Buttonwindow4.setPosition(sf::Vector2f(5, 245));
						window.draw(Buttonwindow4);
						Label.setString("REMOVE");
						Label.setPosition(sf::Vector2f(135, 280));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 365));
						window.draw(Buttonwindow4);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(135, 400));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 485));
						window.draw(Buttonwindow4);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 518));
						window.draw(Label);

						if (test.begin == NULL && test.last == NULL) {

							window.draw(label_empty);
						}
						else {

							TDQueue<Schedule> aux = test;
							if (amount(test) > 10) {

								if (amount(test) + 1 == fator_pagina + 10) {

									for (int p = 0; p < fator_pagina - 1; p++) {

										aux.begin = aux.begin->next;
									}

									fator_pagina--;

								}
								else
								{

									for (int p = 0; p < fator_pagina; p++) {

										aux.begin = aux.begin->next;

									}
								}
							}

							int j = 5;
							for (int i = 0; i < 10; i++) {

								if (amount(test) < 10) {

									for (int i = 0; i < amount(test); i++) {

										LabelLIST.setString(aux.begin->data.name);
										LabelLIST.setPosition(sf::Vector2f(10, j));
										window.draw(LabelLIST);
										LabelLIST.setString(aux.begin->data.number);
										LabelLIST.setPosition(sf::Vector2f(275, j));
										window.draw(LabelLIST);

										j = j + 20;
										aux.begin = aux.begin->next;
									}
									break;
								}
								else
								{

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;

								}

							}
						}

						window.display();
					}
				}
				//Ação da janela 04 --> SELECIONAR O PRIMEIRO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 6 &&
					event.mouseButton.y <= 25.8 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 1;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 6));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O SEGUNDO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 25.9 &&
					event.mouseButton.y <= 45.7 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 2;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 25.9));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O TERCEIRO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 45.8 &&
					event.mouseButton.y <= 65.6 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 3;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 45.8));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O QUARTO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 65.7 &&
					event.mouseButton.y <= 85.5 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 4;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 65.7));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O QUINTO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 85.6 &&
					event.mouseButton.y <= 105.4 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 5;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 85.6));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O SEXTO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 105.5 &&
					event.mouseButton.y <= 125.3 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 6;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 105.5));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O SETIMO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 125.4 &&
					event.mouseButton.y <= 145.2 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 7;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 125.4));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {
						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O OITAVO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 145.3 &&
					event.mouseButton.y <= 165.1 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 8;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 145.3));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O NONO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 165.2 &&
					event.mouseButton.y <= 185 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 9;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 165.2));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> SELECIONAR O DECIMO ELEMENTO DA LISTBOX.
				else if (event.mouseButton.x >= 6 && event.mouseButton.x <= 394 && event.mouseButton.y >= 185.1 &&
					event.mouseButton.y <= 204.9 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					position = 10;
					index = 3;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Select_listbox.setPosition(sf::Vector2f(6, 185.1));
					window.draw(Select_listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);
					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
				//Ação da janela 04 --> BACK.
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 485 &&
					event.mouseButton.y <= 592 && index == 3 && event.mouseButton.button == sf::Mouse::Left) {

					index = 1;
					fator_pagina = 0;
					window.setTitle("SCHEDULE OPTIONS");
					window.clear();
					window.draw(background);
					Button.setPosition(sf::Vector2f(5, 10));
					window.draw(Button);
					Label.setString("ADD CONTACT");
					Label.setPosition(sf::Vector2f(100, 50));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 150));
					window.draw(Button);
					Label.setString("LIST SCHEDULE");
					Label.setPosition(sf::Vector2f(90, 195));
					window.draw(Label);
					Button.setPosition(sf::Vector2f(5, 290));
					window.draw(Button);
					Label.setString("EXIT");
					Label.setPosition(sf::Vector2f(170, 335));
					window.draw(Label);
					window.display();

				}
				//Ação da janela 05 --> ADD
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 330 &&
					event.mouseButton.y <= 455 && index == 4 && event.mouseButton.button == sf::Mouse::Left) {

					if (name == "" && number == "") {

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						asterisco.setPosition(sf::Vector2f(350, 145));
						window.draw(asterisco);
						asterisco.setPosition(sf::Vector2f(350, 265));
						window.draw(asterisco);
						window.display();
					}
					else if (name == "") {

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						asterisco.setPosition(sf::Vector2f(350, 145));
						window.draw(asterisco);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						window.display();
					}
					else if (number == "") {

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						asterisco.setPosition(sf::Vector2f(350, 265));
						window.draw(asterisco);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						window.display();
					}
					else {

						TDQueue<Schedule> swap = test;

						for (int i = 0; i < (position + fator_pagina - 1); i++)
						{

							swap.begin = swap.begin->next;
						}

						swap.begin->data.name = name;
						swap.begin->data.number = number;

						name = "";
						number = "";

						index = 3;
						window.clear();
						window.setTitle("LIST SCHEDULE");
						window.draw(background);
						window.draw(listbox);
						Buttonpage.setPosition(sf::Vector2f(5, 215));
						window.draw(Buttonpage);
						window.draw(seta_cima);
						Buttonpage.setPosition(sf::Vector2f(205, 215));
						window.draw(Buttonpage);
						window.draw(seta_baixo);
						Buttonwindow4.setPosition(sf::Vector2f(5, 245));
						window.draw(Buttonwindow4);
						Label.setString("REMOVE");
						Label.setPosition(sf::Vector2f(135, 280));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 365));
						window.draw(Buttonwindow4);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(135, 400));
						window.draw(Label);
						Buttonwindow4.setPosition(sf::Vector2f(5, 485));
						window.draw(Buttonwindow4);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 518));
						window.draw(Label);
						if (test.begin == NULL && test.last == NULL) {

							window.draw(label_empty);
						}
						else {

							TDQueue<Schedule> aux = test;
							int j = 5;
							for (int i = 0; i < 10; i++) {

								if (amount(test) < 10) {

									for (int i = 0; i < amount(test); i++) {

										LabelLIST.setString(aux.begin->data.name);
										LabelLIST.setPosition(sf::Vector2f(10, j));
										window.draw(LabelLIST);
										LabelLIST.setString(aux.begin->data.number);
										LabelLIST.setPosition(sf::Vector2f(275, j));
										window.draw(LabelLIST);

										j = j + 20;
										aux.begin = aux.begin->next;
									}
									break;
								}
								else
								{

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
							}
						}

						window.display();
					}
				}
				//Ação da janela 05 --> SETA O TEXTO NA CHATBOX NOME.
				else if (event.mouseButton.x >= 9 && event.mouseButton.x <= 390 && event.mouseButton.y >= 139 &&
					event.mouseButton.y <= 191 && index == 4 && event.mouseButton.button == sf::Mouse::Left) {

					index_text = 0;
					name = "";
				}
				else if (event.mouseButton.x >= 9 && event.mouseButton.x <= 390 && event.mouseButton.y >= 259 &&
					event.mouseButton.y <= 310 && index == 4 && event.mouseButton.button == sf::Mouse::Left) {

					index_text = 1;
					number = "";
				}
				//Ação da janela 05 --> BACK
				else if (event.mouseButton.x >= 5 && event.mouseButton.x <= 395 && event.mouseButton.y >= 470 &&
					event.mouseButton.y <= 595 && index == 4 && event.mouseButton.button == sf::Mouse::Left) {

					name = "";
					number = "";
					index = 3;

					position = 0;
					window.clear();
					window.setTitle("LIST SCHEDULE");
					window.draw(background);
					window.draw(listbox);
					Buttonpage.setPosition(sf::Vector2f(5, 215));
					window.draw(Buttonpage);
					window.draw(seta_cima);
					Buttonpage.setPosition(sf::Vector2f(205, 215));
					window.draw(Buttonpage);
					window.draw(seta_baixo);
					Buttonwindow4.setPosition(sf::Vector2f(5, 245));
					window.draw(Buttonwindow4);
					Label.setString("REMOVE");
					Label.setPosition(sf::Vector2f(135, 280));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 365));
					window.draw(Buttonwindow4);
					Label.setString("CHANGE");
					Label.setPosition(sf::Vector2f(135, 400));
					window.draw(Label);
					Buttonwindow4.setPosition(sf::Vector2f(5, 485));
					window.draw(Buttonwindow4);
					Label.setString("BACK");
					Label.setPosition(sf::Vector2f(160, 518));
					window.draw(Label);

					if (test.begin == NULL && test.last == NULL) {

						window.draw(label_empty);
					}
					else {

						TDQueue<Schedule> aux = test;
						if (amount(test) > 10) {

							if (amount(test) + 1 == fator_pagina + 10) {

								for (int p = 0; p < fator_pagina - 1; p++) {

									aux.begin = aux.begin->next;
								}

								fator_pagina--;

							}
							else
							{

								for (int p = 0; p < fator_pagina; p++) {

									aux.begin = aux.begin->next;

								}
							}
						}

						int j = 5;
						for (int i = 0; i < 10; i++) {

							if (amount(test) < 10) {

								for (int i = 0; i < amount(test); i++) {

									LabelLIST.setString(aux.begin->data.name);
									LabelLIST.setPosition(sf::Vector2f(10, j));
									window.draw(LabelLIST);
									LabelLIST.setString(aux.begin->data.number);
									LabelLIST.setPosition(sf::Vector2f(275, j));
									window.draw(LabelLIST);

									j = j + 20;
									aux.begin = aux.begin->next;
								}
								break;
							}
							else
							{

								LabelLIST.setString(aux.begin->data.name);
								LabelLIST.setPosition(sf::Vector2f(10, j));
								window.draw(LabelLIST);
								LabelLIST.setString(aux.begin->data.number);
								LabelLIST.setPosition(sf::Vector2f(275, j));
								window.draw(LabelLIST);

								j = j + 20;
								aux.begin = aux.begin->next;

							}

						}
					}

					window.display();
				}
			}
			//Ação de texto da janela 03 --> ENTRADA DO NOME.
			if (event.type == sf::Event::TextEntered && index_text == 0 && index == 2) {

				name += static_cast<char>(event.text.unicode);
			}
			//Ação de texto da janela 03 --> ENTRADA DO NUMERO.
			else if (event.type == sf::Event::TextEntered && index_text != 0 && index == 2) {

				number += static_cast<char>(event.text.unicode);
			}
			//Ação para o print constante do texto da janela 03 --> EVENT KEYPRESSED
			if (index == 2 && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::B) || sf::Keyboard::isKeyPressed(sf::Keyboard::C) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::F) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::H) || sf::Keyboard::isKeyPressed(sf::Keyboard::I) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::L) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::N) || sf::Keyboard::isKeyPressed(sf::Keyboard::O) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::R) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::U) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket) || sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))) {

				if (index == 2) {

					if (index_text == 0) {

						window.clear();
						window.setTitle("REGISTER SCHEDULE");
						window.draw(background);
						Label.setString("REGISTER");
						Label.setPosition(sf::Vector2f(120, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						window.display();


					}
					else if (index_text == 1) {

						window.clear();
						window.setTitle("REGISTER SCHEDULE");
						window.draw(background);
						Label.setString("REGISTER");
						Label.setPosition(sf::Vector2f(120, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						window.display();
					}
				}
			}
			//Ação de texto da janela 04 --> ENTRADA DO NOME.
			if (event.type == sf::Event::TextEntered && index_text == 0 && index == 4) {

				name += static_cast<char>(event.text.unicode);
			}
			//Ação de texto da janela 04 --> ENTRADA DE NUMERO.
			else if (event.type == sf::Event::TextEntered && index_text != 0 && index == 4) {

				number += static_cast<char>(event.text.unicode);
			}//Ação para o print constante do texto da janela 04 --> EVENT KEYPRESSED.
			if (index == 4 && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::B) || sf::Keyboard::isKeyPressed(sf::Keyboard::C) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::F) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::H) || sf::Keyboard::isKeyPressed(sf::Keyboard::I) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::L) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::N) || sf::Keyboard::isKeyPressed(sf::Keyboard::O) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::R) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::U) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket) || sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))) {

				if (index == 4) {

					if (index_text == 0) {

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						window.display();
					}
					else if (index_text == 1) {

						index = 4;
						window.clear();
						window.setTitle("CHANGE SCHEDULE");
						window.draw(background);
						Label.setString("CHANGE");
						Label.setPosition(sf::Vector2f(130, 10));
						window.draw(Label);
						Label.setString("NAME: ");
						Label.setPosition(sf::Vector2f(10, 100));
						window.draw(Label);
						LabelLIST.setPosition(sf::Vector2f(110, 110));
						LabelLIST.setString(name_chat);
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 140));
						window.draw(Chatbox);
						Chat_text.setString(name);
						Chat_text.setPosition(sf::Vector2f(15, 150));
						window.draw(Chat_text);
						Label.setString("NUMBER: ");
						Label.setPosition(sf::Vector2f(10, 220));
						window.draw(Label);
						LabelLIST.setString(number_chat);
						LabelLIST.setPosition(sf::Vector2f(150, 230));
						window.draw(LabelLIST);
						Chatbox.setPosition(sf::Vector2f(10, 260));
						window.draw(Chatbox);
						Chat_text.setString(number);
						Chat_text.setPosition(sf::Vector2f(15, 270));
						window.draw(Chat_text);
						Button.setPosition(sf::Vector2f(5, 330));
						window.draw(Button);
						Button.setPosition(sf::Vector2f(5, 470));
						window.draw(Button);
						Label.setString("ADD");
						Label.setPosition(sf::Vector2f(165, 370));
						window.draw(Label);
						Label.setString("BACK");
						Label.setPosition(sf::Vector2f(160, 515));
						window.draw(Label);
						window.display();
					}

				}
			}
		}
	}

	return 0;
}