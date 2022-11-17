//
// Created by sejapoe on 10/30/22.
//
// 101. Модифицированный
// Есть волки и овцы. Х встретил Y значит, что они оказались в соседних клетках.
// У животных есть энергия, которую они тратят на передвижение и размножение.
// Если волк встречает овцу, он съедает её, пополняя свой запас энергии.
// Если животное встречает сородича другого пола, самка не беременна и энергии хватает у обоих, то они размножаются - самка беременеет.
// Овцы едят траву из-под ног. Трава восстанавливается сама по себе.
// Когда срок беременности подходит к концу, животное рожает, когда двигается, оставляя детёныша за собой.

#ifndef FIRST_6_3_H
#define FIRST_6_3_H

#include <chrono>
#include <thread>
#include <random>
#include <ostream>

struct AnimalProps {
    double population;
    int maxEnergy;
    int energyByFood;
    int deathAge;
    int pregnancyDuration;

    AnimalProps(const double population, const int maxEnergy, const int energyByFood,
                const int deathAge, const int pregnancyDuration)
            : maxEnergy(maxEnergy), energyByFood(energyByFood),
              deathAge(deathAge), pregnancyDuration(pregnancyDuration), population(population) {}

    AnimalProps(mt19937 &mt) {
        std::uniform_real_distribution<double> dist0to1{0.0, 1.0};
        std::uniform_int_distribution<int> dist1to100{1, 100};

        population = dist0to1(mt);
        maxEnergy = dist1to100(mt);

        std::uniform_int_distribution<int> dist1toMax(1, maxEnergy + 1);

        energyByFood = dist1toMax(mt);
        deathAge = dist1to100(mt);

        std::uniform_int_distribution<int> dist1toDeath(1, deathAge / 2 + 2);

        pregnancyDuration = dist1toDeath(mt);
    }

    friend ostream &operator<<(ostream &os, const AnimalProps &props) {
        os << props.population << "," << props.maxEnergy << ","
           << props.energyByFood << "," << props.deathAge << ","
           << props.pregnancyDuration;
        return os;
    }
};

struct FieldData {
    int wolfCount;
    int sheepCount;
};

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

    Wolf(bool isMale, AnimalProps const &animalProps)
            : Animal(isMale, animalProps.maxEnergy, animalProps.energyByFood, true, animalProps.pregnancyDuration,
                     animalProps.deathAge) {}
};

struct Sheep : Animal {
    explicit Sheep(bool isMale) : Animal(isMale, 30, 10, false, 2, 10) {}

    Sheep(bool isMale, AnimalProps const &animalProps)
            : Animal(isMale, animalProps.maxEnergy, animalProps.energyByFood, false, animalProps.pregnancyDuration,
                     animalProps.deathAge) {}
};

struct Cell {
    Animal *animal;
    bool hasGrass;

    explicit Cell() : animal(nullptr), hasGrass(false) {}

    Cell(Animal *animal, bool hasGrass) : animal(animal), hasGrass(hasGrass) {}

    [[nodiscard]] Cell copy() const {
        return {animal == nullptr ? nullptr : new Animal(*animal), hasGrass};
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

    FieldData data{0, 0};

    int deaths{0};
    int breeds{0};
    int kills{0};
    int birthsWolf{0};
    int birthsSheep{0};

    int day{0};

    Field(int size, AnimalProps const &wolfProps,
          AnimalProps const &sheepProps,
          double grassPopulation,
          double grassSplitChance) : size(size), grassSplitChance(grassSplitChance),
                                     _field(size, vector<Cell>(size)) {
        if (wolfProps.population + sheepProps.population > 1.0)
            throw invalid_argument("wolf and sheep population together must be lesser than 1.0");

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (dist0to1(mt) < grassPopulation) {
                    _field[i][j].hasGrass = true;
                }

                double animalPicker = dist0to1(mt);
                if (animalPicker < sheepProps.population) {
                    _field[i][j].animal = new Sheep(dist0to1(mt) < 0.5, sheepProps);
                    data.sheepCount++;
                } else if (animalPicker - sheepProps.population < wolfProps.population) {
                    _field[i][j].animal = new Wolf(dist0to1(mt) < 0.5, wolfProps);
                    data.wolfCount++;
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
                data.wolfCount++;
            } else {
                source.animal = new Sheep(dist0to1(mt) < 0.5);
                data.sheepCount++;
            }
        }
    }

    void death(Cell &cell) {
        if (cell.animal == nullptr) return;
        if (cell.animal->energy > 0 && cell.animal->age < cell.animal->deathAge) return;

//        delete cell.animal;
        if (cell.animal->isPredator) {
            data.wolfCount--;
        } else {
            data.sheepCount--;
        }
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
            data.sheepCount--;
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

template<typename F>
void measureTime(ostream &out, F &&lambda) {
    auto start = chrono::high_resolution_clock::now();
    lambda();
    auto stop = chrono::high_resolution_clock::now();
    out << "\n" << chrono::duration_cast<chrono::microseconds>((stop - start)).count() << "mcs\n";
}

void task6_3() {
    AnimalProps wolfProps(0.05, 50, 20, 30, 1);
    AnimalProps sheepProps(0.3, 30, 10, 10, 2);
    Field field(20, wolfProps, sheepProps, 1, 1);

    printField(field);

    int n = 1;
    while (true) {
        cout << "Simulate days: ";
        n = enter(anyInt);
        if (n <= 0) break;

        cout << "\n\n";

        measureTime(cout, [&field, &n]() {
            for (int i = 0; i < n; i++) {
                field.oneDayLater();
            }
        });

        printField(field);
    }
}

void bar(const AnimalProps &wolfProps, const AnimalProps &sheepProps, int &sheepDoomsday, int &wolfDoomsday,
         const int &size) {
    sheepDoomsday = -1;
    wolfDoomsday = -1;
    Field field(20, wolfProps, sheepProps, 1, 1);
    while (field.day < 1000) {
        if (field.data.sheepCount <= 0 && sheepDoomsday == -1) {
            sheepDoomsday = field.day;
        }

        if (field.data.wolfCount <= 0) {
            wolfDoomsday = field.day;
            break;
        }

        for (int j = 0; j < 10; j++) {
            field.oneDayLater();
        }
    }
}

void findOptimal() {
    ofstream file0("../life_base");
    ofstream file1("../life_normally");
    ofstream file2("../life_chad");
    ofstream file("../life_data.csv");

    file <<
         "size,"
         "wolf_population,wolf_max_energy,wolf_energy_by_food,wolf_death_age,wolf_pregnancy_duration,"
         "sheep_population,sheep_max_energy,sheep_energy_by_food,sheep_death_age,sheep_pregnancy_duration,"
         "minuses,wolf_doomsday,"
         "sheep_doomsday\n";

    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist10to50{10, 50};

    for (int i = 0; i < 1000; i++) {
        AnimalProps wolfProps(0.1, 20, 10, 70, 15);
        AnimalProps sheepProps(0.6, 70, 20, 60, 5);
        if (wolfProps.population + sheepProps.population > 1.0) {
            i--;
            continue;
        }
        int size = 10 + i / 100 * 10;
        int tries = 1;

        int sheepT = 0;
        int wolfT = 0;
        int minuses = 0;

        int sheepDoomsday;
        int wolfDoomsday;
        for (int j = 0; j < tries; j++) {
            bar(wolfProps, sheepProps, sheepDoomsday, wolfDoomsday, size);
            sheepT += sheepDoomsday;
            wolfT += wolfDoomsday;
            if (wolfDoomsday == -1) minuses++;
        }

        file << size << "," << wolfProps << "," << sheepProps << "," << minuses << "," << wolfDoomsday << ","
             << sheepDoomsday << "\n";

        (minuses == tries ? file2 : (minuses >= 1 ? file1 : file0))
                << "Wolf: " << wolfProps << "\n"
                << "Sheep: " << sheepProps << "\n"
                << "Size: " << size << "\n"
                << "Minuses: " << minuses << "\n"
                << "Wolf doomsday: " << wolfT / tries
                << "\nSheep doomsday: " << sheepT / tries << "\n\n\n";
    }
}

void testThis() {
    ofstream file("../life2");
    AnimalProps wolfProps(0.37, 31, 16, 75, 37);
    AnimalProps sheepProps(0.35, 45, 9, 94, 1);
    for (int i = 0; i < 1000; i++) {
        int sheepDoomsday;
        int wolfDoomsday;
        bar(wolfProps, sheepProps, sheepDoomsday, wolfDoomsday, 0);

        file << "Wolf: " << wolfProps << "\n";
        file << "Sheep: " << sheepProps << "\n";
        file << "Wolf doomsday: " << wolfDoomsday << " Sheep doomsday: " << sheepDoomsday << "\n\n\n";
    }
}
/*
Wolf: population: 0.374111 maxEnergy: 31 energyByFood: 16 deathAge: 75 pregnancyDuration: 37
Sheep: population: 0.351576 maxEnergy: 46 energyByFood: 9 deathAge: 94 pregnancyDuration: 1
 *
 */
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
