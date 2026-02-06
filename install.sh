#!/bin/bash

source /opt/openfoam7/etc/bashrc

of7="source /opt/openfoam7/etc/bashrc && export FOAM_USER_SRC=\$WM_PROJECT_USER_DIR/src/ && export FOAM_USER_LIBRARIES=\$WM_PROJECT_USER_DIR/src/libs && export FOAM_USER_SOLVERS=\$WM_PROJECT_USER_DIR/src/solvers && export FOAM_USER_THIRDPARTY=\$WM_PROJECT_USER_DIR/ThirdParty && export EIGEN_RHEO=\$FOAM_USER_THIRDPARTY/Eigen3.2.9 && export PETSC_DIR=\$FOAM_USER_THIRDPARTY/petsc-3.15.0 && export PETSC_ARCH=arch-linux-c-opt && export LD_LIBRARY_PATH=\$PETSC_DIR/\$PETSC_ARCH/lib:\$LD_LIBRARY_PATH"

echo "alias of7='$of7'" | sudo tee -a $HOME/.bashrc

source $HOME/.bashrc && $of7 

mkdir -p $WM_PROJECT_USER_DIR/{ThirdParty,src/solvers,src/libs}

cp -r ../rheoMultiFluidInterFoam $FOAM_USER_SOLVERS

# Install RheoTool-5.0 (of70_plus is a customized version of of70)
cd $FOAM_USER_SOLVERS/rheoMultiFluidInterFoam/rheoTool-5.0_of70_plus
./downloadEigen
./installPetsc
cd src && ./Allwmake
cd $FOAM_USER_LIBRARIES
ln -s $FOAM_USER_SOLVERS/rheoMultiFluidInterFoam/rheoTool-5.0_of70_plus/src/libs libRheoTool

# Install  rheoMultiFluidInterFoam
cd $FOAM_USER_SOLVERS/rheoMultiFluidInterFoam && ./Allwmake
