#include "algorithm"
#include <iostream>
#include "cstdlib"
#include "vector"
#include "set"
#include <fstream>

using namespace std;

struct roll {
    int i, ii;
    int chance;
    vector<float> distribution;
};

int challenge(int size, vector<int> &r) {
    vector<int> b(size, 0);
    for (int i = 0; i < size; i++) {
        b[i] = rand() % 6 + 1;
    }
    
    sort(r.begin(), r.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    int defeated = 0;
    for (int i = 0; i < size; i++) {
        // cout << r[i] << " vs " << b[i] << "\n";
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
        file << r.i << "-" << r.ii << ":\t\t" << r.chance << "\t\t";
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
        file2 << r.i << "-" << r.ii << ":\t\t" << r.chance << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            file2 << r.distribution[i] << "\t";
        }
        file2 << endl;
    }
    file2.close();
}

int main(int argv, char** argc) {
    srand(time(NULL));
    int i = 1, ii = 1, 
        SIZE = 2, TESTS = 10000;
    vector<int> r(SIZE, 0);

    roll rr = {0, 0, 0, vector<float>(SIZE + 1, 0)};
    vector<roll> rolls(21, rr);

    int count = 0;
    cout << "Defeated\tOccurrences\t0\t1\t2\n" << endl;
    while (i < 7) {
        r[0] = i; r[1] = ii;
        
        // TESTS
        vector<int> distribution(SIZE + 1, 0);
        for (int i = 0; i < TESTS; i++) {
            distribution[challenge(SIZE, r)]++;
        }

        // UPDATE ROLL INFORMATION
        rolls[count].i = i;
        rolls[count].ii = ii;
        set<int> s;
        for (int iii = 1; iii <= ii; iii++) {
            s.clear();
            s.insert(i);
            s.insert(ii);
            s.insert(iii);
            rolls[count].chance += 6 / factorial(4-s.size());
        }

        for (int i = 0; i < SIZE + 1; i++) {
            rolls[count].distribution[i] = float(distribution[i]) / float(TESTS);
        }

        // PRINT RESULTS
        cout << i << "-" << ii << ":\t\t" << rolls[count].chance << "\t\t";
        for (int i = 0; i < SIZE + 1; i++) {
            cout << float(distribution[i]) / float(TESTS) << "\t";
        }
        cout << endl;

        count++;
        ii++;
        if (i < ii) {
            ii = 1;
            i++;
        }
    }

    count = 0;
    for (roll r : rolls) {
        count += r.chance;
    }
    cout << "Possible rolls: " << count << endl;

    saveX(rolls, SIZE);
    saveY(rolls, SIZE);

    return 0;

}