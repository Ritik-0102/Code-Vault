# Docker Commands :-

## Docker Desktop Commands :-
• Start Docker Desktop -> docker desktop start
• Check status -> docker desktop status
• Stop Docker Desktop -> docker desktop stop
• Restart Docker Desktop -> docker desktop restart

## Basic Docker Commands :-
To pull any image from docker hub use the command -> docker pull <image_name>

To run any image -> docker run <image_name>
This will run the image & create a container from that image.

Ex : docker run hello-world
Ex : docker run ubuntu
Ex : docker run -it ubuntu  {this will run the image in interactive mode}

## To start & stop existing container use the following commands :-
• Start container -> docker start <container_id> OR docker start <container_name>
• Stop container -> docker stop <container_id> OR docker stop <container_name>

## To check the list of running containers use the command -> docker ps
## To check the list of all containers use the command -> docker ps -a

To delete any container use the command -> docker rm <container_id> OR docker rm <container_name>
To delete any image use the command -> docker rmi <image_id> OR docker rmi <image_name>

To Download any Specific version of image use the command -> docker pull <image_name>:<version>
Ex : docker pull ubuntu:20.04
Ex : docker pull mysql:8.0

To Run any Container in Background {In Detached Mode} use the command -> docker run -d <image_name>
Ex : docker run -d ubuntu

## To Run MYSQL Container :-

We need to set the root password for MYSQL container using the environment variable MYSQL_ROOT_PASSWORD while running the container.
Ex : docker run -d -e MYSQL_ROOT_PASSWORD=password mysql:8.0

To Give a name to the container we can use the --name option while running the container.
Ex : docker run -d -e MYSQL_ROOT_PASSWORD=password --name mysql-container mysql:8.0

## Docker Image Layers :-

- Container 
- Layer 2
- Layer 1
- Base Layer 

> The base layer is the first layer of the image. It is the foundation of the image and contains the operating system and other essential files. Ex : ubuntu, alpine, debian, centos, etc.

> Most of the times, the base layer, Layer 1 and Layer 2 are read-only and cannot be modified. We can only modify the container layer. The container layer is the topmost layer of the image and is writable. Any changes made to the container are stored in this layer.

## Port Mapping :-

To access the application running inside the container from the host machine, we need to map the container port to the host port using the -p option while running the container.
docker run -d -p <host_port>:<container_port> <image_name>

Ex : docker run -d -p 8080:80 nginx
Ex : docker run -d -p 3000:3306 -e MYSQL_ROOT_PASSWORD=password mysql:8.0

## To Check Logs of Container :-

To check the logs of a container, we can use the following command :-
docker logs <container_id> OR docker logs <container_name>

## To Access the Container Shell OR Bash :-

To access the shell of a running container, we can use the following command :-
docker exec -it <container_id> OR docker exec -it <container_name> bash
docker exec -it <container_id> OR docker exec -it <container_name> sh

## NETWORK :- 
It is a virtual network that allows containers to communicate with each other and with the host machine. Docker provides a default bridge network for containers to communicate with each other. We can also create our own custom networks.

List all networks :- docker network ls
Create a network :- docker network create <network_name>
Remove a network :- docker network rm <network_name>
Remove all unused networks :- docker network prune

## VOLUMES :-

List all Volumes :- docker volume ls
Create new Named volume :- docker volume create <volume_name>
Delete a Named volume :-  docker volume rm <volume_name>

Mount Named volume with running container ->

docker run - -volume <volume_name>:<mount_path>
//or using - -mount
docker run - -mount type=volume,src=<volume_name>,dest=<mount_path>

Mount Anonymous volume with running container -> docker run - -volume <mount_path>

To create a Bind Mount ->
docker run - -volume <host_path>:<container_path>
//or using - -mount
docker run - -mount type=bind,src=<host_path>,dest=<container_path>

Remove unused local volumes -> docker volume prune //for anonymous volumes

## Docker Volumes ->
Windows : C:\ProgramData\Docker\volumes
Mac / Linux : /var/lib/docker/volumes

## How to Use Volumes To Persist Data in Docker Containers :-
To store data in a local folder on the host machine.
Ex : docker run -d -v /host/path:/test/data --name my-container my-image


## TROUBLESHOOT :-

Fetch logs of a container -> docker logs <container_name> (or <container_id>)

## Docker Compose :-
Docker Compose is a tool for defining and running multi-container Docker applications. With Compose, we can use a YAML file to configure our application's services. Then, with a single command, we can create and start all the services from our configuration.

docker compose -f docker-compose.yaml up -d -> This command will start the services defined in the docker-compose.yaml file in detached mode.
docker compose -f docker-compose.yaml down -> This command will stop and remove the containers, networks, and volumes defined in the docker-compose.yaml file.



## Dockerize Our Test-App :-
1. Create a Dockerfile in the root directory of the project.

Dockerfile :-
FROM -> Picks the base image to build on top of.
WORKDIR	-> Sets the directory inside the image that later instructions work in.
COPY -> Copies files from your project into the image.
RUN -> Runs a command during the build, such as installing packages.
EXPOSE	-> Records which port the app listens on.
ENV -> Sets environment variables.
CMD	-> This is the command that starts your app.

2. Create image from the Dockerfile using the command -> docker build -t <image_name>:<version> 

3. Run the image using the command -> docker run -d -p <host_port>:<container_port> <image_name>:<version>

4. To push the image to Docker Hub, we need to login to Docker Hub using the command -> docker login
Then we can push the image using the command -> docker push <username>/<image_name>:<version>