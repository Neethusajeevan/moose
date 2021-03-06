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

#include "CreateProblemAction.h"
#include "Factory.h"
#include "FEProblem.h"
#include "MooseApp.h"

template<>
InputParameters validParams<CreateProblemAction>()
{
  MooseEnum coord_types("XYZ, RZ, RSPHERICAL", "XYZ");
  std::vector<MooseEnum> coord_types_vec(1, coord_types);

  InputParameters params = validParams<MooseObjectAction>();
  params.set<std::string>("type") = "FEProblem";
  params.addParam<std::string>("name", "MOOSE Problem", "The name the problem");
  params.addParam<std::vector<SubdomainName> >("block", "Block IDs for the coordinate systems");
  params.addParam<std::vector<MooseEnum> >("coord_type", coord_types_vec, "Type of the coordinate system per block param");

  params.addParam<bool>("fe_cache", false, "Whether or not to turn on the finite element shape function caching system.  This can increase speed with an associated memory cost.");

  params.addParam<bool>("kernel_coverage_check", true, "Set to false to disable kernel->subdomain kernel coverage check");
  return params;
}


CreateProblemAction::CreateProblemAction(const std::string & name, InputParameters parameters) :
    MooseObjectAction(name, parameters),
    _problem_name(getParam<std::string>("name")),
    _blocks(getParam<std::vector<SubdomainName> >("block")),
    _coord_sys(getParam<std::vector<MooseEnum> >("coord_type")),
    _fe_cache(getParam<bool>("fe_cache"))
{
}

void
CreateProblemAction::act()
{
  if (_mesh != NULL)
  {
    // build the problem only if we have mesh
    {
      _moose_object_pars.set<MooseMesh *>("mesh") = _mesh;
      _moose_object_pars.set<bool>("use_nonlinear") = _app.useNonlinear();
      _problem = dynamic_cast<FEProblem *>(_factory.create(_type, _problem_name, _moose_object_pars));
      if (_problem == NULL)
        mooseError("Problem has to be of a FEProblem type");
    }
    // set up the problem
    _problem->setCoordSystem(_blocks, _coord_sys);
    _problem->useFECache(_fe_cache);
    _problem->setKernelCoverageCheck(getParam<bool>("kernel_coverage_check"));
  }
}
