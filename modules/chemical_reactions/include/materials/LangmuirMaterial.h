#ifndef LANGMUIRMATERIAL_H
#define LANGMUIRMATERIAL_H

#include "Material.h"

//Forward Declarations
class LangmuirMaterial;

template<>
InputParameters validParams<LangmuirMaterial>();

/**
 * Holds Langmuir parameters associated with desorption
 * Calculates mass-flow rates and derivatives thereof for use by kernels
 */
class LangmuirMaterial : public Material
{
public:
  LangmuirMaterial(const std::string & name,
                  InputParameters parameters);

protected:

  /// computes mass flow rates and derivatives
  virtual void computeQpProperties();


private:

  /// reciprocal of desorption time constant
  VariableValue * _one_over_de_time_const;

  /// reciprocal of adsorption time constant
  VariableValue * _one_over_ad_time_const;

  /// langmuir density
  Real _langmuir_dens;

  /// langmuir pressure
  Real _langmuir_p;

  /// concentration of adsorbed fluid in matrix
  VariableValue * _conc;

  /// porespace pressure (or partial pressure if multiphase flow scenario)
  VariableValue * _pressure;

  /// mass flow rate from the matrix = mass flow rate to the porespace
  MaterialProperty<Real> & _mass_rate_from_matrix;

  /// derivative of mass flow rate wrt concentration
  MaterialProperty<Real> & _dmass_rate_from_matrix_dC;

  /// derivative of mass flow rate wrt pressure
  MaterialProperty<Real> & _dmass_rate_from_matrix_dp;
};

#endif //LANGMUIRMATERIAL_H
