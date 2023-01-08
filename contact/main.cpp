//
//  main.cpp
//  contact
//
//  Created by Gary Chen on 12/29/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
struct result{
    string number = "";
    int count = 0;
    int size = 0;
    int digit = 0;
    int info[3];
    void stuff(string a, int ct, int siz, int dig){
        number = a;
        count = ct;
        size = siz;
        digit = dig;
        info[0] = count;
        info[1] = size;
        info[2] = digit;
    }
};


void swap(vector <result> & source, int from, int to){
    result temp;
    temp = source[from];
    source[from] = source[to];
    source[to] = temp;
}
void basic_sorting(vector <result> & res, int arg, int from, int to){
    int max = 0;
    int indicator = 0;
    int pointer = 0;
    if(to - from == 1 && res.size()!=1){
        if(res[from].info[arg] < res[to].info[arg]){
            swap(res, from, to);
            
        }
    }
    else if(to != from + 1){
        for(int i = from; i < to; i++){
            indicator = 0;
            max = 0;
            pointer = 0;
            for(int x = i; x < to; x++){
                if(res[x].info[arg] > max ){
                    max = res[x].info[arg];
                    pointer = x;
                    indicator = 1;
                }
                else if (res[x].info[arg] != 0){
                    indicator = 1;
                }
            }
            if(indicator == 0){
                break;
            }
            swap(res, pointer, i);
        }
    }
}
void sorting(vector<result> & res, int N){
    basic_sorting(res, 0, 0 ,res.size());
    vector <vector<result>> solution;
    int temp = 0;
    int stunt = 0;
    int indicator = res[0].count;
    vector <result> temp2;
    while(temp < N && stunt < res.size()){
        if(indicator != res[stunt].count){
            solution.push_back(temp2);
            temp2.clear();
            temp++;
            indicator = res[stunt].count;
        }
        temp2.push_back(res[stunt]);
        stunt++;
    }
    int start;
    int end;
    for(int i = 0; i < solution.size(); i++){
        basic_sorting(solution[i], 2, 0, solution[i].size());
        cout << endl;
        cout << solution[i][0].count << endl;
        start = 0;
        for(int x = 0; x <= solution[i].size() - 1; x++){
            end = x;
            if(solution[i][x].digit !=  solution[i][x+1].digit){
                basic_sorting(solution[i], 1, start, end);
                start = x + 1;
            }
        }
        cout << solution[i][0].number;
        for(int x = 1; x < solution[i].size() ; x++){
            cout << " " << solution[i][x].number;
        }
    }
}
string base_convert(int number, int max_digit){
    string result;
    int max = 1;
    for(int i = 1; i < max_digit; i++){
        max*=2;
    }
    while(max > 0){
        if(number >= max){
            result.push_back('1');
            number-=max;
        }
        else{
            result.push_back('0');
        }
        max/=2;
    }
    return result;
}

vector <string> generator(int digits){
    vector <string>results;
    int total = 1;
    string number;
    for(int i = 0; i < digits; i++){
        total *=2;
    }
    for(int x = 0; x < total; x++){
        results.push_back(base_convert(x, digits));
    }
    return results;
}
bool check_identical(string signal, string target, int start, int length){
    bool result = true;
    for(int i = 0; i < length; i ++){
        if(signal[start + i] != target[i]){
            result = false;
        }
    }
    
    return result;
}


int main() {
    int min_length;
    int max_length;
    int N;
    int stunt = 1;
    vector <vector <string>> numbers;
    vector <vector <int>> counts;
    string signal;
    fstream input;
    input.open("/Users/gary/Desktop/Miscellaneous/contact/contact/input.txt");
    input >> min_length;
    input >> max_length;
    input >> N;
    input >> signal;
    for(int i = 0; i < min_length; i++){
        stunt*=2;
    }
    int stunt2 = stunt;
    for(int i = min_length; i <= max_length; i++){
        vector <int> temporary(stunt2, 0);
        counts.push_back(temporary);
        stunt2*=2;
        
    }
    int stunt3 = stunt;
    for(int i = min_length; i <= max_length; i++){
        numbers.push_back(generator(i));
        for(int x = 0; x <= signal.length() - i; x++){
            for(int y = 0; y < stunt3; y++){
                if(check_identical(signal, numbers[i-min_length][y], x, i)){
                    counts[i-min_length][y]+=1;
                }
            }
        }
        stunt3 *= 2;
    }
    int temp = stunt;
    result temp2;
    vector <result> res;
    for(int i = 0; i <= max_length - min_length; i++){
        for(int x = 0; x < temp; x++){
            temp2.stuff(numbers[i][x], counts[i][x], temp - x - min_length, max_length - i);
            res.push_back(temp2);
        }
        temp*=2;
    }
    sorting(res, N);
    
    return 0;
}
