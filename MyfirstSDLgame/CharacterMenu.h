#pragma once
#include "Menu.h"


struct characterData {
	string characterClassName;
	string characterPNG;
	string characterSelectedPNG;
	string characterAbilityInfo;
};

class CharacterMenu : public Menu
{
private:
	vector <characterData> charDataArray;
	string selectedCharacter;
public:

	CharacterMenu(int width, int height, point location, const std::vector<menuItem> &options) : Menu(width, height, location, options) {
		selectedCharacter = nullptr;
	}
	~CharacterMenu();


	void characterDataInit() {
		characterData temp;

		temp.characterClassName = string("VOID_WALKER");
		temp.characterPNG = string(VOID_WALKER_PNG);
		temp.characterSelectedPNG = string(VOID_WALKER_PNG_SELECTED);
		temp.characterAbilityInfo = string("< < Teleports at a random location on the map. > >");
		charDataArray.push_back(temp);

		temp.characterClassName = string("MAGE");
		temp.characterPNG = string(MAGE_PNG);
		temp.characterSelectedPNG = string(MAGE_PNG_SELECTED);
		temp.characterAbilityInfo = string("< < Kills the minion in the closest proximity. > >");
		charDataArray.push_back(temp);

		temp.characterClassName = string("KNIGHT");
		temp.characterPNG = string(KNIGHT_PNG);
		temp.characterPNG = string(KNIGHT_PNG_SELECTED);
		temp.characterAbilityInfo = string("< < Atacks all enemies on the same y or x - axis. > > ");
		charDataArray.push_back(temp);
	};


	void moveUp();
	void moveDown();
	void drawMenu() override;
	void selectCurrentItem() override;
	void handleEvents();
	string getSelectedCharacter() {
		return selectedCharacter;
	}
};

