#!/bin/bash -l 
#SBATCH -p batch 
#SBATCH --job-name="Valid_v7" 
#SBATCH --time=2-00:00:00 
#SBATCH --nodes=2-4 
#SBATCH --ntasks=32 
#SBATCH --output=Valid_v7.%j.o  
#SBATCH --error=Valid_v7.%j.e  
#SBATCH --mail-type=ALL 
#SBATCH --mail-user=benjamin.schubert@adelaide.edu.au 
#SBATCH --mem=64GB
#SBATCH --exclude=p2n[1-48],b1c[1-8]n[1-4]

module purge
module load OpenFOAM/7-foss-2016b && source $FOAM_BASH 

# Source tutorial run functions 
export WM_PROJECT_USER_DIR=/fast/users/a1627462/OpenFOAM/a1627462-7/
export FOAM_USER_LIBBIN=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/lib
export FOAM_USER_APPBIN=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/bin
export PATH=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/bin:${PATH}
export LD_LIBRARY_PATH=/fast/users/a1627462/OpenFOAM/a1627462-7/platforms/linux64GccDPInt32Opt/lib:${LD_LIBRARY_PATH}

#. $WM_PROJECT_DIR/bin/tools/RunFunctions 
cd $SLURM_SUBMIT_DIR 

mpirun -np 32 olaDyMFlow -parallel > log.olaDyMFlow
