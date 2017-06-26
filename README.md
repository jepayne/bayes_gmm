# Bayesian GMM estimator


This is a repo for the C++ program that implements the Bayesian GMM estimator of [Gallant, Giacomini and Ragusa (2017)](https://www.aronaldg.org/papers/bliml.pdf). The program **heavily** relies on Gallant's [MLE package](https://www.aronaldg.org/webfiles/mle/).


## Directory Structure

* **base_model:** this folder contains the heart of the MCMC estimator. In principle, this part should be independent from the specific project.
  * **initialize:** reads the InputParamFile ([example](https://github.com/szokeb87/bayes_gmm/blob/master/sv_example/svsim.param.000)) and defines the **specification class**
     * *source files:* `main.cpp`, `initialize.cpp`
     * *header files:* `initialize.h`
  * **estimator:** elements of the mcmc sampler/optimizer, it generates the **mcmc class**
     * *source files:* `asymptotics.cpp`, `mcmc_class.cpp`, `proposal.cpp`
     * *header files:* `estimator_base.h`, `estimator.h`
  * **libscl:** slightly altered version of Gallant's [statistical library](https://www.aronaldg.org/webfiles/libscl) (including the **gmm class**)

* **xxx.example:** these foders belong to separate projects (indicated by the prefix `xxx`). In addition to the subfolders detailed below, they contain (1) the [makefile](https://github.com/szokeb87/bayes_gmm/blob/master/sv_example/makefile) that generates the executable `bayes_gmm`, (2) the [InputParamFile](https://github.com/szokeb87/bayes_gmm/blob/master/sv_example/svsim.param.000) detailing the specifics of the estimator (3) a [python script](https://github.com/szokeb87/bayes_gmm/blob/master/sv_example/plot_generator.py) generating summary statistics and plots from the result files. Each project directory must contain three subfolders:
  * **data:** this contains the data (in the file named `data.dat`; variables in columns [separated by whitespaces](https://github.com/szokeb87/bayes_gmm/blob/master/sv_example/data/data.dat)) and the `initial_particle.dat` file containing an intial draw of particles for the conditional particle filter.
  * **usermodel:** defines the **usermodel class**
     * *source files:* `usermodel.cpp`, `moments.cpp`, `model.cpp`, `default_params.cpp`
     * *header files:* `usermodel.h`, `moments.h`, `model.h`, `default_params.h`
  * **result_files:** a plethora of `.dat` files generated by the estimator for diagnoses and further analyses. It has a subfolder with figures and summary tables generated by `plot_generator.py`


## How to run the examples
