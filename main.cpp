#include <iostream>
#include <cstring>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

char table[10][15];

class Seed {// The class
public:
    string name;
    int initial_time_to_harvest;
    int time_to_harvest;
    int size;
    int price;
    int row;
    int column;
    int cycles;
    int time_to_regrow;
    char *letter;

    Seed(string name, int initial_time_to_harvest, char *letter, int cycles = 1, int time_to_regrow = 2) {
        this->name = name;
        this->initial_time_to_harvest = initial_time_to_harvest;
        this->time_to_harvest = initial_time_to_harvest;
        this->letter = letter;
        this->cycles = cycles;
        this->time_to_regrow = time_to_regrow;
    }

    virtual void set_letter() {};

    virtual void grow() {};

    virtual void harvest() {};

    virtual void plant(int row, int column) {
        this->row = row;
        this->column = column;
        table[row - 1][column - 1] = '.';
    };

};

Seed *seeds[10][15] = {nullptr};

class Crop : public Seed {
public:
    Crop(string name, int initial_time_to_harvest, char *letter) : Seed(name, initial_time_to_harvest, letter) {}

    void grow() override {
        time_to_harvest--;
        if (time_to_harvest < 0) {
            seeds[row - 1][column - 1] = nullptr;
            table[row - 1][column - 1] = '-';
        }else {
            table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
        }
    };

    void harvest() override {
        cycles--;
        if (cycles != 0) {
            time_to_harvest = time_to_regrow;
            table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
        }
    };

    void set_letter() override{
        table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
    };

};

class Potato : public Crop {       // The class
private:
    char letter[3] = {'.', 'p', 'P'};
public:
    int price = 1;

    Potato() : Crop("Potato", 2, letter) {}

};

class Tomato : public Crop {       // The class
private:
    char letter[4] = {'.', 't', 't', 'T'};
public:
    int price = 2;

    Tomato() : Crop("Tomato", 3, letter) {}

};

class Bush : public Seed {       // The class
public:
    Bush(string name, int time_to_harvest, char *letter, int cycles, int time_to_regrow) : Seed(name, time_to_harvest,
                                                                                                letter, cycles,
                                                                                                time_to_regrow) {}

    void grow() override {
        time_to_harvest--;
        if (time_to_harvest < 0) {
            cycles--;
            if (cycles != 0) {
                time_to_harvest = time_to_regrow;
                table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
            } else {
                seeds[row - 1][column - 1] = nullptr;
                table[row - 1][column - 1] = '-';
            }
        }else {
            table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
        }
    };

    void harvest() override {
        cycles--;
        if (cycles != 0) {
            time_to_harvest = time_to_regrow;
            table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
        }
    };

    void set_letter() override{
        table[row - 1][column - 1] = letter[initial_time_to_harvest - time_to_harvest];
    };

};

class Strawberry : public Bush {       // The class
private:
    char letter[4] = {'.', 's', 's', 'S'};
public:
    int price = 1;

    Strawberry() : Bush("Strawberry", 3, letter, 2, 2) {}

};

class Blueberry : public Bush {       // The clas
private:
    char letter[5] = {'.', 'b', 'b', 'b', 'B'};
public:
    int price = 1;

    Blueberry() : Bush("Blueberry", 4, letter, 3, 3) {}

};

class Tree : public Seed {       // The class
public:
    Tree(string name, int time_to_harvest, char *letter, int cycles, int time_to_regrow) : Seed(name, time_to_harvest,
                                                                                                letter, cycles,
                                                                                                time_to_regrow) {}
    void plant(int row, int column) override {
        this->row = row;
        this->column = column;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                table[row - 1 + i][column - 1 + j] = '.';
            }
        }
    };

    void grow() override {
        time_to_harvest--;

        if (time_to_harvest < 0) {
            cycles--;
            if (cycles != 0) {
                time_to_harvest = time_to_regrow;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        table[row - 1 + i][column - 1 + j] = letter[initial_time_to_harvest - time_to_harvest];
                    }
                }
            } else {
                seeds[row - 1][column - 1] = nullptr;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        table[row - 1 + i][column - 1 + j] = '-';
                    }
                }
            }
        } else {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    table[row - 1 + i][column - 1 + j] = letter[initial_time_to_harvest - time_to_harvest];
                }
            }
        }
    };

    void harvest() override {
        cycles--;

        if (cycles != 0) {
            time_to_harvest = time_to_regrow;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    table[row - 1 + i][column - 1 + j] = letter[initial_time_to_harvest - time_to_harvest];
                }
            }
        } else {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    table[row - 1 + i][column - 1 + j] = '-';
                }
            }
        }
    };

    void set_letter() override{
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                table[row - 1 + i][column - 1 + j] = letter[initial_time_to_harvest - time_to_harvest];
            }
        }
    };

};

class Apple : public Tree {       // The class
private:
    char letter[5] = {'.', 'a', 'a', 'a', 'A'};
public:
    int price = 1;

    Apple() : Tree("Apple", 4, letter, 2, 3) {}

};

class Orange : public Tree {       // The class
private:
    char letter[6] = {'.', 'o', 'o', 'o', 'o', 'O'};
public:
    int price = 1;

    Orange() : Tree("Orange", 5, letter, 15, 4) {}

};

void fill_table(char table[10][15]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            table[i][j] = '-';
        }
    }
}

void print_table(char table[10][15]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}

void plant(Seed *seedToBePlant) {
    cout << "Where would you like to plant?" << endl;
    cout << "Enter row: ";
    int row;
    cin >> row;
    cout << "Enter column: ";
    int column;
    cin >> column;

    if (seeds[row - 1][column - 1] != nullptr) {
        cout << "There is already a seed planted there." << endl;
        return;
    }

    if (dynamic_cast<Tree *>(seedToBePlant)) { // Check if the seed is a tree
        if (row == 1 || row == 10 || column == 1 || column == 15) {
            cout << "Tu nie można posadzić drzewa" << endl;
            return;
        }

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (seeds[row - 1 + i][column - 1 + j] != nullptr) {
                    cout << "There is already a seed planted there." << endl;
                    return;
                }
            }
        }

        seeds[row - 1][column - 1] = seedToBePlant;
        seedToBePlant->plant(row, column);

    } else { //Not a tree
        if (!(row == 1 || row == 10 || column == 1 || column == 15)) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (dynamic_cast<Tree *>(seeds[row - 1 + i][column - 1 + j])) {
                        cout << "There is a tree nearby" << endl;
                        return;
                    }
                }
            }
        }
        seeds[row - 1][column - 1] = seedToBePlant;
        seedToBePlant->plant(row, column);
    }
}


class Stack {
public:
    string name;
    int amount;

    void add(int x) {
        amount = amount + x;
    };

    void substract(int x) {
        amount = amount - x;
    };

};

class Store {
private:
    Stack *stacks[10] = {nullptr};
public:
    int capacity = 100;

    void put(string name, int amount) {
        for (int i = 0; i < 10; i++) {
            if (stacks[i] == nullptr) {
                stacks[i] = new Stack;
                stacks[i]->name = name;
                stacks[i]->amount = amount;
                return;
            }
            if (stacks[i]->name == name) {
                stacks[i]->add(amount);
                return;
            }

        }
    };

    void get(string name, int amount) {
        for (int i = 0; i < 10; i++) {
            if (stacks[i]->name == name) {
                if (stacks[i]->amount < amount) {
                    cout << "Not enough to pull out " << name << endl;
                    return;
                }
                stacks[i]->substract(amount);
                return;
            }
        }
        cout << "No such item in the store" << endl;
    };

    void print() {
        for (int i = 0; i < 10; i++) {
            if (stacks[i] != nullptr) {
                cout << stacks[i]->name << " " << stacks[i]->amount << endl;
            }
        }
    };

    void print_to_file(ofstream& file) {
        for (int i = 0; i < 10; i++) {
            if (stacks[i] != nullptr) {
                file << stacks[i]->name << " " << stacks[i]->amount << endl;
            }
        }
    };


};

void fill_table_from_file(Store &store){
    ifstream file("save.txt");//load the game
    string line;
    int row;
    int column;
    int time_to_harvest;
    int amount;
    int cycles;
    string name;
    while (getline(file, line)) {
        if (line == "--------Store---------") {
            while (getline(file, line)) {
                istringstream iss(line);
                iss >> name >> amount;
                store.put(name, amount);
            }
            return;
        }
        istringstream iss(line);
        iss >> name >> row >> column >> time_to_harvest >> cycles;
        if (name == "Potato") {
            Potato *potato1 = new Potato;
            potato1->row = row;
            potato1->column = column;
            potato1->time_to_harvest = time_to_harvest;
            potato1->cycles = cycles;
            seeds[row - 1][column - 1] = potato1;
            seeds[row - 1][column - 1]->set_letter();
        } else if (name == "Tomato") {
            Tomato *tomato1 = new Tomato;
            tomato1->row = row;
            tomato1->column = column;
            tomato1->time_to_harvest = time_to_harvest;
            tomato1->cycles = cycles;
            seeds[row - 1][column - 1] = tomato1;
            seeds[row - 1][column - 1]->set_letter();
        } else if (name == "Strawberry") {
            Strawberry *strawberry1 = new Strawberry;
            strawberry1->row = row;
            strawberry1->column = column;
            strawberry1->time_to_harvest = time_to_harvest;
            strawberry1->cycles = cycles;
            seeds[row - 1][column - 1] = strawberry1;
            seeds[row - 1][column - 1]->set_letter();
        } else if (name == "Blueberry") {
            Blueberry *blueberry1 = new Blueberry;
            blueberry1->row = row;
            blueberry1->column = column;
            blueberry1->time_to_harvest = time_to_harvest;
            blueberry1->cycles = cycles;
            seeds[row - 1][column - 1] = blueberry1;
            seeds[row - 1][column - 1]->set_letter();
        } else if (name == "Apple") {
            Apple *apple1 = new Apple;
            apple1->row = row;
            apple1->column = column;
            apple1->time_to_harvest = time_to_harvest;
            apple1->cycles = cycles;
            seeds[row - 1][column - 1] = apple1;
            seeds[row - 1][column - 1]->set_letter();
        } else if (name == "Orange") {
            Orange *orange1 = new Orange;
            orange1->row = row;
            orange1->column = column;
            orange1->time_to_harvest = time_to_harvest;
            orange1->cycles = cycles;
            seeds[row - 1][column - 1] = orange1;
            seeds[row - 1][column - 1]->set_letter();
        }
    }

    file.close();
}


void harvest(int row, int column, Store &store) {
    string seedName = seeds[row - 1][column - 1]->name;
    store.put(seedName, 1);
    seeds[row - 1][column - 1]->harvest();

    if (seeds[row - 1][column - 1]->cycles != 0) {
        return;
    }

    seeds[row - 1][column - 1] = nullptr;
    table[row - 1][column - 1] = '-';

}

int main() {
    Store store1;
    cout << "Hello, Farm !" << endl;
    cout << "------------------------------" << endl;
    fill_table(table);

    fill_table_from_file(store1);

    for (;;) {
        print_table(table);
        cout << "What do you want to do?" << endl;
        cout << "1.Plant 2.Harvest 3.Skip time 4.Store 5.Save 6.Exit " << endl;
        cout << "------------------------------" << endl;
        int choice_do;
        cin >> choice_do;
        switch (choice_do) {
            case 1:
                cout << "What would you like to plant?" << endl;
                cout << "1.Potato 2.Tomato 3.Strawberry 4.Blueberry 5.Apple 6.Orange 7.Back" << endl;
                cout << "----------------------------------------" << endl;

                int choice;
                cin >> choice;
                if (choice == 1) {
                    plant(new Potato);
                } else if (choice == 2) {
                    plant(new Tomato);
                } else if (choice == 3) {
                    plant(new Strawberry);
                } else if (choice == 4) {
                    plant(new Blueberry);
                } else if (choice == 5) {
                    plant(new Apple);
                } else if (choice == 6) {
                    plant(new Orange);
                } else if (choice == 7) {
                    break;
                } else {
                    cout << "Invalid choice" << endl;
                }
                break;

            case 2:
                for (auto &seed: seeds) {
                    for (auto &j: seed) {
                        if (j != nullptr && j->time_to_harvest == 0) { // Check if there is a grow seed
                            harvest(j->row, j->column, store1); // Call the harvest function for the seed
                        }
                    }
                }
                break;
            case 3:
                cout << "skipping time" << endl;

                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 15; ++j) {
                        if (seeds[i][j] != nullptr) {
                            seeds[i][j]->grow();

//                            if (static_cast<int>(table[seeds[i][j]->row - 1][seeds[i][j]->column - 1]) == 0) {
//                                if (dynamic_cast<Tree *>(seeds[i][j])){
//                                    for (int k = -1; k <= 1; ++k) {
//                                        for (int n = -1; n <= 1; ++n) {
//                                            table[seeds[i][j]->row - 1 + k][seeds[i][j]->column - 1 +n] = '-';
//                                        }
//                                    }
//                                }
//                                    table[seeds[i][j]->row - 1][seeds[i][j]->column - 1] = '-';
//                                    seeds[i][j] = nullptr;
//
//                            }
                        }
                    }
                }

                break;
            case 4:
                cout << "--------Store---------" << endl;
                store1.print();
                cout << "----------------------" << endl;
                break;
            case 5:{
                cout << "........Saving........" << endl;

                ofstream file("save.txt");//save the game

                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 15; ++j) {
                        if (seeds[i][j] != nullptr) {
                            file << seeds[i][j]->name << " " << seeds[i][j]->row << " " << seeds[i][j]->column
                                       << " "
                                       << seeds[i][j]->time_to_harvest << " " << seeds[i][j]->cycles << endl;
                        }
                    }
                }

                file << "--------Store---------" << endl;
                store1.print_to_file(file);

                file.close();
                break;
            }
            case 6:
                return 0;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }
    return 0;
}
