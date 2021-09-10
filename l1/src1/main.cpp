#include "matrix.hpp"

using namespace std;

int main(){
    size_t h = 5, w = 5;
    csw<int> x = csw<int>(5, 5);
    for(size_t i = 0; i < h; i++){
        for(size_t j = 0; j < w; j++){
            int r;
            cout << i << "," << j << ": ";
            cin >> r;
            if(r != 0){
                x.insert(i, j, r);
            }
        }
    }

    cout << x;
}
