#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "log.h"

#include "raylib.h"
#include <map>
#include <functional>

const float PI_VALUE = 3.1416f;


struct CombatOutcome {
	std::string OutcomeText;
	Color TextColor;
	std::function<void(Player&, Enemy&)> ActionOutput;
};

int DoSomethingWithCallBack(std::function<void()> callback, int callbackCount) {
	callback();
	return callbackCount++;
}

void PrintToConsole() {
	std::cout << "Lambda Called" << std::endl;
}


int main() {
	/*
	Player MainPlayer(5, 2, 2, "Hero");
	Enemy Foe(2, 1, 1, "Slime");
	int Round = 1;
	std::string PlayerActionS;
	std::string FoeActionS;

	while (MainPlayer.IsAlive()) {
		Actions PlayerAction = MainPlayer.ChooseAction();
		Actions FoeAction = Foe.ChooseAction();

		switch (PlayerAction) {
		case ATTACK:
			PlayerActionS = "Attack";
			switch (FoeAction) {
				case ATTACK:
					FoeActionS = "Attack";
					MainPlayer.UpdateHealth(-Foe.GetAttack());
					Foe.UpdateHealth(-MainPlayer.GetAttack());
					break;
				case PARRY:
					FoeActionS = "Parry";
					MainPlayer.UpdateHealth(-Foe.GetAttack() * 2);
					break;
				case DEFEND:
					FoeActionS = "Defend";
					Foe.UpdateHealth(-(MainPlayer.GetAttack() - Foe.GetDefende()));
					break;
			}
			break;

		case PARRY:
			PlayerActionS = "Parry";
			switch (FoeAction) {
			case ATTACK:
				FoeActionS = "Attack";
				Foe.UpdateHealth(-MainPlayer.GetAttack() * 2);
				break;
			case PARRY:
				FoeActionS = "Parry";
				break;
			case DEFEND:
				FoeActionS = "Defend";
				MainPlayer.UpdateHealth(-Foe.GetDefende());
				break;
			}
			break;

		case DEFEND:
			PlayerActionS = "Defend";
			switch (FoeAction) {
			case ATTACK:
				FoeActionS = "Attack";
				MainPlayer.UpdateHealth(-(Foe.GetAttack() - MainPlayer.GetDefende()));
				break;
			case PARRY:
				FoeActionS = "Parry";
				Foe.UpdateHealth(-(MainPlayer.GetDefende()));
				break;
			case DEFEND:
				FoeActionS = "Defend";
				break;
			}
			break;
		}

		Log::LogMessage(LOG_DEFAULT, "Player " + PlayerActionS);
		Log::LogMessage(LOG_DEFAULT, "Foe " + FoeActionS);
		

		std::cout << "Hero Health: " << MainPlayer.GetHealth() << " Foe Health: " << Foe.GetHealth() << std::endl;

		if (!Foe.IsAlive()) {
			Round += 1;

			if (Round > 5) {
				Log::LogMessage(LOG_WARNING, MainPlayer.GetName() + " Won! , NO more aspirants left!");
				break;
			}
			Log::LogMessage(LOG_WARNING, MainPlayer.GetName() + " Won! , Here comes a new foe!");
			Foe.IncreaseDifficulty(Round);


			Log::LogMessage(LOG_WARNING, " Beware the " + Foe.GetName());
;
		}
	}

	if (MainPlayer.IsAlive()) {
		Log::LogMessage(LOG_WARNING, MainPlayer.GetName() + ", Congratulations you Won the game!");
	}
	else {
		Log::LogMessage(LOG_WARNING, MainPlayer.GetName() + " thanks for Playing!");
	}*/

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;
	int state = 0;
	int stateBuffer = 0;

	std::map<std::pair<Actions,Actions>, CombatOutcome> OutcomeMap
	{
		{{ATTACK, ATTACK}, {"Both Players Attack each other!", ORANGE, [](Player& player, Enemy& enemy) {player.UpdateHealth(-1); enemy.UpdateHealth(-1);}}},
		{{ATTACK, PARRY},  {"Enemy Parries the Attack", RED, [](Player& player, Enemy& enemy) {player.UpdateHealth(-2);}}},
		{{ATTACK, DEFEND}, {"Enemy Defended", BLUE, [](Player& player, Enemy& enemy) {}}},
		{{DEFEND, ATTACK}, {"You defended from an attack!", BLUE, [](Player& player, Enemy& enemy) {}}},
		{{DEFEND, DEFEND}, {"Both Defended!", BLUE, [](Player& player, Enemy& enemy) {}}},
		{{DEFEND, PARRY},  {"Your enemy couldn't parry!", BLUE, [](Player& player, Enemy& enemy) {}}},
		{{PARRY, ATTACK},  {"You Parried the enemy!" , GREEN, [](Player& player, Enemy& enemy) {enemy.UpdateHealth(-2);}}},
		{{PARRY, DEFEND},  {"You couldn't parry!" , BLUE, [](Player& player, Enemy& enemy) {}}},
		{{PARRY, PARRY},   {"No one parried!" , BLUE, [](Player& player, Enemy& enemy) {}}},
	};

	Actions PlayerAction = ATTACK;
	std::pair<Actions, Actions> OutcomeActions;

	InitWindow(screenWidth, screenHeight, "Duel Game");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	Player MainPlayer(5, 2, 2, "Hero");
	Enemy Foe(2, 1, 1, "Slime");

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("Press 1 to Attack, 2 to Parry or 3 to Defend!", 150, 300, 25, RED);

		switch (GetKeyPressed()) {
		case KEY_ONE:
			PlayerAction = ATTACK;
			break;

		case KEY_TWO:
			PlayerAction = PARRY;
			break;

		case KEY_THREE:
			PlayerAction = DEFEND;
			break;
		}


		DrawText(OutcomeMap[{PlayerAction, ATTACK }].OutcomeText.c_str(), 200, 400, 22, OutcomeMap[{PlayerAction, ATTACK }].TextColor);
		OutcomeMap[{PlayerAction, ATTACK }].ActionOutput(MainPlayer, Foe);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	int x = 1;
	int y = 2;

	auto myLambda = []() {
		int x = 1;
		int y = 0;

		int localX  = x * y;
		std::cout << localX << std::endl;
	};

	auto myLambda = [=]() {
		int localx = x * y;
		std::cout << localx << std::endl;
		};

	auto myLambda = [&]() {
		x = x * y;
		std::cout << x << std::endl;
		};

	auto myLambda = [x, &y]() {
		y = x * y;
		std::cout << y << std::endl;
		};


	int callbacks = 0;

	callbacks = DoSomethingWithCallBack(PrintToConsole, callbacks);

	return 0;
};