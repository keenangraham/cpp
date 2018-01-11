#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

template<class T>
void print(T it, bool sep=false){
    for (auto c: it){
        cout << c;
        if (sep){
            cout << endl;
        }
    }
    if (!sep){
    cout << endl;
    }
}

void print_matching_index(vector<int>& matching, string text){
    cout << "0: " << text << endl;
    for (auto n : matching){
        cout << n << ": ";
        cout << text.substr(n, text.size()) << endl;
    }
}

vector<int> index_of_match(vector<int> z_score, int pattern_size){
    vector<int> results;
    for (int i = 0; i < z_score.size(); i++){
        if (z_score[i] == pattern_size){
            results.push_back(i);
        }
    }
    return results;
}


// Adapted from https://gist.github.com/prasoon2211/c37b18de408a85f24cc7
vector<int> z_score(string combined){
    int full_length = combined.size();
    vector<int> z(full_length);
    z[0] = full_length;
    int rt = 0;
    int lt = 0;
    for (int k = 1; k < full_length; k++){
        if (k > rt){
            int n = 0;
            while (n + k < full_length && combined[n] == combined[n+k]){
                n++;
            }
            z[k] = n;
            if (n > 0){
                lt = k;
                rt = k + n - 1;
            }
        } else {
            int p = k - lt;
            int right_part_len = rt - k + 1;
            if (z[p] < right_part_len){
                z[k] = z[p];
            } else {
                int i = rt + 1;
                while (i < full_length && combined[i] == combined[i - k]){
                    i++;
                }
                z[k] = i - k;
                lt = k;
                rt = i - 1;
            }
        }
    }
    return z;
}

void find_pattern(string pattern, string text){
    string combined = pattern + "$" + text;
    vector<int> matching = index_of_match(z_score(combined), pattern.size());
    print_matching_index(matching, combined);
}


int main(){
    string pattern = "abc";
    string text = "zabcdeabcabcabcabc";
    find_pattern(pattern, text);
}

