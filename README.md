This version based on OpenMPI library

[root@localhost hpc]# wget https://download.open-mpi.org/release/open-mpi/v4.0/o
penmpi-4.0.1.tar.gz

[root@localhost hpc]# tar xvzf openmpi-4.0.1.tar.gz

[root@localhost hpc]# cd openmpi-4.0.1/

[root@localhost hpc]# ./configure

[root@localhost hpc]# make && make install

Если не получится даже проверить версию (mpirun -version), то выполнить команду:
[root@localhost hpc]# sudo ldconfig
