#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// Global game state
bool gameOver = false;

// Class for a character (player and enemies)
class Character {
public:
    string name;
    int health;
    int attackPower;
    int defense;
    int experience;
    int level;

    // Constructor
    Character(string n, int hp, int atk, int def) 
        : name(n), health(hp), attackPower(atk), defense(def), experience(0), level(1) {}

    // Method to display character stats
    void displayStats() {
        cout << name << "'s Stats:" << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attackPower << endl;
        cout << "Defense: " << defense << endl;
        cout << "Experience: " << experience << endl;
        cout << "Level: " << level << endl;
    }

    // Method to level up the character
    void levelUp() {
        if (experience >= 100) {
            level++;
            experience -= 100;
            health += 10;
            attackPower += 5;
            defense += 5;
            cout << name << " leveled up to level " << level << "!" << endl;
        }
    }
};

// Class for an item in the inventory
class Item {
public:
    string name;
    int healthRestore;

    // Constructor
    Item(string n, int hr) : name(n), healthRestore(hr) {}
};

// Class for the player's inventory
class Inventory {
public:
    vector<Item> items;

    // Method to add an item to the inventory
    void addItem(const Item& item) {
        items.push_back(item);
    }

    // Method to use an item from the inventory
    void useItem(Character& player) {
        if (items.empty()) {
            cout << "You have no items to use!\n";
            return;
        }

        cout << "Using " << items[0].name << " to heal for " << items[0].healthRestore << " health.\n";
        player.health += items[0].healthRestore;
        items.erase(items.begin()); // Remove the used item from inventory
    }
};

// Function to handle combat between player and an enemy
void combat(Character& player, Character& enemy) {
    cout << "You encounter a " << enemy.name << "!\n";

    while (player.health > 0 && enemy.health > 0) {
        cout << "Your health: " << player.health << "\n";
        cout << enemy.name << "'s health: " << enemy.health << "\n";

        // Player attacks enemy
        int damageDealt = player.attackPower - enemy.defense;
        if (damageDealt < 0) damageDealt = 0;
        enemy.health -= damageDealt;
        cout << "You attack the " << enemy.name << " for " << damageDealt << " damage!\n";

        if (enemy.health <= 0) {
            cout << "You defeated the " << enemy.name << "!\n";
            player.experience += 50;
            player.levelUp();
            return;
        }

        // Enemy attacks player
        damageDealt = enemy.attackPower - player.defense;
        if (damageDealt < 0) damageDealt = 0;
        player.health -= damageDealt;
        cout << "The " << enemy.name << " attacks you for " << damageDealt << " damage!\n";

        if (player.health <= 0) {
            cout << "You have been defeated...\n";
            gameOver = true;
            return;
        }
    }
}

// Function to explore the world and possibly encounter enemies
void explore(Character& player) {
    cout << "You explore the wilderness...\n";
    int encounter = rand() % 2; // 50% chance of encountering an enemy

    if (encounter == 1) {
        Character enemy("Goblin", 30, 5, 2);
        combat(player, enemy);
    } else {
        cout << "You found nothing interesting.\n";
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "\n[1] Explore" << endl;
    cout << "[2] Check Stats" << endl;
    cout << "[3] Use Item" << endl;
    cout << "[4] Exit Game" << endl;
}

// Function to get the player's input
int getInput() {
    int choice;
    cin >> choice;
    return choice;
}

// Main game loop
int main() {
    // Create the player character
    Character player("Hero", 100, 10, 5);

    // Create the player's inventory and add some items
    Inventory inventory;
    inventory.addItem(Item("Health Potion", 20));

    // Main game loop
    while (!gameOver) {
        displayMenu();
        int choice = getInput();
        switch (choice) {
            case 1:
                explore(player); // Explore the world
                break;
            case 2:
                player.displayStats(); // Display player stats
                break;
            case 3:
                inventory.useItem(player); // Use an item from the inventory
                break;
            case 4:
                gameOver = true; // Exit the game
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}