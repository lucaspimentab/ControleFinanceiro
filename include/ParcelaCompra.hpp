 #ifndef PARCELACOMPRA_HPP
 #define PARCELACOMPRA_HPP

 #include "Compra.hpp"
 #include <vector>

 class ParcelaCompra : public Compra {
 private:
     int numParcelas;
     std::vector<float> valoresParcelas;

 public:
     ParcelaCompra(float valor, const std::string& categoria, const std::string& data, int numParcelas);

     int getNumParcelas() const;
     std::vector<float> getValoresParcelas() const;
     float getValorParcela(int index) const;
 };

 #endif