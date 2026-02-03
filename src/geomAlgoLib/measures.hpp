#pragma once

#include "types.hpp"

namespace geomAlgoLib
{
     
    
    
    FacetDoubleMap aire_calcul(const Mesh &mesh);
    CGAL::Vector_3<Kernel> calcul_normal(const FacetCstIt &f);
    CGAL::Vector_3<Kernel> calcul_angle(const FacetCstIt &f);
    FacetStringMap etiquettage(const FacetDoubleMap &f);
    


}