
installing mpi:
```shell
# https://www.open-mpi.org/software/ompi/

# NOTE replace download link if necessary
wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.4.tar.gz 
folder=$(ls *.tar.gz -1t | head -1) # get latest .tar.gz file
tar -xvf "$folder.tar.gz" # extract
cd $folder
mkdir build && cd build

sudo  ../configure --prefix=/usr/local --enable-mpi-java
sudo make -j3 all 2>&1 | tee make.out
sudo make install 2>&1 | tee install.out
```

note: I was that mpich is an MPI implementation in apt (thanks to Copilot)



mpi clion linux -> https://gist.github.com/tochanenko/10d4c1dc7888b035b55192faaf678458

documentation
1. https://www.open-mpi.org/doc/v4.1/
2. http://parallel.vub.ac.be/documentation/mpi/mpjExpress/javadocs/index.html
3. 