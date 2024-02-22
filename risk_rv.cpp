#include "algorithm"
#include <iostream>
#include "cstdlib"
#include "vector"
#include "set"
#include "map"
#include "math.h"
#include <fstream>

using namespace std;


// ___________________________________________________________________________________


struct roll {
    vector<int> dices;
    int combinations, permutations;
    vector<float> distribution;
};


// ___________________________________________________________________________________


// class Battle {
//     private:

//     public:
//         Battle();
//         int challenge(int red_size, int blue_size, vector<int> &r);
//         int factorial(int n);
//         void print_vector(vector<int> v);
//         void saveX(vector<roll> rolls, int SIZE);
//         void saveY(vector<roll> rolls, int SIZE);    
// }

// ___________________________________________________________________________________


int challenge(int red_size, int blue_size, vector<int> &r) {
    vector<int> b(blue_size, 0);
    for (int i = 0; i < blue_size; i++) {
        b[i] = rand() % 6 + 1;
    }
    
    sort(r.begin(), r.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    int defeated = 0;
    for (int i = 0; i < blue_size; i++) {
        if (r[i] <= b[i]) {
            defeated += 1;
        }
    }

    return defeated;
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    else if (n < 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

void print_vector(vector<int> v) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}


void saveX(vector<roll> rolls, int SIZE) {
    // Sort for Random Variable X: the roll with most chances to win is the greatest
    sort(rolls.begin(), rolls.end(), [](roll a, roll b) {
        if (a.distribution[0] < b.distribution[0]) {
            return true;
        } 
        else if (a.distribution[0] == b.distribution[0]) {
            return a.distribution[1] < b.distribution[1];
        }
        
        return false;
    });

    ofstream file;
    file.open("randomVariableX.txt");
    file << "Random Variable X: the roll with most chances to win is the greatest" << endl;
    file << "Combination\tOccurrences\t\t0\t1\t2\n" << endl;
    for (roll r : rolls) {        
        file << r.dices[0];
        for (int i = 1; i < r.dices.size(); i++) {
            file << "-" << r.dices[i];
        }
        file << ":\t\t" << r.permutations << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            file << r.distribution[i] << "\t\t";
        }
        file << endl;
    }
    file.close();
}

void saveY(vector<roll> rolls, int SIZE) {
    // Sort for Random Variable Y: the roll with most chances to not lose is the greatest
    sort(rolls.begin(), rolls.end(), [](roll a, roll b) {
        if (a.distribution[2] > b.distribution[2]) {
            return true;
        } 
        
        return false;
    });


    ofstream file2;
    file2.open("randomVariableY.txt");
    file2 << "Random Variable Y: the roll with most chances to not lose is the greatest" << endl;
    file2 << "Combination\tOccurrences\t\t0\t1\t2\n" << endl;
    for (roll r : rolls) {
        file2 << r.dices[0];
        for (int i = 1; i < r.dices.size(); i++) {
            file2 << "-" << r.dices[i];
        }
        file2 << ":\t\t" << r.permutations << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            file2 << r.distribution[i] << "\t";
        }
        file2 << endl;
    }
    file2.close();
}

int main(int argv, char** argc) {
    srand(time(NULL));
    int count = 0, it,  
        SIZE, TESTS = 10000,
        red_size, blue_size;
    
    cout << "Define the battle scenario (number of red dice VS number of blue dice): ";
    cin >> red_size >> blue_size;

    SIZE = min(red_size, blue_size);
    vector<int> r(SIZE, 0), 
                dices(SIZE, 1);
    roll rr = {dices, 0, 0, vector<float>(SIZE + 1, 0)};

    int total_rolls = 0;
    for (int i = 1; i <= 6; i++) {
        total_rolls += pow(i, SIZE);
    }
    vector<roll> rolls(total_rolls, rr);

    cout << "Defeated\tPermutations\tCombinations";
    for (int i = 0; i < SIZE + 1; i++) {
        cout << "\t" << i;
    }
    cout << endl << endl;
    while (dices[0] < 7) {
        // TESTS
        vector<int> distribution(SIZE + 1, 0);
        for (int i = 0; i < TESTS; i++) {
            distribution[challenge(red_size, blue_size, dices)]++;
        }

        cout << "!";    

        // UPDATE ROLL INFORMATION
        rolls[count].dices = dices;

        cout << "!";

        // Iterar dados extras
        set<int> s;
        map<int, int> p_hash;
        vector<int> remain(red_size - SIZE, 1);
        if (remain.size() == 0) {
            p_hash.clear();
            for (auto el : dices) {
                p_hash[el]++;
            }
            for (auto el : remain) {
                p_hash[el]++;
            }

            int denominator = 1;
            for (auto el : p_hash) {
                denominator *= factorial(el.second);
            }

            rolls[count].combinations = 1;
            int c = denominator;
            rolls[count].permutations += factorial(red_size) / c;
        }
        else if (remain.size() == 1) {
            while (remain[0] <= dices[SIZE - 1]) {
                s.clear();
                for (int i = 0; i < SIZE; i++) {
                    s.insert(dices[i]);
                }
                s.insert(remain[0]);

                rolls[count].combinations++;
                rolls[count].permutations += factorial(red_size) / factorial(red_size + 1 - s.size());
                remain[0]++;
            }
        }
        else {
            while (remain[0] <= dices[SIZE - 1]) {
                // cout << remain[0] << "#" << remain[1] << " "; 
                p_hash.clear();
                for (auto el : dices) {
                    p_hash[el]++;
                }
                for (auto el : remain) {
                    p_hash[el]++;
                }

                int denominator = 1;
                for (auto el : p_hash) {
                    denominator *= factorial(el.second);
                }

                rolls[count].combinations++;
                int c = denominator;
                rolls[count].permutations += factorial(red_size) / c;

                // s.clear();
                // for (int i = 0; i < SIZE; i++) {
                //     s.insert(dices[i]);
                // }
                // for (auto el : remain) {
                //     s.insert(el);
                // }

                // rolls[count].combinations++;
                // int c = factorial(red_size) / factorial(red_size + 1 - s.size());
                // rolls[count].permutations += c;

                // cout << c << ",";

                it = red_size - SIZE - 1;
                remain[it]++;
                while ((it > 0) && (remain[it-1] < remain[it])) {
                    remain[it] = 1;
                    remain[it - 1]++;
                    it--;
                }
            }
        }

        for (int i = 0; i < SIZE + 1; i++) {
            rolls[count].distribution[i] = float(distribution[i]) / float(TESTS);
        }

        // PRINT RESULTS
        cout << dices[0];
        for (int i = 1; i < dices.size(); i++) {
            cout << "-" << dices[i];
        }
        cout << ":\t\t" << rolls[count].permutations << "\t\t" << rolls[count].combinations << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            cout << float(distribution[i]) / float(TESTS) << "\t";
        }
        cout << endl;

        count++;
        it = SIZE - 1;
        dices[it]++;
        while ((it > 0) && (dices[it-1] < dices[it])) {
            dices[it] = 1;
            dices[it - 1]++;
            it--;
        }
    }

    count = 0;
    for (roll r : rolls) {
        count += r.permutations;
    }
    cout << "Possible rolls: " << count << endl;

    // saveX(rolls, SIZE);
    // saveY(rolls, SIZE);

    return 0;

}