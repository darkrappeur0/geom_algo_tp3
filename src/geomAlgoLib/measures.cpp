#include "measures.hpp"

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
    std::vector<double> aire_calcul(const Mesh &mesh){
        
        std::vector<double> tab;
        for (FacetCstIt i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	    {

            if (i->is_triangle()){
                tab.push_back(calcul_air_triangle(i));
            }
            else{
                if (i->is_quad()){
                    tab.push_back(calcul_quad(i));
                }
                else{
                    throw std::runtime_error("Face ni triangle ni quadrilatère");
                }
            }
           
		        
	    }
        return tab;
   } 

}