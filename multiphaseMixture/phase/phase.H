/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::phase

Description
    Single incompressible phase derived from the phase-fraction.
    Used as part of the multiPhaseMixture for interface-capturing multi-phase
    simulations.

SourceFiles
    phase.C

\*---------------------------------------------------------------------------*/

#ifndef phase_H
#define phase_H

#include "volFields.H"
#include "dictionaryEntry.H"
#include "incompressible/viscosityModels/viscosityModel/viscosityModel.H"
/*
Added by cdd
*/
#include "../../../constitutiveEquations/lnInclude/constitutiveModel.H" 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class phase Declaration
\*---------------------------------------------------------------------------*/

class phase
:
    public volScalarField
{
    // Private Data

        word name_;
        dictionary phaseDict_;
        autoPtr<viscosityModel> nuModel_;
/*
Added by cdd
*/
        autoPtr<constitutiveEq> phaseEqModel_;
                //dimensionedScalar myEtaS_;
/*
*/
        dimensionedScalar rho_;


public:

    // Constructors

        //- Construct from components
        phase
        (
            const word& name,
            const dictionary& phaseDict,
            const volVectorField& U,
            const surfaceScalarField& phi
        );

        //- Return clone
        autoPtr<phase> clone() const;

        //- Return a pointer to a new phase created on freestore
        //  from Istream
        class iNew
        {
            const volVectorField& U_;
            const surfaceScalarField& phi_;

        public:

            iNew
            (
                const volVectorField& U,
                const surfaceScalarField& phi
            )
            :
                U_(U),
                phi_(phi)
            {}

            autoPtr<phase> operator()(Istream& is) const
            {
                dictionaryEntry ent(dictionary::null, is);
                return autoPtr<phase>(new phase(ent.keyword(), ent, U_, phi_));
            }
        };


    // Member Functions

        const word& name() const
        {
            return name_;
        }

        const word& keyword() const
        {
            return name();
        }

        //- Return const-access to phase1 viscosityModel
        const viscosityModel& nuModel() const
        {
            return nuModel_();
        }

        //- Return the kinematic laminar viscosity
        tmp<volScalarField> nu() const
        {
            return nuModel_->nu();
        }

        //- Return the laminar viscosity for patch
        tmp<scalarField> nu(const label patchi) const
        {
            return nuModel_->nu(patchi);
        }

        //- Return const-access to phase1 density
        const dimensionedScalar& rho() const
        {
            return rho_;
        }

/*
Added by CDD
*/

/*

        //- Return const-access to phase1 density
        const dimensionedScalar& myEtaS_() const
        {
            return myEtaS_;
        }
*/

        //- Return const-access to phase1 constitutiveModel
        const constitutiveEq& phaseEqModel() const
        {
            return phaseEqModel_();
        }
        
        bool isGNF() const
        {
            return phaseEqModel_->isGNF();
        }
        
        tmp<volSymmTensorField> tau() const
        {
            return phaseEqModel_->tau();
        }
        
        tmp<volSymmTensorField> tauTotal() const
        {
            return phaseEqModel_->tauTotal();
        }
        
        tmp<fvVectorMatrix> divTau(const volVectorField& U) const
        {
            return phaseEqModel_->divTau(U);
        }
        
        tmp<fvVectorMatrix> divTauS(const volVectorField& U, const volScalarField& alpha) const
        {
            return phaseEqModel_->divTauS(U,alpha);
        }

        tmp<fvVectorMatrix> myDivTauS(const volVectorField& U, const volScalarField& alpha, const volScalarField& myEta) const
        {
            return phaseEqModel_->myDivTauS(U,alpha,myEta);
        }

        tmp<volScalarField> myNu() const
        {
            return phaseEqModel_->myNu();
        }
        
        /*
        tmp<dimensionedScalar> myEtaS_() const
        {
            return phaseEqModel_->myEtaS_();
        }

                tmp<dimensionedScalar> myEtaP_() const
        {
            return phaseEqModel_->myEtaP_();
        }
*/

//        tmp<scalarField> myNu(const label patchi) const
//        {
//            return phaseEqModel_->myNu(patchi);
//        }
                
/*
*/


        //- Correct the phase properties
        void correct();

        //-Inherit read from volScalarField
        using volScalarField::read;

        //- Read base transportProperties dictionary
        bool read(const dictionary& phaseDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
