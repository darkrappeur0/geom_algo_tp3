#include "measures.hpp"
#include <cmath>
namespace geomAlgoLib
{
    double calcul_air_triangle(const FacetCstIt &f) {
        HalfedgeCstIt edges_1 = f->halfedge();
        HalfedgeCstIt edges_2 = edges_1->next();
        HalfedgeCstIt edges_3 = edges_2->next();
        
        double r = CGAL::squared_area(edges_1->vertex()->point(),edges_2->vertex()->point(),edges_3->vertex()->point());
        r = std::sqrt(r);
        return r; 
    }
    double calcul_quad(const FacetCstIt &i) {
        HalfedgeCstIt edges_1 = i->halfedge();
        HalfedgeCstIt edges_2 = edges_1->next();
        HalfedgeCstIt edges_3 = edges_2->next();
        HalfedgeCstIt edges_4 = edges_3->next();

        double r1 = CGAL::squared_area(
        edges_1->vertex()->point(),
        edges_2->vertex()->point(),
        edges_3->vertex()->point()
        );


    double r2 = CGAL::squared_area(
        edges_3->vertex()->point(),
        edges_4->vertex()->point(),
        edges_1->vertex()->point()
    );
        r1 = std::sqrt(r1);
        r2 = std::sqrt(r2);
        return r1+r2;
    }
    FacetDoubleMap aire_calcul(const Mesh &mesh){
        
        FacetDoubleMap tab;
        for (FacetCstIt i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	    {

            if (i->is_triangle()){
                tab[i] = calcul_air_triangle(i);
            }
            else{
                if (i->is_quad()){
                    tab[i] = calcul_quad(i);
                }
                else{
                    throw std::runtime_error("Face ni triangle ni quadrilatère");
                }
            }
           
		        
	    }
        return tab;
   } 

   CGAL::Vector_3<Kernel> calcul_normal(const FacetCstIt &f){
        HalfedgeCstIt edges_1 = f->halfedge();
        HalfedgeCstIt edges_2 = edges_1->next();
        HalfedgeCstIt edges_3 = edges_2->next();
        return CGAL::normal(edges_1->vertex()->point(),edges_2->vertex()->point(),edges_3->vertex()->point());
   }
   CGAL::Vector_3<Kernel> calcul_angle(const FacetCstIt &f){
    CGAL::Vector_3<Kernel> n = calcul_normal(f);
    n = n / std::sqrt(n.squared_length());
    double theta_x = std::acos(n.x());
    double theta_y = std::acos(n.y());
    double theta_z = std::acos(n.z());

    double rad_to_deg = 180.0 / 3.14;

    theta_x *= rad_to_deg;
    theta_y *= rad_to_deg;
    theta_z *= rad_to_deg;
    CGAL::Vector_3<Kernel> v{Kernel::FT(theta_x), Kernel::FT(theta_y), Kernel::FT(theta_z)};

    return v;

   }



}