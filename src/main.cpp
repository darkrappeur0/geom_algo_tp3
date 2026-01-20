#include <io.hpp>
#include <example.hpp>

#include <iostream>
#include <string>

int main(int argc, char *argv[]){

    std::cout << "Hello !" << std::endl;

    if(argc < 2){
        throw std::invalid_argument("This program expects at least 1 argument (path to a mesh).");
    }

    const std::string meshPath = std::string{argv[1]};
    
    geomAlgoLib::Mesh myMesh;

    geomAlgoLib::readOFF(meshPath, myMesh);

    auto genus = geomAlgoLib::computeGenus(myMesh);
    std::cout << "The Genus of [" << meshPath << "] is = " << std::to_string(genus) << std::endl;

    geomAlgoLib::writeOFF(myMesh,"output.off");


    std::vector<double> tab = geomAlgoLib::aire_calcul(myMesh);
	std::cout << "apres le calcul de l'aire au carrée" << std::endl;
    unsigned c = 0;
    for ( auto i = tab.begin();i<tab.end();++i){
        c=c+1;
        std::cout << "aire a la " << c << "-eme valeur " <<*i << std::endl;
        
    }
    //std::cout << "tableau des aires" << tab << std::endl;
    std::cout << "The end..." << std::endl;
    return 0;
}