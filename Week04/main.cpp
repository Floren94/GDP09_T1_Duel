#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "log.h"


int main() {
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
	}

	return 0;
}