/*************************************************************************
*
*  Welcome to HYRAX!
*  Andrea M. Jokisaari
*  CASL/MOOSE
*
*  18 April 2012
*
*************************************************************************/

#include "MaterialSymmElasticityTensorAux.h"

template<>
InputParameters validParams<MaterialSymmElasticityTensorAux>()
{
  InputParameters params = validParams<AuxKernel>();
  // name of the material property of symm elasticity tensor type (probably "elasticity_tensor")
  params.addRequiredParam<std::string>("tensor_matpro","The SymmElasticityTensor material property name");
  params.addRequiredParam<int>("index","The matrix index (0-20) to output");

  return params;
}

MaterialSymmElasticityTensorAux::MaterialSymmElasticityTensorAux(const std::string & name, InputParameters parameters)
    :AuxKernel(name, parameters),
     _tensor_matpro(getParam<std::string>("tensor_matpro")),
     _index(getParam<int>("index")),
     _tensor_prop(getMaterialProperty<SymmElasticityTensor>(_tensor_matpro))
{
  if (_index < 0 || _index > 20)
    mooseError("Please check your index specified for MaterialSymmElasticityTensorAux (between 0 and 20).");
}

Real
MaterialSymmElasticityTensorAux::computeValue()
{
  return (_tensor_prop[_qp]).valueAtIndex(_index);
}
