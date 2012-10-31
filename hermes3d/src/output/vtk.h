// This file is part of Hermes3D
//
// Copyright (c) 2009 hp-FEM group at the University of Nevada, Reno (UNR).
// Email: hpfem-group@unr.edu, home page: http://hpfem.org/.
//
// Hermes3D is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 2 of the License,
// or (at your option) any later version.
//
// Hermes3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes3D; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef _VTK_OUTPUT_ENGINE_H_
#define _VTK_OUTPUT_ENGINE_H_

#include "../output.h"
#include "../../../hermes_common/matrix.h"
#include "../../../hermes_common/judyarray.h"

/// VTK output engine.
///
/// TODO: binary file format
///
/// @ingroup visualization
class HERMES_API VtkOutputEngine : public OutputEngine {
public:
	VtkOutputEngine(FILE *file, int outprec = 1);
	virtual ~VtkOutputEngine();

	/// Run the output with specified output engine
	///
	/// @return true if ok
	/// @param[in] fn A function that will be visualized
	virtual void out(MeshFunction *fn, const char *name, int item = FN_VAL);
	virtual void out(MeshFunction *fn1, MeshFunction *fn2, MeshFunction *fn3, const char *name, int item = FN_VAL_0);
	virtual void out(Mesh *mesh);
	virtual void out_bc_vtk(Mesh *mesh, const char *name = "BCs");

	virtual void out_orders_vtk(Space *space, const char *name = "orders");
	virtual void out_elem_markers(Mesh *mesh, const char *name = "elem-markers");

	virtual void out(Matrix *mat, bool structure = true);

protected:
	Ord3 get_order(int mode);

	/// file into which the output is done
	FILE *out_file;
	int out_prec;
};

/// Functions facilitating output in the format displayable by e.g. Paraview.
// Space (polynomial orders) output.
void HERMES_API out_orders_vtk(Space *space, const char *name, int iter = -1, int iter_2 = -1);
// Solution output for one solution component.
void HERMES_API out_fn_vtk(MeshFunction *fn, const char *name, int iter = -1, int iter_2 = -1);
// Solution output for three solution components.
void HERMES_API out_fn_vtk(MeshFunction *x, MeshFunction *y, MeshFunction *z, const char *name, int iter = -1, int iter_2 = -1);
// Boundary conditions output.
void HERMES_API out_bc_vtk(Mesh *mesh, const char *name, int iter = -1, int iter_2 = -1);
// Mesh output.
void HERMES_API out_mesh_vtk(Mesh *mesh, const char *name, int iter = -1, int iter_2 = -1);

#endif
