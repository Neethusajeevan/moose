/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MATERIALREALVECTORVALUEAUX_H
#define MATERIALREALVECTORVALUEAUX_H

// MOOSE includes
#include "MaterialAuxBase.h"

// Forward declarations
class MaterialRealVectorValueAux;

template<>
InputParameters validParams<MaterialRealVectorValueAux>();

/**
 * AuxKernel for outputting a RealVectorValue material property component to an AuxVariable
 */
class MaterialRealVectorValueAux : public MaterialAuxBase<RealVectorValue>
{
public:

  /**
   * Class constructor
   * @param name AuxKernel name
   * @param parameters The input parameters for this object
   */
  MaterialRealVectorValueAux(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~MaterialRealVectorValueAux();

protected:

  /**
   * Compute the value of the material property for the given component
   */
  virtual Real computeValue();

  /// The vector component to output
  unsigned int _component;
};

#endif //MATERIALREALVECTORVALUEAUX_H
