#include "algorithm"
#include <iostream>
#include <iomanip>
#include "cstdlib"
#include "vector"
#include "set"
#include "map"
#include "math.h"
#include <fstream>
#include <string>

using namespace std;


// ___________________________________________________________________________________


struct roll {
    vector<int> dices;
    int combinations, permutations;
    vector<float> distribution;
};


// Helpers ___________________________________________________________________________________

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    else if (n < 0) {
        return 1;
    }
    return n * factorial(n - 1);
}


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

void print_vector(vector<int> v) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

// 
int permute(int red_size, int blue_size, vector<int> &dices) {
    int SIZE = min(red_size, blue_size);

    // set<int> s;
    map<int, int> p_hash;
    
    // vector<int> remain(SIZE, 1);
    vector<int> remain(0, 1);
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

        // rolls[count].combinations = 1;
        // int c = denominator;
        // rolls[count].permutations += factorial(red_size) / c;

        int c = denominator;
        return factorial(blue_size) / c;
    }
    else if (remain.size() == 1) {
        int permutations = 0;
        while (remain[0] <= dices[SIZE - 1]) {
            // s.clear();
            // for (int i = 0; i < SIZE; i++) {
            //     s.insert(dices[i]);
            // }
            // s.insert(remain[0]);
            
            p_hash.clear();
            for (auto el : dices) {
                p_hash[el]++;
            }
            p_hash[remain[0]]++;

            // rolls[count].combinations++;
            // rolls[count].permutations += factorial(red_size) / factorial(red_size + 1 - s.size());

            int denominator = 1;
            for (auto el : p_hash) {
                denominator *= factorial(el.second);
            }

            permutations += factorial(red_size) / denominator;
            remain[0]++;
        }
        return permutations;
    }
    else {
        int permutations = 0;
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

            // rolls[count].combinations++;
            // int c = denominator;
            // rolls[count].permutations += factorial(red_size) / c;

            permutations += factorial(red_size) / denominator;
        }
        return permutations;
    }   
}


void get_percentage(int red_size, int blue_size, vector<int> &red_dices, vector<int> &distribution) {
    vector<int> blue_dices(blue_size, 1);
    while (blue_dices[0] < 7) {
        // 1 Obtener combinacion de dados : blue_dices
        // 2 Obtener numero de permutaciones posibles
        // 3 Determinar cuantos soldados pierdes
        // 4 Repetir

        // 2
        int permutations = permute(red_size, blue_size, blue_dices);

        // 3
        int defeated = 0;
        for (int i = 0; i < blue_size; i++) {
            if (red_dices[i] <= blue_dices[i]) {
                defeated += 1;
            }
        }
        distribution[defeated] += permutations;

        // 1
        int it = blue_size - 1;
        blue_dices[it]++;
        while ((it > 0) && (blue_dices[it-1] < blue_dices[it])) {
            blue_dices[it] = 1;
            blue_dices[it - 1]++;
            it--;
        }
    }
    return;
}

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

vector<roll> simulate(int red_size, int blue_size, int TESTS) {
    int count = 0, it,  
        SIZE;

    SIZE = min(red_size, blue_size);

    vector<int> r(SIZE, 0), 
                dices(SIZE, 1);
    roll rr = {dices, 0, 0, vector<float>(SIZE + 1, 0)};

    // Define total number of possible relevant rolls
    int total_rolls = 0;
    vector<roll> rolls;

    cout << "Defeated\tPermutations\tCombinations";
    for (int i = 0; i < SIZE + 1; i++) {
        cout << "\t" << i;
    }
    cout << endl << endl;
    while (dices[0] < 7) {
        // TESTS
        vector<int> distribution(SIZE + 1, 0);

        // WINCHANCE COMPUTED WITH METHANPHETAMINE
        get_percentage(red_size, blue_size, dices, distribution);

        // WINCHANCE COMPUTED WITH COMPUTATIONS
        // for (int i = 0; i < TESTS; i++) {
        //     distribution[challenge(red_size, blue_size, dices)]++;
        // }

        // UPDATE ROLL INFORMATION
        rolls.push_back(rr);
        rolls[count].dices = dices;

        // Iterar dados extras
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


                it = red_size - SIZE - 1;
                remain[it]++;
                if (remain.size() == 1)
                    continue;

                while ((it > 0) && (remain[it-1] < remain[it])) {
                    remain[it] = 1;
                    remain[it - 1]++;
                    it--;
                }
            }
        }

        for (int i = 0; i < SIZE + 1; i++) {
            rolls[count].distribution[i] = float(distribution[i]) / pow(6, blue_size) ;
        }

        // PRINT RESULTS
        cout << dices[0];
        // for (int i = 1; i < dices.size(); i++) {
        //     cout << "-" << dices[i];
        // }
        // cout << ":\t\t" << rolls[count].permutations << "\t\t" << rolls[count].combinations << "\t\t";
        // for (int i = 0; i < SIZE + 1; i++) {
        //     // cout << float(distribution[i]) / float(TESTS) << "\t";
        //     cout << distribution[i] / pow(6, blue_size) << "\t";
        // }
        // cout << endl;

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

    return rolls;
}

void genRdata(vector<roll> rolls, int SIZE, char type, int r_size, int b_size) {
    string file_name = "data/rv" + string(1, type) + "/rv" + string(1, type) + "data" + to_string(r_size) + "-" + to_string(b_size) + ".txt";
    cout << "Saving in: " << file_name << endl;
    
    switch (type) {
        case 'Y': {
            sort(rolls.begin(), rolls.end(), [](roll a, roll b) {
                if (a.distribution[0] < b.distribution[0]) {
                    return true;
                } 
                else if (a.distribution[0] == b.distribution[0]) {
                    return a.distribution[1] < b.distribution[1];
                }
                
                return false;
            });

            break;
        }
        case 'Z': {
            sort(rolls.begin(), rolls.end(), [](roll a, roll b) {
                if (a.distribution[2] > b.distribution[2]) {
                    return true;
                } 
                
                return false;
            });

            break;
        }
    }



    ofstream file;
    file.open(file_name);
    file << "x <- c(";

    // file << "\t\t\t" << "Sample\t\t" << "perm..\t" << "comb..\t" << "cum..\t" << "0\t1\t2\n" << endl;
    int count = 0;
    for (roll r : rolls) {        
        file << ", " << count++;  
    }
    file << ")" << endl;
    
    int cummulation = 0;
    file << "cumsumrv" << type << r_size << b_size << " <- c(";
    for (roll r : rolls) {    
        cummulation += r.permutations;    
     
        file << ", " << cummulation;  
    }
    file << ")" << endl;

    file << "pmfrv" << type << r_size << b_size << " <- c(";
    float mean = 0;
    count = 0;
    for (roll r : rolls) {        
        mean += (float)count++ * (float)r.permutations;
        file << ", " << r.permutations;
    }
    file << ")" << endl;
    
    file << "expectation <- " << mean / (float)cummulation << endl; 

    file << "winChancerv" << type << r_size << b_size << " <- c(";

    for (roll r : rolls) {         
        file << ", " << r.distribution[0];  
    }
    file << ")" << endl
        << "loseChancerv" << type << r_size << b_size << " <- c(";

    for (roll r : rolls) {    
        file << ", " << r.distribution[b_size];  
    }
    file << ")" << endl;
    
    // file << "xx <- c(";
    // count = 0;
    // for (roll r : rolls) {    
    //     for (int i = 0; i < r.permutations; i++) {
    //         file << ", " << count;
    //     }
    //     count ++;  
    // }
    // file << ")" << endl;

    file << "battle_out_distribution <- c(";
    vector<float> b_out_dist(b_size + 1, 0);
    for (roll r : rolls) {   
        for (int i = 0; i < b_size + 1; i++) {
            b_out_dist[i] += r.distribution[i] * r.permutations;
        }
    }
    for (int i = 0; i < b_size + 1; i++) {
        file << ", " << (float)b_out_dist[i] / (float)cummulation;
    }
    file << ")" << endl;

    file.close();
}


void saveX(vector<roll> rolls, int SIZE) {
    // Sort for Random Variable X: the roll with most chances to win is the greatest
    ofstream file;
    file.open("randomVariableX.txt");
    file << "Random Variable X: the rolls are sorted as a vector" << endl;
    file << "\t\t\t" << "Sample\t\t" << "perm..\t" << "comb..\t" << "cum..\t" << "0\t1\t2\n" << endl;

    int count = 0, cummulation = 0;
    for (roll r : rolls) {        
        file << count++ << " >>\t\t" << r.dices[0];
        for (int i = 1; i < r.dices.size(); i++) {
            file << "-" << r.dices[i];
        }

        cummulation += r.permutations;
        file << ":\t\t" << r.permutations << "\t\t" << r.combinations << "\t\t" << cummulation << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            file << r.distribution[i] << "\t\t";
        }
        file << endl;
    }

    file << endl << "Total possible rolls: " << cummulation << endl;

    file.close();
}


void saveY(vector<roll> rolls, int SIZE) {
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
    file.open("randomVariableY.txt");
    file << "Random Variable Y: the roll with most chances to win is the greatest" << endl;
    file << "Combination\tOccurrences\t\t0\t1\t2\n" << endl;
    for (roll r : rolls) {        
        file << r.dices[0];
        for (int i = 1; i < r.dices.size(); i++) {
            file << "-" << r.dices[i];
        }
        file << ":\t\t" << r.permutations << "\t\t" << r.combinations << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            file << r.distribution[i] << "\t\t";
        }
        file << endl;
    }
    file.close();
}

void saveZ(vector<roll> rolls, int SIZE) {
    // Sort for Random Variable Y: the roll with most chances to not lose is the greatest
    sort(rolls.begin(), rolls.end(), [](roll a, roll b) {
        if (a.distribution[2] > b.distribution[2]) {
            return true;
        } 
        
        return false;
    });


    ofstream file2;
    file2.open("randomVariableZ.txt");
    file2 << "Random Variable Z: the roll with most chances to not lose is the greatest" << endl;
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
    
    
    cout << fixed << setprecision(4);
    cout << "Define the battle scenario (number of red dice VS number of blue dice): ";
    cin >> red_size >> blue_size;
    
    while((blue_size != 0) || (red_size != 0)) {
        if ((red_size < blue_size) || (red_size < 1) || (blue_size < 1)) {
            cout << "Invalid input" << endl;
            cout << "Define the battle scenario (number of red dice VS number of blue dice): ";
            cin >> red_size >> blue_size;
            continue;
        }

        vector<roll> rolls = simulate(red_size, blue_size, TESTS);

        // saveX(rolls, blue_size);
        // // saveY(rolls, SIZE);
        // // saveZ(rolls, SIZE);

        genRdata(rolls, blue_size, 'X', red_size, blue_size);
        // genRdata(rolls, blue_size, 'Y', red_size, blue_size);
        // genRdata(rolls, SIZE, 'Z', red_size, blue_size);
        
        cout << "Define the battle scenario (number of red dice VS number of blue dice): ";
        cin >> red_size >> blue_size;
    }

    return 0;

}