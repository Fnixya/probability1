#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

int tirada(int d_rojos, int d_azules, int lados) {
  vector<int> t_rojos, t_azules;      // tiradas de cada dado
  for (int i = 0; i < d_rojos; i++) { // rojo tira sus dados
    t_rojos.push_back(rand() % lados + 1);
  }
  for (int i = 0; i < d_azules; i++) { // azul tira sus dados
    t_azules.push_back(rand() % lados + 1);
  }
  int perdidas_r = 0;
  sort(t_rojos.begin(), t_rojos.end());
  reverse(t_rojos.begin(), t_rojos.end());
  sort(t_azules.begin(), t_azules.end());
  reverse(t_azules.begin(), t_azules.end());
  // comparaciones y muerte
  for (int i = 0; i < min(d_rojos, d_azules); i++) {
    if (!(t_rojos[i] > t_azules[i])) {
      perdidas_r++;
    }
  }
  return perdidas_r;
}

int main() {
  srand(time(NULL));
  int d_rojos, d_azules, lados = 6, TESTS = 1000000;

  cout << "dados rojos vs dados azules\n";
  cin >> d_rojos >> d_azules;
  cout << "calculating... \n";

  int mn = min(d_rojos, d_azules);
  vector<int> distribution(min(d_rojos, d_azules) + 1, 0);

  for (int i = 0; i < TESTS; i++) {
    distribution[tirada(d_rojos, d_azules, lados)]++;
  }

  for (int i = 0; i < mn + 1; i++) {
    cout << i << " bajas rojas: " << float(distribution[i]) / float(TESTS)
         << "\n";
  }
}
