#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <iterator>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long connectToAll(int city, int c_road, vector<vector<int>> cities, unordered_set<int> &outHasAccess);

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
    unordered_set<int> hasAccessToLibrary;

    hasAccessToLibrary.insert(1);
    price += c_lib;
    price += connectToAll(1, c_road, cities, hasAccessToLibrary);

    for(int city = 2; city <= n; ++city) {
        if(hasAccessToLibrary.find(city) == hasAccessToLibrary.end()) {
            cout << "New library in " << city << endl;
            hasAccessToLibrary.insert(city);
            price += c_lib;
            price += connectToAll(city, c_road, cities, hasAccessToLibrary);
        }
    }
    return price;
}

long connectToAll(int city, int c_road, vector<vector<int>> cities, unordered_set<int> &outHasAccess){
    long price = 0;
    for(auto iter = cities.cbegin(); iter != cities.cend(); ++iter) {
        int cityA = iter->at(0);
        int cityB = iter->at(1);
        if(cityA == city) {
            if(outHasAccess.find(cityB) == outHasAccess.end()) {
                cout << "City " << cityB << " got access from " << city << endl;
                outHasAccess.insert(cityB);
                price += c_road;
                cout << "Price: " << price << endl;
                cities.erase(iter--);
                price += connectToAll(cityB, c_road, cities, outHasAccess);
            }
        } else if(cityB == city) {
            if(outHasAccess.find(cityA) == outHasAccess.end()) {
                cout << "City " << cityA << " got access from " << city << endl;
                outHasAccess.insert(cityA);
                price += c_road;
                cout << "Price: " << price << endl;
                cities.erase(iter--);
                price += connectToAll(cityA, c_road, cities, outHasAccess);
            }
        }
    }
    return price;
}

int main()
{
    string q_temp;

    ifstream input ("in.txt");
    if(!input.is_open()) return 0;

    getline(input, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(input, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(input, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);
        
        cout << result << "\n";
    }
    input.close();

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
