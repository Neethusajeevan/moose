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

#ifndef SIDEUSEROBJECT_H
#define SIDEUSEROBJECT_H

#include "UserObject.h"
#include "Coupleable.h"
#include "MooseVariableInterface.h"
#include "MooseVariable.h"
#include "TransientInterface.h"
#include "UserObjectInterface.h"
#include "MaterialPropertyInterface.h"

//Forward Declarations
class SideUserObject;

template<>
InputParameters validParams<SideUserObject>();

class SideUserObject :
  public UserObject,
  public Coupleable,
  public UserObjectInterface,
  public MooseVariableInterface,
  public TransientInterface,
  public MaterialPropertyInterface
{
public:
  SideUserObject(const std::string & name, InputParameters parameters);

  const std::vector<BoundaryName> & boundaries() { return _boundaries; }

  virtual Real computeIntegral();

  /**
   * Must override.
   *
   * @param uo The UserObject to be joined into _this_ object.  Take the data from the uo object and "add" it into the data for this object.
   */
//  virtual void threadJoin(const SideUserObject & uo) = 0;

protected:
  MooseVariable & _var;

  std::vector<BoundaryName> _boundaries;

  unsigned int _qp;
  const MooseArray< Point > & _q_point;
  QBase * & _qrule;
  const MooseArray<Real> & _JxW;
  const MooseArray<Real> & _coord;
  const MooseArray<Point> & _normals;

  const Elem * & _current_elem;
  const Elem * & _current_side_elem;
  const Real & _current_side_volume;

  // unknown
  const VariableValue & _u;
  const VariableGradient & _grad_u;

  // Single Instance Variables
  Real & _real_zero;
  MooseArray<Real> & _zero;
  MooseArray<RealGradient> & _grad_zero;
  MooseArray<RealTensor> & _second_zero;

  virtual Real computeQpIntegral() = 0;
};

#endif