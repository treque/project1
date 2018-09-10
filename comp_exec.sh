bash clean.sh
cd lib_dir/
make
cd ../memoire/
make
make install
cd ../exec_dir/
make
make install
cd ..
./robodiag_fedora_26
bash clean.sh
