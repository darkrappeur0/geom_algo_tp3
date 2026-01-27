#include "io.hpp"

namespace geomAlgoLib
{

bool readOFF(const std::string& filePath, Mesh& mesh){

    std::ifstream input(filePath);

	if (!input || !(input >> mesh) || mesh.is_empty())
	{
		std::cerr << "Invalid .OFF file" << std::endl;
		return false;
	}

    return true;

}

void writeOFF(const Mesh& mesh, const std::string& filePath)
{
	std::ofstream in_myfile;
	in_myfile.open(filePath);

	CGAL::set_ascii_mode(in_myfile);

	in_myfile << "COFF" << std::endl // "COFF" makes the file support color information
			  << mesh.size_of_vertices() << ' ' 
			  << mesh.size_of_facets() << " 0" << std::endl; 
			  // nb of vertices, faces and edges (the latter is optional, thus 0)

	std::copy(mesh.points_begin(), mesh.points_end(),
			  std::ostream_iterator<Kernel::Point_3>(in_myfile, "\n"));

	for (FacetCstIt i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	{
		HalfedgeFacetCstCirc j = i->facet_begin();

		CGAL_assertion(CGAL::circulator_size(j) >= 3);

		in_myfile << CGAL::circulator_size(j) << ' ';
		do
		{
			in_myfile << ' ' << std::distance(mesh.vertices_begin(), j->vertex());

		} while (++j != i->facet_begin());

		in_myfile << std::endl;
	}

	in_myfile.close();

	std::cout << "Successfully exported at path: " << filePath << " !" << std::endl;
}

void StoreinFiles(const Mesh& mesh,const FacetDoubleMap & tab, const std::string& filePath ){
	std::ofstream in_myfile;
	in_myfile.open(filePath);

	CGAL::set_ascii_mode(in_myfile);

	in_myfile << "COFF" << std::endl // "COFF" makes the file support color information
			  << mesh.size_of_vertices() << ' ' 
			  << mesh.size_of_facets() << ' ' << mesh.size_of_halfedges() /2 << std::endl; 
			  // nb of vertices, faces and edges (the latter is optional, thus 0)

	std::copy(mesh.points_begin(), mesh.points_end(),
			  std::ostream_iterator<Kernel::Point_3>(in_myfile, "\n"));


	for (auto i = tab.begin(); i != tab.end(); ++i)
	{
		HalfedgeFacetCstCirc j = i->first->facet_begin();

		CGAL_assertion(CGAL::circulator_size(j) >= 3);

		in_myfile << CGAL::circulator_size(j) << ' ';
		do
		{
			in_myfile << ' ' << std::distance(mesh.vertices_begin(), j->vertex());
			

		} while (++j != i->first->facet_begin());
		do
		{
			int c = 255;
			if(i->second > 1 ){
				c = 255 / i->second;
			}
			else{
				c = 255 / (i->second + 1);   // a retravailler peut poser problème
			}
			in_myfile << ' ' << c  ;
			

		} while (++j != i->first->facet_begin());
		in_myfile << std::endl;
	}

	in_myfile.close();

	std::cout << "Successfully exported at path: " << filePath << " !" << std::endl;
}


}