#ifndef __FILE_MODEL_H_SEEN__
#define __FILE_MODEL_H_SEEN__

/*-----------------------------------------------------------------------------

Copyright (C) 2012, 2013

A. Ronald Gallant
Post Office Box 659
Chapel Hill NC 27514-0659
USA

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

-----------------------------------------------------------------------------*/
//#define USE_JACOBIAN
#undef USE_JACOBIAN


#include "libscl.h"
#include "default_params.h"
#include "moments.h"


struct particles_recursive {
      scl::realmat                  particle_path;     // Mean vector of group, not used by r.w. props.
      scl::realmat                  mu;                // Recursive mean moment conditions
      std::vector<scl::realmat>     R;                 // Recursive covariance matrix of moment conditions
                                                       // vector is to take care of lag_hac_gmm

                       particles_recursive () : particle_path(), mu(), R() { };
};


class model {

    private:
        std::vector<scl::realmat>       A_y;
        scl::realmat                    C_y;
        REAL                            rho;
        REAL                            sigma;
        scl::realmat                    lambda_0;
        scl::realmat                    lambda_y;
        scl::realmat                    lambda_x;
        REAL                            delta_0;
        scl::realmat                    delta_y;
        REAL                            delta_x;

        moments*                        moment_cond;      // pointer to moments class
        scl::gmm*                       gmm_objfun;       // pointer to scl::gmm class


    public:
                      model(){ default_params(A_y, C_y, rho, sigma, lambda_0, lambda_y,
                                              lambda_x, delta_0, delta_y, delta_x); }

                      model(moments* mfptr, scl::gmm* gmmptr){
                               default_params(A_y, C_y, rho, sigma, lambda_0, lambda_y,
                                                          lambda_x, delta_0, delta_y, delta_x);
                                moment_cond = mfptr;
                                gmm_objfun = gmmptr;
                                gmm_objfun->set_moment_cond(moment_cond); }

        void          set_theta(const scl::realmat& theta);
        scl::realmat  get_theta() const;

        // gives GMM representation of measurement density
        scl::denval   likelihood(INTEGER t, scl::realmat* particle_path_ptr);

        // facilities to draw a random sample from the model for given parameters
        REAL          draw_x0(INT_32BIT& seed) const;
        REAL          draw_xt(REAL xlag, INT_32BIT& seed) const;
        //REAL          prob_yt(REAL yt, REAL ytlag, REAL xt) const;
        REAL          prob_yt(INTEGER t, scl::realmat* particle_path_ptr, particles_recursive* pr_ptr);
        REAL          prob_ancestor(REAL xt, REAL xtlag);

};

#endif
