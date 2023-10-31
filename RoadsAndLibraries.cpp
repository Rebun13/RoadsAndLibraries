#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long connectToAll(int city, int c_road, vector<vector<int>> cities, unordered_set<int> &outHasAccess, unordered_set<vector<int>> &outConnections);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    if(c_lib < c_road) {
        return n * c_lib;
    }
    long price = 0;
    unordered_set<vector<int>> connections;
    unordered_set<int> hasLibrary;
    unordered_set<int> hasAccessToLibrary;

    // construir en 1 y conectar a todos los aledaños, Conectar puentes
    hasLibrary.insert(1);
    price += c_lib;
    price += connectToAll(1, c_road, cities, hasAccessToLibrary, connections);

    // desde 2 hasta n
    for(int city = 2; city <= n; ++city) {
        // está en hasAccess o en hasLibrary?
        if(hasLibrary.find(city) != hasLibrary.end() || hasAccessToLibrary.find(city) != hasAccessToLibrary.end()) {
            // SI -> connectar con los pueblos aledaños que no estén en hasAccess o hasLibrary. cuenta los puentes
            //price += connectToAll(city, c_road, cities, hasAccessToLibrary, connections);
            cout << "City " << city << " already connected" << endl;
        } else {
            //Construye y conecta con los pueblos aledaños. Cuenta los puentes
            hasLibrary.insert(city);
            price += c_lib;
            price += connectToAll(city, c_road, cities, hasAccessToLibrary, connections);
            cout << "City " << city << " got a new library" << endl;
        }
    }
    return price;
}

long connectToAll(int city, int c_road, vector<vector<int>> cities, unordered_set<int> &outHasAccess, unordered_set<vector<int>> &outConnections){
    long price = 0;
    vector<int> otherCities;
    // TODO: remove cityPair once the road is constructed
    for(vector<int> cityPair : cities) {
        if(cityPair.at(0) == 1) {
            if(outHasAccess.find(cityPair.at(1)) == outHasAccess.end()) {
                outHasAccess.insert(cityPair.at(1));
                outConnections.insert({1, cityPair.at(1)});
                price += c_road;
                price += connectToAll(city, c_road, cities, outHasAccess, outConnections);
            }
        } else if(cityPair.at(1) == 1) {
            if(outHasAccess.find(cityPair.at(0)) == outHasAccess.end()) {
                outHasAccess.insert(cityPair.at(0));
                outConnections.insert({1, cityPair.at(0)});
                price += c_road;
                price += connectToAll(city, c_road, cities, outHasAccess, outConnections);
            }
        }
    }
    return price;
}

int main()
{
    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        cout << result << "\n";
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
