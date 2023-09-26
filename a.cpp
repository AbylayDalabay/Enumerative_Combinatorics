#include <bits/stdc++.h>
using namespace std;
 

bool check(int n, int q, vector<int> necklace){

    vector<int> cnt = {0, 0, 0};
    for(auto x : necklace) cnt[x]++;

    return (cnt[0] == 2 && cnt[1] == 2 && cnt[2] == 2);

}

set<vector<int>> unique_vector(vector<vector<int>> factor){
    set<vector<int>> st;
    for(auto v : factor){
        st.insert(v);
    }

    return st;
}

class Necklace{
private:
    int n, q, SIZE = 0;
    vector<vector<int>> symmetry_group;

    vector<vector<int>> all_necklaces;

    vector<vector<vector<int>>> factors_of_equivalence;

    vector<set<vector<int>>> unique_factors_of_equivalence;

    void construct_symmetry_group(){
        // rotations
        for(int k = 0;k <= n - 1;k++){
            vector<int> cur_symmetry;
            for(int i = 0;i <= n - 1;i++){
                cur_symmetry.push_back((i - k + n) % n);
            }   

            symmetry_group.push_back(cur_symmetry);
        }

        // n - even
        if(n % 2 == 0){
            // diagonal

            for(int i = 0;i < n / 2;i++){
                vector<int> cur_symmetry(n);
                iota(cur_symmetry.begin(), cur_symmetry.end(), 0);

                int left_pos = (i - 1 + n) % n;
                int right_pos = (i + 1) % n;

                for(int rep = 0;rep < (n - 2) / 2;rep++){
                    swap(cur_symmetry[left_pos], cur_symmetry[right_pos]);
                    left_pos = (left_pos - 1 + n) % n;
                    right_pos = (right_pos + 1) % n;
                }

                symmetry_group.push_back(cur_symmetry);
            }

            // perpendicular bisector

            for(int i = 0;i < n / 2;i++){
                vector<int> cur_symmetry(n);
                iota(cur_symmetry.begin(), cur_symmetry.end(), 0);

                int left_pos = i;
                int right_pos = (i + 1) % n;

                for(int rep = 0;rep < n / 2;rep++){
                    swap(cur_symmetry[left_pos], cur_symmetry[right_pos]);

                    if(abs(left_pos - right_pos) == 1 && left_pos != i && right_pos != (i + 1) % n){
                        break;
                    }

                    left_pos = (left_pos - 1 + n) % n;
                    right_pos = (right_pos + 1) % n;
                }

                symmetry_group.push_back(cur_symmetry);
            }

        }
        // n - odd
        if(n % 2 == 1){

            // perpendicular bisector
            for(int i = 0;i < n;i++){
                vector<int> cur_symmetry(n);
                iota(cur_symmetry.begin(), cur_symmetry.end(), 0);

                int left_pos = (i - 1 + n) % n;
                int right_pos = (i + 1) % n;

                for(int rep = 0;rep < (n - 1) / 2;rep++){

                    swap(cur_symmetry[left_pos], cur_symmetry[right_pos]);

                    left_pos = (left_pos - 1 + n) % n;
                    right_pos = (right_pos + 1) % n;

                }

                symmetry_group.push_back(cur_symmetry);
            }

        }
    }

    void construct_necklace(int i, int q_val, vector<int> cur_necklace){
        cur_necklace.push_back(q_val);
        if(i == n - 1){
            if(check(n, q, cur_necklace)){
                all_necklaces.push_back(cur_necklace);
            }
            return;
        }

        for(int next_q_val = 0;next_q_val < q;next_q_val++){
            construct_necklace(i + 1, next_q_val, cur_necklace);
        }
    }

    void construct_all_necklaces(){
        for(int q_val = 0;q_val < q;q_val++){
            construct_necklace(0, q_val, (vector<int>){});
        }
    }   

    void construct_factors_of_equivalence(){
        map<vector<int>, bool> used;

        for(vector<int> necklace : all_necklaces){
            if(used[necklace]) continue;

            vector<vector<int>> cur_factor;

            for(const vector<int> &oper : symmetry_group){
                vector<int> symmetry = get_symmetry(necklace, oper);
                used[symmetry] = true;
                cur_factor.push_back(symmetry);
            }

            factors_of_equivalence.push_back(cur_factor);

            unique_factors_of_equivalence.push_back(unique_vector(cur_factor));
            SIZE += unique_vector(cur_factor).size();
        }
    }
public:
    Necklace(int n, int q){
        this->n = n;
        this->q = q;
        construct_symmetry_group();
        construct_all_necklaces();
        construct_factors_of_equivalence();
    }

    vector<int> get_symmetry(vector<int> necklace, const vector<int> &oper){
        vector<int> ret(n, 0);
        for(int i = 0;i < n;i++){
            ret[i] = necklace[oper[i]];
        }

        return ret;
    }

    void print(vector<int> cur_symmetry){
        if(n == 4){
            cout << cur_symmetry[0] << " - " << cur_symmetry[1] << endl;
            cout << "|   |" << endl;
            cout << cur_symmetry[3] << " - " << cur_symmetry[2] << endl; 
            cout << endl;
        }
        else if(n == 6){
            cout << "  " << cur_symmetry[0] << " - " << cur_symmetry[1] << " " << endl;
            cout << " /     \\" << endl;
            cout << cur_symmetry[5] << "       " << cur_symmetry[2] << endl;
            cout << " \\     /" << endl;
            cout << "  " << cur_symmetry[4] << " - " << cur_symmetry[3] << " " << endl;
            cout << endl;
        }
        else{
            cout << "{ ";
            for(auto x : cur_symmetry) cout << x << " ";
            cout << "}\n";
            return;
        }
    }

    vector<vector<int>> get_all_necklaces(){
        return all_necklaces;
    }

    void print_all_necklaces(){
        cout << "SIZE: " << all_necklaces.size() << endl;

        for(auto necklace : all_necklaces){
            print(necklace);
        }
    }   

    void print_factors_of_equivalence(){
        for(const vector<vector<int>> &cur_factor : factors_of_equivalence){

            for(const vector<int> &necklace : cur_factor){

                print(necklace);

            }
            cout << " //////////////////////////////////////////////// " << endl;

        }
    }

    void print_unique_factors_of_equivalence(){
        cout << "Number of all necklaces : " << SIZE << endl;
        cout << "Size of factors of equivalence : " << unique_factors_of_equivalence.size() << endl << endl;

        for(const set<vector<int>> &cur_factor : unique_factors_of_equivalence){

            for(const vector<int> &necklace : cur_factor){

                print(necklace);

            }
            cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

        }
    }

    void print_factor_minimized(set<vector<int>> factor){

        if(n == 4){
            for(auto necklace : factor){
                cout << necklace[0] << " - " << necklace[1] << "  ";
            }
            cout << endl;
            for(auto necklace : factor){
                cout << "|" << "   " << "|  ";
            }
            cout << endl;
            for(auto necklace : factor){
                cout << necklace[3] << " - " << necklace[2] << "  ";
            }
            cout << endl;
        }

        if(n == 6){
            for(auto necklace : factor) cout << "  " << necklace[0] << " - " << necklace[1] << "   ";
            cout << endl;
            for(auto necklace : factor) cout << " /     \\  ";
            cout << endl;
            for(auto necklace : factor) cout << necklace[5] << "       " << necklace[2] << " ";
            cout << endl;
            for(auto necklace : factor) cout << " \\     /  ";
            cout << endl;
            for(auto necklace : factor) cout << "  " << necklace[4] << " - " << necklace[3] << "   ";
            cout << endl;
        }

    }

    void print_minimized_unique_factors_of_equivalence(){
        cout << "Number of all necklaces : " << SIZE << endl;
        cout << "Size of factors of equivalence : " << unique_factors_of_equivalence.size() << endl << endl;

        for(const set<vector<int>> &cur_factor : unique_factors_of_equivalence){

            print_factor_minimized(cur_factor);
            cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

        }
    }

    void print(){
        cout << "SIZE: " << symmetry_group.size() << endl;

        for(auto cur_symmetry : symmetry_group){
            print(cur_symmetry);
        }
    }
};

int main(){
    freopen("output_6_3.txt","w",stdout);

    Necklace Figure(6, 3);
    // Triangle.print();
    Figure.print_minimized_unique_factors_of_equivalence();
    // Figure.print_all_necklaces();
}
