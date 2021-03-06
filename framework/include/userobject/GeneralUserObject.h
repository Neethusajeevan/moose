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

#ifndef GENERALUSEROBJECT_H
#define GENERALUSEROBJECT_H

#include "UserObject.h"
#include "TransientInterface.h"
#include "FunctionInterface.h"
#include "DependencyResolverInterface.h"
#include "UserObjectInterface.h"
#include "PostprocessorInterface.h"
#include "MaterialPropertyInterface.h"
#include "Problem.h"


//Forward Declarations
class GeneralUserObject;

template<>
InputParameters validParams<GeneralUserObject>();

/* This class is here to combine the Postprocessor interface and the
 * base class Postprocessor object along with adding MooseObject to the inheritance tree*/
class GeneralUserObject :
  public UserObject,
  public MaterialPropertyInterface,
  public TransientInterface,
  public FunctionInterface,
  public DependencyResolverInterface,
  public UserObjectInterface,
  protected PostprocessorInterface
{
public:
  GeneralUserObject(const std::string & name, InputParameters parameters);

  /**
   * This function will get called when this user object needs to update its values
   *
   * Someone somewhere has to override this.
   */
  virtual void execute() = 0;

  const std::set<std::string> & getRequestedItems();

  const std::set<std::string> & getSuppliedItems();

  virtual ~GeneralUserObject() {}

  virtual PostprocessorValue & getPostprocessorValue(const std::string & name);
  virtual const PostprocessorValue & getPostprocessorValueByName(const PostprocessorName & name);

protected:
  std::set<std::string> _depend_vars;
  std::set<std::string> _supplied_vars;
};

#endif
