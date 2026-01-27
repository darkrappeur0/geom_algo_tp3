#pragma once

#include "types.hpp"

namespace geomAlgoLib
{
     
    double calcul_air_triangle(const FacetCstIt &i);
    double calcul_quad(const FacetCstIt &i);
    
    FacetDoubleMap aire_calcul(const Mesh &mesh);
    CGAL::Vector_3<Kernel> calcul_normal(const FacetCstIt &f);
    CGAL::Vector_3<Kernel> calcul_angle(const FacetCstIt &f);
    


}