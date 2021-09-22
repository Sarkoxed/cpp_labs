#include "lib.hpp"
#include "../../tools/toolib.hpp"

using namespace hypo;

int main(){
    float r,k,d;
    get_el(r);
    get_el(k);
    get_el(d);
    hypocycloid a, b(r, k), c(r, k, d);
    
    float phi;
    get_el(phi);

    pair<double, double> rs1 = c.get_rs();
    pair<double, double> crds = b.get_point(phi);
//    hypotypes x = c.get_type(), y = b.get_type();

    std::cout << rs1 << a.get_rs() << b.get_rs() << std::endl;
    std::cout << crds << a.get_point(phi) << c.get_point(phi) << std::endl;
    
  //  std::cout << x << y << a.get_type() << std::endl;

    std::cout << a.curvative_radius(phi) << std::endl;
    std::cout << b.curvative_radius(phi) << std::endl;
    std::cout << c.curvative_radius(phi) << std::endl;

    std::cout << a.sectorial_area() << std::endl;
    std::cout << b.sectorial_area() << std::endl;
    std::cout << c.sectorial_area() << std::endl;
    
    hypocycloid aa(-1, 0, 0);
    std::cout << aa.get_r() << std::endl;

    return 0;
}
