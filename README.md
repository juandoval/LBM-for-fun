# 2D LBM Solver
The initial plan is to create a 2D LBM solver. 
This objective may change depending on how far I go.
There is obviously no intentions to commercialize this,
I am taking this as a personal opportunity to discovery the struggles of Solver Developers.

So starting from my experience such as:
- Data-driven methods for optimization, surrogates, and parametrization
- Orchestrating automated pipelines from Geometry, Meshing, Solver and Post, using Python
- Automated validation of results
- Decent background in Aerodynamics and Fluid Dynamics

I plan to understand what goes on under the hood for a Lattice Boltzmann Method Solver, with the use of C++, a coding language to which I have spent little time learning.

I recently had a Class called Advanced CFD where one of the topics was LBM, taught by [Alessandro De Rosis](https://scholar.google.com/citations?user=xi0xYuUAAAAJ&hl=it)
But the reality is that, if I do not put into practice his shared knowledge, I will not remember.
So, Here we go! I have brought my lecture to refresh concepts and equation, but I can say for sure I will get my head stuck in google finding answers.
In the BIG 2026 seems pointless, with the amazing code Claude is capable of producing, specially for small projects like this, but obviously this defeat the purpose :p 

## LBM
I think for anyone starting their journey in LBM, this post by [SimScale](https://www.simscale.com/docs/simwiki/cfd-computational-fluid-dynamics/lattice-boltzmann-method-lbm/) summarizes the key concepts pretty well.

Stealing some words from them: "The Lattice Boltzmann Method (LBM) is a computational fluid dynamics (CFD) method that represents a paradigm shift in how simulations are conducted, enabling a broad spectrum of applications previously out of reach for traditional Navier-Stokes solvers."

Additionally: "The application of LBM has grown substantially due to its capabilities in handling complex flow scenarios and intricate geometries." Used in sectors like aerospace, automotive, and architecture.

So what is it?

LBM is a numerical method that simulates fluid dynamics on a macroscopic scale based on kinetic equations formulated on a mesoscopic scale [1](https://link.springer.com/referenceworkentry/10.1007/978-3-319-08234-9_107-1). More precisely, it is “a parallel and efficient algorithm for simulating single-phase and multiphase fluid flows and for incorporating additional physical complexities” [2](https://www.annualreviews.org/doi/10.1146/annurev.fluid.30.1.329). It is particularly useful for modeling complex boundary conditions and multiphase interfaces.

## Mathhematical Framework of LBM
### Discrete Velocities
In LBM, the 'lattice' or grid refers to a set of nodes at specific locations connected by discrete velocity directions. Velocities are not continuous but discretized into a fixed set of directions depending on the lattice used, expressed with the notation 'DnQm', where 'n' refers to the spatial dimension (2D or 3D) and 'm' refers to the count of these discrete velocities.

### Collision and Streaming Processes
LBM fundamentally operates on two key processes: Collision and streaming. In Collision Phase, particle distributions at each lattice node interact, resulting in a reshuffling of particle velocities, ensuring both mass and momemtum are conserved. The Streaming Phase sees particles advancing to neightbouring nodes, guided by their velocities post-collision. 

### Boltzmann Equation Derivation
The LBM foundational equation examines the evolution of a particle distribution function (or the likelihood of its presence) over time as influenced by collision. Note its inherent time-dependent or transient framework. Integrated with discretization and delineated collision-streaming process, LBM offers matching or exceeding capabilities to FVM, offering rigorous and flexible depiction of Fluid Dynamics.

The governing equation is:
∂f_i/∂t + c · e_i · ∇f_i = 1/τ (f_i^eq - f_i)

Where the LHS of the equation represents the streaming phase, and RHS represents the collision phase.

- f_i is the discrete probability distribution function of single-particle position and momentum (i=0...8 for D2Q9)
- e_i is the unit direction vector for direction i (e.g. (1,0), (0,1), (1,1), etc.)
- c is the lattice speed (c = Δx/Δt)
- τ is the relaxation time

And after discretizing, equation is as follows:
f_i(r + c · e_i Δt, t + Δt) = f_i(r, t) + Δt/τ [f_i^eq(r, t) - f_i(r, t)]



More cool info can be found here [SimScale](https://www.simscale.com/docs/simwiki/cfd-computational-fluid-dynamics/lattice-boltzmann-method-lbm/) or [Alessandro De Rosis Slides](Alessandro_De_Rosis).

## References
1. https://link.springer.com/referenceworkentry/10.1007/978-3-319-08234-9_107-1
2. https://www.annualreviews.org/doi/10.1146/annurev.fluid.30.1.329
3. https://www.semanticscholar.org/paper/Lattice-Boltzmann-Method-for-Fluid-Simulations-Bao-Meskas/958ff187b47a49c7aad9b0cbbadaf225915e1dd6
4. https://www.semanticscholar.org/paper/Lattice-Boltzmann-Method-for-Fluid-Simulations-Bao-Meskas/958ff187b47a49c7aad9b0cbbadaf225915e1dd6