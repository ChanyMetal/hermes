xsdcxx cxx-tree --generate-doxygen --generate-ostream --hxx-suffix .h --cxx-suffix .cpp mesh_h2d_xml.xsd
xsdcxx cxx-tree --generate-doxygen --generate-ostream --hxx-suffix .h --cxx-suffix .cpp subdomains_h2d_xml.xsd
mv -f *.cpp ../../src/mesh
