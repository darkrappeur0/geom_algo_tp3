#include "measures.hpp"
#include <cmath>
#include <exception>
namespace geomAlgoLib
{
    double calcul_air_triangle(const FacetCstIt &f) {
        HalfedgeCstIt edges_1 = f->halfedge();
        HalfedgeCstIt edges_2 = edges_1->next();
        HalfedgeCstIt edges_3 = edges_2->next();
        
        double r =0.0;
        const auto& p = edges_1->vertex()->point();
        const auto& q = edges_2->vertex()->point();
        const auto& s = edges_3->vertex()->point();
        CGAL::Vector_3<Kernel> pq = q - p;
        CGAL::Vector_3<Kernel> ps = s - p;
        std::cout << "Je suis un triangle" << std::endl;
        
        if(!CGAL::collinear(p,q,s) ){
            r =std::sqrt(CGAL::cross_product(pq, ps).squared_length()) * 0.5;
        }
            
        /*
        try{
            CGAL::Triangle_3<Kernel> t(edges_1->vertex()->point(),edges_2->vertex()->point(),edges_3->vertex()->point());
            if (!t.is_degenerate()){
                r = std::sqrt(t.squared_area());
            }
        }
        catch(const CGAL::Precondition_exception &e){
            r=0.0;
        }*/
        
        //r = std::sqrt(r);
        return r; 
    }
    double calcul_quad(const FacetCstIt &i) {
        HalfedgeCstIt edges_1 = i->halfedge();
        HalfedgeCstIt edges_2 = edges_1->next();
        HalfedgeCstIt edges_3 = edges_2->next();
        HalfedgeCstIt edges_4 = edges_3->next();

        double r1 = 0.0; 
        double r2 = 0.0 ;
        std::cout << "Je suis un carré" << std::endl;
        try{
            if (!CGAL::collinear(edges_1->vertex()->point(),edges_2->vertex()->point(),edges_3->vertex()->point())){
                r1 = CGAL::squared_area(
                edges_1->vertex()->point(),
                edges_2->vertex()->point(),
                edges_3->vertex()->point()
                );
            }
        
            if (!CGAL::collinear(edges_3->vertex()->point(),edges_4->vertex()->point(),edges_1->vertex()->point())){
                r2 = CGAL::squared_area(
                edges_3->vertex()->point(),
                edges_4->vertex()->point(),
                edges_1->vertex()->point()
                );
            }
        }
        catch (const CGAL::Precondition_exception & e){
            r1=0.0;
            r2=0.0;
        } /*
        try{
            CGAL::Triangle_3<Kernel> t1(edges_1->vertex()->point(),edges_2->vertex()->point(),edges_3->vertex()->point());
            if (!t1.is_degenerate()){
                r1 = std::sqrt(t1.squared_area());
            }
            CGAL::Triangle_3<Kernel> t2(edges_3->vertex()->point(),edges_4->vertex()->point(),edges_1->vertex()->point());
            if (!t2.is_degenerate()){
                r2 = std::sqrt(t2.squared_area());
            }
            
        }
        catch(const CGAL::Precondition_exception &e){
            r1=0.0;
            r2 = 0.0;
        }
        */
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
   bool est_zone_marche(const FacetCstIt& f)
    {
    CGAL::Vector_3<Kernel> n = calcul_normal(f);
    double norm = std::sqrt(n.squared_length());
    if(norm == 0.0) return false;

    n = n / norm;

    double verticalite = n.z();   // produit scalaire avec (0,0,1)

    return (verticalite > 0.9);
    }      

    bool est_obstacle(const FacetCstIt& f)
    {
    CGAL::Vector_3<Kernel> n = calcul_normal(f);
    double norm = std::sqrt(n.squared_length());
    if(norm == 0.0) return false;

    n = n / norm;

    double verticalite = std::abs(n.z());

    if(verticalite < 0.6)
        return true;

    return false;
    }
    bool est_a_portee(const FacetCstIt& f)
    {
    HalfedgeCstIt h = f->halfedge();

    Kernel::Point_3 p = h->vertex()->point();
    Kernel::Point_3 q = h->next()->vertex()->point();
    Kernel::Point_3 r = h->next()->next()->vertex()->point();

    Kernel::Point_3 bary(
        (p.x() + q.x() + r.x())/3.0,
        (p.y() + q.y() + r.y())/3.0,
        (p.z() + q.z() + r.z())/3.0
    );

    Kernel::Point_3 avatar(3.0, 3.0, 0.0);

    double dist2 = CGAL::squared_distance(bary, avatar);

    return dist2 < 4.0; // distance < 2
    }




   FacetStringMap etiquettage(const FacetDoubleMap &tab){
    FacetStringMap res;
    for(auto i = tab.begin(); i != tab.end(); ++i){
        if (i->second > 0.0010){
            res[i->first] = "Grande Face";
        }
        else{
            res[i->first] = "Petite Face";
        }
        
        CGAL::Vector_3<Kernel> n = calcul_normal(i->first);
        n = n / std::sqrt(n.squared_length());
        if( est_zone_marche(i->first) & (res[i->first] == "Grande Face")){
            res[i->first] = "orientées vers le haut";
        }
        else if( est_obstacle(i->first) ){
            res[i->first] = "obstacle";
        }
        if( est_a_portee(i->first) ){
            res[i->first] = "a portee";
        }


        
            
        
    }
    return res;
   }



}