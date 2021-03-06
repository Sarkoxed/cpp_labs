#include "lib.hpp"
#include "../../tools/toolib.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace curve;

 

void help(){
    std::cout << "0 to get help" << std::endl;
    std::cout << "1 to get small radius" << std::endl;
    std::cout << "2 to get coef" << std::endl;
    std::cout << "3 to get distance from generating circle centre" << std::endl;
    std::cout << "4 to set small radius" << std::endl;
    std::cout << "5 to set coef" << std::endl;
    std::cout << "6 to set distance from generating circle centre" << std::endl;
    std::cout << "7 to create hypocycloid via r and k" << std::endl;
    std::cout << "8 to create hypocycloid via r, k and d" << std::endl;
    std::cout << "9 to get generating and primary circle" << std::endl;
    std::cout << "10 to get point" << std::endl;
    std::cout << "11 to get curvative radius" << std::endl;
    std::cout << "12 to get sectorial area" << std::endl;
    std::cout << "13 to get type" <<std::endl;
    std::cout << "14 to get values for print" << std::endl;
    std::cout << "15 to exit" << std::endl;
}

int main(){
    hypocycloid a;
    int ch;
    double r, k, d, phi; 
    help();
    while(true){
        std::cout << "do ->";
        get_el(ch);
        switch (ch){ 
            case 0: 
                help();
                continue;
            case 1: std::cout << "small radius: "<< a.get_r() << std::endl; 
                continue;
            case 2: 
                std::cout << "coef: "<< a.get_k() << std::endl; 
                continue;
            case 3: 
                std::cout << "distance: " << a.get_d() << std::endl; 
                continue;
            case 4: 
                std::cout << "input r: "; 
                get_el(r); 
                try{
                    a.set_r(r);
                }
                catch(const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                continue;
            case 5: 
                std::cout << "input k: "; 
                get_el(k); 
                try{
                    a.set_k(k);
                }
                catch(const std::exception &e){
                    std::cerr << e.what() << std::endl; }
                continue;
            case 6: 
                std::cout << "input d: "; 
                get_el(d); 
                try{
                    a.set_d(d);
                }
                catch(const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                continue;           
            case 7: 
                std::cout << "input r: "; 
                get_el(r); 
                std::cout << "input k: "; 
                get_el(k);    
                try{
                    a = hypocycloid(r, k);
                }
                catch(const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                continue;
            case 8:
                std::cout << "input r: "; 
                get_el(r); 
                std::cout << "input k: "; 
                get_el(k);    
                std::cout << "input d: ";
                get_el(d);
                try{
                    a = hypocycloid(r, k, d);
                }
                catch(const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                continue;               
            case 9:
                std::cout << "(r, R): " << a.get_rs() << std::endl;
                continue;
            case 10:
                std::cout << "input phi: ";
                get_el(phi);
                std::cout << "(x, y) at phi: " << a.get_point(phi) << std::endl;
                continue;
            case 11:
                std::cout << "input phi: ";
                get_el(phi);
                std::cout << "curvative rad at phi: " << a.curvative_radius(phi) << std::endl;
                continue;
            case 12:
                std::cout << "area: " << a.sectorial_area() << std::endl;
                continue;
            case 13:
              std::cout << a.get_type();
              continue;

            case 14://not working
                {
                    std::string filename;
                    std::cout << "input filename: ";
                    get_el(filename);
                    std::ofstream ff;
                    ff.open(filename);
                    for(int i = 1; i < 1000; i++){
                        pair<double, double> x = a.get_point(pi*i / 500.0 );
                        ff << "(" << x.x() << ", " << x.y() << ")\n";
                    }
                    ff.close();
                }
                continue;
            case 15:
                exit(0);
            default:
                std::cerr << "no idea, retry" << std::endl;
                continue;
        }
    }
    return 0;
}
