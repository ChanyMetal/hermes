// This file is part of Hermes2D.
//
// Hermes2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __H2D_H1_WEAK_FORMS_H
#define __H2D_H1_WEAK_FORMS_H

#include "../integrals/h1.h"

namespace WeakFormsH1 
{
  /* Default volumetric matrix form \int_{area} const_coeff * function_coeff(x, y) * u * v \bfx
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultMatrixFormVol : public MatrixFormVol<Scalar>
  {
  public:
    DefaultMatrixFormVol<Scalar>(int i, int j, std::string area = HERMES_ANY,
      Scalar const_coeff = 1.0, DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      SymFlag sym = HERMES_NONSYM, GeomType gt = HERMES_PLANAR);

    DefaultMatrixFormVol<Scalar>(int i, int j, Hermes::vector<std::string> areas,
      Scalar const_coeff = 1.0, DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      SymFlag sym = HERMES_NONSYM, GeomType gt = HERMES_PLANAR);

    ~DefaultMatrixFormVol<Scalar>();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *u, Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u,
      Func<Ord> *v, Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormVol<Scalar>* clone();

  private:
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  /* Default volumetric matrix form \int_{area} const_coeff * spline_coeff'(u_ext[0]) u \nabla u_ext[0] \cdot \nabla v
  + const_coeff * spline_coeff(u_ext[0]) * \nabla u \cdot \nabla v d\bfx
  const_coeff... constant number
  spline_coeff... nonconstant parameter given by cubic spline
  */

  template<typename Scalar>
  class HERMES_API DefaultJacobianDiffusion : public MatrixFormVol<Scalar>
  {
  public:
    DefaultJacobianDiffusion(int i, int j, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE,
      SymFlag sym = HERMES_NONSYM, GeomType gt = HERMES_PLANAR);

    DefaultJacobianDiffusion(int i, int j, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE,
      SymFlag sym = HERMES_NONSYM, GeomType gt = HERMES_PLANAR);

    ~DefaultJacobianDiffusion();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *u,
      Func<double> *v, Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u, Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormVol<Scalar>* clone();

  private:
    int idx_j;
    Scalar const_coeff;
    CubicSpline* spline_coeff;
    GeomType gt;
  };

  /* Default volumetric matrix form
  \int_{area} spline_coeff1`(u_ext[0]) * u * u_ext[0]->dx * v
  + spline_coeff1(u_ext[0]) * u->dx * v
  + spline_coeff2`(u_ext[0]) * u * u_ext[0]->dy * v
  + spline_coeff2(u_ext[0]) * u->dy * v d\bfx.
  spline_coeff1, spline_coeff2... non-constant parameters given by cubic splines
  */

  template<typename Scalar>
  class HERMES_API DefaultJacobianAdvection : public MatrixFormVol<Scalar>
  {
  public:
    DefaultJacobianAdvection(int i, int j, std::string area = HERMES_ANY, 
      Scalar const_coeff1 = 1.0, Scalar const_coeff2 = 1.0,
      CubicSpline* c_spline1 = HERMES_DEFAULT_SPLINE,
      CubicSpline* c_spline2 = HERMES_DEFAULT_SPLINE, GeomType gt = HERMES_PLANAR);

    DefaultJacobianAdvection(int i, int j, Hermes::vector<std::string> areas, 
      Scalar const_coeff1 = 1.0, Scalar const_coeff2 = 1.0,
      CubicSpline* c_spline1 = HERMES_DEFAULT_SPLINE,
      CubicSpline* c_spline2 = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);

    ~DefaultJacobianAdvection();

    template<typename Real, typename Scalar>
    Scalar matrix_form(int n, double *wt, Func<Scalar> *u_ext[], Func<Real> *u,
      Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) const;

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *u,
      Func<double> *v, Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u, Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormVol<Scalar>* clone();

  private:
    int idx_j;
    Scalar const_coeff1, const_coeff2;
    CubicSpline* spline_coeff1, *spline_coeff2;
    GeomType gt;
  };

  /* Default volumetric vector form \int_{area} const_coeff * function_coeff(x, y) * v d\bfx
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultVectorFormVol : public VectorFormVol<Scalar>
  {
  public:
    DefaultVectorFormVol<Scalar>(int i, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    DefaultVectorFormVol<Scalar>(int i, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    ~DefaultVectorFormVol<Scalar>();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormVol<Scalar>* clone();

  private:
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  /* Default volumetric vector form \int_{area} const_coeff * function_coeff(x, y) * u_ext[0] * v d\bfx
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultResidualVol : public VectorFormVol<Scalar>
  {
  public:
    DefaultResidualVol(int i, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);
    DefaultResidualVol(int i, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    ~DefaultResidualVol();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormVol<Scalar>* clone();

  private:
    int idx_i;
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  /* Default volumetric vector form \int_{area} const_coeff * spline_coeff(u_ext[0]) *
  \nabla u_ext[0] \cdot \nabla v d\bfx
  const_coeff... constant number
  spline_coeff... non-constant parameter given by a cubic spline
  */

  template<typename Scalar>
  class HERMES_API DefaultResidualDiffusion : public VectorFormVol<Scalar>
  {
  public:
    DefaultResidualDiffusion(int i, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);

    DefaultResidualDiffusion(int i, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE, 
      GeomType gt = HERMES_PLANAR);

    ~DefaultResidualDiffusion();

    template<typename Real, typename Scalar>
    Scalar vector_form(int n, double *wt, Func<Scalar> *u_ext[],
      Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) const;

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormVol<Scalar>* clone();

  private:
    int idx_i;
    Scalar const_coeff;
    CubicSpline* spline_coeff;
    GeomType gt;
  };

  /* Default volumetric vector form \int_{area} spline_coeff1(u_ext[0]) * u->dx * v->val
  + spline_coeff2(u_ext[0]) * u->dy * v->val d\bfx
  spline_coeff1, spline_coeff2... non-constant parameters given by cubic splines
  */

  template<typename Scalar>
  class HERMES_API DefaultResidualAdvection : public VectorFormVol<Scalar>
  {
  public:
    DefaultResidualAdvection(int i, std::string area = HERMES_ANY, 
      Scalar const_coeff1 = 1.0, Scalar const_coeff2 = 1.0, 
      CubicSpline* c_spline1 = HERMES_DEFAULT_SPLINE,
      CubicSpline* c_spline2 = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);
    DefaultResidualAdvection(int i, Hermes::vector<std::string> areas,\
      Scalar const_coeff1 = 1.0, Scalar const_coeff2 = 1.0,
      CubicSpline* c_spline1 = HERMES_DEFAULT_SPLINE,
      CubicSpline* c_spline2 = HERMES_DEFAULT_SPLINE, GeomType gt = HERMES_PLANAR);

    ~DefaultResidualAdvection();

    template<typename Real, typename Scalar>
    Scalar vector_form(int n, double *wt, Func<Scalar> *u_ext[],
      Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) const;

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormVol<Scalar>* clone();

  private:
    int idx_i;
    Scalar const_coeff1, const_coeff2;
    CubicSpline* spline_coeff1, *spline_coeff2;
    GeomType gt;
  };

  /* Default surface matrix form \int_{area} const_coeff * function_coeff(x, y) * u * v dS
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultMatrixFormSurf : public MatrixFormSurf<Scalar>
  {
  public:
    DefaultMatrixFormSurf<Scalar>(int i, int j, std::string area = HERMES_ANY,
      Scalar const_coeff = 1.0, DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    DefaultMatrixFormSurf<Scalar>(int i, int j, Hermes::vector<std::string> areas,
      Scalar const_coeff = 1.0, DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    ~DefaultMatrixFormSurf<Scalar>();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *u, Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u,
      Func<Ord> *v, Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormSurf<Scalar>* clone();

  private:
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  /* Default surface matrix form \int_{area} const_coeff * spline_coeff'(u_ext[0]) * u_ext[0] * u * v
  + const_coeff * spline_coeff(u_ext[0]) * u * v dS
  spline_coeff... non-constant parameter given by a spline
  */

  template<typename Scalar>
  class HERMES_API DefaultJacobianFormSurf : public MatrixFormSurf<Scalar>
  {
  public:
    DefaultJacobianFormSurf<Scalar>(int i, int j, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);
    DefaultJacobianFormSurf<Scalar>(int i, int j, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      CubicSpline* c_spline = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);

    ~DefaultJacobianFormSurf<Scalar>();

    template<typename Real, typename Scalar>
    Scalar matrix_form_surf(int n, double *wt, Func<Scalar> *u_ext[], Func<Real> *u,
      Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) const;

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *u, Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *u,
      Func<Ord> *v, Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual MatrixFormSurf<Scalar>* clone();

  private:
    int idx_j;
    Scalar const_coeff;
    CubicSpline* spline_coeff;
    GeomType gt;
  };

  /* Default surface vector form \int_{area} const_coeff * function_coeff(x, y) * v dS
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultVectorFormSurf : public VectorFormSurf<Scalar>
  {
  public:
    DefaultVectorFormSurf<Scalar>(int i, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);
    DefaultVectorFormSurf<Scalar>(int i, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    ~DefaultVectorFormSurf<Scalar>();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormSurf<Scalar>* clone();

  private:
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  template<typename Scalar>
  class HERMES_API DefaultMultiComponentVectorFormSurf : public MultiComponentVectorFormSurf<Scalar>
  {
  public:
    DefaultMultiComponentVectorFormSurf<Scalar>(Hermes::vector<unsigned int> coordinates,
      std::string area = HERMES_ANY,
      Hermes::vector<Scalar> coeffs = Hermes::vector<Scalar>(1.0),
      GeomType gt = HERMES_PLANAR);
    DefaultMultiComponentVectorFormSurf<Scalar>(Hermes::vector<unsigned int> coordinates,
      Hermes::vector<std::string> areas,
      Hermes::vector<Scalar> coeffs, GeomType gt = HERMES_PLANAR);

    virtual void value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext, Hermes::vector<Scalar>& result) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    /* FIXME
    virtual VectorFormSurf<Scalar>* clone() {
    return new DefaultMultiComponentVectorFormSurf<Scalar>(*this);
    }
    */

  private:
    Hermes::vector<Scalar> coeffs;
    GeomType gt;
  };

  /* Default surface vector form \int_{area} const_coeff * function_coeff(x, y) * u_ext[0] v dS
  const_coeff... constant number
  function_coeff... (generally nonconstant) function of x, y
  */

  template<typename Scalar>
  class HERMES_API DefaultResidualSurf : public VectorFormSurf<Scalar>
  {
  public:
    DefaultResidualSurf(int i, std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);
    DefaultResidualSurf(int i, Hermes::vector<std::string> areas, Scalar const_coeff = 1.0,
      DefaultFunction<Scalar>* f_coeff = HERMES_DEFAULT_FUNCTION,
      GeomType gt = HERMES_PLANAR);

    ~DefaultResidualSurf();

    virtual Scalar value(int n, double *wt, Func<Scalar> *u_ext[], Func<double> *v,
      Geom<double> *e, ExtData<Scalar> *ext) const;

    virtual Ord ord(int n, double *wt, Func<Ord> *u_ext[], Func<Ord> *v,
      Geom<Ord> *e, ExtData<Ord> *ext) const;

    virtual VectorFormSurf<Scalar>* clone();

  private:
    int idx_i;
    Scalar const_coeff;
    DefaultFunction<Scalar>* function_coeff;
    GeomType gt;
  };

  /* Default weak form for the Laplace equation -div(const_coeff spline_coeff(u) grad u) = 0. */

  template<typename Scalar>
  class HERMES_API DefaultWeakFormLaplace : public WeakForm<Scalar>
  {
  public:
    DefaultWeakFormLaplace(std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      CubicSpline* spline_coeff = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);
  };


  /* Default weak form for the Poisson equation -div(const_coeff spline_coeff(u) grad u) - rhs = 0. */

  template<typename Scalar>
  class HERMES_API DefaultWeakFormPoisson : public WeakForm<Scalar>
  {
  public:
    DefaultWeakFormPoisson(DefaultFunction<Scalar>* rhs = HERMES_DEFAULT_FUNCTION,
      std::string area = HERMES_ANY, Scalar const_coeff = 1.0,
      CubicSpline* spline_coeff = HERMES_DEFAULT_SPLINE,
      GeomType gt = HERMES_PLANAR);
  };
};

#endif