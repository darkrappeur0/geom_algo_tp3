#pragma once

#include "types.hpp"

namespace geomAlgoLib
{
     
    
    
    FacetDoubleMap aire_calcul(const Mesh &mesh);
    CGAL::Vector_3<Kernel> calcul_normal(const FacetCstIt &f);
    CGAL::Vector_3<Kernel> calcul_angle(const FacetCstIt &f);
    
    
    
    bool est_zone_marche(const FacetCstIt& f);
    bool est_obstacle(const FacetCstIt& f);
    bool est_a_portee(const FacetCstIt& f);
    FacetStringMap etiquettage(const FacetDoubleMap &f);

    double calcul_angle_min_face(const FacetCstIt& f);
    FacetDoubleMap angle_min_calcul(const Mesh &mesh);

}