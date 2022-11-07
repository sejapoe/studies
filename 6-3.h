//
// Created by sejapoe on 10/30/22.
//

#ifndef FIRST_6_3_H
#define FIRST_6_3_H

#include <chrono>
#include <thread>
#include <random>

struct Animal {
    uint age{0};
    int energy;
    int pregnancyTimer{0};
    bool isMale;

    int const maxEnergy;
    int const energyByFood;
    bool const isPredator;
    int const deathAge;
    int const pregnancyDuration;

    explicit Animal(bool isMale, int maxEnergy, int energyByFood, bool isPredator, const int pregnancyDuration,
                    const int deathAge)
            : isMale(isMale), energy(maxEnergy), energyByFood(energyByFood), maxEnergy(maxEnergy),
              isPredator(isPredator),
              pregnancyDuration(pregnancyDuration), deathAge(deathAge) {}

    bool eat() {
        if (energy + energyByFood > maxEnergy) return false;
        energy = energy + energyByFood;
        return true;
    }

    [[nodiscard]] bool canBreed() const {
        return energy > maxEnergy / 2 && (isMale || pregnancyTimer == 0);
    }

    void tiredOfBreed() {
        energy -= maxEnergy / (isMale ? 5 : 3);
        energy = max(0, energy);
    }

    void tiredOfMove() {
        --energy;
        energy = max(0, energy);
    }
};

struct Wolf : Animal {
    explicit Wolf(bool isMale) : Animal(isMale, 50, 20, true, 1, 30) {}
};

struct Sheep : Animal {
    explicit Sheep(bool isMale) : Animal(isMale, 30, 10, false, 2, 10) {}
};

struct Cell {
    Animal *animal;
    bool hasGrass;

    explicit Cell() : animal(nullptr), hasGrass(false) {}

    Cell(Animal *animal, bool hasGrass) : animal(animal), hasGrass(hasGrass) {}

    [[nodiscard]] Cell copy() const {
        return {animal == nullptr ? nullptr : new Animal(*animal), hasGrass};
    }

    ~Cell() {
//        delete animal;
    }
};

struct Field {
    // Random stuff
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_real_distribution<double> dist0to1{0.0, 1.0};

    int size;
    double grassSplitChance;
    vector<vector<Cell>> _field;
    vector<pair<pair<int, int>, pair<int, int>>> neighbours;

    int deaths{0};
    int breeds{0};
    int kills{0};
    int birthsWolf{0};
    int birthsSheep{0};

    int day{0};

    Field(int size, double wolfPopulation,
          double sheepPopulation,
          double grassPopulation,
          double grassSplitChance) : size(size), grassSplitChance(grassSplitChance),
                                     _field(size, vector<Cell>(size)) {
        if (wolfPopulation + sheepPopulation > 1.0)
            throw invalid_argument("wolf and sheep population together must be lesser than 1.0");

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (dist0to1(mt) < grassPopulation) {
                    _field[i][j].hasGrass = true;
                }

                double animalPicker = dist0to1(mt);
                if (animalPicker < sheepPopulation) {
                    _field[i][j].animal = new Sheep(dist0to1(mt) < 0.5);
                } else if (animalPicker - sheepPopulation < wolfPopulation) {
                    _field[i][j].animal = new Wolf(dist0to1(mt) < 0.5);
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (j != 0) neighbours.emplace_back(make_pair(i, j), make_pair(i, j - 1));
                if (i != 0) neighbours.emplace_back(make_pair(i, j), make_pair(i - 1, j));
            }
        }
    }

    void oneDayLater() {
        vector<vector<Cell>> newState(size, vector<Cell>(size));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                newState[i][j] = _field[i][j].copy();
                // Sunset - growing
                if (newState[i][j].animal != nullptr) {
                    ++newState[i][j].animal->age;
                    if (newState[i][j].animal->pregnancyTimer > 1) --newState[i][j].animal->pregnancyTimer;
                }
                // Midnight - death
                death(newState[i][j]);
                // Sunrise - sheep are eating
                eatGrass(newState[i][j]);
            }
        }

        if (day % 10 == 0) std::shuffle(neighbours.begin(), neighbours.end(), mt);

        for (auto it : neighbours) {
            // Morning - grass is growing;
            grassDistribution(newState[it.first.first][it.first.second], newState[it.second.first][it.second.second]);
            // Noon - wolves on the hunt
            hunt(newState[it.first.first][it.first.second], newState[it.second.first][it.second.second]);
            // Afternoon - time to breed
            breed(newState[it.first.first][it.first.second], newState[it.second.first][it.second.second]);
        }
        _field = newState;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // Evening - move before sleep
                moveAnimal(i, j);
            }
        }

        ++day;
    }


    void moveAnimal(int i, int j) {
        Cell &source = _field[i][j];
        if (source.animal == nullptr) return;
        vector<Cell *> targets;
        // Move up
        if (i != 0) {
            Cell *target = &_field[i - 1][j];
            if (target->animal == nullptr) {
                targets.push_back(target);
            }
        }
        // Move left
        if (j != 0) {
            Cell *target = &_field[i][j - 1];
            if (target->animal == nullptr) {
                targets.push_back(target);
            }
        }
        // Move down
        if (i != size - 1) {
            Cell *target = &_field[i + 1][j];
            if (target->animal == nullptr) {
                targets.push_back(target);
            }
        }
        // Move right
        if (j != size - 1) {
            Cell *target = &_field[i][j + 1];
            if (target->animal == nullptr) {
                targets.push_back(target);
            }
        }
        if (targets.empty()) return; // No moves

        int i1 = (int) (dist0to1(mt) * targets.size());

        Cell *target = targets[i1];
        target->animal = source.animal;
        source.animal = nullptr;
        target->animal->tiredOfMove();

        if (target->animal->pregnancyTimer == 1) {
            target->animal->pregnancyTimer = 0;
            if (target->animal->isPredator) {
                source.animal = new Wolf(dist0to1(mt) < 0.5);
                birthsWolf++;
            } else {
                source.animal = new Sheep(dist0to1(mt) < 0.5);
                birthsSheep++;
            }
        }
    }

    void death(Cell &cell) {
        if (cell.animal == nullptr) return;
        if (cell.animal->energy > 0 && cell.animal->age < cell.animal->deathAge) return;

//        delete cell.animal;
        cell.animal = nullptr;
        deaths++;
    }

    void grassDistribution(Cell &cell1, Cell &cell2) {
        if (cell1.hasGrass == cell2.hasGrass) return;

        if (dist0to1(mt) < grassSplitChance) {
            cell1.hasGrass = true;
            cell2.hasGrass = true;
        }
    }

    void hunt(Cell &cell1, Cell &cell2) {
        if (cell1.animal == nullptr || cell2.animal == nullptr) return;
        if (cell1.animal->isPredator == cell2.animal->isPredator) return;

        Cell &predator = cell1.animal->isPredator ? cell1 : cell2;
        Cell &victim = cell1.animal->isPredator ? cell2 : cell1;

        if (predator.animal->eat()) {
//            delete victim.animal;
            victim.animal = nullptr;
            kills++;
        }
    }

    static void eatGrass(Cell &cell) {
        if (cell.animal == nullptr || cell.animal->isPredator) return;
        if (cell.animal->eat()) {
            cell.hasGrass = false;
        }
    }

    void breed(Cell &cell1, Cell &cell2) {
        if (cell1.animal == nullptr || cell2.animal == nullptr) return;
        if (cell1.animal->isPredator != cell2.animal->isPredator) return; // Now impossible, but whatever
        if (cell1.animal->isMale == cell2.animal->isMale) return; // No LGBT
        if (!cell1.animal->canBreed() || !cell2.animal->canBreed()) return; // No tired and not pregnant yet

        Cell &female = cell1.animal->isMale ? cell2 : cell1;

        female.animal->pregnancyTimer = female.animal->pregnancyDuration;
        cell1.animal->tiredOfBreed();
        cell2.animal->tiredOfBreed();

        breeds++;
    }
};

void printField(const Field &field) {
    for (int i = 0; i < field.size; i++) {
        for (int j = 0; j < field.size; j++) {
            const Cell &cell = field._field[i][j];
            if (cell.hasGrass) cout << GREEN_BG << BLACK_FG;
            else cout << RESET;
            if (cell.animal != nullptr && cell.animal->pregnancyTimer != 0) cout << RED_FG;
            cout << (cell.animal != nullptr ? (cell.animal->isPredator ? " W " : " S ") : "   ");
        }
        cout << RESET << "\n";
    }
    cout << "Deaths: " << field.deaths << " Kills: " << field.kills << " Breeds: " << field.breeds << " Births: "
         << field.birthsWolf << " / " << field.birthsSheep << "\n";
    cout << field.neighbours.size() << "\n";
}

template <typename F>
void measureTime(ostream &out, F&& lambda) {
    auto start = chrono::high_resolution_clock::now();
    lambda();
    auto stop = chrono::high_resolution_clock::now();
    out << "\n"<< chrono::duration_cast<chrono::microseconds>((stop - start)).count() << "mcs\n";
}

void task6_3() {
    Field field(20, 0.05, 0.3, 1, 1);

    printField(field);

    int n = 1;
    while (true) {
        cout << "Simulate days: ";
        cin >> n;
        if (n == 0) break;

        cout << "\n\n";

        measureTime(cout, [&field, &n](){
            for (int i = 0; i < n; i++) {
                field.oneDayLater();
            }
        });

        printField(field);
    }
}
/*
grass dist0to1
wolf eat
sheep eat
animal sex
animal move

0 0 0 0
W S 0 0
0 0 0 0
0 0 0 0
 * */

#endif //FIRST_6_3_H
