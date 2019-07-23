\# build dockerfile

docker build -t gingerbread .

\# run docker

docker run --name gingerbread -it -d -p 8888:80 gingerbread