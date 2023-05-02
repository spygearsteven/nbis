# NIST Biometric Image Software (NBIS)

> The NIST Biometric Image Software (NBIS) distribution is developed by the National Institute of Standards and Technology (NIST) for the Federal Bureau of Investigation (FBI) and Department of Homeland Security (DHS). [More info...](https://www.nist.gov/services-resources/software/nist-biometric-image-software-nbis)

> https://www.nist.gov/services-resources/software/nist-biometric-image-software-nbis

This repo is based off the latest release (v5.0) of the NIST Biometric Image Software (NBIS). 

# Build Instructions
NBIS v5.0.0 seems to require GCC v7.5 to compile successfully. 

Due to this, I found the easiest way to build the NBIS packages is using docker containers. This provides a disposable environment where we don't have to worry about package conflicts and such.

## Steps:
1. Clone the repository
    ```
    git clone https://github.com/spygearsteven/nbis.git
    ```
2. Checkout the branch/tag you wish to build
    ```
    git checkout v5.0.0
    ```
3. Build the docker container
    ```
    docker build -t nbis .
    ```
4. Run the container and mount a directory on your host to the `/mnt` directory.
    ```
    docker run -it -v ./build:/mnt nbis /bin/bash
    ```
5. Copy the compiled build artifacts to the folder we mounted in the container
    ```
    root@container_name:/app# cp -r /build/* /mnt
    ```
6. You should now have all the build artifacts copied to directory on the host you mounted to the container!
    ```
    ls -la ./build
    
    total 0
    drwxr-xr-x 1 root   root     40 May  1 23:25 .
    drwxr-xr-x 1 steven steven  586 May  1 23:23 ..
    drwxr-xr-x 1 root   root    874 May  1 23:25 bin
    drwxr-xr-x 1 root   root   1652 May  1 23:25 include
    drwxr-xr-x 1 root   root    458 May  1 23:25 lib
    drwxr-xr-x 1 root   root      8 May  1 23:25 man
    drwxr-xr-x 1 root   root     28 May  1 23:25 nbis
    ```
