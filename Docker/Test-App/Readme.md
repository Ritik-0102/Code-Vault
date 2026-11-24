To Run the App :- Node server.js

## Setup Mongo & Mongo-Express :-

Note :- use backticks (`) for multiline command in powershell

Create a network for mongo & mongo-express containers to communicate with each other ->
docker network create mongo-network

1. Mongo :-
    ```
    docker run -d -p 27017:27017 --name mongo-container `
    --network mongo-network `
    -e MONGO_INITDB_ROOT_USERNAME=admin `
    -e MONGO_INITDB_ROOT_PASSWORD=password `
    mongo 
    ```

2. Mongo-Express :-
    ```
    docker run -d -p 8081:8081 `
    --name mongo-express-container `
    --network mongo-network `
    -e ME_CONFIG_MONGODB_ADMINUSERNAME=admin `
    -e ME_CONFIG_MONGODB_ADMINPASSWORD=password `
    -e ME_CONFIG_MONGODB_URL=mongodb://admin:password@mongo-container:27017 `
    mongo-express
    ```
Now we can access the Mongo-Express UI at http://localhost:8081
login with username: admin and password: pass

Create a database named "test-db" and a collection named "users". Add some sample data to the "users" collection.

```
{
        "_id": ObjectId(),
    	"email": "jane@gmail.com",
    	"username": "Jane Doe",
        "password": "secret"
}
```


## Note :- We can also use docker Compose to run the mongo and mongo-express containers together.

Run this command -> docker compose -f docker-compose.yaml up -d
After running the above command, we can access the Mongo-Express UI at http://localhost:8081

### Note -> It will automatically create a network for mongo and mongo-express containers to communicate with each other.

