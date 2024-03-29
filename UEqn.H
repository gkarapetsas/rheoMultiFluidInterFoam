    MRF.correctBoundaryVelocity(U);

    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(rhoPhi, U)
      + MRF.DDt(rho, U)   
//      + turbulence->divDevRhoReff(rho, U)  
     ==
        fvOptions(rho, U)
      + mixture.divTauMF(U)   
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

     
    spSolverU->solve
    (
      UEqn
      ==
      fvc::reconstruct
       (
         (
            mixture.surfaceTensionForce()
          - ghf*fvc::snGrad(rho)
          - fvc::snGrad(p_rgh)
         ) * mesh.magSf()
       )
    );

   fvOptions.correct(U);
   
