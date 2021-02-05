/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "modifiedBistableSpring.H"
#include "addToRunTimeSelectionTable.H"
#include "sixDoFRigidBodyMotion.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace sixDoFRigidBodyMotionRestraints
{
    defineTypeNameAndDebug(modifiedBistableSpring, 0);

    addToRunTimeSelectionTable
    (
        sixDoFRigidBodyMotionRestraint,
        modifiedBistableSpring,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::sixDoFRigidBodyMotionRestraints::modifiedBistableSpring::modifiedBistableSpring
(
    const word& name,
    const dictionary& sDoFRBMRDict
)
:
    sixDoFRigidBodyMotionRestraint(name, sDoFRBMRDict),
    anchor_(),
    refAttachmentPt_(),
    stiffness_(),
    damping_(),
    restLength_(),
    pretension_(),
    BistableCoeff_(),
    BistableR_()
{
    read(sDoFRBMRDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::sixDoFRigidBodyMotionRestraints::modifiedBistableSpring::~modifiedBistableSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::sixDoFRigidBodyMotionRestraints::modifiedBistableSpring::restrain
(
    const sixDoFRigidBodyMotion& motion,
    vector& restraintPosition,
    vector& restraintForce,
    vector& restraintMoment
) const
{
    restraintPosition = motion.transform(refAttachmentPt_);

    vector r = restraintPosition - anchor_;

    scalar magR = mag(r);
    scalar Dl = magR - restLength_;
    r /= (magR + VSMALL);

    vector v = motion.velocity(restraintPosition);

    vector restraintForceBistable = (BistableCoeff_*(9.0*Dl / pow(pow(BistableR_,2)+pow(Dl,2),5.0/2.0) - 15.0*pow(Dl,3) / pow(pow(BistableR_,2)+pow(Dl,2),7.0/2.0) ))*r;
    vector restraintForceLinear = -stiffness_*(magR - restLength_)*r - damping_*(r & v)*r - pretension_*r;
    restraintForce = restraintForceLinear + restraintForceBistable;

    restraintMoment = vector::zero;

    if (motion.report())
    {
        Info<< " attachmentPt - anchor " << r*magR
            << " spring length " << magR
            << " force " << restraintForce
            << " Bistable force " << restraintForceBistable
            << " N1 " << 9.0*magR
            << " D1 " << pow(pow(BistableR_,2)+pow(magR,2),5.0/2.0)
            << " N2 " <<  15.0*pow(magR,3)
            << " D2 " << pow(pow(BistableR_,2)+pow(magR,2),7.0/2.0)
            << " 1 " << 9.0*magR / pow(pow(BistableR_,2)+pow(magR,2),5.0/2.0)
            << " 2 " << 15.0*pow(magR,3) / pow(pow(BistableR_,2)+pow(magR,2),7.0/2.0)
            << " BistableCoeff " << BistableCoeff_
            << endl;
    }
}


bool Foam::sixDoFRigidBodyMotionRestraints::modifiedBistableSpring::read
(
    const dictionary& sDoFRBMRDict
)
{
    sixDoFRigidBodyMotionRestraint::read(sDoFRBMRDict);

    sDoFRBMRCoeffs_.lookup("anchor") >> anchor_;
    sDoFRBMRCoeffs_.lookup("refAttachmentPt") >> refAttachmentPt_;
    sDoFRBMRCoeffs_.lookup("stiffness") >> stiffness_;
    sDoFRBMRCoeffs_.lookup("damping") >> damping_;
    sDoFRBMRCoeffs_.lookup("restLength") >> restLength_;
    sDoFRBMRCoeffs_.lookup("pretension") >> pretension_;
    sDoFRBMRCoeffs_.lookup("BistableCoeff") >> BistableCoeff_;
    sDoFRBMRCoeffs_.lookup("BistableR") >> BistableR_;
    return true;
}


void Foam::sixDoFRigidBodyMotionRestraints::modifiedBistableSpring::write
(
    Ostream& os
) const
{
    os.writeKeyword("anchor")
        << anchor_ << token::END_STATEMENT << nl;

    os.writeKeyword("refAttachmentPt")
        << refAttachmentPt_ << token::END_STATEMENT << nl;

    os.writeKeyword("stiffness")
        << stiffness_ << token::END_STATEMENT << nl;

    os.writeKeyword("damping")
        << damping_ << token::END_STATEMENT << nl;

    os.writeKeyword("restLength")
        << restLength_ << token::END_STATEMENT << nl;

    os.writeKeyword("pretension")                    
        << pretension_ << token::END_STATEMENT << nl;

}
// ************************************************************************* //
