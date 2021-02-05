module purge
module load OpenFOAM/7-foss-2016b && source $FOAM_BASH 


# Source tutorial run functions 


export WM_PROJECT_USER_DIR=/fast/users/a1627462/OpenFOAM/a1627462-7/
export FOAM_USER_LIBBIN=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/lib
export FOAM_USER_APPBIN=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/bin
export PATH=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/bin:${PATH}
export LD_LIBRARY_PATH=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/lib:${LD_LIBRARY_PATH}

. $WM_PROJECT_DIR/bin/tools/RunFunctions 



runApplication blockMesh > meshing.log  
surfaceFeatureExtract > surfaceFeatureExtract.log 
runApplication snappyHexMesh > snappy.log 
runApplication createPatch
cp -r 0.4/polyMesh/* constant/polyMesh/. 
rm -r 0.1 0.2 0.3 0.4
cp -r 0.org 0 > /dev/null
runApplication setFields 
runApplication decomposePar -force