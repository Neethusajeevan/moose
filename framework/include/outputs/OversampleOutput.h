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

#ifndef OVERSAMPLEOUTPUT_H
#define OVERSAMPLEOUTPUT_H

// MOOSE includes
#include "PetscOutput.h"

// libMesh
#include "libmesh/equation_systems.h"
#include "libmesh/equation_systems.h"
#include "libmesh/numeric_vector.h"
#include "libmesh/mesh_function.h"

// Forward declerations
class OversampleOutput;

template<>
InputParameters validParams<OversampleOutput>();

/**
 * Based class for providing re-positioning and oversampling support to output objects
 *
 * This class performs the actual oversampling calculations and makes the correct
 * changes to the libMesh::EquationsSystems() pointer (_es_ptr), i.e., this pointer is
 * will point to the oversampled system, if oversamping is utilized.
 *
 * Additionally, the class adds a pointer the the mesh object (_mesh_ptr) that again
 * points to the correct mesh depending on the use of oversampling.
 *
 * The use of oversampling is triggered by setting the oversample input parameter to a
 * integer value greater than 0, indicating the number of refinements to perform.
 *
 * @see Exodus
 */
class OversampleOutput :
  public PetscOutput
{
public:

  /**
   * Class constructor
   *
   * If oversampling is desired the constructor will perform the correct initialization
   * required for oversampling.
   * @see initOversample()
   */
  OversampleOutput(const std::string & name, InputParameters & parameters);

  /**
   * Class destructor
   *
   * Cleans up the various objects associated with the oversample EquationsSystem and Mesh
   * objects.
   */
  virtual ~OversampleOutput();

  /**
   * Performs the initial output, including the creation of the oversampled solution vector
   */
  void outputInitial();

  /**
   * Performs the output of a time step, including the creation of the oversampled solution vector
   */
  void outputStep();

  /**
   * Performs the final output, including the creation of the oversampled solution vector
   */
  void outputFinal();


protected:

  /**
   * Performs the update of the solution vector for the oversample/re-positioned mesh
   */
  virtual void update();

  /**
   * A pointer to the current mesh
   * When using oversampling this points to the created oversampled, which must
   * be cleaned up by the destructor.
   */
  MooseMesh * _mesh_ptr;

private:

  /**
   * Setups the output object to produce re-positioned and/or oversampled results.
   * This is accomplished by creating a new, finer mesh that the existing solution is projected
   * upon. This function is called by the creating action (addOutputAction) and should not be called
   * by the user as it will create a memory leak if called multiple times.
   */
  void initOversample();

  /**
   * Clone mesh in preperation for re-positioning or oversampling.
   * This changes the pointer, _mesh_ptr, with a clone of the current mesh so that it may
   * be modified to perform the necessary oversample/positioning actions
   */
  void cloneMesh();

  /**
   * A vector of pointers to the mesh functions
   * This is only populated when the oversample() function is called, it must
   * be cleaned up by the destructor.
   */
  std::vector<std::vector<MeshFunction *> > _mesh_functions;

  /// Flag for enabling oversampling
  bool _oversample;

  /// The number of oversampling refinements
  const unsigned int _refinements;

  /// Flag for re-positioning
  bool _change_position;

  /// When oversampling, the output is shift by this amount
  Point _position;

  /// Oversample solution vector
  /* Each of the MeshFunctions keeps a reference to this vector, the vector is updated for the current system
   * and variable before the MeshFunction is applied. This allows for the same MeshFunction object to be
   * re-used, unless the mesh has changed due to adaptivity */
  AutoPtr<NumericVector<Number> > _serialized_solution;
};

#endif // OVERSAMPLEOUTPUT_H
