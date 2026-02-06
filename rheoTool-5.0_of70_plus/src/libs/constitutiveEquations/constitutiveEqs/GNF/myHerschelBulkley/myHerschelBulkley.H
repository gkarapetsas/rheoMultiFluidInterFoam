/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    myHerschelBulkley

SourceFiles
    myHerschelBulkley.C

\*---------------------------------------------------------------------------*/

#ifndef myHerschelBulkley_H
#define myHerschelBulkley_H

#include "constitutiveEq.H"
#include "thermoFunction.H" 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace constitutiveEqs
{ 

/*---------------------------------------------------------------------------*\
                           Class myHerschelBulkley Declaration
\*---------------------------------------------------------------------------*/

class myHerschelBulkley
:
    public constitutiveEq
{
    // Private data

        // Model constants

            //- Density
            dimensionedScalar rho_;
            
            //- Is Papanastasiou's regularization to be used
            Switch reg_;
  
            //- Yield stress 
            dimensionedScalar tau0_;

            //- Low strain rate viscosity 
            dimensionedScalar eta0_;

            //- Consistency index
            dimensionedScalar k_;

            //- Behavior index
            dimensionedScalar n_;
            
            //- Exponential growth parameter
            dimensionedScalar m_;

        //- Transported viscoelastic stress
        volScalarField IItauD_;

        //- Transported viscoelastic stress
        volSymmTensorField tauD_;

        //- Transported viscoelastic stress
        volScalarField IItauALL_;

        //- Transported viscoelastic stress
        volScalarField IItau_;

        //- Transported viscoelastic stress
        volSymmTensorField tau2_;

        //- Transported viscoelastic stress
        volSymmTensorField tau_;

        //- Viscosity field
        volScalarField eta_;
        
        //- Thermofunction for temperature dependence of viscosity
        autoPtr<thermoFunction> thermoEtaPtr_;

//cdd///  

            //- Vector of solved-for directions in mesh
            vector  dims_;
            
            //- Number of solved-for directions in mesh 
            scalar  nDims;
      
            //- Identity tensor consistent with nDims
            dimensionedSymmTensor Itensor;
            
            //- Write second invariant of deviatoric stresses ?
            Switch writeII_;
/////////


    // Private Member Functions

        //- Disallow default bitwise copy construct
        myHerschelBulkley(const myHerschelBulkley&);

        //- Disallow default bitwise assignment
        void operator=(const myHerschelBulkley&);
        
protected:
   
     //- Return the viscosity field
     virtual const volScalarField& eta() const
       {
          return eta_;
       }

public:

    //- Runtime type information
    TypeName("myHerschelBulkley");

    // Constructors

        //- Construct from components
        myHerschelBulkley
        (
            const word& name,
            const volVectorField& U,
            const surfaceScalarField& phi,
            const dictionary& dict
        );


    // Destructor

        virtual ~myHerschelBulkley()
        {}


    // Member Functions

        //- Return the viscoelastic stress tensor
        virtual tmp<volSymmTensorField> tau() const
        {
            return tau_;
        }

        //- Return the density
        virtual const dimensionedScalar rho() const
        {
            return rho_;
        }

        //- Return true if GNF (non-elastic)
        virtual bool isGNF() const
        {
          return true;
        };

        //- Correct the viscoelastic stress
        virtual void correct();


/*
Added by CDD
*/

        //- Return the viscoelastic stress tensor
        virtual tmp<volSymmTensorField> tauD() const
        {
            return tauD_;
        }

        //- Return the viscoelastic stress tensor
        virtual tmp<volSymmTensorField> tau2() const
        {
            return tau2_;
        }

        //- 
        tmp<volScalarField> IItau() const
        {
            return IItau_;
        }

        //- 
        tmp<volScalarField> IItauD() const
        {
            return IItauD_;
        }

        //- 
        tmp<volScalarField> myNu() const
        {
            return eta_/rho_;
        }
        tmp<volScalarField> myEta() const
        {
            return eta_;
        }

/*
        //- 
        tmp<volScalarField> myNuCalc() const;
        tmp<volScalarField> myNu() const;
//        tmp<scalarField> myNu(const label patchi) const
//        {
//            return eta_.boundaryField()[patchi];
//        }
*/

/*
*/


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace constitutiveEqs 
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
