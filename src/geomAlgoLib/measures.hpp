#pragma once

#include "types.hpp"

namespace geomAlgoLib
{
     
    double calcul_air_triangle(const FacetCstIt &i);
    double calcul_quad(const FacetCstIt &i);
    
    std::vector<double>aire_calcul(const Mesh &mesh);
        


}