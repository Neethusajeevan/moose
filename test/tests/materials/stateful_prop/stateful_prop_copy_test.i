[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 10
  ymin = 0
  ymax = 10
  nx = 4
  ny = 4
[]

[Variables]
  active = 'u prop1'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./prop1]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  active = 'heat ie prop1_output'

  [./heat]
    type = MatDiffusion
    variable = u
    prop_name = thermal_conductivity
  [../]

  [./ie]
    type = TimeDerivative
    variable = u
  [../]

  [./prop1_output]
    type = RealPropertyOutput
    variable = prop1
    prop_name = thermal_conductivity
  [../]
[]

[BCs]
  active = 'bottom top'

  [./bottom]
    type = DirichletBC
    variable = u
    boundary = 3
    value = 0.0
  [../]

  [./top]
#    type = DirichletBC
    type = MTBC
    variable = u
    boundary = 1
#    value = 1.0
    grad = 1.0
    prop_name = thermal_conductivity
  [../]
[]

[Materials]
  active = 'stateful'

  [./stateful]
    type = StatefulSpatialTest
    block = 0
  [../]
[]

[UserObjects]
  [./copy]
    type = MaterialCopyUserObject
    copy_times = 0.3
    copy_from_element = 0
    copy_to_element = 15
  [../]
[]

[Executioner]
  type = Transient

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  start_time = 0.0
  num_steps = 5
  dt = .1
[]

[Outputs]
  file_base = out_stateful_copy
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
  [../]
[]
