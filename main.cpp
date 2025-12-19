// Ameen Khan
// CIS - 7 
//12/18/2025
//Final Project - UCR Medical Volunteers

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

enum Language {EN, IT, DE, BN, ZH, UR, TR, RU, LANG_COUNT};

enum Specialty { CARDIO, NEURO, ORTHO, RADIO, NEPHRO, DERMA, PULMO, SPECIAL_COUNT};

static const string LANGS[LANG_COUNT] = { "English", "Italian", "Dutch", "Bengali", "Chinese", "Urdu", "Turkish", "Russian" };
static const string SPECIALS[SPECIAL_COUNT] = { "Cardiology", "Neurology", "Orthopedics", "Radiology", "Nephrology", "Dermatology", "Pulmonology" };

struct Volunteer {
    int id;
    bool spoken_Lang[LANG_COUNT];
    Specialty specials;
};

struct Country {
    string name;
    bool langReq[LANG_COUNT];
    bool specialReq[SPECIAL_COUNT];
};

bool languageIntersect(const Volunteer& v, const Country& c) {
    for (int i = 0; i < LANG_COUNT; i++) {
        if (v.spoken_Lang[i] && c.langReq[i]) return true;
   }
    return false;
    }

bool specialtyMatch(const Volunteer& v, const Country& c) {
        return c.specialReq[v.specials];
    }
bool isMatch(const Volunteer& v, const Country& c) {
        return languageIntersect(v, c) && specialtyMatch(v, c);
    }

vector<Volunteer> buildVolunteerList(int N) {
    vector<Volunteer> V;
    V.reserve(N);

    for (int k = 0; k < N; k++) {
        Volunteer v;
        v.id = k + 1;

    for (int i = 0; i < LANG_COUNT; i++) v.spoken_Lang[i] = false;

    int L1 = (k * 3 + 1) % LANG_COUNT;
    int L2 = (k * 5 + 3) % LANG_COUNT;
    v.spoken_Lang[L1] = true;
    v.spoken_Lang[L2] = true;

    v.specials = (Specialty)(k % SPECIAL_COUNT);

    V.push_back(v);
    }
  return V;
}

vector<Country> buildCountryList() {
     vector<Country> C(10);

    auto clearCountry = [&](Country& c) {
         for (int i = 0; i < LANG_COUNT; i++) c.langReq[i] = false;
         for (int i = 0; i < SPECIAL_COUNT; i++) c.specialReq[i] = false;
    };
    C[0].name = "Italy"; clearCountry(C[0]); 
    C[0].langReq[IT] = true; C[0].langReq[EN] = true;
    C[0].specialReq[CARDIO] = true; C[0].specialReq[NEURO] = true;

    C[1].name = "Germany"; clearCountry(C[1]);
    C[1].langReq[DE] = true; C[1].langReq[EN] = true;
    C[1].specialReq[ORTHO] = true; C[1].specialReq[RADIO] = true;

    C[2].name = "Bangladesh"; clearCountry(C[2]);
    C[2].langReq[BN] = true; C[2].langReq[EN] = true;
    C[2].specialReq[NEPHRO] = true; C[2].specialReq[DERMA] = true;

    C[3].name = "China"; clearCountry(C[3]);
    C[3].langReq[ZH] = true; C[3].langReq[EN] = true;
    C[3].specialReq[PULMO] = true; C[3].specialReq[CARDIO] = true;

    C[4].name = "Pakistan"; clearCountry(C[4]); 
    C[4].langReq[UR] = true; C[4].langReq[EN] = true;
    C[4].specialReq[NEURO] = true; C[4].specialReq[ORTHO] = true;

     C[5].name = "Turkey"; clearCountry(C[5]);
     C[5].langReq[TR] = true; C[5].langReq[EN] = true;
     C[5].specialReq[RADIO] = true; C[5].specialReq[NEPHRO] = true;

     C[6].name = "Russia"; clearCountry(C[6]);
     C[6].langReq[RU] = true; C[6].langReq[EN] = true;
     C[6].specialReq[DERMA] = true; C[6].specialReq[PULMO] = true;

     C[7].name = "India"; clearCountry(C[7]);
     C[7].langReq[BN] = true; C[7].langReq[EN] = true;
     C[7].specialReq[CARDIO] = true; C[7].specialReq[NEURO] = true;

     C[8].name = "Japan"; clearCountry(C[8]);
     C[8].langReq[EN] = true;
     C[8].specialReq[ORTHO] = true; C[8].specialReq[RADIO] = true;

     C[9].name = "Egypt"; clearCountry(C[9]);
     C[9].langReq[UR] = true; C[9].langReq[EN] = true;
     C[9].specialReq[NEPHRO] = true; C[9].specialReq[DERMA] = true;

     return C;

}

int main() {
    const int N = 100;
    const int M = 10;

    auto V = buildVolunteerList(N);
    auto C = buildCountryList();

    int relations = 0;
    vector<int> countryDeg(M, 0);
    vector<int> volunteerDeg(N, 0);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (isMatch(V[i], C[j])) {
            relations++;
            countryDeg[j]++;
            volunteerDeg[i]++;
        }
      }
    }

int eligibleVolunteers = 0;
for (int i = 0; i < N; i++) {
    if (volunteerDeg[i] > 0) eligibleVolunteers++;
}
cout << fixed << setprecision(2);
cout << "Project: UCR Medical Volunteers\n";
cout << "Volunteers: " << N << "\n";
cout << "Countries: " << M << "\n";

cout << "Total Relations: " << relations << "\n";
cout << "Eligible Volunteers: " << eligibleVolunteers << "\n";

double Prob = (double)eligibleVolunteers / N;
cout << "Probability of Matching: " << (Prob * 100) << "%\n\n";
cout << "Match probablity by country:\n";
     for (int j = 0; j < M; j++) {
         double p = (double)countryDeg[j] / N;
         cout << " _ " << C[j].name << ": " << (p * 100) << "%\n";
     }
cout << "Finished.\n";

    return 0;
}
