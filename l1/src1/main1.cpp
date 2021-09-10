#include "line.hpp"

using namespace std;

int main(){
    size_t h = 5, w = 5;
    line<line<int>> x = line<line<int>>(h);
    for(size_t i = 0; i < h; i++){
        line<int> tmp = line<int>(w);
        for(size_t j = 0; j < w; j++){
            int r;
            cout << i << "," << j << ": ";
            cin >> r;
            if(r != 0){
                tmp.append(j, r);
            }
        }
        if(tmp.length() != 0){
            x.append(i, tmp);
        }
    }

    cout << x;
}
